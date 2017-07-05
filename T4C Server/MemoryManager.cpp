#pragma warning( disable : 4786 )

#include "stdafx.h"

#include <windows.h>
#include <malloc.h>
#include "stdio.h"
#include "MemoryManager.h"
#include "Lock.h"
#include "stackhlp.h"
#include "AutoLock.h"
#undef new

void *operator new(size_t size)
{		
   MemManager *Mem = MemManager::GetInstance();
   
   if (!Mem->Init)
      return malloc(size);

   DWORD callStack[ MemManager::CALL_STACK_SIZE ];
   DWORD levels = WalkStack( callStack, MemManager::CALL_STACK_SIZE );

   Autolock AL(&Mem->cs);
   return Mem->Create(size, callStack );
}


void operator delete( void *ptr )
{
   MemManager *Mem = MemManager::GetInstance();

   if (!Mem->Init) {
      free(ptr);
      return;
   }
   
   Autolock AL(&Mem->cs);
   Mem->Free(ptr);
}

MemManager *MemManager::GetInstance(void) {
   static MemManager X;
   return &X;
}

MemManager::MemManager(void) {
// Constructor.
   Initialize();
}	

void MemManager::Initialize(void) {
// Constructor.
	nItems  = 0;
	memTop  = NULL;
	memWalk = NULL;
	memPtr  = NULL;
	memOld  = NULL;
   dwTotalAlloc = 0;

	// Creation de la tab.
	memTab = (MemTab *) malloc (sizeof(MemTab));
	ZeroMemory(memTab, sizeof(MemTab));

	InitializeCriticalSection(&cs);
   Init = false;
}


MemManager::~MemManager(void)
// Destructor.
{
   Release();
   if (Init) {
      Init = false;
   }
}

void MemManager::Start(){
    Init = true;
}

void MemManager::Stop(){
    Init = false;
    Release();
}



void MemManager::Release(void) {
	Init = false;

   int i;
   int j = 0;

    FILE *f = fopen( "Memory.log", "ab" );
       
//    fprintf( f, "\r\n-----" );
      
   DWORD dwTotalLeak = 0;
   for (i=0; i<MEMTAB_SIZE; i++) {
//   for (i=0; i<999; i++) {
	
		memPtr = memTab->memTop[i];
													
		while(memPtr) {
			memWalk = memPtr->Next;
			if (memPtr->ptr) {
				char Temp[1000];
//				fprintf(f, "\r\n[%5d] Memory Leak (0x%x) of size %d, call stack: ", 
//						++j, 
//                        memPtr->ptr,
//                        memPtr->Size
//                 );
				j++;

                int i = 1;
                while( i < CALL_STACK_SIZE && memPtr->callStack[ i ] != NULL ){
//                     fprintf( f, i == 1 ? "0x%x" : ", 0x%x", memPtr->callStack[ i ] );
                    
                    i++;
                }

				OutputDebugString(Temp);
                dwTotalLeak += memPtr->Size;
			}
			memPtr = memWalk;
		}
	}
   
   char Temp[1000];
   if (j!=0){
	   fprintf(f, "\r\nTotal leak of %ld %ld %d", dwTotalLeak/j,dwTotalLeak,j);
   }

   fclose( f );
   OutputDebugString(Temp);
}

DWORD
MemManager::takeofs(void *ptr)
{
	DWORD ofs = ((DWORD)ptr & 0xffff) >> 6;
	return ofs;
}

void *
MemManager::Create(int size, DWORD callStack[] )
// Create a new entry.
{
	if (!memTab)
		return NULL;
  
   void *ptr = malloc(size);

	DWORD addr = takeofs(ptr);

	if (memTab->memTop[ addr ]) {
		memWalk = memTab->memTop[ addr ];
		while(memWalk->Next)
			memWalk = memWalk->Next;
		memWalk->Next = (MemWalk *)malloc(sizeof(MemWalk));
		ZeroMemory(memWalk->Next, sizeof(MemWalk));
		memPtr = memWalk->Next;
	}
	else {
		memTab->memTop[ addr ] = (MemWalk *)malloc(sizeof(MemWalk));
		ZeroMemory(memTab->memTop[ addr ], sizeof(MemWalk));
		memWalk = memTab->memTop[ addr ];
		memPtr = memWalk;
	}
  
	memPtr->ptr = ptr;
  	dwTotalAlloc += size;
	memPtr->Size = size;
    memcpy( memPtr->callStack, callStack, sizeof( memPtr->callStack ) );
	memPtr->Next = NULL;
	nItems ++;
	
	return ptr;
}
void
MemManager::Free(void *ptr)
// 
// Free an allocated pointer entry
//
{
	MemWalk *memPrev = NULL, *memNext = NULL;
	DWORD addr = takeofs(ptr);
	int found=0;

   if (!memTab) {
   	free(ptr);	
		return;
   }
	
	memPtr = memTab->memTop[ addr ];
   if (!memPtr) {
   	free(ptr);	
		return;
   }

	while(memPtr->Next || memPtr->ptr == ptr) {
		if (memPtr->ptr == ptr) {
			memPtr->ptr = NULL;
      	dwTotalAlloc -= memPtr->Size;
			memPtr->Size = 0;
			memNext = memPtr->Next;
			if (memPrev) 
				memPrev->Next = memNext;
			else {
				memTab->memTop[ addr ] = memNext;
			}
			free(memPtr);
			found = 1;
			nItems --;
			break;
		}
		memPrev = memPtr;
		memPtr = memPtr->Next;
	}

	free(ptr);	
}

DWORD MemManager::GetAllocMem(void) {
   return dwTotalAlloc;
}

void MemManager::Dump(void) {
   Release();
}

#ifndef __MEMORY_MANAGER_H
#define __MEMORY_MANAGER_H

#include <windows.h>

#define MEMORY_LOGGING

#define MEMTAB_SIZE			1024

void *operator new(size_t size);
void operator delete( void * );

class MemManager {
	friend void *operator new(size_t);
	friend void operator delete( void * );

	public:
        enum{ CALL_STACK_SIZE = 10 };
		static MemManager *GetInstance(void); // Get Instance.
      virtual ~MemManager(void);	// Destructor.
      DWORD GetAllocMem(void);
      void Dump(void);

      void Start();
      void Stop();

	protected:
        
		class MemWalk {
			public:
				void    *ptr;			// Pointer allocated
				size_t  Size;			// Its size
                DWORD   callStack[ CALL_STACK_SIZE ];
				MemWalk *Next;			// Next in list
		};

		class MemTab {
			public:
				MemWalk *memTop[MEMTAB_SIZE]; // low 16-bits >> 6 table
		};

		DWORD dwTotalAlloc;
      
      CRITICAL_SECTION cs;
      bool Init;
		
		MemWalk *memTop;
		MemWalk *memWalk;
		MemWalk *memPtr;
		MemWalk *memOld;

		MemTab  *memTab;
		
		int nItems;
	
		MemManager(void);			// Constructor.

      DWORD takeofs(void *ptr);	// Return offset.
      void Initialize(void);    // Init.
      void Release(void);        // Release.

		void *Create( int size, DWORD callStack[] );				  // New
		void Free(void *ptr);								  // Delete
	
};

#endif

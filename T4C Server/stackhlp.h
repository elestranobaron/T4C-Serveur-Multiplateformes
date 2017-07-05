#ifndef STACKHLP_H_12052000
#define STACKHLP_H_12052000

#ifdef _M_IX86

#define GET_CALLER_ADDR( callerAddr ){\
                __asm{ push eax };\
                __asm{ mov eax, dword ptr[ ebp + 4 ] };\
                __asm{ mov callerAddr, eax };\
                __asm{ pop eax };\
}

#else
#define GET_CALLER_ADDR( callerAddr ) callerAddr = 0;
#endif

DWORD WalkStack( DWORD bufferCallAddr[], DWORD bufferSize );
DWORD WalkStack( DWORD bufferCallAddr[], DWORD bufferSize, DWORD Ebp );

#endif
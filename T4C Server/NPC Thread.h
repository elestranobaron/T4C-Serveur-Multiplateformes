#ifndef NPCMAIN_H_INCLUDE
#define NPCMAIN_H_INCLUDE

class NPCMain{
public:
    static NPCMain &GetInstance();

    unsigned int GetThreadId(){ return nNPCThreadId; };
    HANDLE GetThreadHandle(){ return hNPCThread; };

    Creatures *GetNPC( LPCTSTR npcName, DWORD order, WORD wLang );
    DWORD CountNPC( LPCTSTR npcName, WORD wLang );

    void KillAll();
private:
    NPCMain();

    void NPCThreadFunc( void );

    static unsigned int CALLBACK NPCThread( void *pParam );

    HANDLE hNPCThread;
    unsigned int    nNPCThreadId;

    bool boNPCThreadDone;
};


#endif
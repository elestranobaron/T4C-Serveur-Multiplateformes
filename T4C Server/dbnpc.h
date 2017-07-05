// NPC.h: interface for the NPC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPC_H__DEDFE6E3_3C9D_11D4_B5B3_00E0296B9056__INCLUDED_)
#define AFX_NPC_H__DEDFE6E3_3C9D_11D4_B5B3_00E0296B9056__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Commands.h"

///////////////////////
namespace vir{
class NPC  
{
public:	
	virtual ~NPC();

    string GetName(){ return name; };
    void   SetName( string iname ){ name = iname; };

    static NPC *CreateNewNPC();
    static NPC *CreateVirginNPC();    

    ScriptContainer &OnTalk(){ return onTalk; };

    DWORD  creatureId;
 
    void Load( WDAFile &i, DWORD ver );
    void Save( WDAFile &o );
    

private:
    NPC();

    DWORD  id;
    string name;
    
    ScriptContainer onTalk;
};
}

#endif // !defined(AFX_NPC_H__DEDFE6E3_3C9D_11D4_B5B3_00E0296B9056__INCLUDED_)

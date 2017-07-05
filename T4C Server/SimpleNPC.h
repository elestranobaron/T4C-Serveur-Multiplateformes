// SimpleNPC.h: interface for the SimpleNPC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLENPC_H__AD5E35C3_4C46_11D4_B5C9_00E0296B9056__INCLUDED_)
#define AFX_SIMPLENPC_H__AD5E35C3_4C46_11D4_B5C9_00E0296B9056__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NPCstructure.h"
#include "NPC_Editor/NPC.h"

class SimpleNPC : public NPCstructure  
{
public:
	SimpleNPC();
	virtual ~SimpleNPC();

	virtual void OnInitialise( UNIT_FUNC_PROTOTYPE );
    virtual void OnTalk( UNIT_FUNC_PROTOTYPE );
    virtual void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
	virtual void OnDeath( UNIT_FUNC_PROTOTYPE );
	virtual void OnAttack( UNIT_FUNC_PROTOTYPE );
	virtual void OnAttacked( UNIT_FUNC_PROTOTYPE );

    NPC_Editor::NPC *theNpc;
};

#endif // !defined(AFX_SIMPLENPC_H__AD5E35C3_4C46_11D4_B5C9_00E0296B9056__INCLUDED_)

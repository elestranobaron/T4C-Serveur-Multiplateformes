// Chest.h: interface for the Chest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHEST_H__AD5E35C3_4C46_11D4_B5C9_00E0296B9056__INCLUDED_)
#define AFX_CHEST_H__AD5E35C3_4C46_11D4_B5C9_00E0296B9056__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NPCstructure.h"
#include "NPC_Editor/NPC.h"

class Chest 
{
public:	
	virtual ~Chest();

    static Chest &GetInstance();

	virtual void OnTalk( UNIT_FUNC_PROTOTYPE );
    virtual void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

    void AddItem( void );
    void TakeItem( void );


private:
    Chest();

    static unsigned int PipeThread( void *lpInstance );

};

#endif
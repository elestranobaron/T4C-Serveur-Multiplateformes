// NPCstructure.h: interface for the NPCstructure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPCSTRUCTURE_H__8745E2D4_0F4C_11D1_BCDB_00E029058623__INCLUDED_)
#define AFX_NPCSTRUCTURE_H__8745E2D4_0F4C_11D1_BCDB_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "stdafx.h"
#include "Unit.h"
#include "StaticFlags.h"
#include "random.h"
#include "MonsterStructure.h"
#include "Broadcast.h"
#include "StatModifierFlagsListing.h"
#include "Doings.h"
#include "TFC_MAIN.h"
#include "Objects.h"
#include "Creatures.h"
#include "ObjectListing.h"
#include "CreatureListing.h"
#include "MonsterStructure.h"
#include "QuestFlagsListing.h"
#include "NPCmacroScriptLng.h"
#include "RaceListing.h"
#include "ClanListing.h"
#include "SpellListing.h"
#include "TFCTime.h"
#include "SkillListing.h"
#include "ClanListing.h"
#include "_item.h"

/*	Color Code

~<color><text>

ex.
  "Hi, this text is red -> ~rHi hello!!~~ woohoo!"
~~  DEFAULT COLOR
~r	RED
~b  BLUE
~c  CYAN
~y  YELLOW
~g  GREEN
~p  PURPLE
~w  WHITE
~e  GREY
 */


extern Random rnd;

#define SET_NPC_NAME( __name )	npc.name = new char[ strlen( __name ) + 1 ];\
								strcpy( npc.name, __name );


#define SET_RANGE( lox, loy, hix, hiy ) npc.wLoXrange = lox;\
    npc.wLoYrange = loy;\
    npc.wHiXrange = hix;\
    npc.wHiYrange = hiy;

typedef struct _NPCSCHEDULE{
	TFCTIME tTriggerTime;

	int			iBehavior;		// Behavior to instill at the time
	WorldPos	wlDestination;	// Where the NPC should urge :)
	Unit		*Target;		// new target of the unit

} NPCSCHEDULE, *LPNPCSCHEDULE;


class __declspec(dllexport) NPCstructure : /*public StaticFlags,*/ public BaseReferenceMessages
{
public:
	NPCstructure();
	virtual ~NPCstructure();
	
	// Here are implementated the default message handlings for the NPC.
	virtual void OnInitialise( UNIT_FUNC_PROTOTYPE );
	virtual void OnAttack( UNIT_FUNC_PROTOTYPE );
	virtual void OnAttacked( UNIT_FUNC_PROTOTYPE );
	virtual void OnHit( UNIT_FUNC_PROTOTYPE );
	virtual void OnServerInitialisation( UNIT_FUNC_PROTOTYPE, WORD wBaseReferenceID );
	virtual void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
	virtual void OnGetUnitStructure( UNIT_FUNC_PROTOTYPE );
	virtual void OnQuerySchedule( UNIT_FUNC_PROTOTYPE );
    virtual void OnDeath( UNIT_FUNC_PROTOTYPE );
    virtual void OnAttackHit( UNIT_FUNC_PROTOTYPE );

	class __declspec(dllexport) NPC : public MonsterStructure{
	public:
		WORD BaseReferenceID;
		//WorldPos InitialPos;

		DWORD dwTextColor;		
		MonsterStructure *GetMonsterStructure( void );		
	} npc;

	TemplateList <NPCSCHEDULE> tlSchedule;
};
/*
extern NPCstructure::NPC Lord;
extern NPCstructure::NPC Lighthaven_Necromancer;
extern NPCstructure::NPC Peasant;
extern NPCstructure::NPC Priest;
extern NPCstructure::NPC Mage;
extern NPCstructure::NPC Lighthaven_Mage;
extern NPCstructure::NPC Guard;
extern NPCstructure::NPC Lighthaven_Priestess;
extern NPCstructure::NPC STAT_WINDHOWL_SAILOR;
extern NPCstructure::NPC STAT_WINDHOWL_PAYSAN;
extern NPCstructure::NPC STAT_WINDHOWL_GUARD;
extern NPCstructure::NPC STAT_WINDHOWL_GUNTERTAG;
extern NPCstructure::NPC STAT_WINDHOWL_WOUNDED_GUARD;
extern NPCstructure::NPC STAT_WINDHOWL_NOBLE;
extern NPCstructure::NPC STAT_WINDHOWL_PAYSANNE;
extern NPCstructure::NPC STAT_WINDHOWL_LORD_SUNROCK;
extern NPCstructure::NPC STAT_WINDHOWL_WOUNDED_KNIGHT;
extern NPCstructure::NPC STAT_WINDHOWL_DRUNK;
extern NPCstructure::NPC STAT_WINDHOWL_TRAINER;
extern NPCstructure::NPC STAT_WINDHOWL_PRIEST;
extern NPCstructure::NPC STAT_WINDHOWL_PRIESTESS;
extern NPCstructure::NPC STAT_WINDHOWL_ASSASSIN;
extern NPCstructure::NPC STAT_WINDHOWL_THIEF;
extern NPCstructure::NPC STAT_WINDHOWL_MAGE;
extern NPCstructure::NPC Silversky_Paysan;
extern NPCstructure::NPC Silversky_Smith;
extern NPCstructure::NPC Silversky_Sailor;
extern NPCstructure::NPC Silversky_Paysanne;
extern NPCstructure::NPC Silversky_Priestess;
extern NPCstructure::NPC Silversky_Priest;
extern NPCstructure::NPC Silversky_Drunk;
extern NPCstructure::NPC BleedingPrisonner;
extern NPCstructure::NPC Arakas_Druid;
extern NPCstructure::NPC Arakas_DeadKing;
extern NPCstructure::NPC Arakas_Brigand;
extern NPCstructure::NPC Arakas_Lady_Brigand;
extern NPCstructure::NPC Balork;
  */

#endif // !defined(AFX_NPCSTRUCTURE_H__8745E2D4_0F4C_11D1_BCDB_00E029058623__INCLUDED_)

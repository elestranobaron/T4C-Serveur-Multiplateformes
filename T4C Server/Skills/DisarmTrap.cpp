// DisarmTrap.cpp: implementation of the DisarmTrap class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DisarmTrap.h"
#include "..\_item.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LPSKILLPNTFUNC DisarmTrap::lpOnAddPnts = NULL;

DisarmTrap::DisarmTrap()
{
	s_saAttrib.Class = 0;
	s_saAttrib.Cost = 1;
	s_saAttrib.Level = 21;
	s_saAttrib.AGI = 45;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 30;
	s_saAttrib.LCK = 45;
	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 210;
	s_saAttrib.ClassPnts[PRIEST] = 0;

	ADD_REQUIRED_SKILL( __SKILL_PICKLOCK, 42 )
}

void DisarmTrap::Destroy( void )
{
	s_saAttrib.tlSkillRequired.AnnihilateList();
}

//////////////////////////////////////////////////////////////////////////////////////////
int DisarmTrap::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Implements faith, does nothing.
// -- Hook_None --
(
 DWORD dwReason,			// Hook used to call function.
 Unit *self,				// Unused
 Unit *medium,				// Unused
 Unit *target,				// Unused
 void *valueIN,				// Unused
 void *valueOUT,			// Unused
 LPUSER_SKILL lpusUserSkill // Unused
)
// Return: int, SKILL_NO_FEEDBACK, does nothing
//////////////////////////////////////////////////////////////////////////////////////////
{

	if( dwReason & HOOK_USE_TARGET_UNIT ){

	/*	// Can only disarm objects
		if( target->GetType() == U_OBJECT ){
			_item *sItem;
			target->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &sItem );

			WORD wDisarm = 0;
			// If trap is on the object itself.			
            if( sItem->trap.wDisarm != 0 ){
				wDisarm = sItem->trap.wDisarm;
			}else if( sItem->lock.wDisarm ){
				// If trap is in the object's lock.
				wDisarm = sItem->lock.wDisarm;
			}

			// If object has a trap.
			if( wDisarm != 0 ){
				// Do disarm test.
				int nTest = rnd.testvs( lpusUserSkill->nSkillPnts, wDisarm );
				// If test succeeds.
				if( nTest >= 0 ){
					// Disable trap.
					target->AddFlag( __FLAG_TRAP_DISABLED, 1 );					
				}else{
					// Otherwise blow off trap.
#ifdef _TODO
#error Do trap blowoff in DisarmTrap.cpp line 83, Skills.DLL
#endif

				}
			}

		}*/

	}
	return SKILL_NO_FEEDBACK;
}
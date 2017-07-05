// Sneak.cpp: implementation of the Sneak class.
//
//////////////////////////////////////////////////////////////////////

#pragma hdrstop
#include "stdafx.h"
#include "Sneak.h"
#include "../TFC_MAIN.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Sneak::Sneak()
{
   	s_saAttrib.Class = 0;
	s_saAttrib.Cost = 1;
	s_saAttrib.Level = 24;
	s_saAttrib.AGI = 75;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
}

void Sneak::Destroy( void )
{
	s_saAttrib.tlSkillRequired.AnnihilateList();
}

LPSKILLPNTFUNC Sneak::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
int Sneak::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Powerfull blow function
// 
(
 DWORD dwReason,			// Hook which made the skill function call.
 Unit *self,				// Unit attacking
 Unit *medium,				// Unused.
 Unit *target,				// Unit attacked.
 void *valueIN,				// LPATTACK_STRUCTURE, blow/strike
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Skill strength.
)
// Return: int, SKILL_SUCCESSFULL or SKILL_FAILED
//////////////////////////////////////////////////////////////////////////////////////////
{	
	// This skill is only used when moving and hidden.
	if( !( dwReason & HOOK_MOVE ) || self->ViewFlag( __FLAG_HIDDEN ) == 0 )	
	{
        return SKILL_NO_FEEDBACK;
	}
	
    WorldMap *wl = TFCMAIN::GetWorld( self->GetWL().world );

    if( wl == NULL )
	{
        return SKILL_NO_FEEDBACK;
    }
	
    // Get all units within the default range.
    TemplateList< Unit > *unitList = wl->GetLocalUnits( self->GetWL(), _DEFAULT_RANGE, FALSE );//BLBLBL 30=>_DEFAULT_RANGE

    if( unitList == NULL )
	{
        return SKILL_NO_FEEDBACK;
    }
	
    DWORD sneakSkill = lpusUserSkill->GetSkillPnts( self );
    int userHeuristic;
    if( unitList->NbObjects() == 0 )
	{
        userHeuristic = 0;
    }else
	{
        userHeuristic = ( unitList->NbObjects() - 1 ) * 10;   
    }	

    // If sneak succeeds
	int nRand = rnd.roll( dice( 1, 100 ) );
	int nSuccess = sneakSkill + self->GetAGI() / 6 - userHeuristic;		

	if( nRand < nSuccess )
	{
        // Nothing happens.		
        delete unitList;
        return SKILL_NO_FEEDBACK;
    }

    // Unhide the unit.
    self->Unhide();

    delete unitList;

	return SKILL_NO_FEEDBACK;
}
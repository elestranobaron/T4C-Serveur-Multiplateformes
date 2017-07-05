// Meditate.cpp: implementation of the Meditate class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FastHealing.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FastHealing::FastHealing()
{
	s_saAttrib.Class = MAGE;
	s_saAttrib.Cost = 0;
	s_saAttrib.Level = 30;
	s_saAttrib.AGI = 0;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 80;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 25;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;

}

void FastHealing::Destroy( void )
{

}

LPSKILLPNTFUNC FastHealing::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
int FastHealing::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Called when a player regenerates.
// 
(
 DWORD dwReason,			// Hook which called the skill.
 Unit *self,				// Unit meditating.
 Unit *medium,				// Unused.
 Unit *target,				// Unused.
 void *valueIN,				// Unused.
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Skill strength.
)
// Return: int, SKILL_PERSONNAL_FEEDBACK_SUCCESSFULL or SKILL_PERSONNAL_FEEDBACK_FAILED 
//				(HOOK_USE), SKILL_NO_FEEDBACK (HOOK_REGEN)
//////////////////////////////////////////////////////////////////////////////////////////
{
	// If skill was for regeneration (while meditating).
	if(dwReason & HOOK_REGEN){
        self->Lock();      

        DWORD dwHP = self->GetHP();
		DWORD dwMaxHP = self->GetMaxHP();

		// regen hp only if its under the max hp.
		if( dwHP < dwMaxHP ){
            if( rnd( 1, 100 ) <= 60 ){
                // Calculate normal regen.
                int nRegen = rnd( 0, self->GetEND() / 40 ) + 1;

                nRegen *= ( lpusUserSkill->GetSkillPnts( self ) + 25 ) / 25;
                
                dwHP += static_cast< DWORD >( nRegen );

                // If new health is smaller than max hp.
                if( dwHP < dwMaxHP ){
                    self->SetHP( dwHP, true );
                }else{
                    self->SetHP( dwMaxHP, true );
                }
            }
		}        
        self->Unlock();
	}


	return SKILL_NO_FEEDBACK;
}
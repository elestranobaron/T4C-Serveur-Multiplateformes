// Meditate.cpp: implementation of the Meditate class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Meditate.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Meditate::Meditate()
{
	s_saAttrib.Class = MAGE;
	s_saAttrib.Cost = 26;
	s_saAttrib.Level = 16;
	s_saAttrib.AGI = 0;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 30;
	s_saAttrib.WIS = 30;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 25;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;

}

void Meditate::Destroy( void )
{

}

LPSKILLPNTFUNC Meditate::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
int Meditate::Func
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
/*
In a safe place. (In a house or druid camp and temple)

Mana regenerate at a rate of 20% of Meditate skill + the normal regenerate.
Those regeneration are done each hour of gametime(2min).

Note: All light is reduced to 0% during the meditation. None can speak
      with the player and if the player is hit, he loose concentration.
      This makes him unable to get mana with the time spent.
*/

	// If skill was used (start meditating)
	if(dwReason & HOOK_USE){
        if( self->GetType() == U_PC ){
            Character *ch = static_cast< Character * >( self );
            ch->StopAutoCombat();
        }


		UINT nMeditating = self->ViewFlag(__FLAG_MEDITATING);

		// if player is not currently meditating, make him meditate
		if(!nMeditating){
			self->SetFlag(__FLAG_MEDITATING, 1);

		}
        self->DealExhaust( 3000, 3000, 3000 );

		return SKILL_PERSONNAL_FEEDBACK_SUCCESSFULL;
	}else 
	// If skill was for regeneration (while meditating).
	if(dwReason & HOOK_REGEN){
		UINT nMeditating = self->ViewFlag(__FLAG_MEDITATING);
		
		// only regen if person is meditating.
		if( nMeditating != 0 ){
			WORD wMana = self->GetMana();
			WORD wMaxMana = self->GetMaxMana();

			// If mana is not maxed
			if( wMana < wMaxMana ){
                
                if( rnd( 1, 100 ) <= 60 ){    
                    int nRegen = rnd( 0, self->GetINT() / 160 ) + self->GetINT() / 160 + 
                                 rnd( 0, self->GetWIS() / 160 ) + self->GetWIS() / 160 + 1;

                    nRegen *= ( lpusUserSkill->GetSkillPnts( self ) + 25 ) / 25;

                    TRACE( "\r\nRegen=%u.", nRegen );
                    wMana += static_cast< WORD >( nRegen );

                    self->Lock();
                    // If mana is smaller than max mana
                    if( wMana < wMaxMana ){
                        self->SetMana( wMana );
                    }else{
                        self->SetMana( wMaxMana );
                    }
                    self->Unlock();
                }
		    }
    	}
    }

	return SKILL_NO_FEEDBACK;
}
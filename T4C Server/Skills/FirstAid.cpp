// FirstAid.cpp: implementation of the FirstAid class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FirstAid.h"
#include "../format.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FirstAid::FirstAid()
{
	s_saAttrib.Class = ANY_CLASS;
	s_saAttrib.Cost = 40;
	s_saAttrib.Level = 12;
	s_saAttrib.AGI = 0;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 20;
	s_saAttrib.WIS = 20;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;

	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;

    UnitEffectManager::RegisterEffect( EFFECT_FIRST_AID_EXHAUST, ExhaustRemovallCallback );
}

void FirstAid::Destroy( void )
{

}

LPSKILLPNTFUNC FirstAid::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
void FirstAid::ExhaustRemovallCallback
//////////////////////////////////////////////////////////////////////////////////////////
// Timer callback when stunblow should be removed.
// 
(
 EFFECT_FUNC_PROTOTYPE 
)
//////////////////////////////////////////////////////////////////////////////////////////
{		
	self->RemoveFlag( __FLAG_FIRST_AID_EXHAUST );
}


//////////////////////////////////////////////////////////////////////////////////////////
int FirstAid::Func
//////////////////////////////////////////////////////////////////////////////////////////
// First aid skill..
// 
(
 DWORD dwReason,			// Hook used to call function.
 Unit *self,				// Unit using the skill.
 Unit *medium,				// Unused.
 Unit *target,				// Unit targetted by skill.
 void *valueIN,				// Unused.
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Skill strength.
)
// Return: int, SKILL_SUCCESSFULL or SKILL_FAILED
//////////////////////////////////////////////////////////////////////////////////////////
{
    int nSuccess = SKILL_FAILED;
	
    // Set target equal to self.
    target = self;

	// If skill was used
	if(dwReason & HOOK_USE){	
        CAutoLock cLock( self );

        if( self->GetType() == U_PC ){
            Character *ch = static_cast< Character * >( self );
            ch->StopAutoCombat();
        }

        // If the player can use first aid.
        if( target->ViewFlag( __FLAG_FIRST_AID_EXHAUST ) == 0 ){

			DWORD percentModified				= 0;
            DWORD dwInitialHP					= target->GetHP();
			DWORD dwHP							= dwInitialHP;
            DWORD dwMaxHP						= target->GetMaxHP();

            // If skill succeeds
            if( rnd( dice( 1, 100 ) ) < 50 + ( lpusUserSkill->GetSkillPnts( self ) / 4 ) ){
				DWORD percentMin = lpusUserSkill->GetSkillPnts( self ) / 6,
					  percentMax = lpusUserSkill->GetSkillPnts( self ) / 4;
				percentModified = percentMin + ( rnd( 0, 100 ) * (percentMax-percentMin) / 100 );
				dwHP += percentModified*dwMaxHP/100;
  
                dwHP = dwHP > dwMaxHP ? dwMaxHP : dwHP;
                target->SetHP( dwHP, true );
            }
            // If skill fails.
            else{
				DWORD percentMin = lpusUserSkill->GetSkillPnts( self ) / 8,
					  percentMax = lpusUserSkill->GetSkillPnts( self ) / 6;
				percentModified = percentMin + ( rnd( 0, 100 ) * (percentMax-percentMin) / 100 );
				DWORD dwDamage = percentModified*dwMaxHP/100;

                // If skill did more damage than the user's hp
                if( dwDamage >= dwHP ){
                    // Do not kill, set hp to 1.
                    dwHP = 1;
                }else{
                    dwHP -= dwDamage;
                }
                target->SetHP( dwHP, true );
            }
        
		    // Carlos note: Calling RemoveEffect triggers the effect (in this case), so, we must call RemoveEffect *before* calling the SetFlag =)
			target->RemoveEffect( EFFECT_FIRST_AID_EXHAUST );
		    target->SetFlag(__FLAG_FIRST_AID_EXHAUST, (UINT)FirstAid::ExhaustRemovallCallback );
		    
		    CREATE_EFFECT(
	            target, 
			    MSG_OnTimer, 
			    EFFECT_FIRST_AID_EXHAUST, 
			    ExhaustRemovallCallback, 
			    NULL, 
			    45 SECONDS TDELAY, // Timer frequency
                45 SECONDS TDELAY, // Duration
                __SKILL_FIRST_AID,
                0
		    );

            self->DealExhaust( 5000, 5000, 5000 );

			TFormat format;
			if (dwHP >= dwInitialHP) {
				self->SendSystemMessage( format(_STR(12957, self->GetLang()), dwHP-dwInitialHP ));
			} else {
				self->SendSystemMessage( format(_STR(12958, self->GetLang()), dwInitialHP-dwHP ));
			}
        }else{
            // Send a 'You cannot execute this action right now...' message.
            self->SendSystemMessage( _STR( 2847, self->GetLang() ) );
        }
	}

return nSuccess;
}


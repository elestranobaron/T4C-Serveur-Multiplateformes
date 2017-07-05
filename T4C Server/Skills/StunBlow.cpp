// StunBlow.cpp: implementation of the StunBlow class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "StunBlow.h"

StunBlow::StunBlow(){
	s_saAttrib.Class = WARRIOR;
	s_saAttrib.Cost = 5;
	s_saAttrib.Level = 3;
	s_saAttrib.AGI = 20;
	s_saAttrib.STR = 25;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 25;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;

	UnitEffectManager::RegisterEffect( EFFECT_STUN_BLOW, TimerStunRemovallCallback );

}

void StunBlow::Destroy( void ){
	s_saAttrib.tlSkillRequired.AnnihilateList();
}

LPSKILLPNTFUNC StunBlow::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
void StunBlow::TimerStunRemovallCallback
//////////////////////////////////////////////////////////////////////////////////////////
// Timer callback when stunblow should be removed.
// 
(
 EFFECT_FUNC_PROTOTYPE 
)
//////////////////////////////////////////////////////////////////////////////////////////
{		
	self->RemoveFlag(__FLAG_STUN);		
	TRACE("\r\n\r\nRemove stun!!\r\n\r\n");	
}

//////////////////////////////////////////////////////////////////////////////////////////
int StunBlow::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Stunblow function.
// 
(
 DWORD dwReason,			// Hook which called this skill.
 Unit *self,				// Unit attacking
 Unit *medium,				// Unused.
 Unit *target,				// Unit attacked.
 void *valueIN,				// LPATTACK_STRUCTURE, the blow..
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Skill strength
)
// Return: int, SKILL_SUCCESSFULL or SKILL_FAILED
//////////////////////////////////////////////////////////////////////////////////////////
{
	// If skill got called by an attack hook
	if(dwReason == HOOK_ATTACK){

		// This skill is an OnAttack skill, so it receives an ATTACK_STRUCTURE as valueIN
		LPATTACK_STRUCTURE s_asBlow	= (LPATTACK_STRUCTURE)valueIN;
		
        int nStunSuccess = 0;

        if( self->GetLevel() >= target->GetLevel() * 3 / 4 ){
            nStunSuccess = lpusUserSkill->GetSkillPnts( self ) / 2;
        }else{
            nStunSuccess = lpusUserSkill->GetSkillPnts( self ) / 4;
        }

        // If stun blow is successfull.
        if( rnd.roll( dice( 1, 100 ) ) < nStunSuccess ){
            // If strength vs endurance roll succeeds.
            if( rnd.roll( dice( 1, self->GetSTR() ) ) > rnd.roll( dice( 1, target->GetEND() ) ) ){
                TRACE("\r\n\r\nStunned!\r\n\r\n");
				target->SetFlag(__FLAG_STUN, (UINT)StunBlow::TimerStunRemovallCallback);
				target->RemoveEffect( EFFECT_STUN_BLOW );
				
                DWORD timer = rnd.roll( dice( 1, 1000, 1000 ) );
                
                CREATE_EFFECT(
					target, 
					MSG_OnTimer, 
					EFFECT_STUN_BLOW, 
					TimerStunRemovallCallback, 
					NULL, 
					timer MILLISECONDS TDELAY,
                    timer,
                    __SKILL_STUN_BLOW,
                    0
				);
                return SKILL_SUCCESSFULL;
            }            
        }
		
	
		return SKILL_FAILED;
	}
	
	return SKILL_FAILED;
}
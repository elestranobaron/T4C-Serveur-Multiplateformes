// CriticalStrike.cpp: implementation of the CriticalStrike class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CriticalStrike.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CriticalStrike::CriticalStrike()
{
	s_saAttrib.Class = WARRIOR;
	s_saAttrib.Cost = 51;
	s_saAttrib.Level = 35;
	s_saAttrib.AGI = 0;
	s_saAttrib.STR = 70;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 35;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 200;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;

	//ADD_REQUIRED_SKILL( __SKILL_MONSTER_LORE, 72 )
}

void CriticalStrike::Destroy( void )
{
	s_saAttrib.tlSkillRequired.AnnihilateList();
}

LPSKILLPNTFUNC CriticalStrike::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
int CriticalStrike::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Critical strike main function
// 
(
 DWORD dwReason,			// Hook which was used to call the skill.
 Unit *self,				// Unit using the skill.
 Unit *medium,				// Unused.
 Unit *target,				// Target of attack.
 void *valueIN,				// LPATTACK_STRUCTURE, current blow.
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Current skill strength of the user.
)
// Return: int, SKILL_* return parameter.
//////////////////////////////////////////////////////////////////////////////////////////
{

/*Quand l'attaque reussi.

300 - Critical Strike = CC (Chiffre Critique)
Roule un de egal au CC.
Si resultat est entre 1 et 5,
6 - Resultat = Mouhaha
Mouhaha * Damage = Damage done ce round la.
*/
	// If skill was called for an attack
	if(dwReason & HOOK_ATTACK)
   {
		LPATTACK_STRUCTURE s_asBlow = (LPATTACK_STRUCTURE)valueIN;

		DWORD dwCriticalNum = 250 - lpusUserSkill->GetSkillPnts( self );
		DWORD dwDiceRoll = rnd(1, dwCriticalNum);
		
		if(dwDiceRoll < 5)
		{
			int nDamMod = 6 - dwDiceRoll;
			s_asBlow->Strike *= nDamMod;

			if( ((Character*)self)->GetGodFlags() & GOD_DEVELOPPER )
			{
				CString csMessage;
		 		csMessage.Format( "[\"Critical\" \"Strike\"] increased damages. (Old: %lf, New: %lf)", (double) s_asBlow->Strike/nDamMod, s_asBlow->Strike );
				self->SendSystemMessage( csMessage );
			}
		}else{
			return SKILL_FAILED;
		}

		return SKILL_SUCCESSFULL;

	}

	return SKILL_FAILED;
}
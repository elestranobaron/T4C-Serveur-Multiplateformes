// PowerfullBlow.cpp: implementation of the PowerfullBlow class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PowerfullBlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PowerfullBlow::PowerfullBlow()
{
	s_saAttrib.Class = WARRIOR;
	s_saAttrib.Cost = 10;
	s_saAttrib.Level = 15;
	s_saAttrib.AGI = 30;
	s_saAttrib.STR = 50;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 25;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;
}

void PowerfullBlow::Destroy( void )
{}

LPSKILLPNTFUNC PowerfullBlow::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
int PowerfullBlow::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Powerfull blow function
// 
(
 DWORD dwReason,			// Hook which made the skill function call.
Unit *self,					// Unit attacking
 Unit *medium,				// Unused.
 Unit *target,				// Unit attacked.
 void *valueIN,				// LPATTACK_STRUCTURE, blow/strike
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Skill strength.
)
// Return: int, SKILL_SUCCESSFULL or SKILL_FAILED
//////////////////////////////////////////////////////////////////////////////////////////
{
   // If function was called by an attack hook
   if(dwReason & HOOK_ATTACK)
   {
      LPATTACK_STRUCTURE s_asBlow = (LPATTACK_STRUCTURE)valueIN;
      
      int nSuccess = lpusUserSkill->GetSkillPnts( self ) / 2;
      
      if( rnd.roll( dice( 1, 100 ) ) < nSuccess )
      {
		  double oldDmg = s_asBlow->Strike;
		  double rand   = rnd.roll( dice( 1, 33 ) );
         s_asBlow->Strike *= 133;
         s_asBlow->Strike /= 100;
		  if( ((Character*)self)->GetGodFlags() & GOD_DEVELOPPER )
		  {
				CString csMessage;
		 		csMessage.Format( "[\"Powerfull\" \"Blow\"] increased damages. (Old: %lf, New: %lf (+%lf%))", oldDmg, s_asBlow->Strike, rand );
				self->SendSystemMessage( csMessage );
		  }
      }
      else
      {
         return SKILL_FAILED;
      }
      
      return SKILL_SUCCESSFULL;
   }
   
   return SKILL_FAILED;
}
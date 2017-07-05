// Pray.cpp: implementation of the Pray class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Pray.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pray::Pray()
{
	s_saAttrib.Class = PRIEST;
	s_saAttrib.Cost = 26;
	s_saAttrib.Level = 12;
	s_saAttrib.AGI = 0;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 40;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 25;

}

void Pray::Destroy( void )
{
}


LPSKILLPNTFUNC Pray::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
int Pray::Func
//////////////////////////////////////////////////////////////////////////////////////////
// This is the pray skill. Regenerates faith for priests.
// 
(
 DWORD dwReason,			// Hook which made the call to this function
 Unit *self,				// Unit using/regen the skill.
 Unit *medium,				// Unused.
 Unit *target,				// Unused.
 void *valueIN,				// Unused.
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Strength of the skill
)
// Return: int, SKILL_PERSONNAL_FEEBACK_SUCCESSFULL or SKILL_NO_FEEDBACK
//////////////////////////////////////////////////////////////////////////////////////////
{
/*
In a safe place.   

Faith regenerate at a rate of 20% of pray skill + the normal regenerate.
Those regeneration are done each hour of gametime(2min).

Note: All light is reduced to 0% during the meditation. None can speak
      with the player and if the player is hit, he loose concentration.
      This makes him unable to get mana with the time spent.
*/
/*
	// If we use the skill to start praying.
	if(dwReason & HOOK_USE){
		UINT nPraying = self->ViewFlag(__FLAG_PRAYING);

		// If we're not already praying.
		if(!nPraying){
			// then make us pray..
			self->SetFlag(__FLAG_PRAYING, 1);
		}
		// We are current praying
		else{
			// then stop praying
			self->RemoveFlag(__FLAG_PRAYING);
		}

		return SKILL_PERSONNAL_FEEDBACK_SUCCESSFULL;
	}else 
	// If the skill effect is making us regenerate.
	if(dwReason & HOOK_REGEN){
		UINT nPraying = self->ViewFlag(__FLAG_PRAYING);

		// if user was praying..
		if(nPraying){
			WORD Faith = self->GetFaith();
			WORD MaxFaith = self->GetMaxFaith();

			if(Faith < MaxFaith){
				Faith += lpusUserSkill->GetSkillPnts( self ) * 20 PERCENT;
				Faith = Faith > MaxFaith ? MaxFaith : Faith;
			}
		
			self->SetFaith(Faith);
		}
	}
*/
return SKILL_NO_FEEDBACK;
}
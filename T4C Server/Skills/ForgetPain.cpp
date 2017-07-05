// ForgetPain.cpp: implementation of the ForgetPain class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ForgetPain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ForgetPain::ForgetPain()
{
	s_saAttrib.Class = 0;
	s_saAttrib.Cost = 1;
	s_saAttrib.Level = 40;
	s_saAttrib.AGI = 0;
	s_saAttrib.STR = 62;
	s_saAttrib.END = 70;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 400;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;

//	ADD_REQUIRED_SKILL( __SKILL_TWO_WEAPONS, 80 );
}

ForgetPain::~ForgetPain()
{
	s_saAttrib.tlSkillRequired.AnnihilateList();
}

//////////////////////////////////////////////////////////////////////////////////////////
void ForgetPain::OnAddPoints
//////////////////////////////////////////////////////////////////////////////////////////
// Function which will add parry points
// 
(
 Unit *lpuTrained,			// Unit that trained.
 LPUSER_SKILL lpUserSkill,	// Skill's current points.
 DWORD dwNbPoints			// New skill points.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	lpUserSkill->SetSkillPnts( lpUserSkill->GetTrueSkillPnts() + dwNbPoints );
	GAME_RULES::CalcStatBonus( STAT_END, 0, (WORD)dwNbPoints, static_cast< Character *>( lpuTrained ) );
	lpUserSkill->SetSkillPnts( lpUserSkill->GetTrueSkillPnts() - dwNbPoints );
}

LPSKILLPNTFUNC ForgetPain::lpOnAddPnts = OnAddPoints;

//////////////////////////////////////////////////////////////////////////////////////////
int ForgetPain::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Parry's function, does nothing
// -- Hook_None -- 
(
 DWORD dwReason,			// Hook which called this strike.
 Unit *self,				// Unused.
 Unit *medium,				// Unused.
 Unit *target,				// Unused.
 void *valueIN,				// Unused.
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Skill strength.
)
// Return: int, SKILL_NO_FEEDBACK
//////////////////////////////////////////////////////////////////////////////////////////
{
	return SKILL_NO_FEEDBACK;
}
// EvadeView.cpp: implementation of the EvadeView class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "EvadeView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EvadeView::EvadeView()
{	
	s_saAttrib.Class = 0;
	s_saAttrib.Cost = 26;
	s_saAttrib.Level = 28;
	s_saAttrib.AGI = 53;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 54;
	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 280;
	s_saAttrib.ClassPnts[PRIEST] = 0;

//	ADD_REQUIRED_SKILL( __SKILL_DISARM_TRAP, 56 );
}

void EvadeView::Destroy( void )
{
	s_saAttrib.tlSkillRequired.AnnihilateList();
}

//////////////////////////////////////////////////////////////////////////////////////////
void EvadeView::OnAddPoints
//////////////////////////////////////////////////////////////////////////////////////////
// Function which will add EvadeView points
// 
(
 Unit *lpuTrained,			// Unit that trained.
 LPUSER_SKILL lpUserSkill,	// Skill's current points.
 DWORD dwNbPoints			// New skill points.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	int nEvasive = lpuTrained->ViewFlag( __FLAG_EVASIVNESS );
	nEvasive += dwNbPoints;
	lpuTrained->SetFlag( __FLAG_EVASIVNESS, nEvasive );
}

LPSKILLPNTFUNC EvadeView::lpOnAddPnts = OnAddPoints;

//////////////////////////////////////////////////////////////////////////////////////////
int EvadeView::Func
//////////////////////////////////////////////////////////////////////////////////////////
// EvadeView's function, does nothing
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
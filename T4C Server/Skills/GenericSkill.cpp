// GenericSkill.cpp: implementation of the GenericSkill class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "GenericSkill.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GenericSkill::GenericSkill()
{
	s_saAttrib.Class = PRIEST;
	s_saAttrib.Cost = 0;
	s_saAttrib.Level = 0;
	s_saAttrib.AGI = 0;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 0;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;

}

void GenericSkill::Destroy( void )
{
}


LPSKILLPNTFUNC GenericSkill::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
int GenericSkill::Func
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
    return SKILL_NO_FEEDBACK;
}
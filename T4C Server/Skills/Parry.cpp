// Parry.cpp: implementation of the Parry class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Parry.h"
#include "..\TFC Server.h"

extern CTFCServerApp theApp;

//static BoostFormula bfSuccess;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Parry::Parry()
{
	// Setup the formula for the success rate :)
	//bfSuccess.SetFormula("( (1 - (0.5 * self.weight/self.maxweight)) - (1 - if(self.hp < self.maxhp? (self.hp/self.maxhp)/4 : 1))) * (0.5+if(global.hour>=7? if(global.hour<=19?0.5:0):0))");
	s_saAttrib.Class = WARRIOR;
	s_saAttrib.Cost = 26;
	s_saAttrib.Level = 10;
	s_saAttrib.AGI = 30;
	s_saAttrib.STR = 0;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 20;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 25;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;
}

void Parry::Destroy( void )
{

}

//////////////////////////////////////////////////////////////////////////////////////////
void Parry::OnAddPoints
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

}

LPSKILLPNTFUNC Parry::lpOnAddPnts = OnAddPoints;

//////////////////////////////////////////////////////////////////////////////////////////
int Parry::Func
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
	// Added an option to enable servers to disable it in case it turns out to be buggy or unbalanced.
	// This option *will* be removed on next releases
	if (theApp.dwDebugSkillParryDisabled != 0) return SKILL_NO_FEEDBACK;

    // Player got attacked?
    if( dwReason == HOOK_HIT )
	{
        LPATTACK_STRUCTURE s_asBlow = (LPATTACK_STRUCTURE)valueIN;

		// NOTE: When attack is a spell, lDodgeSkill will be 0. In this case, no parry :)
		if (s_asBlow->lDodgeSkill == 0)
		{
			return SKILL_NO_FEEDBACK;
		}

        //int nSuccess = lpusUserSkill->GetSkillPnts( self ) / 4 * bfSuccess.GetBoost(self);				
		double nSuccess = ((double)lpusUserSkill->GetSkillPnts( self)/(lpusUserSkill->GetSkillPnts( self )+50))*10+((double)lpusUserSkill->GetSkillPnts( self )*self->GetSTR()/3000);		

		// If the % is negative, set it to 0 to avoid any problems
		if( nSuccess < 0 )
		{
			nSuccess = 0;
		}
		// If > 50%, set to 50%
		else if( nSuccess > 19 )//BLBLBL on cap à 19 au lieu de 25
		{
			nSuccess = 19;//BLBLBL on cap à 19 au lieu de 25
		}

		// Roll the dice! And... Should we parry?
        if( rnd.roll( dice( 1, 100 ) ) < nSuccess )
		{						
			// You can only deflect an attack if you have something equiped on hands!
			Unit **equipment = ((Character*)self)->GetEquipment();
			if (equipment[Character::weapon_right] != NULL)
			{
				// Nullifie damage.
				s_asBlow->Strike = 0;

				//Show a tiny effect :)
			    Broadcast::BCSpellEffect( self->GetWL(), _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE 
					30009, 
					self->GetID(), 
					0, 
					self->GetWL(),
					self->GetWL(),
					GetNextGlobalEffectID(),
					0
				);


				if( ((Character*)self)->GetGodFlags() & GOD_DEVELOPPER ){
					self->SendSystemMessage("Attack deflected by your parry skill.");
				}
			}

        }
   }

	return SKILL_NO_FEEDBACK;
}
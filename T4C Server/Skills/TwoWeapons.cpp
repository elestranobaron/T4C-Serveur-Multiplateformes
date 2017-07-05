// TwoWeapons.cpp: implementation of the TwoWeapons class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TwoWeapons.h"
#include "..\T4CLog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TwoWeapons::TwoWeapons()
{
   s_saAttrib.Class = WARRIOR;
	s_saAttrib.Cost = 5;
	s_saAttrib.Level = 25;
	s_saAttrib.AGI = 40;
	s_saAttrib.STR = 75;
	s_saAttrib.END = 0;
	s_saAttrib.INT = 30;
	s_saAttrib.WIS = 0;
	s_saAttrib.WIL = 0;
	s_saAttrib.LCK = 0;
	s_saAttrib.ClassPnts[WARRIOR] = 0;
	s_saAttrib.ClassPnts[MAGE] = 0;
	s_saAttrib.ClassPnts[THIEF] = 0;
	s_saAttrib.ClassPnts[PRIEST] = 0;
   srand((unsigned)time(NULL));
}

TwoWeapons::~TwoWeapons()
{

}

LPSKILLPNTFUNC TwoWeapons::lpOnAddPnts = NULL;


//////////////////////////////////////////////////////////////////////////////////////////
int TwoWeapons::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Makes a user shout and scare the hell out of people.
// 
(
 DWORD dwReason,			// Hook which called the skill.
 Unit *self,				// User who warcries.
 Unit *medium,				// Unused.
 Unit *target,				// Unused.
 void *valueIN,				// Unused.
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // User's skill strength.
)
// Return: int, SKILL_SUCCESSFULL or SKILL_FAILED
//////////////////////////////////////////////////////////////////////////////////////////
{
   // If function was called by an attack hook
   if(dwReason & HOOK_ATTACK)
   {
      Character *ch = static_cast< Character * >( self );   
      Unit **lpuEquipped = ch->GetEquipment();

      

      if( lpuEquipped[ Character::weapon_left ] != NULL)
      {
         _item *obj = NULL;
		   lpuEquipped[ Character::weapon_left ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &obj);
        
         if(obj && obj->item_type == 1 /*weapons on left hand*/)
         {
            
            LPATTACK_STRUCTURE s_asBlow = (LPATTACK_STRUCTURE)valueIN;
            int dwDamageWeapon2 = obj->weapon.cDamage.GetBoost( self, target );
            int dwSkillValue    = lpusUserSkill->GetSkillPnts( self );

            int dwVal2 = 0;

            //SKILL a 500 == 25% du degat de l<arme...
            //si le skill ets bouster et monte a 750 == 35% du degat max...
            // 1000 == 50% de l<arme...
            int dwMaxVal = (dwSkillValue*(dwDamageWeapon2/4))/500;
            if(dwMaxVal <0)
            {
               dwVal2 = 0;
            }
            else
            {
               if(dwMaxVal >20)
               {
                  int dwEcart = dwMaxVal/5;
                  int dwValE  = (rand()%(dwEcart*2))-dwEcart;
                  dwVal2 = dwMaxVal+dwValE;
               }
               else
               {
                  dwVal2 = dwMaxVal;
               }
               
            }



            // on ajoute un facteur d<erreur de 20% de la valeur du degat la dessus...
            
         

            int dwDamageWeapon1 = 0;
            if( lpuEquipped[ Character::weapon_right ] != NULL)
            {
               _item *objR = NULL;
		         lpuEquipped[ Character::weapon_right ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &objR);
               if(objR && objR->item_type == 1 )
               {
                  dwDamageWeapon1 = objR->weapon.cDamage.GetBoost( self, target );
               }
            }
            
            _LOG_ITEMS
               LOG_MISC_1,
               "Damage [%d][%d]   [%d] [%d]",
               dwDamageWeapon1,
               dwDamageWeapon2,
               dwMaxVal,
               dwVal2
               
               LOG_

            s_asBlow->Strike += dwVal2;
           
            return SKILL_SUCCESSFULL;
            
         }
      }
   }
   return SKILL_NO_FEEDBACK;
}
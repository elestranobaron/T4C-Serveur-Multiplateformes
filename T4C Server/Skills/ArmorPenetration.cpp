// ArmorPenetration.cpp: implementation of the ArmorPenetration class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ArmorPenetration.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArmorPenetration::ArmorPenetration()
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
   
}

LPSKILLPNTFUNC ArmorPenetration::lpOnAddPnts = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
int ArmorPenetration::Func
//////////////////////////////////////////////////////////////////////////////////////////
// ArmorPenetration's function
// -- Hook_Attack -- 
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
   if( dwReason == HOOK_ATTACK )
   {
      
      if (target != NULL && target->GetAC() >= 5000) return SKILL_NO_FEEDBACK;//BL Note : Checks if target is under Sanctuary effect
      
      LPATTACK_STRUCTURE s_asBlow = (LPATTACK_STRUCTURE)valueIN;
      
      int nSuccess = lpusUserSkill->GetSkillPnts( self ) / 2;
      
      if( rnd.roll( dice( 1, 100 ) ) < nSuccess )
      {     
         //Old formula
         /*
         double dAC    = target->GetAC();
         double dNewAC = dAC - lpusUserSkill->GetSkillPnts( self ) * dAC / 150;    // Determine the new target's AC
         
         double dBuf = dNewAC;
         double dMax = dAC - (double) (9*dAC/10);			
         
         if( dNewAC <= dMax )
         {
            self->SendSystemMessage( "Higher than 90%" );				
            dNewAC = dMax;
         }
         */
         
         
         // Destiny's new formula
         // If player's skill pnts > 130, the % increases faster.
         // The 100% isn't reached at anytime.
         /*
         double dAC	   = target->GetAC();
         double dNewAC  = lpusUserSkill->GetSkillPnts( self ) > 125 ?
            (double)lpusUserSkill->GetSkillPnts( self )/(lpusUserSkill->GetSkillPnts( self )+25) * dAC :
         (double)lpusUserSkill->GetSkillPnts( self )/(lpusUserSkill->GetSkillPnts( self )+50) * dAC;
         
         // Send a little message to the debugger
         if( ((Character*)self)->GetGodFlags() & GOD_DEVELOPPER )
         {
            CString csMessage;
            csMessage.Format( "[\"Armor\" \"Penetration\"] transpierced the target AC (Gained %lf dmg)", dNewAC );
            self->SendSystemMessage( csMessage );
         }
         
         // Insures that low AC doesn't actually add damage to the blow.
         dNewAC = dNewAC > 0 ? dNewAC : 0;
         
         // Calculate new blow using the first strike and the new AC.
         double dDam = s_asBlow->TrueStrike + dNewAC;
         
         // If damage was dealt. (insure very high AC doesn't get even passed through ).
         if( dDam > 0 )
         {
            // Plus to damage equals how more damage this blow would have done over normal AC.
            double dDeltaDam = dDam - ( s_asBlow->TrueStrike - dAC );
            
            // Add the more damage this would have done.
            s_asBlow->Strike += dDeltaDam;
         }     
         */

      
         ///NMS Methode...
         /*
         double dAC	   = target->GetAC();
         double dTA     = lpusUserSkill->GetSkillPnts( self );
         double dNewAC  = lpusUserSkill->GetSkillPnts( self ) > 125 ?
            (double)lpusUserSkill->GetSkillPnts( self )/(lpusUserSkill->GetSkillPnts( self )+25) * dAC :
         (double)lpusUserSkill->GetSkillPnts( self )/(lpusUserSkill->GetSkillPnts( self )+50) * dAC;
         
         dNewAC = dNewAC > 0 ? dNewAC : 0;
         
         double dBoust = dTA<200?(dTA/200) * (s_asBlow->TrueStrike/4):(s_asBlow->TrueStrike/4);
         double dDam   = s_asBlow->TrueStrike + dNewAC;
         
         s_asBlow->Strike = dDam + dBoust;
         */

         ///NMS Methode...
         
         double dAC	   = target->GetAC();
         double dTA     = lpusUserSkill->GetSkillPnts( self );
         double dNewAC  = lpusUserSkill->GetSkillPnts( self ) > 125 ?
            (double)lpusUserSkill->GetSkillPnts( self )/(lpusUserSkill->GetSkillPnts( self )+5) * dAC :
         (double)lpusUserSkill->GetSkillPnts( self )/((double)lpusUserSkill->GetSkillPnts( self )+13.2) * dAC;
         
         dNewAC = dNewAC > 0 ? dNewAC : 0;
         
         double dBoust = dTA<200?(dTA/200) * (s_asBlow->TrueStrike/3.05):(s_asBlow->TrueStrike/3.05);
         double dDam   = s_asBlow->TrueStrike + dNewAC;
         
         
         s_asBlow->Strike = dDam + dBoust;
         
         if( ((Character*)self)->GetGodFlags() & GOD_DEVELOPPER )
         {
            CString csMessage;
            csMessage.Format( "dNewAC = %f", dNewAC );
            self->SendSystemMessage( csMessage );
            csMessage.Format( "dBoust = %f", dBoust );
            self->SendSystemMessage( csMessage );
            csMessage.Format( "dDam = %f", dDam );
            self->SendSystemMessage( csMessage );
            csMessage.Format( "s_asBlow->Strike = %f", s_asBlow->Strike );
            self->SendSystemMessage( csMessage );
         }
      }
   }
   return SKILL_NO_FEEDBACK;
}


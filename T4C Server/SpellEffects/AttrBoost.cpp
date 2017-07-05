// AttrBoost.cpp: implementation of the AttrBoost class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AttrBoost.h"
#include "../tfc_main.h"
#include "../t4clog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AttrBoost::AttrBoost()
{
    boRealtime = FALSE;
}

AttrBoost::~AttrBoost()
{

}

#define BOOST_MANA          0xF0


#define REMOVE_BOOST    dwEffectID

REGISTER_SPELL_EFFECT( ATTRBOOST, AttrBoost::NewFunc, ATTR_BOOST_EFFECT, NULL );

#define SAME( __text )  csParam.CompareNoCase( __text ) == 0

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADD_BOOSTv1{
    DWORD dwBoostID;
} ADD_BOOSTv1, *LPADD_BOOSTv1;

typedef struct _ADD_BOOST{
    DWORD dwBoostID;
    DWORD dwSpellID;
} ADD_BOOST, *LPADD_BOOST;

//////////////////////////////////////////////////////////////////////////////////////////
BOOL AttrBoost::InputParameter
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 CString csParam,   // Parameter value.
 WORD wParamID      // Parameter ID.
)
// Return: BOOL, TRUE if parameter was accepted.
//////////////////////////////////////////////////////////////////////////////////////////
{


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT BoostRealtime = 1;
    const INT BoostedStat = 2;
    const INT Boost = 3;



    BOOL boReturn = TRUE;
    int  nPos = 0;

    switch( wParamID ){
    case BoostRealtime:
        if( SAME( "true" ) ){
            boRealtime = TRUE;
        }
    break;
    case BoostedStat:
        // Check which stat was boosted
        if( SAME( "strength" ) || SAME( "str" ) ){
            wBoostedStat = STAT_STR;
        }else if( SAME( "agility" ) || SAME( "agi" ) ){
            wBoostedStat = STAT_AGI;
        }else if( SAME( "endurance" ) || SAME( "end" ) ){
            wBoostedStat = STAT_END;
		}else if( SAME( "luck" ) || SAME( "lck" ) ){
            wBoostedStat = STAT_LCK;
        }else if( SAME( "wisdom" ) || SAME( "wis" ) ){
            wBoostedStat = STAT_WIS;
        }else if( SAME( "intelligence" ) || SAME( "int" ) ){
            wBoostedStat = STAT_INT;
        }else if( SAME( "attack skill" ) || SAME( "attack" ) ){
            wBoostedStat = STAT_ATTACK;
        }else if( SAME( "dodge skill" ) || SAME( "dodge" ) ){
            wBoostedStat = STAT_DODGE;
        }else if( SAME( "damage" ) || SAME( "dam" ) ){
            wBoostedStat = STAT_DAMAGE;
        }else if( SAME( "radiance" ) ){
            wBoostedStat = STAT_RADIANCE;
        }else if( SAME( "mana" ) ){
            wBoostedStat = BOOST_MANA;
        }else if( SAME( "air resist" ) || SAME( "r_air" ) ){
            wBoostedStat = STAT_AIR_RESIST;
        }else if( SAME( "water resist" ) || SAME( "r_water" ) ){
            wBoostedStat = STAT_WATER_RESIST;        
        }else if( SAME( "fire resist" ) || SAME( "r_fire" ) ){
            wBoostedStat = STAT_FIRE_RESIST;
        }else if( SAME( "earth resist" ) || SAME( "r_earth" ) ){
            wBoostedStat = STAT_EARTH_RESIST;
        }else if( SAME( "air power" ) || SAME( "air" ) ){
            wBoostedStat = STAT_AIR_POWER;
        }else if( SAME( "water power" ) || SAME( "water" ) ){
            wBoostedStat = STAT_WATER_POWER;
        }else if( SAME( "fire power" ) || SAME( "fire" ) ){
            wBoostedStat = STAT_FIRE_POWER;
        }else if( SAME( "earth power" ) || SAME( "earth" ) ){
            wBoostedStat = STAT_EARTH_POWER;
        }else if( SAME( "light resist" ) || SAME( "r_light" ) ){
            wBoostedStat = STAT_LIGHT_RESIST;
        }else if( SAME( "dark resist" ) || SAME( "r_dark" ) ){
            wBoostedStat = STAT_DARK_RESIST;
        }else if( SAME( "light power" ) || SAME( "light" ) ){
            wBoostedStat = STAT_LIGHT_POWER;
        }else if( SAME( "dark power" ) || SAME( "dark" ) ){
            wBoostedStat = STAT_DARK_POWER;
        }else if( SAME( "ac" ) ){
            wBoostedStat = STAT_AC;
        }else if( SAME( "max hp" ) ){
            wBoostedStat = STAT_MAX_HP;
        }else if( SAME( "max mana" ) ){
            wBoostedStat = STAT_MAX_MANA;
        }else if( csParam.MakeLower(), nPos = csParam.Find( "skill " ) != -1 ){
            
            wBoostedStat = atoi( &((LPCTSTR)( csParam ))[ nPos + sizeof( "skill" ) - 1 ] );

            if( wBoostedStat == 0 ){                    
                boReturn = FALSE;
            }else{
                wBoostedStat += SKILL_BOOST_OFFSET;
            }
        }else{           
            boReturn = FALSE;
        }
    break;
    case Boost:
        if( !bBoost.SetFormula( csParam ) ){
            boReturn = FALSE;
        }
    break;
    default:
        boReturn = FALSE;
    break;
    }
    
    return boReturn;
}
//////////////////////////////////////////////////////////////////////////////////////////
void AttrBoost::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Conjures a boost.Conjures a monster or an object.
// 
(
 SPELL_EFFECT_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Attr boosts must have a target.
    if( target != NULL ){

        TRACE( "\r\nTrying to cast boost attr %u.", REMOVE_BOOST );
        
        // If this is a mana boost.
        if( wBoostedStat == BOOST_MANA ){
            int nMana = target->GetMana();

            nMana += (int)bBoost.GetBoost( self, target );

            if( nMana < 0 ){
                nMana = 0;
            }else{
                if( nMana > target->GetMaxMana() ){
                    nMana = target->GetMaxMana();
                }
            }
            
            target->SetMana( (WORD)nMana );
        }else{
    	    // Remove both the effect and the boost if it priorly existed.
		    target->RemoveEffect( REMOVE_BOOST );
            target->RemoveBoost( REMOVE_BOOST );

            // Get duration now.
            DWORD dwDuration = lpSpell->bfDuration.GetBoost( self, target );

            // If duration is non-null
            if( dwDuration != 0 ){
                
                TRACE( "\r\nBoosting stat #%u.", wBoostedStat );
                // If boost should be updated in realtime.
                // Add formula value to boost.
                target->AddBoost( REMOVE_BOOST, wBoostedStat, (int)bBoost.GetBoost( self, target ) );

                // If light spell
                if( wBoostedStat == STAT_RADIANCE ){
                    // Send light update.
                    TFCPacket sending;
                    sending << (RQ_SIZE)RQ_UnitUpdate;
                    target->PacketUnitInformation( sending );
                    Broadcast::BCast( target->GetWL(), _DEFAULT_RANGE, sending );
                }

                // If max HP or max Mana changed
                if( wBoostedStat == STAT_MAX_HP || wBoostedStat == STAT_MAX_MANA ){
                    // Send a status packet.
                    if( target->GetType() == U_PC ){
                        Character *ch = static_cast< Character * >( target );
                        TFCPacket sending;
                        ch->PacketStatus( sending );
                        ch->SendPlayerMessage( sending );
                    }
                }


                // Setup the add boost structure
                LPADD_BOOST lpAddBoost = new ADD_BOOST;
                lpAddBoost->dwBoostID = REMOVE_BOOST;
                lpAddBoost->dwSpellID = lpSpell->wSpellID;
        
#if 0
// ELx removed at Richard's request.
                _LOG_DEBUG
                    LOG_DEBUG_LVL1,
                    "Creating effect status on player!!"
                LOG_
#endif                
                // Create an effect status update for the client.
                CreateEffectStatus(
                    target,
                    lpSpell->wSpellID,
                    dwDuration,
                    dwDuration,
                    lpSpell
                );

                // Setup the effect on the target.
                CREATE_EFFECT(
                    target,
                    MSG_OnTimer,
                    REMOVE_BOOST,
                    BoostRemoval,
                    lpAddBoost,
                    dwDuration MILLISECONDS TDELAY,
                    dwDuration,
                    lpSpell->wSpellID,
                    0
                );
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void AttrBoost::BoostRemoval
//////////////////////////////////////////////////////////////////////////////////////////
// Called when timer expires and flag must be removed.
// 
(
 EFFECT_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	// Timer make the call to the function.
	if( wMessageID == MSG_OnTimer ){
        // Destroy the boost.
        LPADD_BOOST lpAddBoost = (LPADD_BOOST)lpEffectData;

        LPBOOST theBoost = self->GetBoost( lpAddBoost->dwBoostID );
        if( theBoost != NULL ){
            bool updateStatus = theBoost->wStat == STAT_MAX_HP || theBoost->wStat == STAT_MAX_MANA;

            self->RemoveBoost( lpAddBoost->dwBoostID );

            // If max HP or max Mana changed
            if( updateStatus ){
                // Send a status packet.
                if( self->GetType() == U_PC ){
                    Character *ch = static_cast< Character * >( self );
                    TFCPacket sending;
                    ch->PacketStatus( sending );
                    ch->SendPlayerMessage( sending );
                }
            }
        }

        TFCPacket sending;
        sending << (RQ_SIZE)RQ_UnitUpdate;
        self->PacketUnitInformation( sending );
        Broadcast::BCast( self->GetWL(), _DEFAULT_RANGE, sending );

        // Remove the effect from the client.
        DispellEffectStatus( self, lpAddBoost->dwSpellID );
    }else
    // Effect got dispelled.
    if( wMessageID == MSG_OnDispell ){
        // Destroy the boost.
        LPADD_BOOST lpAddBoost = (LPADD_BOOST)lpEffectData;

        LPBOOST theBoost = self->GetBoost( lpAddBoost->dwBoostID );
        if( theBoost != NULL ){        
            bool updateStatus = theBoost->wStat == STAT_MAX_HP || theBoost->wStat == STAT_MAX_MANA;

            self->RemoveBoost( lpAddBoost->dwBoostID );

            // If max HP or max Mana changed
            if( updateStatus ){
                // Send a status packet.
                if( self->GetType() == U_PC ){
                    Character *ch = static_cast< Character * >( self );
                    TFCPacket sending;
                    ch->PacketStatus( sending );
                    ch->SendPlayerMessage( sending );
                }
            }
        }


        TFCPacket sending;
        sending << (RQ_SIZE)RQ_UnitUpdate;
        self->PacketUnitInformation( sending );
        Broadcast::BCast( self->GetWL(), _DEFAULT_RANGE, sending );

        // Remove the effect from the client.
        DispellEffectStatus( self, lpAddBoost->dwSpellID );

        // Remove the effect
        self->RemoveEffect( dwEffect );
        
    }else
    // Player exited
    if( wMessageID == MSG_OnSavePlayer ){
        // Fetch the pointers
        LPADD_BOOST lpAddBoost = (LPADD_BOOST)lpEffectData;
		LPDATA_SAVE lpDataSave = (LPDATA_SAVE)lpUserData;
		// Prepare buffer to save on player
        lpDataSave->bBufferSize = sizeof( ADD_BOOST );
        lpDataSave->lpbData = new BYTE[ sizeof( ADD_BOOST ) ];        
        memcpy( lpDataSave->lpbData, lpAddBoost, sizeof( ADD_BOOST ) );        
    }else
    // Player loads
    if( wMessageID == MSG_OnLoadPlayer ){
        LPUNIT_EFFECT lpUnitEffect = (LPUNIT_EFFECT)lpEffectData;
        LPDATA_SAVE lpDataSave = (LPDATA_SAVE)lpUserData;

        LPADD_BOOST lpAddBoost = new ADD_BOOST;

        // Fetch the LPADD_BOOST
        if( lpDataSave->bBufferSize == sizeof( ADD_BOOST ) ){
            memcpy( lpAddBoost, lpDataSave->lpbData, sizeof( ADD_BOOST ) );

            // Get the spell
            LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpell( lpAddBoost->dwSpellID );

            if( lpSpell != NULL ){
                // Create an effect status update for the client.
                CreateEffectStatus(
                    self,
                    lpAddBoost->dwSpellID,
                    lpUnitEffect->dwTotalDuration == 0xFFFFFFFF ? 0xFFFFFFFF : ( lpUnitEffect->dwTimer - TFCMAIN::GetRound() ) * 50,
                    lpUnitEffect->dwTotalDuration,
                    lpSpell
                );
            }
        }else 
        // If its a 1st generation boost
        if( lpDataSave->bBufferSize == sizeof( ADD_BOOSTv1 ) ){
            ADD_BOOSTv1 v1;            
            memcpy( &v1, lpDataSave->lpbData, sizeof( ADD_BOOSTv1 ) );

            // Simply convert the boost.
            lpAddBoost->dwBoostID = v1.dwBoostID;
            lpAddBoost->dwSpellID = 0;
        }

        // Attach the boost structure to the effect.
        lpUnitEffect->lpData = lpAddBoost;
    }else
    // Effect is getting destroyed.
    if( wMessageID == MSG_OnDestroy ){
        // Delete the AddFlag structure associated to the effect.
        LPADD_BOOST lpAddBoost = (LPADD_BOOST)lpEffectData;
        delete lpAddBoost;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *AttrBoost::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// Create a SpellEffect object.
// 
(
 LPSPELL_STRUCT lpSpell // The spell structure for any spell effect registration.
)
// Return: SpellEffect, the spell effect. 
//////////////////////////////////////////////////////////////////////////////////////////
{
  // Register this spell's effect function.
  REGISTER_EFFECT( lpSpell->dwNextEffectID, BoostRemoval );
   
  CREATE_EFFECT_HANDLE( AttrBoost, 1 )
}
// HealthEffect.cpp: implementation of the HealthEffect class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "HealthEffect.h"
#include "../blockinglisting.h"
#include "../tfc_main.h"
#include "../Broadcast.h"
#include "../Game_Rules.h"
#include <math.h>
#include "../format.h"
#include "../Character.h"
#include "../T4CLog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


REGISTER_SPELL_EFFECT( HEALTH, HealthEffect::NewFunc, HEALTH_EFFECT, NULL );

HealthEffect::HealthEffect()
{

}

HealthEffect::~HealthEffect()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL HealthEffect::InputParameter
//////////////////////////////////////////////////////////////////////////////////////////
// Enters a parameters needed for this effect to work
// 
(
 CString csParam,    // The parameter value.
 WORD wParamID      // The parameter ID.
)
//////////////////////////////////////////////////////////////////////////////////////////
{


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT HealthBoost = 1;
    const INT RadialHealthBoost = 2;
    const INT Success = 3;
    


    BOOL boParamOK = TRUE;

    switch( wParamID ){
    // The standard spell health modifier for the target unit
    case HealthBoost:
        // If the given formula isn't valid
        if( !cHealth.SetFormula( csParam ) ){
            // Invalidate parameter.
            boParamOK = FALSE;
        }
        break;
    // Peripheral damage, this parameter can be null.
    case RadialHealthBoost:
        csParam.TrimRight();
        csParam.TrimLeft();
        
        // If the parameter doesn't exist, leave formula untouched (it will return 0).
        if( !csParam.IsEmpty() ){
            // If the given formula isn't valid
            if( !cRadialHealth.SetFormula( csParam ) ){
                // Invalidate parameter.
                boParamOK = FALSE;
            }
        } break;
    case Success:
        if( !successPercent.SetFormula( csParam ) ){
            return FALSE;
        }
        break;
    default:
        boParamOK = FALSE;
        break;
    }

    return boParamOK;
}

//////////////////////////////////////////////////////////////////////////////////////////
int HealthEffect::DoUnitDamage
//////////////////////////////////////////////////////////////////////////////////////////
// Deals damage to a unit
// 
(
 Unit *self,                // Unit dealing damage.
 Unit *target,              // Unit target of damage.
 LPSPELL_STRUCT lpSpell,    // Spell effect dealing damage.
 double dblDamage           // Damage to deal.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TRACE( "\r\nself=%u, target=%u",
        self->GetUnderBlock(),
        target->GetUnderBlock()
    );
    // Return if any of the two opponents are in a safe area.
    if( (self->GetUnderBlock() == __SAFE_HAVEN || self->GetUnderBlock() == __INDOOR_SAFE_HAVEN ||
	    target->GetUnderBlock() == __SAFE_HAVEN || target->GetUnderBlock() == __INDOOR_SAFE_HAVEN )
        && target->GetType() == U_PC && self->GetType() == U_PC ){
        return 0;
    }
    // Quantity of damage dealt.
    int nDamage = 0;


    // If the two units are in PVP
    if( GAME_RULES::InPVP( self, target ) ){
    
        double dblHealth = dblDamage;

        // Avoid unnecessary damage calculation if no damage was dealt.
        if( dblHealth != 0 ){
            // Organise an attack.
            ATTACK_STRUCTURE Blow = {0,0,0,0,0};

            Blow.Strike = -dblHealth;            

            TRACE( "Blow->Strike=%f.", Blow.Strike );
            target->Lock();
        
            double dblPreACstrike = Blow.Strike;

            // If this is a 'physical' spell.
			nDamage = Blow.Strike;
            target->attacked( &Blow, NULL );
			if( lpSpell->bDamageType == ATTACK_PHYSICAL )
			{
                Blow.Strike = Blow.Strike > 0 ? Blow.Strike : 0;
				nDamage = Blow.Strike;
			}
			else
				Blow.Strike = nDamage;
			// Then process 'attack' with a NULL unit.            
           	
            if( self->GetType() == U_PC ){
                Players *lpPlayer = static_cast< Character *>( self )->GetPlayer();
                if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                    TFormat format;
                    self->SendSystemMessage(
                        format(
                            "Spell %u hits %s for %.2f damages (%.2f post-AC damages).",
                            lpSpell->wSpellID,
                            (LPCTSTR)target->GetName(_DEFAULT_LNG),
                            dblPreACstrike,
                            Blow.Strike
                        )
                    );
                }
            }
            if( target->GetType() == U_PC ){
                Players *lpPlayer = static_cast< Character *>( target )->GetPlayer();
                if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                    TFormat format;
                    target->SendSystemMessage(
                        format(
                            "%s casts spell %u on you for %.2f damages (%.2f post-AC damages).",                            
                            (LPCTSTR)self->GetName(_DEFAULT_LNG),
                            lpSpell->wSpellID,
                            dblPreACstrike,
                            Blow.Strike
                        )
                    );
                }
            }


            // Hit target with blast.
            if( target->hit( &Blow, self ) == -1 ){
		        // Tell everyone that the "thing" died
                Broadcast::BCObjectChanged( target->GetWL(), _DEFAULT_RANGE,//BLBLBL _DEFAULT_RANGE+5=>_DEFAULT_RANGE
                    target->GetCorpse(),
                    target->GetID()
                );
            }

            // If the blow did damage to the unit.
            if( Blow.Strike != 0 ){
                // Broadcast HP change.
                TFCPacket sending;
                sending << (RQ_SIZE)RQ_UnitUpdate;
                target->PacketUnitInformation( sending );

                Broadcast::BCast( target->GetWL(), _DEFAULT_RANGE, sending );
            }

            self->TrainUnit();

            target->Unlock();
        }
    }

    // Return the quantity of damage delt. Damage is NEGATIVE
    return( -nDamage );
}

//////////////////////////////////////////////////////////////////////////////////////////
int HealthEffect::DoUnitHealing
//////////////////////////////////////////////////////////////////////////////////////////
// Heals the current target.
// 
(
 Unit *self,                // Caster.
 Unit *target,              // Target of healing.
 LPSPELL_STRUCT lpSpell,    // Spell.
 double dblHealth           // Health to heal.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    target->Lock();
    
    int nHP = target->GetHP();
    int nOldHP = nHP;

    TRACE( "\r\nHealing target for %d damage", (int)dblHealth );

    TRACE( ", HP Before=%d. ", nHP );
    nHP += (int)dblHealth;
    TRACE( ", HP After=%d. ", nHP );

    if( self->GetType() == U_PC ){
        Players *lpPlayer = static_cast< Character *>( self )->GetPlayer();
        if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
            TFormat format;
            self->SendSystemMessage(
                format(
                    "Spell %u healed %s for %f hp.",
                    lpSpell->wSpellID,
                    (LPCTSTR)target->GetName(_DEFAULT_LNG),
                    dblHealth
                )
            );
        }
    }else
    if( target->GetType() == U_PC ){
        Players *lpPlayer = static_cast< Character *>( target )->GetPlayer();
        if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
            TFormat format;
            target->SendSystemMessage(
                format(
                    "%s casts spell %u on you, which healed %f hp.",                    
                    (LPCTSTR)self->GetName(_DEFAULT_LNG),
                    lpSpell->wSpellID,
                    dblHealth
                )
            );
        }
    }


    // If health would mean giving too much HP
    if( nHP >= (int)target->GetMaxHP() ){
        // Set unit's HP to max.
        target->SetHP( target->GetMaxHP(), true );
    }else{
        // Set the new unit's HP.
        target->SetHP( nHP, true );
    }

    target->Unlock();

	TFCPacket sending;
	sending << (RQ_SIZE)RQ_HPchanged;
	sending << (long)target->GetHP();
	sending << (long)target->GetMaxHP();
	target->SendPlayerMessage( sending );

    sending.Destroy();
    sending << (RQ_SIZE)RQ_UnitUpdate;
    target->PacketUnitInformation( sending );

    Broadcast::BCast( target->GetWL(), _DEFAULT_RANGE, sending );


    // Returns the quantity of healt given.
    return (int)dblHealth;
}

//////////////////////////////////////////////////////////////////////////////////////////
int HealthEffect::DealHealthEffect
//////////////////////////////////////////////////////////////////////////////////////////
//  Deals the health effect. Also usefull for derivative functions.
// 
(
 SPELL_EFFECT_PROTOTYPE // The spell effect prototype.
)
// Return: int, the quantity of damage totally dealt.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Default center is the spell's target position
    double dblHealth;

    int nTotalDamage = 0;
    
    // If there is a unit in center.
    if( target == NULL ){
        return 0;
    }

    // If spell failed.
    static Random rnd;
    if( rnd( 1, 100 ) > successPercent.GetBoost( self, target, 0, 0, range ) ){
        return 0;
    }

    if( range == 0 ){
        dblHealth = cHealth.GetBoost( self, target );
    }else{
        dblHealth = cRadialHealth.GetBoost( self, target, 0, 0, range );
    }
         
    // If this does damage.
    if( dblHealth < 0 ){
        // Deal damage.
        nTotalDamage += DoUnitDamage( self, target, lpSpell, dblHealth );
    }else{
        // Heal target.
        nTotalDamage += DoUnitHealing( self, target, lpSpell, dblHealth );
    }

    return nTotalDamage;
}

//////////////////////////////////////////////////////////////////////////////////////////
void HealthEffect::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Does the spell effect.
// 
(
 SPELL_EFFECT_PROTOTYPE // The spell effect variables.
)
//////////////////////////////////////////////////////////////////////////////////////////
{    
    // Simply deal health effect.
    DealHealthEffect( SPELL_EFFECT_PARAMS );
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *HealthEffect::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// Returns a pointer to a HealthEffect object.
// 
(
 LPSPELL_STRUCT lpSpell
)
// Return: SpellEffect, The returned spelleffect object
//////////////////////////////////////////////////////////////////////////////////////////
{    
    CREATE_EFFECT_HANDLE( HealthEffect, 0 );
}


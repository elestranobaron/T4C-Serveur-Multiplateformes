// SpellMessageHandler.cpp: implementation of the SpellMessageHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "SpellMessageHandler.h"
#include "Broadcast.h"
#include "TFC_MAIN.h"
#include "BlockingListing.h"
#include <math.h>
#include "format.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

LPSPELL_STRUCT SpellMessageHandler::lpSpellTable[ MAX_SPELLS ];

extern Random rnd;

//////////////////////////////////////////////////////////////////////////////////////////
void SpellMessageHandler::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creates the spell message handler
// 
//////////////////////
////////////////////////////////////////////////////////////////////
{
	int i;
	// Init the proc table to NULL
	for( i = 0; i < MAX_SPELLS; i++ ){
		lpSpellTable[ i ] = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void SpellMessageHandler::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroys all registered spells.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	int i;
	// Init the proc table to NULL
	for( i = 0; i < MAX_SPELLS; i++ ){
        if( lpSpellTable[ i ] != NULL ){
//		    delete lpSpellTable[ i ]->lpszSpellName;
            lpSpellTable[ i ]->tlEffects.AnnihilateList();
            lpSpellTable[ i ]->saAttrib.tlSkillRequired.AnnihilateList();
        
            lpSpellTable[ i ]->Delete();
        }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void SpellMessageHandler::RegisterSpell
//////////////////////////////////////////////////////////////////////////////////////////
// Registers a spell for use.
// 
(
 WORD wSpellID,					// unique ID of the spell.
 LPSPELL_STRUCT lpSpellStruct	// Procedure attached to spell.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( wSpellID >= SPELL_ID_OFFSET ){
		if( wSpellID - SPELL_ID_OFFSET < MAX_SPELLS ){
			if( lpSpellTable[ wSpellID - SPELL_ID_OFFSET ] ){
                _LOG_DEBUG
                    LOG_DEBUG_LVL1,
                    "Found duplicate spell ID %u, unregistering previous one. (overriding it)",
                    wSpellID
                LOG_

                lpSpellTable[ wSpellID - SPELL_ID_OFFSET ]->Delete();
			}

            TRACE( "\r\nRegistering spell ID %u", wSpellID );
			lpSpellTable[ wSpellID - SPELL_ID_OFFSET ] = lpSpellStruct;
			
		}else{
			CString TheText;
			TheText.Format(
				"Tried to register the spell ID %u which is beyond the maximum number of spells. Spell Name: %s (Desc: %s)",
				wSpellID,
				lpSpellStruct->GetName(_DEFAULT_LNG),
				lpSpellStruct->GetDesc(_DEFAULT_LNG).c_str()
			);
			//Removed the message box. Message is now getting sent to the DEBUG LOG
			//Messagebox makes server shutdown and never go back till the sysop go to the console and clicks ok.
			//MessageBox( NULL, TheText, "DLL error", MB_OK );
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				TheText
			LOG_
		}
	}else{
		CString TheText;
		TheText.Format( 
			"Tried to register the spell ID %u which is below the lowest available spell ID. Spell Name: %s (Desc: %s)",
			wSpellID,
			lpSpellStruct->GetName(_DEFAULT_LNG),
			lpSpellStruct->GetDesc(_DEFAULT_LNG)
		);
		//Removed the message box. Message is now getting sent to the DEBUG LOG
		//Messagebox makes server shutdown and never go back till the sysop go to the console and clicks ok.
		//MessageBox( NULL, TheText, "DLL error", MB_OK );
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
			TheText
		LOG_
	}
}

inline bool IsTargetOK( LPSPELL_STRUCT lpSpell, Unit *self, Unit *target ){
    if( target == NULL ){
        return false;
    }

    switch( lpSpell->bTarget ){                    
    ////////////////////////////
    case TARGET_UNIT_ANY_FAVOR_PC:
    case TARGET_UNIT_ANY: break;
    ////////////////////////////
    case TARGET_UNIT_OBJECT:
        if( target->GetType() != U_OBJECT ){
            return false;
        } break;
    ////////////////////////////
    case TARGET_UNIT_NPC:
        if( target->GetType() != U_NPC ){
            return false;
        } break;
    ////////////////////////////
    case TARGET_UNIT_PC:
        if( target->GetType() != U_PC ){
            return false;
        } break;
    ////////////////////////////
    case TARGET_UNIT_LIVING_FAVOR_PC:
    case TARGET_UNIT_LIVING_FAVOR_NPC:
    case TARGET_UNIT_LIVING:
        if( target->GetType() != U_PC && target->GetType() != U_NPC ){
            return false;
        } break;
    ////////////////////////////
    case TARGET_SELF:     break;
    ////////////////////////////
    case TARGET_POSITION: break;
    ////////////////////////////
    case TARGET_UNIT_PC_NONSELF:                            
        if( target == self ){                                                                
            return false;
        }else if( target->GetType() != U_PC ){
            return false;
        }
        break;
    ////////////////////////////
    case TARGET_UNIT_LIVING_FAVOR_NPC_NONSELF:
    case TARGET_UNIT_LIVING_NONSELF:
        if( target == self ){
            return false;
        }else if( target->GetType() != U_NPC && target->GetType() != U_PC ){
            return false;
        }
        break;
    ////////////////////////////
    case TARGET_UNIT_ANY_NONSELF:
        if( target == self ){
            return false;
        }
        break;
    case TARGET_GROUP_SELF:
        if( self == target ){
            return true;
        }
    case TARGET_GROUP_UNIT:    
    case TARGET_GROUP_POSITION:{
        // Non-PC casters don't have groups.
        if( self->GetType() != U_PC ){
            return false;
        }
        
        // The caster is always a member of its own group.
        if( self == target ){
            return true;
        }
        
        // Must target PCs.
        if( target->GetType() != U_PC ){
            return false;
        }

        Character *selfCh = static_cast< Character * >( self );
        Character *targetCh = static_cast< Character * >( target );

        // If the caster isn't in a group.
        if( selfCh->GetGroup() == NULL ){
            return false;
        }
        // If the target character isn't in the caster's group.
        if( !selfCh->GetGroup()->IsGroupMember( targetCh ) ){
            return false;
        }

    } break;
    case TARGET_NONGROUP_SELF:
        if( target == self ){
            return false;
        }
    case TARGET_NONGROUP_UNIT:    
    case TARGET_NONGROUP_POSITION:
        // Cannot target self nor can caster be a non-PC.
        if( target == self ){
            return false;
        }
        // If caster isn't a PC it cannot be in a group.
        if( self->GetType() != U_PC ){
            return true;
        }

        // Only check PC characters.
        if( target->GetType() == U_PC ){
            Character *selfCh = static_cast< Character * >( self );
            Character *targetCh = static_cast< Character * >( target );

            // If the player isn't in a group.
            if( selfCh->GetGroup() == NULL ){
                return true;
            }
                
            // If the target character is in the caster's group.
            if( selfCh->GetGroup()->IsGroupMember( targetCh ) ){
                return false;
            }
        }
    }
    
    return true;
}

inline bool SafeMultiLock( CLock *cLockL, CLock *cLockR, DWORD maxTry = 10 ){
    DWORD tries = 0;
    cLockL->Lock();
    while( !cLockR->PickLock() ){
        cLockL->Unlock();
        Sleep( 0 );
        tries++;
        if( tries >= maxTry ){
            return false;
        }
        cLockL->Lock();
    }
    return true;
}


//////////////////////////////////////////////////////////////////////////////////////////
static bool CastSpell
//////////////////////////////////////////////////////////////////////////////////////////
// Casts the spell
// 
(
 LPSPELL_STRUCT lpSpell,
 Unit *self,
 Unit *target,
 WorldPos wlPos,
 double range
)
// Return: static BOOL, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Lock the involved units
    if( target != NULL ){
        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "[spell]Self=0x%x, Target=0x%x",
            self,
            target
        LOG_       
        
        // If the two units were not locked within reasonable time, abort.
        if( !SafeMultiLock( self, target ) ){
            return false;
        }

        // Virtually create the unit.
        target->CreateVirtualUnit();
    }else{
        self->Lock();
    }

    if( target == NULL ){
        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "Spell %u triggered. Caster %s (ID %u). Target is caster.",
            lpSpell->wSpellID,
            self->GetName(_DEFAULT_LNG),
            self->GetID()
        LOG_
    }else{
        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "Spell %u triggered. Caster %s (ID %u). Target is %s (ID %u).",
            lpSpell->wSpellID,
            (LPCTSTR)self->GetName(_DEFAULT_LNG),
            self->GetID(),
            (LPCTSTR)target->GetName(_DEFAULT_LNG),
            target->GetID()
        LOG_
    }


    lpSpell->tlEffects.Lock();
    lpSpell->tlEffects.ToHead();
    // Call each effect on spell.
    while( lpSpell->tlEffects.QueryNext() ){
        lpSpell->tlEffects.Object()->CallEffect( self, NULL, target, wlPos, range );
    }
    lpSpell->tlEffects.Unlock();

    // Unlock resources.
    self->Unlock();
    if( target != NULL ){
        target->Unlock();

        // Delete the unit's virtual image. See the preceeding target->CreateVirtualUnit()
        target->DeleteUnit();
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL SpellMessageHandler::ActivateSpell
//////////////////////////////////////////////////////////////////////////////////////////
// Activates a spell
// 
(
 SPELL_PROC_PROTOTYPE // Spell prototype
)
// Return: BOOL, TRUE if spell succeeded. Specific to the spell
//////////////////////////////////////////////////////////////////////////////////////////
{
    // *must* have a self.
    if( self == NULL ){
        return FALSE;
    }


       /*         _LOG_DEBUG
                    LOG_DEBUG_LVL4,
                    "Activating spell ID %u",
                    wSpellID
                LOG_
    */

    WorldMap *wlWorld = TFCMAIN::GetWorld( self->GetWL().world );

    // Spell must affect a valid world.
    if( wlWorld == NULL ){
        return FALSE;
    }
    TRACE( "Trying to cast spell ID %u.", wSpellID );

	// If the spellID is not within the spell table.
    if( wSpellID < SPELL_ID_OFFSET || ( wSpellID - SPELL_ID_OFFSET ) >= MAX_SPELLS ){
        return FALSE;
    }
	if( lpSpellTable[ wSpellID - SPELL_ID_OFFSET ] == NULL ){
        return FALSE;
    }

    LPSPELL_STRUCT lpSpell = lpSpellTable[ wSpellID - SPELL_ID_OFFSET ];

    // If the spell is a self spell
    if( lpSpell->bTarget == TARGET_SELF || 
        lpSpell->bTarget == TARGET_GROUP_SELF ||
        lpSpell->bTarget == TARGET_NONGROUP_SELF ){
        target = self;
    }

    // If the spell fails.
    if( ( static_cast< double >( rnd( 1, 100000 ) ) / 1000 ) > lpSpell->successPercentage.GetBoost( self, target ) ){
        return FALSE;
    }

    // If this spell requires PVP check before casting.
    if( lpSpell->boPVPcheck && target != NULL ){
        if( !GAME_RULES::InPVP( self, target ) ){
            // Sends a 'cannot cast spell because of pvp blabla' msg to caster.
            self->SendSystemMessage( _STR( 463, self->GetLang() ) );
            return FALSE;
        }
        // Return if any of the two opponents are in a safe area.
        if( (self->GetUnderBlock() == __SAFE_HAVEN || self->GetUnderBlock() == __INDOOR_SAFE_HAVEN ||
	        target->GetUnderBlock() == __SAFE_HAVEN || target->GetUnderBlock() == __INDOOR_SAFE_HAVEN )//BLBLBL faudrait ptet changer la règle ici pour tester le areatype au lieu du underblock de l'unité pour éviter les risques de changement de case
            && target->GetType() == U_PC && self->GetType() == U_PC ){
            // Sends a 'cannot cast spell because of pvp blabla' msg to caster.
            self->SendSystemMessage( _STR( 463, self->GetLang() ) );
            return FALSE;
        }
    }

    // Determine the starting and ending course
    WorldPos wlFrom = self->GetWL();
    WorldPos wlTo   = target == NULL ? wlPos : target->GetWL();
       
    // If spell requires a line of sight, and spell isn't targetted to self.
    if( lpSpell->nLineOfSight != 0 && target != self ){
        // Determine the starting and ending course
        Unit *lpCollisionUnit = NULL;
        
        WorldPos wlCollidePos = { 0, 0, 0 };
   
        // If a collision was detected.
        if( wlWorld->GetCollisionPos( wlFrom, wlTo, &wlCollidePos, &lpCollisionUnit, false ) ){                            
            // Setup new target according to the collision pos.
            target = lpCollisionUnit;
            // Set the collide pos as the spell's target pos.
            wlPos = wlCollidePos;                                
        }
    }else if( target != NULL ){
        wlPos = target->GetWL();
    }
    
    // If there is a target which is not targettable.
    if( target != NULL && !IsTargetOK( lpSpell, self, target ) && lpSpell->bTarget != TARGET_NONGROUP_SELF ){
        // Send a 'wrong unit' message.
        self->SendSystemMessage( _STR( 470, self->GetLang() ) );
        return FALSE;
    }

    if( lpSpell->bTarget == TARGET_NONGROUP_SELF ){
        wlPos = self->GetWL();
        target = NULL;
    }

    DWORD masterEffectId = 0;

    // If there is a visual effect associated with the spell.
    if( lpSpell->wVisualEffect != 0 ){
        DWORD dwTargetID;
        WorldPos wlTargetPos;

        // If a victim was selected.
        if( target != NULL ){
            // The target is the victim.
            dwTargetID  = target->GetID();
            wlTargetPos = target->GetWL();
        }else{
            // Otherwise use the specified position as target.
            dwTargetID  = 0;
            wlTargetPos = wlPos;
        }

        TRACE( "\r\nSending spell effect %u from ID %u to ID %u at ( %u, %u )",
            lpSpell->wVisualEffect,
            self->GetID(),
            dwTargetID,
            wlTargetPos.X,
            wlTargetPos.Y
        );

        masterEffectId = GetNextGlobalEffectID();

        Broadcast::BCSpellEffect( self->GetWL(), _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
            lpSpell->wVisualEffect,
            self->GetID(),
            dwTargetID,
            self->GetWL(),
            wlTargetPos,
            masterEffectId,
            0
        );
    }

    // Deal the spell's exhaust.
    DWORD dwTempAttackExhaust = lpSpell->sInducedExhaust.bfAttack.GetBoost( self, target );
	DWORD dwTempMentalExhaust = lpSpell->sInducedExhaust.bfMental.GetBoost( self, target );
	DWORD dwTempMoveExhaust   = lpSpell->sInducedExhaust.bfMove.GetBoost( self, target );

	if (dwTempAttackExhaust||dwTempMentalExhaust||dwTempMoveExhaust){//BLBLBL on n'exhaust que si il y a un changement
		self->DealExhaust( 
			/*lpSpell->sInducedExhaust.bfAttack.GetBoost( self, target ),
			lpSpell->sInducedExhaust.bfMental.GetBoost( self, target ),
			lpSpell->sInducedExhaust.bfMove.GetBoost( self, target )*/
			dwTempAttackExhaust,
			dwTempMentalExhaust,
			dwTempMoveExhaust
		);
	}

    // Cast the spell which hits the center unit.
    bool success = CastSpell( lpSpell, self, target, wlPos, 0 );

    // Area effects
    
    // If this is not an area effect.
    if( lpSpell->bRange == 0 ){
        return success;
    }

    // The spell's center area.
    WorldPos wlCenter = wlPos;

    // Get X & Y starting position as well as X & Y extension.
    int nMinX = wlCenter.X - lpSpell->bRange;
    nMinX = nMinX < 0 ? 0 : nMinX;
    
    int nMinY = wlCenter.Y - lpSpell->bRange;
    nMinY = nMinY < 0 ? 0 : nMinY;
    
    int nMaxX = wlCenter.X + lpSpell->bRange;
    nMaxX = nMaxX >= (int)wlWorld->GetMAXX() ? (int)wlWorld->GetMAXX() - 1 : nMaxX;

    int nMaxY = wlCenter.Y + lpSpell->bRange;
    nMaxY = nMaxY >= (int)wlWorld->GetMAXY() ? (int)wlWorld->GetMAXY() - 1 : nMaxY;

    // Scroll through the area.
    int x, y;
    
    DWORD centeredId;    
    WorldPos centeredPos;
    if( target == NULL ){
        centeredPos = wlPos;
        centeredId = 0;
    }else{
        centeredPos = target->GetWL();
        centeredId = target->GetID();
    }

    
    for( x = nMinX; x < nMaxX; x++ ){
        for( y = nMinY; y < nMaxY; y++ ){                        
            // Get relative X and Y
            int relX = ( x - wlCenter.X );
            int relY = ( y - wlCenter.Y );
            // If position is dead center.
            if( relX == 0 && relY == 0 ){
                // Already processed
                continue;
            }

            // Find the ray length of this point.
            double dblRay = sqrt((double) relX * relX + relY * relY ); // steph ajout de (double)

            // If the ray is not within the spell's range.
            if( dblRay >= lpSpell->bRange ){
                continue;
            }
            
            WorldPos wlTopUnitPos = { x, y, wlCenter.world };
                
            // Get the unit standing on this spot.
            target = wlWorld->ViewTopUnit( wlTopUnitPos );
            
            // If a no unit was found at this position.
            if( target == NULL ){
                continue;
            }
            // Do not target hives.
            if( target->GetType() == U_HIVE || target->GetType() == U_OBJECT ){
                continue;
            }
            // If its a player
            if( target->GetType() == U_PC ){
                // Check if it has true invisibility or not.
                Character *ch = static_cast< Character * >( target );
                Players *pl = reinterpret_cast< Players * >( ch->GetPlayer() );
                if( pl != NULL ){
                    if( pl->GetGodFlags() & GOD_TRUE_INVISIBILITY ){
                        continue;
                    }
                }
            }

            // If unit is not targettable by spell.
            if( !IsTargetOK( lpSpell, self, target ) ){
                continue;
            }
            // If the spell requires PVP check with target.
            if( lpSpell->boPVPcheck ){
                // If players are not in PVP.
                if( !GAME_RULES::InPVP( self, target ) ){
                    continue;
                }
            }

            // Determine the starting and ending course
            Unit *lpCollisionUnit = NULL;                       
            WorldPos wlCollidePos = { 0, 0, 0 };

            // If a collision was detected between the center of the spell effect and the target position                
            // Wall crossing effect
			if( wlWorld->GetCollisionPos( wlCenter, target->GetWL(), &wlCollidePos, &lpCollisionUnit, false, false ) ){
                // Do not cast effect.
                continue;
            }

            wlPos = target->GetWL();

            // If a range spell blast effect was specified.
            if( lpSpell->wRangeVisualEffect != 0 ){
                Broadcast::BCSpellEffect( wlPos, _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
                    lpSpell->wRangeVisualEffect, // Spell effect ID.
                    centeredId,           // Caster's ID.
                    target->GetID(),         // Target ID
                    centeredPos,         // Caster's position.
                    wlPos,                // Target position
                    GetNextGlobalEffectID(),
                    masterEffectId
                );
            }

            // Cast the spell in the unit that got blasted.
            CastSpell( lpSpell, self, target, wlPos, dblRay );
        }
    }

    return success;
}

/////////////////////////////////////////////////////////////////////////////////////////
LPSPELL_STRUCT SpellMessageHandler::GetSpell
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the spell structure of a given spell.
// 
(
 WORD wSpellID // The spell Id if the spell to get.
)
// Return: LPSPELL_STRUCT, The spell structure returned
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPSPELL_STRUCT lpSpellStruct = NULL;
	if( wSpellID >= SPELL_ID_OFFSET ){
		if( ( wSpellID - SPELL_ID_OFFSET ) < MAX_SPELLS ){
			TRACE( "\r\nQueried spell structure %u", wSpellID );
			lpSpellStruct = lpSpellTable[ wSpellID - SPELL_ID_OFFSET ];
		}else{
			TRACE( "\r\nFailed to obtain spell structure %u", wSpellID );
		}
	}

	
	return lpSpellStruct;
}

//////////////////////////////////////////////////////////////////////////////////////////
LPSPELL_STRUCT SpellMessageHandler::GetSpellByName
//////////////////////////////////////////////////////////////////////////////////////////
//  Gets the spell structure which has the specified name.
// 
(
 std::string spellName, // The spell name.
 WORD wLang
)
// Return: LPSPELL_STRUCT, NULL if spell not found.
//////////////////////////////////////////////////////////////////////////////////////////
{
    LPSPELL_STRUCT lpSpellStruct = NULL;
    int i;
    for( i = 0; i < MAX_SPELLS; i++ ){    
        LPSPELL_STRUCT lpSpellStruct = lpSpellTable[ i ];
        if( lpSpellStruct != NULL && 
            stricmp( lpSpellStruct->GetName( wLang ), spellName.c_str() ) == 0 ){
            return lpSpellStruct;
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL SpellMessageHandler::IsSpellLearnable
//////////////////////////////////////////////////////////////////////////////////////////
// Tests if the skill can be learned.
// 
(
 WORD wSpellID,		// The ID of the skill to query.
 Unit *uLearner,	// Unit which should learn the skill.
 CString &reqText   // Holds the requirements description.
)
// Return: BOOL, TRUE if the spell can be learned.
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( wSpellID - SPELL_ID_OFFSET < MAX_SPELLS ){
		LPSPELL_STRUCT lpSpell = lpSpellTable[ wSpellID - SPELL_ID_OFFSET ];
	
		if( lpSpell ){
            TFormat format;

			LPSKILL_ATTRIBUTES lpAttrib = &lpSpell->saAttrib;
			/*	s_saAttrib.Class
				s_saAttrib.Cost;
				s_saAttrib.Level;
				s_saAttrib.AGI;
				s_saAttrib.STR;
				s_saAttrib.END;
				s_saAttrib.INT;
				s_saAttrib.WIS;
				s_saAttrib.ClassPnts[WARRIOR];
				s_saAttrib.ClassPnts[MAGE];
				s_saAttrib.ClassPnts[THIEF];
				s_saAttrib.ClassPnts[PRIEST];
				s_saAttrib.tlSkillRequired;
			*/	

            // Form the description string.
            reqText = _STR( 7277, uLearner->GetLang() );
            bool prev = false;
            bool nothin = true;
            if( lpAttrib->Level != 0 ){
                reqText += format( _STR( 7278, uLearner->GetLang() ), lpAttrib->Level );;
                prev = true;
                nothin = false;
            }
            if( lpAttrib->INT != 0 ){
                if( prev ){
                    reqText += ", ";
                }                
                reqText += format( _STR( 7282, uLearner->GetLang() ), lpAttrib->INT );
                prev = true;
                nothin = false;
            }
            if( lpAttrib->WIS != 0 ){
                if( prev ){
                    reqText += ", ";
                }                
                reqText += format( _STR( 7283, uLearner->GetLang() ), lpAttrib->WIS );
                prev = true;
                nothin = false;
            }

            if( lpAttrib->tlSkillRequired.NbObjects() != 0 ){
                if( prev ){
                    reqText += _STR( 7284, uLearner->GetLang() );
                }
                nothin = false;
                
                if( lpAttrib->tlSkillRequired.NbObjects() > 1 ){
                    reqText += _STR( 7288, uLearner->GetLang() );
                }else{
                    reqText += _STR( 7289, uLearner->GetLang() );
                }
                lpAttrib->tlSkillRequired.ToHead();
                if( lpAttrib->tlSkillRequired.QueryNext() ){
                    LPUSER_SKILL lpRequired = lpAttrib->tlSkillRequired.Object();
                    LPSPELL_STRUCT lpSpell = GetSpell( lpRequired->GetSkillID() );
                    if( lpSpell != NULL ){
                        reqText += lpSpell->GetName( uLearner->GetLang() );   
                    }
                        
                    while( lpAttrib->tlSkillRequired.QueryNext() ){
                        reqText += ", ";
                        lpRequired = lpAttrib->tlSkillRequired.Object();
                        LPSPELL_STRUCT lpSpell = GetSpell( lpRequired->GetSkillID() );
                        if( lpSpell != NULL ){
                            reqText += lpSpell->GetName( uLearner->GetLang() );   
                        }           
                    }
                }
            }
            if( nothin ){
                reqText += _STR( 7286, uLearner->GetLang() );
            }else{
                reqText += ".";
            }


			if(lpAttrib->Level <= (int)uLearner->GetLevel()){
				if(/* lpAttrib->AGI <= uLearner->GetAGI() && 
					lpAttrib->STR <= uLearner->GetSTR() &&
					lpAttrib->END <= uLearner->GetEND() &&*/
					lpAttrib->INT <= uLearner->GetTrueINT() &&
					lpAttrib->WIS <= uLearner->GetTrueWIS()/* &&
					lpAttrib->WIL <= uLearner->GetWIL() &&
					lpAttrib->LCK <= uLearner->GetLCK()*/){
					
					BOOL boOK = TRUE;
					LPUSER_SKILL lpRequired;
					LPUSER_SKILL lpUserSkill;
					lpAttrib->tlSkillRequired.Lock();
					lpAttrib->tlSkillRequired.ToHead();
					while( lpAttrib->tlSkillRequired.QueryNext() && boOK ){
						lpRequired = lpAttrib->tlSkillRequired.Object();

						lpUserSkill = uLearner->GetSkill( lpRequired->GetSkillID() );
						// If user doesn't have the spell
						if( !lpUserSkill ){
							// Cannot learn if user doesn't have a required spell.
							boOK = FALSE;
						}
					}
					lpAttrib->tlSkillRequired.Unlock();

					return boOK;
				}
			}
		}
	}
	return FALSE;
}

DWORD GetNextGlobalEffectID(){
    static DWORD globalEffectID = 1;
    InterlockedIncrement( (long*)&globalEffectID );
    return globalEffectID;
}
// Rob.cpp: implementation of the Rob class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Rob.h"
#include "Peek.h"
#include <math.h>
#include "../blockinglisting.h"
#include "../intltext.h"
#include "../ObjectListing.h"
#include "../t4clog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Rob::Rob()
{
	s_saAttrib.Class = 0;
	s_saAttrib.Cost = 1;
	s_saAttrib.Level = 17;
	s_saAttrib.AGI = 50;
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

	ADD_REQUIRED_SKILL( __SKILL_PEEK, 25 )
}

//////////////////////////////////////////////////////////////////////////////////////////
void Rob::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
//	Destroys peek.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
}

LPSKILLPNTFUNC Rob::lpOnAddPnts = NULL;

#define ROB_SKILL	lpusUserSkill->GetSkillPnts( self )

//////////////////////////////////////////////////////////////////////////////////////////
int Rob::Func
//////////////////////////////////////////////////////////////////////////////////////////
// Critical strike main function
// 
(
 DWORD dwReason,			// Hook which was used to call the skill.
 Unit *self,				// Unit using the skill.
 Unit *medium,				// Unused.
 Unit *target,				// Target of attack.
 void *valueIN, 			// LPATTACK_STRUCTURE, current blow.
 void *valueOUT,			// Unused.
 LPUSER_SKILL lpusUserSkill // Current skill strength of the user.
)
// Return: int, SKILL_* return parameter.
//////////////////////////////////////////////////////////////////////////////////////////
{	 
	const INT PeekRange = 2; // steph ajout de INT

	// Requires both target and self to be present.
	if( !target || !self ) return SKILL_NO_FEEDBACK;

	// Skill only works on OTHER characters.
	if( self->GetType() != U_PC || target->GetType() != U_PC || self == target ){
		self->RemoveFlag( __FLAG_ROBBING );
		self->SendSystemMessage( _STR( 23, self->GetLang() ) ); 	   
		return SKILL_NO_FEEDBACK;
	}


	Character *lpChar = static_cast<Character*>( self );

	target->Lock();

	const INT HidingBonus = 0; // steph ajout de INT

	// Calculate the range between the two players.
	int nXdiff = abs( self->GetWL().X - target->GetWL().X );
	int nYdiff = abs( self->GetWL().Y - target->GetWL().Y );
	int nRange = ::sqrt((double) nXdiff * nXdiff + nYdiff * nYdiff ); // steph ajout de (double)
	
	// If there isn't any items to rob yet, do a normal peek
	if( valueOUT == NULL )
	{			 
		// Peek at the user's target.
		Peek::Func( dwReason, self, medium, target, valueIN, valueOUT, lpusUserSkill );
	}
	// Otherwise if a rob itemID was specified, attempt to rob it!!
	else
	{
		// Return if any of the two opponents are in a safe area.
		if( (self->GetUnderBlock() == __SAFE_HAVEN || self->GetUnderBlock() == __INDOOR_SAFE_HAVEN ||
			target->GetUnderBlock() == __SAFE_HAVEN || target->GetUnderBlock() == __INDOOR_SAFE_HAVEN )
			&& target->GetType() == U_PC && self->GetType() == U_PC )
		{
			self->RemoveFlag( __FLAG_ROBBING );
			self->SendSystemMessage( _STR( 36, self->GetLang() ) );
			target->Unlock();
			return SKILL_NO_FEEDBACK;
		}

		// Return if there is a wall or any building between players
		{
			WorldPos tempPos;
			WorldMap *wlWorld = TFCMAIN::GetWorld( self->GetWL().world );
	        Unit *lpCollisionUnit = NULL;
			if (wlWorld->GetCollisionPos( self->GetWL(), target->GetWL(), &tempPos, &lpCollisionUnit, false, false )) {
				self->RemoveFlag( __FLAG_ROBBING );
				self->SendSystemMessage( _STR( 36, self->GetLang() ) );
				target->Unlock();
				return SKILL_NO_FEEDBACK;
			}
		}

		if( !GAME_RULES::InPVP( self, target ) ){
			self->RemoveFlag( __FLAG_ROBBING );
			self->SendSystemMessage( _STR( 36, self->GetLang() ) );
            target->Unlock();
			return SKILL_NO_FEEDBACK;
		}

        if( self->GetType() == U_PC ){
            Character *ch = static_cast< Character * >( self );
            ch->StopAutoCombat();
        }

        if( nRange <= PeekRange ){
            // If robbed was successful.
            if(  rnd( 0, 100 ) <= 
                 (
                    ROB_SKILL / 2 + 
                    self->GetINT() / 5 * ROB_SKILL / 100 +
                    self->GetAGI() / 3 * ROB_SKILL / 100 +
                    HidingBonus
                 ) - (
                    target->GetINT() / 10 +
                    target->GetAGI() / 3
                 )
            ){
                BOOL boFound = FALSE;
                BOOL boCannotGet = FALSE;
                
                // Find the object in the target's backpack.
                TemplateList< Unit > *lpBackpack = target->GetBackpack();
                TemplateList< Unit > *lpThiefBackpack = self->GetBackpack();

                // If both target and the thieve's backpack exist.
                if( lpBackpack && lpThiefBackpack ){
                    MultiLock( lpBackpack, lpThiefBackpack );
                    
                    lpBackpack->ToHead();
                    while( lpBackpack->QueryNext() && !boFound ){
                        Objects *lpItem = static_cast< Objects * >( lpBackpack->Object() );

                        // If the object was found.
                        if( lpItem->GetID() == (DWORD)valueOUT ){

                            // Get the item's structure.
                            _item *lpItemStructure = NULL;
                            lpItem->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItemStructure );

                            // If the object can be dropped, robbed
                            if( !( lpItemStructure->dwDropFlags & CANNOT_DROP_ITEM ) && 
                                !( lpItemStructure->dwDropFlags & CANNOT_ROB_ITEM ) 
                            ){
                                // If the item is not too heavy
                                if( lpItemStructure->size + self->GetWeight() < self->GetMaxWeight() ){                                                                   
                                    // Special case for gold.                                
                                    if( lpItem->GetStaticReference() == __OBJ_GOLD ){
                                        int nGoldRobbed = (
                                            ( 
                                                rnd.roll(
                                                    dice( 1, self->GetAGI() * 2 ) 
                                                ) * 
                                                self->GetLevel() 
                                             ) -
                                             (
                                                target->GetAGI() *
                                                target->GetLevel() /
                                                2
                                             )
                                        );

                                        // If gold was robbed
                                        if( nGoldRobbed > 0 ){
                                            DWORD dwTargetGold = target->GetGold();
                                            // If the amount stolen is smaller than the total amount on the target.
                                            if( nGoldRobbed < dwTargetGold ){
                                                // Substract from the total amount.
                                                dwTargetGold -= nGoldRobbed;
                                            }else{
                                                // Gold robbed equals the total target's gold.
                                                nGoldRobbed = static_cast< int >( dwTargetGold );

                                                dwTargetGold = 0;                                                                                        
                                            }

                                            // Update target gold
                                            target->SetGold( dwTargetGold );

                                            // Update robber's gold
                                            DWORD dwRobberGold = self->GetGold();
                                            dwRobberGold += nGoldRobbed;


                                            if( self->GetType() == U_PC && target->GetType() == U_PC ){
                                                Character *selfCh = static_cast< Character * >( self );
                                                Character *targetCh = static_cast< Character * >( target );

                                                Players *selfPlayer = selfCh->GetPlayer();
                                                Players *targetPlayer = selfCh->GetPlayer();

                                                _LOG_PC
                                                    LOG_MISC_1,
                                                    "Player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u) robbed %u gold from player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u) (new amount=%u gold).",
                                                    (LPCTSTR)self->GetName( _DEFAULT_LNG ),
                                                    self->GetID(),
                                                    (LPCTSTR)selfPlayer->GetFullAccountName(),
                                                    self->GetLevel(),
                                                    self->GetWL().X,
                                                    self->GetWL().Y,
                                                    self->GetWL().world,
                                                    nGoldRobbed,
                                                    (LPCTSTR)target->GetName( _DEFAULT_LNG ),
                                                    target->GetID(),
                                                    (LPCTSTR)targetPlayer->GetFullAccountName(),
                                                    target->GetLevel(),
                                                    target->GetWL().X,
                                                    target->GetWL().Y,
                                                    target->GetWL().world,
                                                    dwTargetGold
                                                LOG_
                                            }

                                            self->SetGold( dwRobberGold );
                                        }else{
                                            // Tell the robber.
                                            self->SendSystemMessage( _STR( 2778, self->GetLang() ) );
                                        }                                   
                                    }else{
                                        TFCPacket sending;

                                        // Create a copy of the item.
                                        Objects *itemCopy = new Objects;
                                        if( !itemCopy->Create( U_OBJECT, lpItem->GetStaticReference() ) ){
                                            itemCopy->DeleteUnit();
                                            itemCopy = NULL;
                                        }

                                        if( itemCopy != NULL ){
                                            DWORD remove = 1;
                                            // If this is a quiver.
                                            if( lpItemStructure->itemStructureId == 12 ){
                                                // Remove many arrows.
                                                remove = (
                                                    ( 
                                                        rnd.roll(
                                                            dice( 1, self->GetAGI() * 2 ) 
                                                        ) * 
                                                        self->GetLevel() 
                                                     ) -
                                                     (
                                                        target->GetAGI() *
                                                        target->GetLevel() /
                                                        2
                                                     )
                                                );
                                            }
                                            if( self->GetType() == U_PC && target->GetType() == U_PC ){
                                                Character *selfCh = static_cast< Character * >( self );
                                                Character *targetCh = static_cast< Character * >( target );

                                                Players *selfPlayer = selfCh->GetPlayer();
                                                Players *targetPlayer = selfCh->GetPlayer();

                                                _LOG_PC
                                                    LOG_MISC_1,
                                                    "Player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u) robbed item %s from player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u).",
                                                    (LPCTSTR)self->GetName( _DEFAULT_LNG ),
                                                    self->GetID(),
                                                    (LPCTSTR)selfPlayer->GetFullAccountName(),
                                                    self->GetLevel(),
                                                    self->GetWL().X,
                                                    self->GetWL().Y,
                                                    self->GetWL().world,
                                                    (LPCTSTR)lpItem->GetName( _DEFAULT_LNG ),
                                                    (LPCTSTR)target->GetName( _DEFAULT_LNG ),
                                                    target->GetID(),
                                                    (LPCTSTR)targetPlayer->GetFullAccountName(),
                                                    target->GetLevel(),
                                                    target->GetWL().X,
                                                    target->GetWL().Y,
                                                    target->GetWL().world
                                                LOG_
                                            }

                                            DWORD oldQty = lpItem->GetQty();
                                            lpItem->Remove( remove );
                                            if( lpItem->GetQty() == 0 ){                                        
                                                // Remove the object from the target's backpack.
                                                lpBackpack->Remove();

                                                // Reset its quantity
                                                lpItem->SetQty( oldQty );

                                                // Destroy the copy and use this item
                                                // as the 'copy'.
                                                itemCopy->DeleteUnit();
                                                itemCopy = lpItem;
                                            }

                                            // Add the item copy to the thief's backpack.
                                            lpChar->AddToBackpack( itemCopy );

    		                                // Update the thieve's personnal backpack.
                                            sending << (RQ_SIZE)RQ_ViewBackpack;
	    	                                sending << (char)1;
		                                    sending << (long)target->GetID();		    		    
                                            self->PacketBackpack( sending );
                                            // Send it to the peeking player.
                                            self->SendPlayerMessage( sending );

    		                                // Update the victim's backpack (for opened backpacks).
                                            sending.Destroy();
                                            sending << (RQ_SIZE)RQ_ViewBackpack;
	    	                                sending << (char)0;
		                                    sending << (long)target->GetID();		    		    
                                            target->PacketBackpack( sending );
                                            // Send it to the peeking player.
                                            target->SendPlayerMessage( sending );
                                        }
                                    }
                                }else{
                                    boCannotGet = TRUE;
                                    // Send a too much weight message.
                                    self->SendSystemMessage( _STR( 17, self->GetLang() ) );
                                }
                            }else{
                                boCannotGet = TRUE;
                                // Send a strange force message.
                                self->SendSystemMessage( _STR( 29, self->GetLang() ) );
                            }
                            boFound = TRUE;
                        }
                    }
                    lpBackpack->Unlock();
                    lpThiefBackpack->Unlock();
                }
                if( boFound ){
                    if( !boCannotGet ){
                        // Send success message.
                        self->SendSystemMessage( _STR( 27, self->GetLang() ) );
                    }
                }else{
                    self->SendSystemMessage( _STR( 28, self->GetLang() ) );
                }
            }else{
                // If detected.
                if( rnd( 0, 100 ) <=
                    (
                        100 -
                        (
                            (
                                (
                                    ROB_SKILL / 2 +
                                    self->GetINT() / 5 * ROB_SKILL / 100 +
                                    self->GetAGI() / 3 * ROB_SKILL / 100 +
                                    HidingBonus
                                ) - (
                                    target->GetINT() / 10 +
                                    target->GetAGI() / 3
                                )
                            )
                        )
                    ) / 2
                ){
                    // Send warning to target.
                    target->SendSystemMessage( _STR( 7684, self->GetLang() ) );
                }
                // Send failure message to robber.
                self->SendSystemMessage( _STR( 26, self->GetLang() ) );
            }
        }else{
            self->SendSystemMessage( _STR( 24, self->GetLang() ) );
        }
        
        // Stop robbing!
        self->RemoveFlag( __FLAG_ROBBING );
    }

    target->Unlock();
    return SKILL_NO_FEEDBACK;
}
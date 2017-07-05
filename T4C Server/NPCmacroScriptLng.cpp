////////////////////////////////////////////////////////////////////////////////////////
//

#include "stdafx.h"
#include "TFC_MAIN.h"
#include "TFC Server.h"
#include "IntlText.h"
#include "format.h"
#include "RegKeyHandler.h"

#include "PlayerManager.h"

#include "NPCMAcroscriptLng.h"

#ifdef EXPORT
#undef EXPORT
#endif

#define EXPORT __declspec( dllexport )

DynamicFlags EXPORT dfGlobalFlags;
//BLBLBL

extern CTFCServerApp theApp;

//////////////////////////////////////////////////////////////////////////////////////////
int EXPORT NPCatoi
//////////////////////////////////////////////////////////////////////////////////////////
// Converts a character string to numbers, strips commas
// 
(
 const char *szString // The string.
)
// Return: int, the returned integer.
//////////////////////////////////////////////////////////////////////////////////////////
{
    int nNumber = 0;
    
    while( isdigit( *szString ) || *szString == ',' )
	{
        if( *szString != ',' )
		{
            nNumber *= 10;
            nNumber += *szString - '0';
        }
        szString++;
    }
    return nNumber;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL EXPORT __GiveItem
//////////////////////////////////////////////////////////////////////////////////////////
// Gives an item to a player.
// 
( 
 Unit *self,
 Unit *target,
 WORD wItemID,  // The item ID.
 BOOL boEcho,    // TRUE if backpack should be displayed.
 bool boGiveAbsolute,
 bool boBackpackUpdate // True if backpack should be updated.
)
// Return: BOOL, TRUE if the item could be given.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Only deal with characters.
    if( target->GetType() != U_PC ){
        return FALSE;
    }
    
    BOOL boGiven = FALSE;
	Objects *new_obj = new Objects;
    Character *lpChar = static_cast< Character * >( target );

	if(new_obj->Create(U_OBJECT, wItemID)){
        bool boOverweight = ( new_obj->GetWeight() + target->GetWeight() < target->GetMaxWeight() ? false : true );

        // If the target can hold this item or the item is in give absolute.
        if( !boOverweight || boGiveAbsolute ){

            // Avoid deletion of new_obj
            new_obj->CreateVirtualUnit();

            // Add the object to the bacpkack.
            lpChar->AddToBackpack( new_obj );
                        
            if( boBackpackUpdate ){
                TFCPacket sending;
	    		sending << (RQ_SIZE)RQ_ViewBackpack;
                if( boEcho ){
                    sending << (char)1;
                }else{
                    sending << (char)0;
                }
			    sending << (long)target->GetID();
			    target->PacketBackpack( sending );
			    target->SendPlayerMessage( sending );

                sending.Destroy();
                if( target->GetType() == U_PC ){
                    Character *ch = static_cast< Character * >( target );
                    ch->packet_equiped( sending );
                    ch->SendPlayerMessage( sending );
                }
            }
            boGiven = TRUE;
            
            char lpszID[ 256 ];
            Unit::GetNameFromID( new_obj->GetStaticReference(), lpszID, U_OBJECT );

            _LOG_NPCS
                LOG_MISC_1,
                "NPC %s gave item %s ( ID %s ) to player %s.",
                self->GetName( _DEFAULT_LNG ),
                new_obj->GetName( _DEFAULT_LNG ),
                lpszID,
                target->GetName( _DEFAULT_LNG )
            LOG_

            if( boOverweight ){
                // Make function fail for overweight even though we gave the item.
                boGiven = false;
            }

            // Delete new_obj's virtual unit.
            new_obj->DeleteUnit();

        }else{            
            target->SendSystemMessage( _STR( 37, target->GetLang() ) );

            new_obj->DeleteUnit();
        }
	}else{
        new_obj->DeleteUnit();
    };

    return boGiven;
}

//////////////////////////////////////////////////////////////////////////////////////////                             
LPVOID __declspec( dllexport) __GetItemHandle
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the Unit object of an item in the player's backpack or equipment.
// 
(
 Unit *lpuUnit, // The unit holding the backpack or equip.
 int nItem      // The item base reference ID.
)
// Return: Unit, The unit object or NULL.
//////////////////////////////////////////////////////////////////////////////////////////
{
	TemplateList <Unit> *bp = lpuUnit->GetBackpack();	
    Unit *uReturn = NULL;

	if(bp){
		bp->Lock();
        bp->ToHead();		
		while(bp->QueryNext() && uReturn == NULL){				
			// Check for the static reference, not the appearance
			if(bp->Object()->GetStaticReference() == (WORD)nItem ){
                uReturn = bp->Object();
			}
        }
        bp->Unlock();
	}

    // If item wasn't found in backpack.
    if( uReturn == NULL ){
        // If unit is a PC
        if( lpuUnit->GetType() == U_PC ){
            int nI;
            // Search equipped items
            Character *lpuChar = static_cast< Character * >( lpuUnit );
            Unit **lpuEquip = lpuChar->GetEquipment( );
            for( nI = 0; nI < EQUIP_POSITIONS; nI++ ){
                if( lpuEquip[ nI ] != NULL ){
                    if( lpuEquip[ nI ]->GetStaticReference() == (WORD)nItem ){
                        uReturn = lpuEquip[ nI ];
                    }
                }
            }
        }
    }
    
    return uReturn;
}
//////////////////////////////////////////////////////////////////////////////////////////
int EXPORT __CheckItem
//////////////////////////////////////////////////////////////////////////////////////////
// Checks to see how many items a PC has
// 
(
 Unit *target,
 WORD item // the ID of the item to check for
)
// Return: int, How many of this item is on the player
//////////////////////////////////////////////////////////////////////////////////////////
{
	TemplateList <Unit> *bp = target->GetBackpack();
	
	int nCount = 0;
	if(bp){
        bp->Lock();
		bp->ToHead();		
		while(bp->QueryNext()){
            Objects *obj = static_cast< Objects * >( bp->Object() );
			// Check for the static reference, not the appearance
			if( obj->GetStaticReference() == item ){
				nCount += obj->GetQty();
			}
        }
        bp->Unlock();
	}

	return nCount;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL EXPORT __TeachSkill
//////////////////////////////////////////////////////////////////////////////////////////
// Makes NPCs able to teach skills to player!
// 
(
 Unit *lpuWho, // Unit which should learn, must be a U_PC
 DWORD dwSkill, // Skill to learn.
 WORD wInitialStrength, // Initial strength to give to player
 DWORD dwGoldCost
)
// Return: BOOL, TRUE if skill has been learned.
//////////////////////////////////////////////////////////////////////////////////////////
{

	if( lpuWho->GetType() == U_PC ){

		Character *lpch = static_cast< Character *>( lpuWho );
        // If this is a skill
        if( dwSkill < SPELL_ID_OFFSET ){
            LPSKILL lpSkill = Skills::GetSkill( dwSkill );

            if( lpSkill != NULL ){
                DWORD dwGold = lpch->GetGold();

                if( dwGold >= static_cast< DWORD >( dwGoldCost ) ){
    		        CString dummy;
                    // If user can learn skill
	    	        if( Skills::IsSkillLearnable( dwSkill, lpuWho, dummy ) ){
	    	        
                        CString errMsg;
                        // Learn skill.
			            if( lpch->LearnSkill( dwSkill, wInitialStrength, true, errMsg ) ){

                            _LOG_PC
                                LOG_MISC_1,
                                "Player %s has been taught skill %s ( %u ).", 
                                lpuWho->GetName( _DEFAULT_LNG ), 
                                lpSkill->GetName( _DEFAULT_LNG ),
                                dwSkill
                            LOG_

                            dwGold -= dwGoldCost;
                            lpch->SetGold( dwGold );
				            return TRUE;
			            }
		            }
                }else{
                    lpch->SendSystemMessage( _STR( 38, lpch->GetLang() ) );
                }
            }
        }
        // If this is a spell.
        else{
		    LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpell( (WORD)dwSkill );

            if( lpSpell != NULL ){
                DWORD dwGold = lpch->GetGold();

                if( dwGold >= dwGoldCost ){
                    CString dummy;
    		        // If user can learn skill
	    	        if( SpellMessageHandler::IsSpellLearnable( (WORD)dwSkill, lpuWho, dummy ) ){
		    	        CString errMsg;
                        // Learn skill.
			            if( lpch->LearnSkill( dwSkill, wInitialStrength, true, errMsg ) ){

                            _LOG_PC
                                LOG_MISC_1,
                                "Player %s has been taught spell %s ( %u ).", 
                                lpuWho->GetName( _DEFAULT_LNG ), 
                                lpSpell->GetName( _DEFAULT_LNG ),
                                dwSkill
                            LOG_

                            dwGold -= dwGoldCost;
                            lpch->SetGold( dwGold );
				            return TRUE;
			            }
		            }
                }else{
                    lpch->SendSystemMessage( _STR( 39, lpch->GetLang() ) );
                }
            }
        }
	}

return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL EXPORT __TrainSkill
//////////////////////////////////////////////////////////////////////////////////////////
// Allows a NPC to train a user's skill
// 
(
 Unit *lpuTarget, // 
 WORD wSkillID, // 
 WORD wTrainPnts, // 
 DWORD dwCost,
 WORD wMax
)
// Return: BOOL, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    dwCost *= wTrainPnts;

	if( lpuTarget->GetType() == U_PC ){	

        // Get the character structure of the user
		Character *lpch = static_cast< Character *>( lpuTarget );

        DWORD dwGold = lpch->GetGold();

        if( dwGold >= dwCost ){
		    if( wSkillID == __SKILL_DODGE ){
			    DWORD dwFlag = lpch->GetTrueDODGE();

                // If skill points goes over the max.
                if( dwFlag + wTrainPnts > wMax ){                    
                    if( dwFlag < wMax ){
                        wTrainPnts = wMax - (WORD)dwFlag;
                    }else{
                        wTrainPnts = 0;
                    }
                }
                if( wTrainPnts != 0 ){
    			    // If player successfully spent its skill points
	    		    if( lpch->UseSkillPnts( wTrainPnts ) ){
		    		    DWORD dwBefore = lpch->GetTrueDODGE();
                        
                        dwGold -= dwCost;
                        lpch->SetGold( dwGold );                        
                        dwFlag += (DWORD)wTrainPnts;
				        lpch->SetDODGE( (WORD)dwFlag );

                        _LOG_PC
                            LOG_MISC_1,
                            "Player %s trained %u skill points in dodge skill %u->%u.", 
                            lpuTarget->GetName( _DEFAULT_LNG ),
                            wTrainPnts,
                            dwBefore,
                            lpch->GetTrueDODGE()
                        LOG_

				        return TRUE;
			        }
                }
		    }else
		    if( wSkillID == __SKILL_ATTACK ){
			    DWORD dwFlag = lpch->GetTrueATTACK();

                // If skill points goes over the max.
                if( dwFlag + wTrainPnts > wMax ){                    
                    if( dwFlag < wMax ){
                        wTrainPnts = wMax - (WORD)dwFlag;
                    }else{
                        wTrainPnts = 0;
                    }
                }
                if( wTrainPnts != 0 ){
			        if( lpch->UseSkillPnts( wTrainPnts ) ){
                        DWORD dwBefore = lpch->GetTrueATTACK();

                        dwGold -= dwCost;
                        lpch->SetGold( dwGold );
				        dwFlag += (DWORD)wTrainPnts;
				        lpch->SetATTACK( (WORD)dwFlag );

                        _LOG_PC
                            LOG_MISC_1,
                            "Player %s trained %u skill points in attack skill %u->%u.", 
                            lpuTarget->GetName( _DEFAULT_LNG ),
                            wTrainPnts,
                            dwBefore,
                            lpch->GetTrueATTACK()
                        LOG_

				        return TRUE;
                    }
                }
            }else{
                // Fetch the current user skill points.
                LPUSER_SKILL lpusSkill = lpch->GetSkill( wSkillID );
                if( lpusSkill != NULL ){
                    // Save the skill points before training.
                    DWORD dwSkillBefore = lpusSkill->GetTrueSkillPnts();

                    // If skill was successfully trained.
                    if( lpch->TrainSkillPnt( wSkillID, wTrainPnts, wMax ) ){
                        // Get skill structure and the new user skill structure.
                        LPSKILL lpSkill = Skills::GetSkill( wSkillID );
                        lpusSkill = lpch->GetSkill( wSkillID );

                        // If both structure exist
                        if( lpSkill != NULL && lpusSkill != NULL ){
                            // Log skill training.
                            _LOG_PC
                                LOG_MISC_1,
                                "Player %s trained %u skill points in skill %s(ID %u) %u->%u.", 
                                lpuTarget->GetName( _DEFAULT_LNG ),
                                wTrainPnts,
                                lpSkill->GetName( _DEFAULT_LNG ),
                                wSkillID,
                                dwSkillBefore,
                                lpusSkill->GetTrueSkillPnts()
                            LOG_

                            // Deduct gold.
                            dwGold -= dwCost;
                            lpch->SetGold( dwGold );
                        }
	    		        return TRUE;
                    }
                }
		    }
        }else{
            _TELL_PLAYER( lpch, 20 );
        }
	}

return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////
BOOL EXPORT _ORDER
//////////////////////////////////////////////////////////////////////////////////////////
// REturns TRUE if cmd1 and cmd2 are in msg and in order of appearance.
// 
(
 CString msg,  // message.
 LPCTSTR cmd1, // First keyword.
 LPCTSTR cmd2, // Second keyword.
 LPCTSTR cmd3, // Third keyword.
 LPCTSTR cmd4, // Fourth keyword.
 LPCTSTR cmd5  // Fifth keyword.
)
// Return: BOOL, TRUE if cmd1 and cmd2 are there in order in msg
//////////////////////////////////////////////////////////////////////////////////////////
{
	int i = msg.Find( cmd1 );
	int j;
	
	if( i != -1 ){

		if( !cmd3 ){
			if( i < msg.Find( cmd2 )){
				return TRUE;
			}			
		}else if( !cmd4 ){
			j = msg.Find( cmd2 );
			if( i < j ){
				i = msg.Find( cmd3 );
				if( j < i ){
					return TRUE;
				}
			}		
		}else if( !cmd5 ){
			j = msg.Find( cmd2 );
			if( i < j ){
				i = msg.Find( cmd3 );
				if( j < i ){
					j = msg.Find( cmd4 );
					if( i < j ){
						return TRUE;
					}
				}
			}
		}else{
			j = msg.Find( cmd2 );
			if( i < j ){
				i = msg.Find( cmd3 );
				if( j < i ){
					j = msg.Find( cmd4 );
					if( i < j ){
						i = msg.Find( cmd5 );
						if( j < i ){
							return TRUE;
						}
					}
				}
			}

	}
	


	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT TeleportFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Teleports a user.
// 
(
 int x,
 int y,
 int world,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    WorldPos wlPos = { x, y, world };
    target->Teleport( wlPos, 0 );
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT BreakFunc
//////////////////////////////////////////////////////////////////////////////////////////
// Breaks a conversation.
// 
(
 Unit *npc,
 Unit *target
)
// Return: void EXPORT, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( npc != NULL ){
        if( !npc->IsPrivateTalk() ){
            npc->Do( wandering );
            WorldPos dest = { -1,-1,-1 };
	        npc->SetDestination( dest );
        }
        npc->SetTarget( npc->GetBond() );
    }
	
    TFCPacket sending;
	sending << (RQ_SIZE)RQ_BreakConversation;
	target->SendPlayerMessage( sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT TakeItemFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Takes an item from the backpack
// 
(
 UINT itemID,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TemplateList <Unit> *bp = target->GetBackpack();
    
    if( bp == NULL ){
        return;
    }
    
    // Find the object in the backpack.
    bp->Lock();
    bp->ToHead();
    while( bp->QueryNext() ){
        Objects *obj = static_cast< Objects * >( bp->Object() );
        if( obj->GetStaticReference() == itemID){
            // Remove an item from the stack
            obj->Remove();
            if( obj->GetQty() == 0 ){            
                bp->Object()->DeleteUnit();
                bp->Remove();
            }
            
            break;
        }
    }
    bp->Unlock();
    
    /*TFCPacket sending;
    sending << (RQ_SIZE)RQ_ViewBackpack;
    sending << (char)0;
    sending << (long)target->GetID();
    target->PacketBackpack( sending );
    target->SendPlayerMessage( sending );*/
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT TakeItemHandleFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Takes an item.
// 
(
 Unit *&handle,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TemplateList <Unit> *bp = target->GetBackpack();
    
    if( bp == NULL ){
        return;
    }
    
    bp->Lock(); 
    bp->ToHead();
    while( bp->QueryNext() ){
        Objects *obj = static_cast< Objects * >( bp->Object() );
        if( obj == static_cast< Objects * >( handle ) ){            
            obj->Remove();
            if( obj->GetQty() == 0 ){
                bp->Object()->DeleteUnit();
                bp->Remove();
                handle = NULL;
            }
        }
    }
    bp->Unlock();

    /*TFCPacket sending;
    sending << (RQ_SIZE)RQ_ViewBackpack;
    sending << (char)0;
    sending << (long)target->GetID();
    target->PacketBackpack( sending );
    target->SendPlayerMessage( sending );*/
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT GiveGoldFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Give gold.
// 
(
 int amount,
 Unit *target,
 bool echo
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    int gold = target->GetGold();
    gold += amount;
    target->SetGold( gold, echo );
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT TakeGoldFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Takes gold.
// 
(
 int amount,
 Unit *target,
 bool echo
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    int gold = target->GetGold();
    gold -= amount;
    gold = gold < 0 ? 0 : gold;
    target->SetGold( gold, echo );
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT GiveXPFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Gives XP.
// 
(
 int amount,
 Unit *npc,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( -amount > target->GetXP() ){
        target->SetXP( 0 );
    }else{
        target->SetXP( target->GetXP() + amount );
    }
    
    target->TrainUnit();
	 TFCPacket sending;
	 sending << (RQ_SIZE)RQ_XPchanged;
	 sending << (long)(target->GetXP() >> 32);
	 sending << (long)target->GetXP();
	 target->SendPlayerMessage( sending );
    _LOG_NPCS
        LOG_MISC_1,
        "NPC %s gave %u xp to player %s.",
        npc->GetName(_DEFAULT_LNG),
        amount,
        target->GetName(_DEFAULT_LNG)
    LOG_
};

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT SummonFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Summons a monster.
// 
(
 LPCTSTR mobID,
 int absx,
 int absy,
 int world,
 Unit *npc,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    WorldMap *wlWorld = TFCMAIN::GetWorld( world );
    if( wlWorld == NULL ){
		return;
	}

    Creatures *lpuCreature = new Creatures;
    if( !lpuCreature->Create( U_NPC, Unit::GetIDFromName( mobID, U_NPC ) ) ){
		lpuCreature->DeleteUnit();
		return;
	}
    WorldPos wlPos = { absx, absy, world };
    wlPos = wlWorld->FindValidSpot( wlPos, 5 );
    if( wlPos.X == -1 || wlPos.Y == -1 ){
		lpuCreature->DeleteUnit();
		return;
	}
    lpuCreature->SetWL( wlPos );

    if( !wlWorld->SummonMonster( lpuCreature, TRUE ) ){
		lpuCreature->DeleteUnit();
		return;
	}

	_LOG_NPCS
		LOG_MISC_1,
		"NPC %s summoned creature %s ( ID %s ) at ( %u, %u, %u )",
		npc->GetName(_DEFAULT_LNG),
		lpuCreature->GetName(_DEFAULT_LNG),
		mobID,
		wlPos.X,
		wlPos.Y,
		world
	LOG_
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT LogGoldWithdrawFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Logs withdrawing from bank.
// 
(
 int currentGold,
 int goldWithdrew,
 LPCTSTR bankName,
 Character *lpChar
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( lpChar != NULL ){
        Players *lpPlayer = lpChar->GetPlayer();
        if( lpPlayer != NULL ){
            _LOG_PC
                LOG_MISC_1,
                "Player %s (%s) withdrew %u gold (now has %u gold) from %s.",
                (LPCTSTR)lpChar->GetTrueName(),
                (LPCTSTR)lpPlayer->GetFullAccountName(),
                goldWithdrew,
                currentGold,
                bankName
            LOG_  
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT LogGoldDepositFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Logs depositing
// 
(
 int currentGold,
 int goldDeposited,
 LPCTSTR bankName,
 Character *lpChar
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( lpChar != NULL ){
        Players *lpPlayer = lpChar->GetPlayer();
        if( lpPlayer != NULL ){
            _LOG_PC
                LOG_MISC_1,
                "Player %s (%s) deposited %u gold (now has %u gold) in %s.",
                (LPCTSTR)lpChar->GetTrueName(),
                (LPCTSTR)lpPlayer->GetFullAccountName(),
                goldDeposited,
                currentGold,
                bankName
            LOG_
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT HealPlayerFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Heals the player.
// 
(
 int hitPnts,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD maxHitPoints = target->GetMaxHP();
    DWORD hitPoints = target->GetHP();
    hitPoints += hitPnts;
    hitPoints  = hitPoints > maxHitPoints ? maxHitPoints : hitPoints;
    target->SetHP( hitPoints, true );
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT ShoutFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Shouts a message.
// 
(
 LPCTSTR msg,
 Unit *npc,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( npc->IsPrivateTalk() ){
        CString csMsg( msg );
        if( target != NULL ){
            target->SendPrivateMessage( csMsg, npc );
        }else{
            npc->Talk( csMsg );
        }
    }else{
        CString csMsg( msg );;
        npc->Talk( (LPCTSTR)csMsg );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT AddTeachSkillFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds a skill to a teaching list.
// 
(
 int skillID,
 DWORD skillCost,
 DWORD skillPnts,
 BOOL &boCantLearn,
 TemplateList< _SKILLITEM > &tlSkillList,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( skillID < SPELL_ID_OFFSET ){
		LPSKILL lpSkill = Skills::GetSkill( skillID );
		if( lpSkill != NULL ){
			_SKILLITEM *NewItem = new _SKILLITEM;
			LPUSER_SKILL lpUserSkill = target->GetSkill( skillID );
			NewItem->cCanHave = Skills::IsSkillLearnable( skillID, target, NewItem->reqDesc );
			if( lpUserSkill ) NewItem->cCanHave = FALSE;
			NewItem->wCurPnts = 0;
			NewItem->dwSkillCost = skillCost;
			NewItem->csSkillName = lpSkill->GetName( target->GetLang() );
			NewItem->wID = skillID;
            NewItem->dwIcon = skillID;
            NewItem->wMaxLearnPnts = skillPnts;
			tlSkillList.AddToTail(NewItem);
		}
	}else{
		LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpell( skillID );
		if( lpSpell != NULL ){ /* If spell exists */
			_SKILLITEM *NewItem = new _SKILLITEM;
			LPUSER_SKILL lpUserSkill = target->GetSkill( skillID );
			NewItem->cCanHave = SpellMessageHandler::IsSpellLearnable( skillID, target, NewItem->reqDesc );
			if( lpUserSkill != NULL ) NewItem->cCanHave = FALSE;
			NewItem->wCurPnts = 0;
			NewItem->dwSkillCost = skillCost;
			NewItem->csSkillName = lpSpell->GetName( target->GetLang() );
            NewItem->wMaxLearnPnts = skillPnts;
            NewItem->dwIcon = lpSpell->dwIcon;
			NewItem->wID = skillID;
			tlSkillList.AddToTail(NewItem);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT AddTrainSkillFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds a skill to a training list.
// 
(
 int skillId,
 int maxPnts,
 DWORD skillCost,
 BOOL &boCantLearn,
 TemplateList< _SKILLITEM > &tlSkillList,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPUSER_SKILL lpUserSkill = target->GetSkill( skillId );
	LPSKILL lpSkill = Skills::GetSkill( skillId );
	if( lpSkill != NULL || ( skillId == __SKILL_DODGE || skillId == __SKILL_ATTACK ) ) /* If skill exists */{
		_SKILLITEM *NewItem = new _SKILLITEM;
		if( skillId == __SKILL_DODGE ){
			NewItem->csSkillName = _STR( 450, target->GetLang() );
			NewItem->cCanHave = TRUE;
			NewItem->wCurPnts = target->GetTrueDODGE();
		}else
		if( skillId == __SKILL_ATTACK ){
			NewItem->csSkillName = _STR( 449, target->GetLang() );
			NewItem->cCanHave = TRUE;
			NewItem->wCurPnts = target->GetTrueATTACK();
		}else{
			if( lpUserSkill ){
				NewItem->cCanHave = TRUE;
				NewItem->wCurPnts = lpUserSkill->GetTrueSkillPnts();
			}else{
				NewItem->cCanHave = FALSE;
				NewItem->wCurPnts = 0;
			}
			NewItem->csSkillName = lpSkill->GetName( target->GetLang() );
		}
		NewItem->dwSkillCost = skillCost;
		NewItem->wID = skillId;
		NewItem->wMaxLearnPnts = maxPnts;
		if( NewItem->cCanHave ) boCantLearn = FALSE;
		tlSkillList.AddToTail(NewItem);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT SendTrainSkillListFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends the list of train items to the target.
// 
(
 BOOL boCantLearn,
 TemplateList< _SKILLITEM > &tlSkillList,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{

	tlSkillList.ToHead(); TFCPacket sending;
	sending << (RQ_SIZE)RQ_SendTrainSkillList;
	sending << (short)target->GetSkillPoints();
	sending << (short)tlSkillList.NbObjects();
	_SKILLITEM *lpSkillItem;
	tlSkillList.ToHead();
	while(tlSkillList.QueryNext()){
		lpSkillItem = tlSkillList.Object();
		sending << (char)(lpSkillItem->cCanHave);
		sending << (short)lpSkillItem->wID;
		sending << (short)lpSkillItem->wCurPnts;
		sending << (short)lpSkillItem->wMaxLearnPnts;
		sending << (long)lpSkillItem->dwSkillCost;
		TRACE("\r\nSending skill %s", lpSkillItem->csSkillName );
		sending << (CString)lpSkillItem->csSkillName;
		tlSkillList.DeleteAbsolute();
	}
	target->SendPlayerMessage( sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT SendTeachSkillListFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends a list of skills to teach to the target.
// 
(
 BOOL boCantLearn,
 TemplateList< _SKILLITEM > &tlSkillList,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    tlSkillList.ToHead(); TFCPacket sending;
    sending << (RQ_SIZE)RQ_SendTeachSkillList;
    sending << (short)target->GetSkillPoints();
    sending << (short)tlSkillList.NbObjects();
    _SKILLITEM *lpSkillItem;
    tlSkillList.ToHead();
    while( tlSkillList.QueryNext() ){
        lpSkillItem = tlSkillList.Object();
        sending << (char)(lpSkillItem->cCanHave);
        sending << (short)lpSkillItem->wID;
        sending << (long)lpSkillItem->dwSkillCost;
        sending << (CString)lpSkillItem->csSkillName;
        sending << (CString)lpSkillItem->reqDesc;
        sending << (long)lpSkillItem->wMaxLearnPnts;
        sending << (long)lpSkillItem->dwIcon;
        tlSkillList.DeleteAbsolute();
    }
    target->SendPlayerMessage( sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT AddBuyItemFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds an item to buy in an item list.
// 
(
 DWORD price,
 DWORD id,
 TemplateList< _OBJECTITEM > &tlItemList,
 Character *lpChar
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( lpChar == NULL ){
        return;
    }

    Objects *newObj = new Objects;
    if( newObj->Create( U_OBJECT, id ) ){
        _OBJECTITEM *NewObject = new _OBJECTITEM;
        NewObject->dwPrice = price;
        NewObject->wAppearance = newObj->GetAppearance();
        NewObject->dwID = id;
        NewObject->csItemName = newObj->GetName( lpChar->GetLang() );        
        if( lpChar->CanEquip( newObj, NULL, FALSE, &NewObject->reqDesc ) ){
            NewObject->bCanEquip = 1;
        }else{
            NewObject->bCanEquip = 0;
        }
        tlItemList.AddToTail(NewObject);
   }
   newObj->DeleteUnit();
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT AddSellItemFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds an item to sell to a list of items.
// 
(
 DWORD itemType,
 DWORD lowPriceRange,
 DWORD hiPriceRange,
 TemplateList< _OBJECTITEM > &tlItemList,
 Character *lpChar
)
//////////////////////////////////////////////////////////////////////////////////////////
{
   if( lpChar == NULL ){
       return;
   }
    
   TemplateList <Unit> *lpBackpack = lpChar->GetBackpack();\
	if( lpBackpack ){
		// Search the backpack
		lpBackpack->Lock();
		lpBackpack->ToHead();
		while( lpBackpack->QueryNext() ){
			Objects *lpUnit = static_cast< Objects * >( lpBackpack->Object() );
			
            // Only process objects
            if( lpUnit->GetType() != U_OBJECT ){
                continue;
            }
		    
            // Gets the item structure
            _item *lpItem = NULL;
            lpUnit->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );

            if( lpItem == NULL ){
                continue;
            }
                            
			if( lpItem->sell_type != itemType ){
                continue;
            }
			// If NPC can buy the item
			if( lpItem->cost >= lowPriceRange && lpItem->cost < hiPriceRange ){
				_OBJECTITEM *NewObject = new _OBJECTITEM;
				NewObject->dwPrice = lpItem->cost;
				NewObject->wAppearance = lpUnit->GetAppearance();
				NewObject->dwID = lpUnit->GetID();
				NewObject->csItemName = lpUnit->GetName( lpChar->GetLang() );
                NewObject->dwQty = lpUnit->GetQty();
				tlItemList.AddToTail(NewObject);
			}
		}
		lpBackpack->Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT SendBuyItemListFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends a list of items to buy from a target.
// 
(
 TemplateList< _OBJECTITEM > &tlItemList,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    tlItemList.ToHead(); 
    TFCPacket sending;
    
    sending << (RQ_SIZE)RQ_SendBuyItemList;
	 sending << (long)target->GetGold();
	 sending << (short)tlItemList.NbObjects();
	 
    tlItemList.ToHead();
	 while(tlItemList.QueryNext()){
        sending << (short)tlItemList.Object()->dwID;
        sending << (short)tlItemList.Object()->wAppearance;
        sending << (long)tlItemList.Object()->dwPrice;
        sending << (char)tlItemList.Object()->bCanEquip;
        sending << (CString)tlItemList.Object()->csItemName;
        sending << (CString)tlItemList.Object()->reqDesc;
	 	
        tlItemList.DeleteAbsolute();
    } 
    
    target->SendPlayerMessage(sending);	
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT SendSellItemListFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends a list of items to sell to the target.
// 
(
 CString &output,
 LPCTSTR text,
 TemplateList< _OBJECTITEM > &tlItemList,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( tlItemList.NbObjects() == 0 ){
        output = text;
    }else{
        tlItemList.ToHead(); TFCPacket sending;
        sending.Destroy();
        sending << (RQ_SIZE)RQ_SendSellItemList;
        sending << (long)target->GetGold();
        sending << (short)tlItemList.NbObjects();
        
        tlItemList.ToHead();
        while(tlItemList.QueryNext()){
            sending << (long)tlItemList.Object()->dwID;
            sending << (short)tlItemList.Object()->wAppearance;
            sending << (long)tlItemList.Object()->dwPrice;
            sending << (long)tlItemList.Object()->dwQty;
            sending << (CString)tlItemList.Object()->csItemName;

            tlItemList.DeleteAbsolute();
        } 
        target->SendPlayerMessage(sending);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
bool EXPORT NPC_BUYFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Makes an NPC buy an item from the player.
// 
(
 Unit *npc, // 
 Unit *target, // 
 WORD ItemType, // 
 DWORD LowPriceRange, // 
 DWORD HiPriceRange, // 
 int   &MoneyData,
 LPSHOP_DATA shop
)
// Return: void EXPORT, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    TemplateList <Unit> *lpBackpack = target->GetBackpack();
	if( lpBackpack == NULL ){
        return false;
    }
		
	// Search the backpack
	lpBackpack->Lock();
	lpBackpack->ToHead();    
    while( lpBackpack->QueryNext() ){
        Objects *lpUnit = static_cast< Objects * >( lpBackpack->Object() );
		// If unit was not found or unit is not an item
		if( lpUnit->GetID() != shop->ID || lpUnit->GetType() != U_OBJECT ){
            continue;
        }

        // Get the item's structure.
        _item *lpItem = NULL;
		lpUnit->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );
        
        if( lpItem == NULL ){
            break;
        }

        // If this is not the kind of items we sell
		if( lpItem->sell_type != ItemType ){
            break;
        }
		// If NPC cannot buy the item
		if( !( lpItem->cost >= LowPriceRange && lpItem->cost < HiPriceRange ) ){
            break;
        }
        if( shop->wQuantity > lpUnit->GetQty() ){
            shop->wQuantity = lpUnit->GetQty();
        }
				
        // Give gold to user.
		int nGold = target->GetGold();
		nGold += lpItem->cost * shop->wQuantity;
        
        
        // Log transaction.
        _LOG_NPCS
            LOG_MISC_1,
            "NPC %s bought %u item %s ( ID %u ) from player %s for %u gold (now at %u gold).",
            (LPCTSTR)npc->GetName(target->GetLang()),
            shop->wQuantity,
            (LPCTSTR)lpUnit->GetName(target->GetLang()),
            lpUnit->GetStaticReference(),
            (LPCTSTR)target->GetName(target->GetLang()),
            lpItem->cost,
            nGold
        LOG_
        
        // Remove the unit from the stack
        lpUnit->Remove( shop->wQuantity );
        if( lpUnit->GetQty() == 0 ){
            lpUnit->DeleteUnit();
            lpBackpack->Remove();    
        }

        target->SetGold( nGold );

		MoneyData = 3;

        lpBackpack->Unlock();
        // Item found and sold.
        return true;
	}
	lpBackpack->Unlock();
    // Item not found.
    return false;
}


//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT ChatterShoutFunc
//////////////////////////////////////////////////////////////////////////////////////////
// This function allows a NPC to shout a message.
// 
(
 LPCTSTR msg,   // The text to shout
 Unit *npc,     // The NPC
 Unit *target   // The current NPC target.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Create a shout packet
    TFCPacket sending;
    
    sending << (RQ_SIZE)RQ_SendChatterMessage;
    sending << CPlayerManager::GetChatter().GetMainChannel();
    sending << (CString &)npc->GetName(_DEFAULT_LNG);
    sending << (const char *)msg;
    
    Broadcast::BCast( npc->GetWL(), 0, sending );                

}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT NewChatterShoutFunc
//////////////////////////////////////////////////////////////////////////////////////////
// This function allows a NPC to shout a message.
//
(
 string Channel,
 LPCTSTR msg,
 Unit *npc,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	TFCPacket sending;

	sending << (RQ_SIZE)RQ_SendChatterMessage;
	sending << Channel;
	sending << (CString &)npc->GetName(_DEFAULT_LNG);
	sending << (const char *)msg;

	Broadcast::BCast( npc->GetWL(), 0, sending);

    _LOG_SHOUTS
        LOG_MISC_1,
        "NPC %s said in channel %s: %s",
		(LPCTSTR)npc->GetName(_DEFAULT_LNG),
        Channel.c_str(),
        msg
    LOG_


	/*Players *self = static_cast< Players * >(npc->GetPlayer());

	ChatterChannels &cChatter = CPlayerManager::GetChatter();

    cChatter.Talk( self, Channel, msg );*/
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT SysMsgFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Allows a NPC to send out system messages, either globally or privatly.
// 
(
 LPCTSTR msg,       // The message to send.
 Unit *npc,         // The NPC
 Unit *target,      // The current NPC target.
 bool privateMsg    // Wether the message is global or private.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( privateMsg ){
        target->SendSystemMessage( msg );
    }else{
        WorldPos wlPos = {0,0,0};
        Broadcast::BCServerMessage( wlPos, 0,
            msg    
        );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
bool IsCharacterManglingDisabled()
{
    return stricmp( theApp.sGeneral.csLang, "t4c_kor.elng" ) == 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
BYTE GetMsgChar
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the character equivalent.
// 
(
 BYTE ch // The TChar
)
// Return: TCHAR, the converterted char
//////////////////////////////////////////////////////////////////////////////////////////
{   
    static bool disableCharacterMangling = IsCharacterManglingDisabled();

	if ( disableCharacterMangling ){	//DC
		return ch;									//For korean
	}else{											//DC
		// Check if the character is an accent character.
		switch( ch ){
		case 192: //'À':
		case 193: //'Á':
		case 194: //'Â':
		case 195: //'Ã':
		case 196: //'Ä':
		case 197: //'Å':
		case 198: //'Æ':
			return 'A';
		case 199: //'Ç':
			return 'C';
		case 200: //'È':
		case 201: //'É':
		case 202: //'Ê':
		case 203: //'Ë':
			return 'E';
		case 204: //'Ì':
		case 205: //'Í':
		case 206: //'Î':
		case 207: //'Ï':
			return 'I';
		case 209: //'Ñ':
			return 'N';
		case 210: //'Ò':
		case 211: //'Ó':
		case 212: //'Ô':
		case 213: //'Õ':
		case 214: //'Ö':
			return 'O';
		case 217: //'Ù':
		case 218: //'Ú':
		case 219: //'Û':
		case 220: //'Ü':
			return 'U';
		case 221: //'Ý':
			return 'Y';
		case 224: //'à':
		case 225: //'á':
		case 226: //'â':
		case 227: //'ã':
		case 228: //'ä':
		case 229: //'å':
		case 230: //'æ':
			return 'a';
		case 231: //'ç':
			return 'c';
		case 232: //'è':
		case 233: //'é':
		case 234: //'ê':
		case 235: //'ë':
			return 'e';
		case 236: //'ì':
		case 237: //'í':
		case 238: //'î':
		case 239: //'ï':
			return 'i';
		case 240:
			return 'o';
		case 241: //'ñ':
			return 'n';
		case 242: //'ò':
		case 243: //'ó':
		case 244: //'ô':
		case 245: //'õ':
		case 246: //'ö':
			return 'o';
		case 249: //'ù':
		case 250: //'ú':
		case 251: //'û':
		case 252: //'ü':
			return 'u';
		case 253: //'ý':
		case 255: //'ÿ':
			return 'y';
		};
		return ch;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
bool EXPORT NPCKeyWord
//////////////////////////////////////////////////////////////////////////////////////////
// Determines wether the given keyword was found in the message
// 
(
 const CString &msg,    // 
 const char *kw         // 
)
// Return: bool, true if the keyword was found.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Add a space in front of the keyword
    CString keyWord;
    
    if( kw[ 0 ] != ' ' ){
        keyWord += ' ';
    }
    
    keyWord += kw;

    // Convert all characters in the keyword.
    int i;
    for( i = 0; i < keyWord.GetLength(); i++ ){
        keyWord.SetAt( i, toupper( GetMsgChar( keyWord.GetAt( i ) ) ) );
    }

    if( msg.Find( keyWord ) != -1 ){
        return true;
    }
    keyWord.SetAt( 0, '-' );

    return( msg.Find( keyWord ) != -1 );
}


//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT NPCFormatMsg
//////////////////////////////////////////////////////////////////////////////////////////
//  Formats incoming messages for parsing.
// 
(
 CString &msg, // 
 CString &parammsg
)
// Return: void, 
//////////////////////////////////////////////////////////////////////////////////////////
{        
    msg.TrimLeft();
    msg.TrimRight();

    // Convert all characters in the msg.
    int i;
    for( i = 0; i < msg.GetLength(); i++ ){
        msg.SetAt( i, GetMsgChar( msg.GetAt( i ) ) );
    }

    // Insert a space at the beginning and at the end.
    msg.Insert( 0, " " );
    msg += " ";

    // Create the parammsg from the current state of the msg
    parammsg = msg;
    parammsg.TrimRight();
    parammsg += ".";

    // Convert the msg to uppercase.
    msg.MakeUpper();
}

//////////////////////////////////////////////////////////////////////////////////////////
bool EXPORT NPCGetParameters
//////////////////////////////////////////////////////////////////////////////////////////
//  Gets the parameters from a parameter keyword template
// 
(
 const char *cmd,       // The parameter template
 CString &parammsg,     // The parameter message
 CString *lpcsParams    // The found parameters (must be able to hold the quantity of
                        // parameters specified in the parameter template).
)
// Return: bool, true if the parameter message complies with the template.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Add a space in front of the keyword
    CString keyWord( " " );
    keyWord += cmd;

    // Convert all characters in the keyword.
    int i;
    for( i = 0; i < keyWord.GetLength(); i++ ){
        keyWord.SetAt( i, GetMsgChar( keyWord.GetAt( i ) ) );
    }
        
    return SysopCmd::GetParametersForNPC( keyWord, parammsg, lpcsParams ) == TRUE ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT __CastSpell
//////////////////////////////////////////////////////////////////////////////////////////
// Makes the NPC cast a spell on the desired target.
// 
(
 DWORD dwSpellID,   // The spell to cast.
 Unit *caster,      // The caster.
 Unit *target       // The spell's target.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Activate the spell!
    SpellMessageHandler::ActivateSpell(
		dwSpellID,			
		caster,
		NULL,
		target,
		target->GetWL()
	);
}

struct FlagList{
	DWORD flagID;
	DWORD flagValue;
};
list< FlagList > flagList;

#include "QuestFlagsListing.h"
extern Random rnd;
//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT RemortTo
//////////////////////////////////////////////////////////////////////////////////////////
// Remorts a player
// 
(
 Unit *self,
 DWORD x,       // Teleport X, Y, World positions
 DWORD y,       // 
 DWORD world    // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( self == NULL ){
        return;
    }
    if( self->GetType() != U_PC ){
        return;
    }
    
    Character *ch = static_cast< Character * >( self );

    /////////////////////////////
    // FLAG WIPE
    int FlagBankOfWindhowl  = ch->ViewFlag( __FLAG_BANK_OF_WINDHOWL );
    int numberOfRemorts = ch->ViewFlag( __FLAG_NUMBER_OF_REMORTS );
    int FlagUserAlignment  = ch->ViewFlag( __QUEST_FIXED_ALIGNMENT );
	// BEGIN : Mestoph -> Fix bug of dopplganger portal
	int UserKnowsAboutDopplganger = ch->ViewFlag( __FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER );
	// END : Mestoph -> Fix bug of dopplganger portal

	// V2 - Open the registry and find flags to save from destruction
	RegKeyHandler regKey;
	regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY );

	flagList.clear();
	TFormat format;

	int i = 1;
	DWORD flags = static_cast< DWORD >( regKey.GetProfileInt( "OracleFlag1", 0 ) );
	while( flags != 0 ){
		FlagList flag;
		flag.flagID = flags;
		flag.flagValue = ch->ViewFlag( flags );
		flagList.push_back( flag );

		_LOG_NPCS
			LOG_MISC_1,
			"NPC The Oracle stored player %s's flag ( %u = %u ).",
			(LPCTSTR)ch->GetTrueName(),
			flag.flagID,
			flag.flagValue
		LOG_

		i++;
		flags = static_cast< DWORD >( regKey.GetProfileInt( format( "OracleFlag%u", i ), 0 ) );
	}

    ch->DestroyFlags();

    numberOfRemorts++;

    // Restore flags that are to be kept.
	// BEGIN : Mestoph -> Fix bug of dopplganger portal
	ch->SetFlag( __FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER, UserKnowsAboutDopplganger );
	// END : Mestoph -> Fix bug of dopplganger portal
    ch->SetFlag( __FLAG_BANK_OF_WINDHOWL, FlagBankOfWindhowl );
    ch->SetFlag( __FLAG_NUMBER_OF_REMORTS, numberOfRemorts );
    ch->SetFlag( __FLAG_USER_ALIGNMENT, FlagUserAlignment );
    ch->SetFlag( __QUEST_FIXED_ALIGNMENT, FlagUserAlignment );
    ch->SetFlag( __FLAG_REMORT_POINTS, 8 + 2 * numberOfRemorts );

	// V2 - Retore those flags saved from destruction
	list< FlagList >::iterator j;
   	for( j = flagList.begin(); j != flagList.end(); j++ ){
		ch->SetFlag ( (*j).flagID , (*j).flagValue );
		_LOG_NPCS
			LOG_MISC_1,
			"NPC The Oracle restored player %s's flag ( %u = %u ).",
			(LPCTSTR)ch->GetTrueName(),
			(*j).flagID,
			(*j).flagValue
		LOG_
	}

    //////////////////////////////
    // REMOVAL OF ALL ITEMS
    for( i = 0; i < EQUIP_POSITIONS; i++ ){
        ch->unequip_object( i );
    }
    Unit **equip = ch->GetEquipment();
    for( i = 0; i < EQUIP_POSITIONS; i++ ){
        // Flush all items that couldn't be unequipped.
        equip[ i ] = NULL;
    }

    // Scroll the backpack for "quest" items
    TemplateList< Unit > *backpack = ch->GetBackpack();
    if( backpack != NULL ){
        backpack->Lock();
        backpack->ToHead();
        while( backpack->QueryNext() ){
            Objects *obj = static_cast< Objects * >( backpack->Object() );

            if( obj->GetStaticReference() == __OBJ_GEM_OF_DESTINY ){
                continue;
            }

			_item *itemStructure = NULL;

			// Get the item structure.
			obj->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &itemStructure );

			if( itemStructure == NULL ){
                continue;
            }
            // If the object should be junked.
            if( itemStructure->dwDropFlags & JUNK_AT_SERAPH ){
                // Destroy it.
                backpack->Remove();
                obj->DeleteUnit();
            }            
        }
        backpack->Unlock();
    }
    //////////////////////////////
    // STAT RESET
    ch->SetAirResist  ( 100 );
    ch->SetWaterResist( 100 );
    ch->SetFireResist ( 100 );
    ch->SetEarthResist( 100 );
    ch->SetLightResist( 5000 );
    ch->SetDarkResist ( 100 );
    
    ch->SetAirPower  ( 100 );
    ch->SetWaterPower( 100 );
    ch->SetFirePower ( 100 );
    ch->SetEarthPower( 100 );
    ch->SetLightPower( 100 );
    ch->SetDarkPower ( 100 );

	ch->SetINT( 20 + 5 * numberOfRemorts );
	ch->SetEND( 20 + 5 * numberOfRemorts );
	ch->SetSTR( 20 + 5 * numberOfRemorts );
	ch->SetAGI( 20 + 5 * numberOfRemorts );
	ch->SetWIS( 20 + 5 * numberOfRemorts );
	ch->SetLCK( 100 );
	ch->SetATTACK( 15 );
	ch->SetDODGE( 15 );    

    ch->SetMaxHP( rnd.roll( dice( 2, 5 ) ) + 48 + ch->GetEND() );
    ch->SetHP( ch->GetMaxHP(), false );

    ch->SetMaxMana( 10 + ch->GetTrueINT() * 2 / 3 + ch->GetTrueWIS() / 3 + rnd( 0, 5 ) );
    ch->SetMana( ch->GetMaxMana() );    

    ch->ClearAllSkillsAndSpells();
    ch->SetXP( 0 );
    ch->SetLevel( 1 );

    //////////////////////////////////
    // NEW POWERS
    WorldPos wlPos = { 0, 0, 0 };
    // Cast the permanent remort spell.
    SpellMessageHandler::ActivateSpell( 10696, ch, NULL, NULL, wlPos );

    /////////////////////////////////////
    // TELEPORT TO REMORT AREA

    DWORD itemId;
    if( FlagUserAlignment >= 0 ){
        itemId = __OBJ_REMORT_WHITE_WINGS;
    }else{
        itemId = __OBJ_REMORT_BLACK_WINGS;
    }
    // Create seraph wings.
    Objects *obj = new Objects;
    if( obj->Create( U_OBJECT, itemId ) ){
        DWORD itemGlobalId = obj->GetID();

        // Add the wings to the backpack.
        ch->AddToBackpack( obj );
        
        // And equip them
        ch->equip_object( itemGlobalId );
    }

    TeleportFunc( x, y, world, ch );

    TFCPacket sending;
    sending << (RQ_SIZE)RQ_Remort;
    ch->SendPlayerMessage( sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
bool EXPORT __IsBlocked
//////////////////////////////////////////////////////////////////////////////////////////
// Makes the NPC check for a clear path to the target
// 
( 
 Unit *self,		// The NPC
 Unit *target		// The Player
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( (self != NULL) && (target != NULL))
	{
		WorldPos tempPos;
		WorldMap *wlWorld = TFCMAIN::GetWorld( self->GetWL().world );
		Unit *lpCollisionUnit = NULL;

		if (wlWorld->GetCollisionPos( self->GetWL(), target->GetWL(), &tempPos, &lpCollisionUnit, false, false )) {
			return TRUE;
		}

		return FALSE;
	} else {
		return FALSE;
	}
}

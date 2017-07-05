// GAME_RULES.cpp: implementation of the GAME_RULES class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "GAME_RULES.h"
#include "AutoConfig.h"
#include "Random.h"
#include "ObjectListing.h"
#include "blockinglisting.h"
#include "QUestFlagsListing.h"
#include "NPCmacroScriptLng.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern Random rnd;
extern CTFCServerApp theApp;

BYTE GAME_RULES::bPVPRule = PVP_LEVEL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GAME_RULES::GAME_RULES()
{    
}

GAME_RULES::~GAME_RULES()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
// Helper inline functions.
inline void AddPVPVar( LPCTSTR lpszValue, int nDefault ){
    CAutoConfig::AddRegInt( T4C_KEY "PVPDeath", lpszValue, nDefault );
};

inline int QueryPVPVar( LPCTSTR lpszValue ){
    return CAutoConfig::GetIntValue( T4C_KEY "PVPDeath", lpszValue );
}
//////////////////////////////////////////////////////////////////////////////////////////
void GAME_RULES::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creates the game rule.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    AddPVPVar( "MIN_PVP", 9 );
    AddPVPVar( "PVP_RANGE", 2 );
    AddPVPVar( "MOB_BACKPACK_LOSS", 5 );
    AddPVPVar( "MOB_EQUIP_LOSS", 0 );
    AddPVPVar( "MOB_XP_LOSS", 5 );
    AddPVPVar( "MOB_GOLD_LOSS", 0 );
	AddPVPVar( "MOB_GOLD_DROP", 0 );
    AddPVPVar( "PC_BACKPACK_LOSS", 1 );
    AddPVPVar( "PC_EQUIP_LOSS", 0 );
    AddPVPVar( "PC_XP_LOSS", 1 );
    AddPVPVar( "PC_GOLD_LOSS", 0 );
	AddPVPVar( "PC_GOLD_DROP", 0 );
	AddPVPVar( "CRIME_POINTS", 0 );
}

////////////////////////////////////////////////////////////////////////////////////////////////
// This function returns the precision of a blow
DWORD GAME_RULES::GetBlowPrecision(DWORD dwAttackSkill, DWORD dwDodgeSkill, DWORD dwAttackAgi, DWORD dwTargetAgi ){
//(rnd( 1, dwAttackSkill ) + rnd( 1, dwAttackAgi / 3 ) ) - rnd( 1, dwDodgeSkill ) + rnd( 1, dwTargetAgi / 3) )

	dwAttackSkill = dwAttackSkill > 0 ? dwAttackSkill : 1;
	dwDodgeSkill = dwDodgeSkill > 0 ? dwDodgeSkill : 1;
	return( ( rnd( 1, dwAttackSkill ) + rnd( 1, dwAttackAgi / 3 ) ) - ( rnd( 1, dwDodgeSkill ) + rnd( 1, dwTargetAgi / 3 ) ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Returns the strength (natural) damage of a unit
DWORD GAME_RULES::GetNaturalDamage(Unit *lpuUnit){
    DWORD rtn = 0;
    
    if( lpuUnit->GetType() == U_PC ){
        Character *ch = static_cast< Character * >( lpuUnit );

        if( ch->RangedAttack() ){
            if( lpuUnit->GetSTR() >= 20 ){
                rtn = ( lpuUnit->GetSTR() - 20 ) / 20;
            }
            if( lpuUnit->GetAGI() >= 20 ){
                rtn += ( lpuUnit->GetAGI() - 20 ) / 10;
            }

            return rtn;
        }
    }
    if( lpuUnit->GetSTR() >= 20 ){
        rtn = ( lpuUnit->GetSTR() - 20 ) / 5;   
	    rtn = rtn > 0 ? rtn : 0;
    }
	return( rtn );
}

//////////////////////////////////////////////////////////////////////////////////////////
void GAME_RULES::HPregen
//////////////////////////////////////////////////////////////////////////////////////////
// Regenerates the unit's HP
// 
(
 Unit *lpuRegen // Unit on which we should regenerate HP
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	DWORD HP	= lpuRegen->GetHP();
	DWORD MaxHP = lpuRegen->GetMaxHP();
	BOOL boUpdate = FALSE;

	TRACE( "\r\n\r\n1-HP %u MaxHP %u\r\n", HP, MaxHP );
	// If HP is lower then maxHP, regen tends to pull it to it's normal state
	if(HP < MaxHP){
        int nRegen = rnd( 0, lpuRegen->GetEND() / 40 ) + 1;

        nRegen = nRegen < 0 ? 0 : nRegen;

        if( rnd( 1, 100 ) <= 60 ){
            HP += nRegen;            

            HP = HP > MaxHP ? MaxHP : HP;
            lpuRegen->SetHP( HP, true );

            boUpdate = TRUE;
        }        
    }
	// Otherwise regen tends to pull it back to it's normal state
	else{		
		HP -= MaxHP * 5 PERCENT;
		HP = HP < MaxHP ? MaxHP : HP;
		boUpdate = TRUE;
        lpuRegen->SetHP( HP, true );
	}
	TRACE( "\r\n2-HP %u MaxHP %u\r\n", HP, MaxHP );
}

//////////////////////////////////////////////////////////////////////////////////////////
void GAME_RULES::ManaRegen
//////////////////////////////////////////////////////////////////////////////////////////
// Regenerates the units mana.
// 
(
 Unit *lpuRegen // The unit which wants to regenerate
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	int nMana		= lpuRegen->GetMana();
	int nMaxMana	= lpuRegen->GetMaxMana();

	// If HP is lower then maxHP, regen tends to pull it to it's normal state
	if( nMana < nMaxMana ){
        int nRegen = rnd( 0, lpuRegen->GetINT() / 160 ) + lpuRegen->GetINT() / 160 + 
                     rnd( 0, lpuRegen->GetWIS() / 160 ) + lpuRegen->GetWIS() / 160 + 1;

        
        if( rnd( 1, 100 ) <= 60 ){
            nMana += nRegen;

            nMana = nMana > nMaxMana ? nMaxMana : nMana;

            lpuRegen->SetMana((WORD)nMana);
        }
	}
	// Otherwise regen tends to pull it back to it's normal state
	else{
		nMana -= nMaxMana * 2 PERCENT;
		nMana = nMana < nMaxMana ? nMaxMana : nMana;

        lpuRegen->SetMana((WORD)nMana);
	}	
}

//////////////////////////////////////////////////////////////////////////////////////////
void GAME_RULES::FaithRegen
//////////////////////////////////////////////////////////////////////////////////////////
// Regenerates the units faith
// 
(
 Unit *lpuRegen // Unit which should regenerate its faith
)
//////////////////////////////////////////////////////////////////////////////////////////
{
/*	WORD Faith		= lpuRegen->GetFaith();
	WORD MaxFaith	= lpuRegen->GetMaxFaith();

	// If HP is lower then maxHP, regen tends to pull it to it's normal state
	if(Faith < MaxFaith){
		Faith += MaxFaith * 5 PERCENT;
		Faith = Faith > MaxFaith ? MaxFaith : Faith;
	}
	// Otherwise regen tends to pull it back to it's normal state
	else{
		Faith -= MaxFaith * 5 PERCENT;
		Faith = Faith < MaxFaith ? MaxFaith : Faith;
	}

	lpuRegen->SetFaith(Faith); */
}

//////////////////////////////////////////////////////////////////////////////////////////
void GAME_RULES::DeathPenalties
//////////////////////////////////////////////////////////////////////////////////////////
// Applies the penalties of a player's death.
// 
(
 Character *chUser,         // The character who died.
 Unit *lpAttacker,          // The attacker (may be NULL).
 TemplateList< Unit > *invSpillList,
 TemplateList< Unit > *equipSpillList,// The list of objects to spill.
 DWORD &goldLoss
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    enum{ DeathPVP, DeathMob };     

    int nDeathType = DeathMob;
    
    // Determine if this was a death by PVP.
    if( lpAttacker != NULL ){
        if( lpAttacker->GetType() == U_PC ){
            nDeathType = DeathPVP;

/////////////////////////////////////////////////////////////////////
/////////////////////TEST XP OR FLAG GAIN////////////////////////////
/////////////////////////////////////////////////////////////////////
			if(BATTLE_MODE)
			{
			
			if( (lpAttacker->ViewFlag(__FLAG_TEAM) == 1) & (chUser->ViewFlag(__FLAG_TEAM) == 2))
			{
				__int64 xp = lpAttacker->GetXP();
				__int64 xp2 = chUser->GetXP();
				__int64 gold = lpAttacker->GetGold();
				__int64 gold2 = chUser->GetGold();
				__int64 kill = lpAttacker->ViewFlag(__FLAG_KILL);
				
				lpAttacker->SetXP(xp + (XPTM1KILLTM2*xp2)); // Si l'equipe Good tue la personne
				lpAttacker->SetGold(gold + (GOLDTM1KILLTM2*gold2));
				lpAttacker->SetFlag(__FLAG_KILL, (kill + 1));
				if( lpAttacker->GetKarma() <= 0 )
				{
					lpAttacker->SetKarma((lpAttacker->GetKarma()) + KARMATM1KILLTM2);
				}
				else
				{
					lpAttacker->SetKarma((lpAttacker->GetKarma()) - KARMATM1KILLTM2);
				}
				lpAttacker->SendSystemMessage("You gained  1 point for team 1!");

				if(lpAttacker->ViewFlag(__FLAG_KILL) == BONUSKILL1)
				{

					lpAttacker->SetXP(xp + (XPBONUS1*xp2));
					lpAttacker->SetGold(gold + GOLDBONUS1);
					CString fff;
					fff.Format("You gained an extra bonus of experience points for your %u th murder", BONUSKILL1);
					lpAttacker->SendSystemMessage(fff);
					//lpAttacker->SendSystemMessage("You gained an extra bonus of experience points for your 10th murder");
				}
				else if (lpAttacker->ViewFlag(__FLAG_KILL) == BONUSKILL2)
				{
					lpAttacker->SetXP(xp + (XPBONUS2*xp2));
					lpAttacker->SetGold(gold + GOLDBONUS2);
					CString fff;
					fff.Format("You gained an extra bonus of experience points for your %u th murder", BONUSKILL2);
					lpAttacker->SendSystemMessage(fff);
					//lpAttacker->SendSystemMessage("You gained an extra bonus of experience points for your 25th murder");
				}
				else if (lpAttacker->ViewFlag(__FLAG_KILL) == BONUSKILL3)
				{
					lpAttacker->SetXP(xp + (XPBONUS3*xp2));
					lpAttacker->SetGold(gold + GOLDBONUS3);
					CString fff;
					fff.Format("You gained an extra bonus of experience points for your %u th murder", BONUSKILL3);
					lpAttacker->SendSystemMessage(fff);
					//lpAttacker->SendSystemMessage("You gained an extra bonus of experience points for your 50th murder");
				}
			
				//Character::AddTotalKill("good", true);
			}
			else if( (lpAttacker->ViewFlag(__FLAG_TEAM) == 2) & (chUser->ViewFlag(__FLAG_TEAM) == 1))
			{
				__int64 xp = lpAttacker->GetXP();
				__int64 xp2 = chUser->GetXP();
				__int64 gold = lpAttacker->GetGold();
				__int64 gold2 = chUser->GetGold();
				__int64 kill = lpAttacker->ViewFlag(__FLAG_KILL);
					
				lpAttacker->SetXP(xp + (XPTM2KILLTM1*xp2)); // Si l'equipe Evil tue la personne
				lpAttacker->SetGold(gold + (GOLDTM2KILLTM1*gold2));
				lpAttacker->SetFlag(__FLAG_KILL, (kill + 1));
				
				if( lpAttacker->GetKarma() <= 0 ) 
				{
					lpAttacker->SetKarma((lpAttacker->GetKarma()) + KARMATM1KILLTM2);
				}
				else
				{
					lpAttacker->SetKarma((lpAttacker->GetKarma()) - KARMATM1KILLTM2);
				}
					
				lpAttacker->SendSystemMessage("You gained  1 point for team 2!");
				
			    if(lpAttacker->ViewFlag(__FLAG_KILL) == BONUSKILL1)
				{
					lpAttacker->SetXP(xp + (XPBONUS1*xp2));
					lpAttacker->SetGold(gold + GOLDBONUS1);
					CString fff;
					fff.Format("You gained an extra bonus of experience points for your %u th murder", BONUSKILL1);
					lpAttacker->SendSystemMessage(fff);
					//lpAttacker->SendSystemMessage("You gained an extra bonus of experience points for your 10th murder");
				}
				else if (lpAttacker->ViewFlag(__FLAG_KILL) == BONUSKILL2)
				{
					lpAttacker->SetXP(xp + (XPBONUS2*xp2));
					lpAttacker->SetGold(gold + GOLDBONUS2);
					CString fff;
					fff.Format("You gained an extra bonus of experience points for your %u th murder", BONUSKILL2);
					lpAttacker->SendSystemMessage(fff);
					//lpAttacker->SendSystemMessage("You gained an extra bonus of experience points for your 25th murder");
				}
				else if (lpAttacker->ViewFlag(__FLAG_KILL) == BONUSKILL3)
				{
					lpAttacker->SetXP(xp + (XPBONUS3*xp2));
					lpAttacker->SetGold(gold + GOLDBONUS3);
					CString fff;
					fff.Format("You gained an extra bonus of experience points for your %u th murder", BONUSKILL3);
					lpAttacker->SendSystemMessage(fff);
					//lpAttacker->SendSystemMessage("You gained an extra bonus of experience points for your 50th murder");
				}

				//Character::AddTotalKill("evil", true);
			}
			else
			{
				__int64 xp = lpAttacker->GetXP();
				__int64 xp2 = chUser->GetXP();
				__int64 gold = lpAttacker->GetGold();
				__int64 gold2 = chUser->GetGold();
				__int64 kill = lpAttacker->ViewFlag(__FLAG_KILL);
				
					
				lpAttacker->SetXP(xp - (XPLOSTSAMETEAM*xp2)); // Si deux joueurs de la meme equipe s'entre tues.
				lpAttacker->SetGold(gold - (GOLDLOSTSAMETEAM*gold2));
				lpAttacker->SetFlag(__FLAG_TEAM_KILLING, (kill + 1));

				lpAttacker->SendSystemMessage("{You just team-killed one of yours!!{");

				if(lpAttacker->GetKarma() <= 0)
				{
					lpAttacker->SetKarma((lpAttacker->GetKarma()) - KARMALOSTTK);
				}
				else
				{
					lpAttacker->SetKarma((lpAttacker->GetKarma()) + KARMAGAINTK);
				}
			}
			}
/////////////////////////////////////////////////////////////////////
/////////////////////TEST XP OR FLAG GAIN////////////////////////////
/////////////////////////////////////////////////////////////////////
        }
    }

    double dXPLoss = 0;
    int    nBackpackLoss = 0;
    int    nEquipLoss = 0;
    int    nGoldLoss = 0;
	int	   nGoldDrop = 0;

	// Get the level cap of the user.
    WORD wLevel = chUser->GetLevel();
	
    if(wLevel >= MAX_LEVEL){
		wLevel = MAX_LEVEL - 1;
    }else if( wLevel == 0 ){
        wLevel = 1;
    }

	if( nDeathType == DeathMob ){
        // Query mob-death variables.
		//BLBLBL 14/12/2010 : Si on met une valeur entre 900 et 999, ça augmente virtuellement niveau de drop progressif, entre +0% et +99%.
		//Donc, 900 : est équivalent à level %, 950 : est équivalent à Level+50%, 999 est équivalent à level+99%

        dXPLoss       = (double)QueryPVPVar( "MOB_XP_LOSS" );
		if (dXPLoss >= 900 && dXPLoss <=999) dXPLoss=(wLevel+dXPLoss-900)>=100?100:(wLevel+dXPLoss-900); //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.
		dXPLoss /= 100.0;

        nBackpackLoss = QueryPVPVar( "MOB_BACKPACK_LOSS" );  
		if (nBackpackLoss >= 900 && nBackpackLoss <=999) nBackpackLoss=(wLevel+nBackpackLoss-900)>=100?100:wLevel+nBackpackLoss-900; //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.

		nEquipLoss    = QueryPVPVar( "MOB_EQUIP_LOSS" );   
		if (nEquipLoss >= 900 && nEquipLoss <=999) nEquipLoss=(wLevel+nEquipLoss-900)>=100?100:wLevel+nEquipLoss-900; //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.

		nGoldLoss     = QueryPVPVar( "MOB_GOLD_LOSS" );
		if (nGoldLoss >= 900 && nGoldLoss <=999) nGoldLoss=(wLevel+nGoldLoss-900)>=100?100:wLevel+nGoldLoss-900; //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.

		nGoldDrop     = QueryPVPVar( "MOB_GOLD_DROP" );
		if (nGoldDrop >= 900 && nGoldDrop <=999) nGoldDrop=(wLevel+nGoldDrop-900)>=100?100:wLevel+nGoldDrop-900; //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.
	}else{
		// if pvp drops have not been disabled (by a SysopCmd)
		if( !theApp.dwPVPDropDisabled )
		{
			// Query PC-death variables.
			dXPLoss       = (double)QueryPVPVar( "PC_XP_LOSS" );
			if (dXPLoss >= 900 && dXPLoss <=999) dXPLoss=(wLevel+dXPLoss-900)>=100?100:(wLevel+dXPLoss-900); //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.
			dXPLoss /= 100.0;

			nBackpackLoss = QueryPVPVar( "PC_BACKPACK_LOSS" );  
			if (nBackpackLoss >= 900 && nBackpackLoss <=999) nBackpackLoss=(wLevel+nBackpackLoss-900)>=100?100:wLevel+nBackpackLoss-900; //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.

			nEquipLoss    = QueryPVPVar( "PC_EQUIP_LOSS" );   
			if (nEquipLoss >= 900 && nEquipLoss <=999) nEquipLoss=(wLevel+nEquipLoss-900)>=100?100:wLevel+nEquipLoss-900; //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.

			nGoldLoss     = QueryPVPVar( "PC_GOLD_LOSS" );
			if (nGoldLoss >= 900 && nGoldLoss <=999) nGoldLoss=(wLevel+nGoldLoss-900)>=100?100:wLevel+nGoldLoss-900; //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.

			nGoldDrop     = QueryPVPVar( "PC_GOLD_DROP" );
			if (nGoldDrop >= 900 && nGoldDrop <=999) nGoldDrop=(wLevel+nGoldDrop-900)>=100?100:wLevel+nGoldDrop-900; //BLBLBL Dans le cas d'un taux de drop de 999, on met level % taux de drop.
	}else{

		}
	}
    TRACE( "\r\nXPloss=%f%%, BackpackLoss=%u, EquipLoss=%u.", dXPLoss, nBackpackLoss, nEquipLoss );

	
    // Get the differenct
    __int64 qwXpLoss;
    if( chUser->GetXP() > Character::sm_n64XPchart[wLevel - 1] ){
        qwXpLoss = chUser->GetXP() - Character::sm_n64XPchart[wLevel - 1];
        qwXpLoss = static_cast< __int64 >( static_cast< double >( qwXpLoss ) * dXPLoss );
    }else{
        // If user is already under this level's XP.
        qwXpLoss = 0;
    }
    
    __int64 qwCurrentXP = chUser->GetXP();
    if( qwCurrentXP > qwXpLoss ){
        qwCurrentXP -= qwXpLoss;
    }else{
        qwCurrentXP = 0;
    }

    chUser->SetXP( qwCurrentXP );

    // Scroll through the backpack items to determine which ones are dropped.
    TemplateList< Unit > *lpBackpack = chUser->GetBackpack();
    
    if( lpBackpack != NULL ){
        lpBackpack->ToHead();
        while( lpBackpack->QueryNext() ){
            // If this item was lost.
            if( rnd( 0, 100 ) <= nBackpackLoss )//BLBLBL mis <= au lieu de < car sinon même à 100% de drop il reste 1% de chance de pas dropper !
			{
                Objects *lpObject = static_cast< Objects * >( lpBackpack->Object() );

                _item *lpItemStructure = NULL;

                lpObject->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItemStructure );               								

                // If the object can be dropped.
                if( !( lpItemStructure->dwDropFlags & CANNOT_DROP_ITEM ) && lpObject->GetStaticReference() != (UINT)__OBJ_GOLD ){
                    lpObject->Remove();
                    if( lpObject->GetQty() == 0 ){
                        // Remove it from the backpack
                        lpBackpack->Remove();
                        
                        // Use at least one object.
                        lpObject->Add( 1 );
                    }else{
                        // Create a copy item.
                        DWORD baseID = lpObject->GetStaticReference();
                        lpObject = new Objects;
                        if( !lpObject->Create( U_OBJECT, baseID ) ){
                            lpObject->DeleteUnit();
                            lpObject = NULL;
                        }
                    }

                    if( lpObject != NULL ){
                        // And add it to the spilled objects list.
                        invSpillList->AddToTail( lpObject );
                    }
                }
            }
        }
    }

    // Scroll through the equipped items.
    Unit **lpuEquipped = chUser->GetEquipment();

    int i = 0;
    int j;
    for( i = 0; i < EQUIP_POSITIONS; i++ ){
        // If there is an item at this position.
        if( lpuEquipped[ i ] != NULL ){
            // If this item gets lost.
            if( rnd( 0, 100 ) <= nEquipLoss ){//BLBLBL mis <= au lieu de < car sinon même à 100% de drop il reste 1% de chance de pas dropper !
                Unit *lpObject = lpuEquipped[ i ];

                _item *lpItemStructure = NULL;

                lpObject->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItemStructure );

                // If the object can be dropped.
                if( !( lpItemStructure->dwDropFlags & CANNOT_DROP_ITEM ) && lpObject->GetStaticReference() != (UINT)__OBJ_GOLD ){
                    chUser->unequip_object( i, true );

                    // Remove all occurences of this item (as it may appear twice) from the equipment.
                    for( j = 0; j < EQUIP_POSITIONS; j++ ){
                        if( lpuEquipped[ j ] == lpObject ){
                            lpuEquipped[ j ] = NULL;
                        }
                    }

                    // Add the object to the spilled list.
                    equipSpillList->AddToTail( lpObject );
                }
            }
        }
    }   	

    DWORD oldGold = chUser->GetGold();
    goldLoss = oldGold * nGoldLoss / 100;
    	
	// If some gold pieces must be dropped on the ground
	if( nGoldDrop > 0 )
	{
		DWORD goldDrop = goldLoss * nGoldDrop / 100;

		if( goldDrop > 1 )
		{			
			Objects *lpGold = new Objects;
			if( !lpGold->Create( U_OBJECT, __OBJ_GOLD ) )
			{				
				lpGold->DeleteUnit();
				lpGold = NULL;
			}
			else
			{				
				lpGold->Add( goldDrop );
				invSpillList->AddToTail( lpGold );
			}
		}
	}

	// Put player to half HP.
    chUser->SetHP( chUser->GetHP() / 2, true );
}

//////////////////////////////////////////////////////////////////////////////////////////
void GAME_RULES::CalcStatBonus
//////////////////////////////////////////////////////////////////////////////////////////
// Calculates any bonus given by any stats
// 
(
 int nStat,				// The stat
 WORD wStatTrain,		// Points assigned to 
 WORD wSkillTrain,		// ..
 Character *lpPlayer	// The character
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	switch( nStat ){
	case STAT_END:{
	/*	// Get the forget pain skill strength.
		LPUSER_SKILL lpusUserSkill = lpPlayer->GetSkill( __SKILL_FORGET_PAIN );
		
		DWORD dwSkillPnts = 0;

		if( lpusUserSkill != NULL ){
			dwSkillPnts = lpusUserSkill->nSkillPnts;
		}

		// If user train endurance, calculate a new HP bonus
		int nEnd = lpPlayer->GetEND();
		DWORD dwMaxHP = lpPlayer->GetMaxHP();
		int nE;
		int nBonus;

		// Substract previous bonus.
		nEnd -= wStatTrain;
		dwSkillPnts -= wSkillTrain;
		nE = nEnd / 10;
		nBonus = nE * ( nE + 1 );
		// Remove the old endurance bonus
		if( dwSkillPnts != 0 ){
			dwMaxHP -= ( dwSkillPnts / 10 ) * nBonus;
		}else{
			dwMaxHP -= nBonus;		
		}

		dwSkillPnts += wSkillTrain;
		nEnd += wStatTrain;
		nE = nEnd / 10;
		nBonus = nE * ( nE + 1 );

		if( dwSkillPnts != 0 ){
			dwMaxHP += ( lpusUserSkill->nSkillPnts / 10 ) * nBonus;
		}else{
			dwMaxHP += nBonus;
		} */
		// Set the new HP
		//lpPlayer->SetHP( dwMaxHP );
	}break;
	
	}

}


//////////////////////////////////////////////////////////////////////////////////////////
BOOL GAME_RULES::InPVP
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if two units are in PVP range.
// 
(
 Unit *lpuFirst, // First unit.
 Unit *lpuSecond // Second unit.
)
// Return: BOOL, TRUE if the units can do PVP
//////////////////////////////////////////////////////////////////////////////////////////
{    



	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT wLevelRestriction = QueryPVPVar( "PVP_RANGE" );
    const INT wMinLevel         = QueryPVPVar( "MIN_PVP" );




    // If one of the opponents doesn't exist or if the opponent is himself.
    if( lpuFirst == NULL || lpuSecond == NULL || ( lpuFirst == lpuSecond ) ){
        return TRUE;
    }

    // If both opponents are in a FULL PVP area, allow PVP interaction.
    if( lpuFirst->GetUnderBlock() == __AREA_FULL_PVP && lpuSecond->GetUnderBlock() == __AREA_FULL_PVP ){
        return TRUE;
    }

	//BLBLBL : If player is in an arena :
	//marche pas.. faudra trouver où on choppe les coordonnées du joueur d'ici :
/*	list< sArenaLocation >::iterator i;
	bool boFound = false;	
	for( i = theApp.arenaLocationList.begin(); i != theApp.arenaLocationList.end(); ++i )
	{
		// If player is in the same world as the current location
		if( *lpuFirst.world == (*i).wlTopLeft.world )
		{
			// If player is in the good x range
			if( *lpuFirst.X >= (*i).wlTopLeft.X && *lpuFirst.X <= (*i).wlBottomRight.X )
			{
				// And if player is in the good y range
				if( *lpuFirst.Y >= (*i).wlTopLeft.Y && *lpuFirst.Y <= (*i).wlBottomRight.Y )
				{
					// Player is in this kind of area!
					boFound = true;					
					break;
				}
			}
		}
	}
	if (boFound) {
			return TRUE;
	}*/


    // If both parties are players.
    if( lpuFirst->GetType() == U_PC && lpuSecond->GetType() == U_PC ){
        // Transfert them into characters.
        Character *lpFirstChar    = static_cast< Character * >( lpuFirst );
        Character *lpSecondChar   = static_cast< Character * >( lpuSecond );
        Players   *lpFirstPlayer  = lpFirstChar->GetPlayer();
        Players   *lpSecondPlayer = lpSecondChar->GetPlayer();

        // If any of the player structures have been deleted.
        if( lpFirstPlayer == NULL || lpSecondPlayer == NULL ){
            // Refuse pvp.
            return FALSE;
        }

        // If either of the player cannot PVP.
        if( !lpFirstPlayer->CanPVP() || !lpSecondPlayer->CanPVP() ){
            return FALSE;
        }

        // If any of them are in full-PVP mode.
        if( lpFirstPlayer->IsFullPVP() || lpSecondPlayer->IsFullPVP() ){
            return TRUE;
        }

        // If both parties are in a group.
        if( lpFirstChar->GetGroup() != NULL && lpSecondChar->GetGroup() != NULL ){
            // If the second character is a member of the first character's group.
            if( lpFirstChar->GetGroup()->IsGroupMember( lpSecondChar ) ){
                // No PVP allows.
                return FALSE;
            }
        }
    }

    BOOL boPVP = TRUE;
    switch( bPVPRule ){
    case PVP_LEVEL:{
        TRACE( "\r\nlpuFirst=0x%x.lpuSecond=0x%x.", lpuFirst, lpuSecond );
        // Both must be 
        if( lpuFirst->GetType() == U_PC && lpuSecond->GetType() == U_PC ){
            // If the unit's levels aren't in range.
            if( abs( lpuFirst->GetLevel() - lpuSecond->GetLevel() ) >= wLevelRestriction ||
                lpuFirst->GetLevel() < wMinLevel || lpuSecond->GetLevel() < wMinLevel ){
                boPVP = FALSE;
            }
        }
    } break;
    }

    return boPVP;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL GAME_RULES::InSafeHaven
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if the PVP rules apply in this area.
// 
(
 Unit *lpuFirst, // 1st
 Unit *lpuSecond // 2nd
)
// Return: BOOL, TRUE if the unit is in a safe haven.
//////////////////////////////////////////////////////////////////////////////////////////
{

	if( 
        (   // If either the attacker or the attacked is on a safe-haven
            lpuFirst->GetUnderBlock() == __SAFE_HAVEN 
                || 
            lpuFirst->GetUnderBlock() == __INDOOR_SAFE_HAVEN 
                ||
			lpuSecond->GetUnderBlock() == __SAFE_HAVEN
                ||
            lpuSecond->GetUnderBlock() == __INDOOR_SAFE_HAVEN 
        )
            && 
        (   // If both the attacker and target are players.
            lpuFirst->GetType() == U_PC 
                && 
            lpuSecond->GetType() == U_PC 
        )
    ){
        return TRUE;
    }
    return FALSE;
}
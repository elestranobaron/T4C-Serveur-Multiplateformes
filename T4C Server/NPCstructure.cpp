// NPCstructure.cpp: implementation of the NPCstructure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NPCstructure.h"
#include "ObjectFlagsListing.h"
#include "TFC_MAIN.h"
#include "T4CLog.h"
#include "BlockingListing.h"
#include "IntlText.h"
#include "RegKeyHandler.h"

const int _PHYSICAL = 0;
const int _SPELL	= 1;

extern Random rnd;
extern Broadcast BCast;

#include "TFC Server.h"
extern CTFCServerApp theApp;

//#define STAND_STILL

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
NPCstructure::NPCstructure()
{
    npc.boCanExitBuilding = FALSE;
    npc.boInit = false;
    npc.name = NULL;	
}
NPCstructure::~NPCstructure(){
	//delete npc.name;
}

//////////////////////////////////////////////////////////////////////////////////////////
void NPCstructure::OnInitialise
//////////////////////////////////////////////////////////////////////////////////////////
//  Called when a NPC instance is being created.
// 
(
 UNIT_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	bool *lpboInit = static_cast< bool * >( valueIN );

    // If swap NPC wasn't initialized, creation fails.
    if( !npc.boInit ){
        *lpboInit = false;
        return;
    }
    
    npc.boCanExitBuilding = FALSE;
	
	self->SetSystemDestroy(FALSE); // avoid system idle destruction
//	self->SetStaticFlagsReference(this);
	self->SetFlag(__FLAG_CANNOT_DISPELL, 1);
	self->SetFlag(__FLAG_BLOCKING, 1);

	self->SetLevel( npc.level );
    self->SetMaxHP(npc.HP);
	self->SetHP( npc.HP, false );
	self->SetDODGE( npc.DodgeSkill );
	self->SetATTACK( 0 );
	self->SetTarget(NULL);
	self->SetSpeed(npc.speed);
	self->SetAgressivness(npc.agressive);
	self->SetClan(npc.clan);
	self->SetCorpse(npc.Corpse);
	self->SetAppearance(npc.appearance);
	//self->SetName(npc.isName.get_str( DEFAULT_LNG ) );	
	self->SetINT( npc.INT );
	self->SetEND( npc.END );
	self->SetSTR( npc.STR );
	self->SetWIS( npc.WIS );
	self->SetAGI( npc.AGI );
	self->SetAttack( npc.boCanAttack );
    
//    TRACE( "%s Private? %u.", npc.isName.get_str(), npc.boPrivateTalk );	
	self->SetPrivateTalk( npc.boPrivateTalk );


    self->SetStatus( CAN_TALK );

	///////////////////////////////
	// test
	WorldPos wlUpperLimit = npc.InitialPos;
	wlUpperLimit.X += npc.wHiXrange;
	wlUpperLimit.Y += npc.wHiYrange;
	WorldPos wlLowerLimit = npc.InitialPos;
	wlLowerLimit.X -= npc.wLoXrange;
	wlLowerLimit.Y -= npc.wLoYrange;


	self->SetUpperLimit(wlUpperLimit);
	self->SetLowerLimit(wlLowerLimit);

	WorldPos dest = {-1,-1,-1};
	self->Do(wandering);
	self->SetDestination(dest);
    self->SetBlock( __BLOCK_CAN_FLY_OVER );

    if( npc.FireResist  != 0 ){ self->SetFireResist ( npc.FireResist ); }
    if( npc.WaterResist != 0 ){ self->SetWaterResist( npc.WaterResist ); }
    if( npc.AirResist   != 0 ){ self->SetAirResist  ( npc.AirResist ); }
    if( npc.EarthResist != 0 ){ self->SetEarthResist( npc.EarthResist ); }
    if( npc.LightResist != 0 ){ self->SetLightResist( npc.LightResist ); }
    if( npc.DarkResist  != 0 ){ self->SetDarkResist ( npc.DarkResist  ); }

    if( npc.FirePower  != 0 ){ self->SetFirePower ( npc.FirePower ); }
    if( npc.WaterPower != 0 ){ self->SetWaterPower( npc.WaterPower ); }
    if( npc.AirPower   != 0 ){ self->SetAirPower  ( npc.AirPower ); }
    if( npc.EarthPower != 0 ){ self->SetEarthPower( npc.EarthPower ); }
    if( npc.LightPower != 0 ){ self->SetLightPower( npc.LightPower ); }    
    if( npc.DarkPower  != 0 ){ self->SetDarkPower( npc.DarkPower ); }	

    _LOG_NPCS
        LOG_MISC_1,
        "NPC %s was spawned.",
        self->GetName( _DEFAULT_LNG ),
        self->GetWL().X,
        self->GetWL().Y,
        self->GetWL().world
    LOG_
}

//////////////////////////////////////////////////////////////////////////////////////////
void NPCstructure::OnServerInitialisation
//////////////////////////////////////////////////////////////////////////////////////////
//  Called when the server first initializes.
// 
(
 UNIT_FUNC_PROTOTYPE,
 WORD wBaseReferenceID // The unit's base referenceID.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	npc.BaseReferenceID = wBaseReferenceID;

	TRACE( "\r\nInit NPC #%u", wBaseReferenceID );

	if(npc.appearance != -1){
		WorldMap *world = TFCMAIN::GetWorld(npc.InitialPos.world);	
		if(world){
			Unit *newNPC = world->create_world_unit(U_NPC, wBaseReferenceID, npc.InitialPos, FALSE);
			if(newNPC){
				// Then put it in the creature list for it to become alive
				TFCMAIN::AddMonster(newNPC);
			}else{
                char szID[ 256 ];
                Unit::GetNameFromID( wBaseReferenceID, szID );

                // If this NPC has no 'position' (perhaps in a hive).
                if( npc.InitialPos.X == 0 || npc.InitialPos.Y == 0 ){
				    // Only log at lvl 4.
                    _LOG_DEBUG
                        LOG_DEBUG_LVL4,
					    "Could not create NPC \"%s\" ID( %s ) at <POSSIBLY ON BLOCK> (%u, %u, %u)", 
					    npc.name,/*npc.isName.get_str( _DEFAULT_LNG )*/
                        szID,
					    npc.InitialPos.X, 
					    npc.InitialPos.Y, 
					    npc.InitialPos.world
				    LOG_
                }else{
    				_LOG_DEBUG
                        LOG_DEBUG_LVL1,
		    			"Could not create NPC \"%s\" ID( %s ) at <POSSIBLY ON BLOCK> (%u, %u, %u)", 
			    		npc.name,/*npc.isName.get_str( _DEFAULT_LNG )*/
                        szID,
    					npc.InitialPos.X, 
	    				npc.InitialPos.Y, 
		    			npc.InitialPos.world
			    	LOG_
               }

//				TRACE("\r\n\r\n!WARNING! Could not create NPC \"%s\"at <POSSIBLY ON BLOCK> (%u, %u, %u)\r\n\r\n", npc.name, npc.InitialPos.X, npc.InitialPos.Y, npc.InitialPos.X);
			}
		}else{
            char szID[ 256 ];
            Unit::GetNameFromID( wBaseReferenceID, szID );

            _LOG_DEBUG
				LOG_DEBUG_LVL1,
				"Could not create NPC ID(%u, %s) \"%s\" at <WRONG, UNDEFINED WORLD> (%u, %u, %u)\r\n\r\n", 
				wBaseReferenceID,
                szID,
                npc.name,//npc.isName.get_str( _DEFAULT_LNG ), 
				npc.InitialPos.X, 
				npc.InitialPos.Y, 
				npc.InitialPos.world
			LOG_
//			TRACE("\r\n\r\n!WARNING! Could not create NPC \"%s\" at <WRONG, UNDEFINED WORLD> (%u, %u, %u)\r\n\r\n", npc.name, npc.InitialPos.X, npc.InitialPos.Y, npc.InitialPos.X);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void NPCstructure::OnAttack
//////////////////////////////////////////////////////////////////////////////////////////
//  If NPC attacks.
// 
(
 UNIT_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPATTACK_STRUCTURE Blow = (LPATTACK_STRUCTURE)valueIN;
	int  WhichAttack = 0;

	// If there are monster attacks.
    if( !npc.vlpMonsterAttacks.empty() ){
		WhichAttack = rnd(0, npc.vlpMonsterAttacks.size() - 1);
		
        // Deal damage.
        Blow->Strike += npc.vlpMonsterAttacks[ WhichAttack ]->DamageRoll.GetBoost( self, target );			
		
		self->SetATTACK( npc.vlpMonsterAttacks[ WhichAttack ]->AttackSkill );
	}
			
	TRACE("Value of Strike(attack)=%u\r\n", Blow->Strike);	
}
//////////////////////////////////////////////////////////////////////////////////////////
void NPCstructure::OnAttacked
//////////////////////////////////////////////////////////////////////////////////////////
//  When NPC gets attacked
// 
(
 UNIT_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPATTACK_STRUCTURE Blow = (LPATTACK_STRUCTURE)valueIN;

	Blow->Strike -= self->GetAC(); // remove monster's AC
	
	TRACE("Value of Strike(after defense)=%u\r\n", Blow->Strike);
}

//////////////////////////////////////////////////////////////////////////////////////////
void NPCstructure::OnHit
//////////////////////////////////////////////////////////////////////////////////////////
// When NPC gets struck
// 
(
 UNIT_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPATTACK_STRUCTURE Blow = (LPATTACK_STRUCTURE)valueIN;
	
    if( npc.boCanAttack ){
        if( self != NULL && target != self ){
            self->SetTarget( target );
            self->Do( fighting );
        }
    }

	if( target->GetType() != U_PC ){									//DC for GPs
        return;
    }

// Il semble qu'il peut y avoir un target=U_PC pour un Player=NULL		//DC for GPs
	if ( static_cast< Character * >( target )->GetPlayer() == NULL ){	//DC for GPs
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
			"DC - GPs - target->GetPlayer() is a null pointer while NPCstructure::OnHit."
		LOG_
	}
	if( static_cast< Character * >( target )->GetPlayer() != NULL ){	//DC for GPs

        TRACE("Value of Strike(hit)=%f\r\n", Blow->Strike);
	    __int64 xp = target->GetXP();
        __int64 lastxp = target->GetXP();
	    TRACE("XP before %u  ", xp);	
	    if(Blow->Strike > 0){
		    __int64 n64XPGain;
		    
            DWORD dwHP = self->GetHP();
            // If blow does more damage than the monster's current HP
            if( dwHP < Blow->Strike ){
                // Give XP equal to the creature's XP
			    n64XPGain = (int)( npc.XPperHit * dwHP );
            }else{
                // Get the blow's xp.
                n64XPGain = (int)( npc.XPperHit * Blow->Strike );
            }
	
            if( n64XPGain > 0 )
			{
				RegKeyHandler regKey;
				regKey.Open( HKEY_LOCAL_MACHINE, "SOFTWARE\\Vircom\\The 4th Coming Server\\GeneralConfig" );

				__int64 XPNormalRatio = regKey.GetProfileInt( "XPNormalRatio", 1 );
				__int64 XPMaxLevelXpMultiplier = regKey.GetProfileInt( "XPMaxLevelXpMultiplier", 250 );//BLBLBL 24/12/2010

                Players *lpPlayer = static_cast< Character *>( target )->GetPlayer();
				//n64XPGain *= XPNormalRatio;
				if (target->GetLevel()<=XPMaxLevelXpMultiplier) {//BLBLBL 24/12/2010
					// Apply the ratio
					n64XPGain *= XPNormalRatio;
				}

                if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_BOOST_XP )
				{
					int XPBoostRatio = regKey.GetProfileInt( "XPBoostRatio", 10 );

                    //n64XPGain *= 10;
					n64XPGain *= XPBoostRatio;
                }

				regKey.Close();

                if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                    TFormat format;
                    target->SendSystemMessage(
                        format(
                            "Gained %I64u xp (hit).",
                            n64XPGain
                        )
                    );
                }
                
                xp += n64XPGain;
            }

		    
		    TRACE("XP after %u\r\n", xp);
            // If player gained xp.
            if( xp > lastxp && target->GetLevel() < MAX_LEVEL ){
                // Cannot gain more then 2 levels..!
                if( xp < Character::sm_n64XPchart[ target->GetLevel() + 1 ] ){                        
                    if( theApp.dwLogXPGains != 0 && n64XPGain > 10 * Blow->Strike ){
                        _LOG_PC
                            LOG_WARNING,
                            "Player %s gained %I64u xp striking monster %s ( ID %u ).",
                            (LPCTSTR)target->GetName( _DEFAULT_LNG ),
                            n64XPGain,
                            (LPCTSTR)self->GetName( _DEFAULT_LNG ),
                            self->GetStaticReference()
                        LOG_
                    }

                    target->SetXP(xp);
                }
            }
	    }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void NPCstructure::OnDeath
//////////////////////////////////////////////////////////////////////////////////////////
// When monster dies
// 
(
 UNIT_FUNC_PROTOTYPE // self/medium etc
)
//////////////////////////////////////////////////////////////////////////////////////////
{	
    if( target != NULL ){
        if( target->GetType() == U_PC ){
            _LOG_NPCS
                LOG_DEBUG_LVL3,
                "Player %s killed creature %s. ( pladdr=0x%x, mnaddr=0x%x )",
                (LPCTSTR)target->GetName( _DEFAULT_LNG ),
                (LPCTSTR)self->GetName( _DEFAULT_LNG ),
                target,
                self
            LOG_
        }else{
            _LOG_NPCS
                LOG_DEBUG_LVL3,
                "Creature %s killed creature %s. ( pladdr=0x%x, mnaddr=0x%x )",
                (LPCTSTR)target->GetName( _DEFAULT_LNG ),
                (LPCTSTR)self->GetName( _DEFAULT_LNG ),
                target,
                self
            LOG_
        }
    }


//	if( target != NULL ){												//DC for GPs
// Il semble qu'il peut y avoir un target=U_PC pour un Player=NULL		//DC for GPs
	if( target != NULL && 
        target->GetType() == U_PC ){

        if( static_cast< Character * >( target )->GetPlayer() == NULL ){	//DC for GPs
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "DC - GPs - target->GetPlayer() is a null pointer while NPCstructure::OnDeath."
            LOG_
        }else{
            __int64 xp = target->GetXP();
	        TRACE("XP before %u  ", xp);	
	    
	        __int64 n64XPGain = (__int64)( ( npc.XPperDeath * npc.level ) / target->GetLevel() );			

	        if( n64XPGain > npc.XPperDeath ){
		        n64XPGain = (__int64)npc.XPperDeath;
	        }
            // If the killer is a PC higher then level 10
            if( target->GetType() == U_PC && target->GetLevel() > 10 ){
                Character *ch = static_cast< Character * >( target );
                // Make sure that he doesn't get more than 5% of the quantity
                // of XP required between two levels.            
                __int64 maxXpDiff = (ch->NextLevelXP() - ch->PreviousLevelXP()) / 20;
                if( n64XPGain > maxXpDiff ){
                    n64XPGain = maxXpDiff - 1;
                }
            }

			__int64 n64XPGainPure = n64XPGain;//BLBLBL 04/01/2011
            __int64 boostGain = 0;

			RegKeyHandler regKey;
			regKey.Open( HKEY_LOCAL_MACHINE, "SOFTWARE\\Vircom\\The 4th Coming Server\\GeneralConfig" );

			__int64 XPNormalRatio = regKey.GetProfileInt( "XPNormalRatio", 1 );
			__int64 XPMaxLevelXpMultiplier = regKey.GetProfileInt( "XPMaxLevelXpMultiplier", 250 );
			// Set the ratio
			//n64XPGain *= XPNormalRatio;
			if (target->GetLevel()<=XPMaxLevelXpMultiplier) {//BLBLBL 24/12/2010
				// Apply the ratio
				n64XPGain *= XPNormalRatio;				
			}		    
            // If this is a player that has boost xp flag.
            if( target->GetType() == U_PC && 
                static_cast< Character * >( target )->GetPlayer()->GetGodFlags() & GOD_BOOST_XP )
			{
				int XPBoostRatio = regKey.GetProfileInt( "XPBoostRatio", 10 );
				
                boostGain = n64XPGain * XPBoostRatio;
                xp += boostGain;

				// Set player's xp now.
                target->SetXP( xp );            
            }
			else
			{				
                xp += n64XPGain;
            }

			regKey.Close();
        
    
            if( theApp.dwLogXPGains != 0 && n64XPGain > 1000 ){
                _LOG_PC
                    LOG_WARNING,
                    "Player %s gained %I64u xp killing creature %s ( ID %u ).",
                    (LPCTSTR)target->GetName( _DEFAULT_LNG ),
                    n64XPGain,
                    (LPCTSTR)self->GetName( _DEFAULT_LNG ),
                    self->GetStaticReference()
                LOG_        
            }
        
            // If XP was gained and target is a Character.
            if( n64XPGain > 0 && target->GetType() == U_PC ){          
                // Convert the attacker to character.
                Character *lpCharacter = static_cast< Character * >( target );
            
                // If the character is NOT grouped
                if( lpCharacter->GetGroup() == NULL ){
                    // If the character is a GOD_DEVELOPPER
                    Players *lpPlayer = lpCharacter->GetPlayer();
                    if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                        if( boostGain != 0 ){
                            // Send debug information.
                            TFormat format;
                            target->SendSystemMessage(
                                format(
                                    "Gained %I64u xp (death).",
                                    boostGain
                                )
                            );                        
                        }else{                    
                            // Send debug information.
                            TFormat format;
                            target->SendSystemMessage(
                                format(
                                    "Gained %I64u xp (death).",
                                    n64XPGain
                                )
                            );
                        }
                    }

                    // Set player's xp.
                    lpCharacter->SetXP( xp );            
                }else{
                    // Otherwise let the group distribute the XP.
                    lpCharacter->GetGroup()->DistributeKillXP( lpCharacter, n64XPGainPure ); //BLBLBL 04/01/2011 en groupe on ne prend pas le bonus d'xp des bas levels
                }
            }
        }
    }//endif( target != NULL && target->GetPlayer() != NULL )	

	
	UINT i;
	vector< ItemToGive > &vDeathItems = npc.vDeathItems;	// for ease of use.
	TemplateList <Unit> *Holdings = (TemplateList<Unit> *)valueOUT;

    const INT DeathItemPrecision = 1000000; // steph ajout de INT
	for(i = 0; i < npc.vDeathItems.size(); i++)
	{
		double dProb = 0;

		/*if( target != NULL ) //BLBLBL désactivation du taux de drop personnalisé en fonction de la chance
			dProb = (( vDeathItems[ i ].ItemGivePercentage * DeathItemPrecision ) * target->GetLCK() / 100);
		else*/
			dProb = ( vDeathItems[ i ].ItemGivePercentage * DeathItemPrecision );

		if(rnd(0, 100 * DeathItemPrecision ) < dProb )
		{
			Objects *item = new Objects;
            if( item->Create(U_OBJECT, vDeathItems[ i ].ItemID) ){
			    Holdings->AddToTail(item);
            }else{
                item->DeleteUnit();
            }
		}
	}


// Il semble qu'il peut y avoir un target=U_PC pour un Player=NULL		//DC for GPs
	if( target == NULL ){	//DC for GPs
        return;
    }

    for(i=0; i<npc.vOnDeathFlag.size();i++)
    {
       // Checks flags to give
       if( npc.vOnDeathFlag[i].nDeathGiveFlag != 0 )
       {
           // If flag value should be incremented.
           if( npc.vOnDeathFlag[i].boDeathFlagIncrement )
           {
               // Set increment flag value.
               target->SetFlag( npc.vOnDeathFlag[i].nDeathGiveFlag, target->ViewFlag( npc.vOnDeathFlag[i].nDeathGiveFlag ) + npc.vOnDeathFlag[i].nDeathFlagValue );
           }
           else
           {
               // Sets the flag value.
               target->SetFlag( npc.vOnDeathFlag[i].nDeathGiveFlag, npc.vOnDeathFlag[i].nDeathFlagValue );
           }
       }
    }



    // If target is a character.
    if( target->GetType() != U_PC ){
        return;
    }
    
	// Cast character.
    Character *lpCharacter = static_cast< Character * >( target );

    if ( lpCharacter->GetPlayer() == NULL ){	//DC for GPs
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "DC - GPs - target->GetPlayer() is a null pointer while NPCstructure::OnDeath."
        LOG_
    }
    
    // Give gold to the target	
    DWORD dwGold = rnd( npc.MinGold, npc.MaxGold );    

    // If character is NOT grouped.
    if( lpCharacter->GetGroup() == NULL ){        
        // Simply update its gold.
        lpCharacter->SetGold( target->GetGold() + dwGold );
    }else{
        // Otherwise let the group distribute the gold.
        lpCharacter->GetGroup()->DistributeKillGold( lpCharacter, dwGold );
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
MonsterStructure *NPCstructure::NPC::GetMonsterStructure( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the monster structure associated with a NPC
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	return this;
}

////////////////////////////////////////////////////////////////////////////////////////
// Dead function, only there for virtual purposes
void NPCstructure::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE ){};

////////////////////////////////////////////////////////////////////////////////////////
// Returns the structure of the NPC
void NPCstructure::OnGetUnitStructure( UNIT_FUNC_PROTOTYPE ){
	(*(MonsterStructure **)valueOUT) = &npc;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This function is polled to see if the NPC has any "time-relative" behavior
void NPCstructure::OnQuerySchedule( UNIT_FUNC_PROTOTYPE ){
}

void NPCstructure::OnAttackHit( UNIT_FUNC_PROTOTYPE ){};

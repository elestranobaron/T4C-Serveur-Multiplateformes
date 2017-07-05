#include "stdafx.h"
#include "TFC Server.h"
#include "Unit.h"
#include "TFC_MAIN.h"
#include "TFC ServerDlg.h"
#include "VDList.h"
#include "Random.h"
#include "TFCTimers.h"
#include "Clans.h"
#include "Players.h"
#include "TFCServerGP.h"
#include "MonsterStructure.h"
#include <eh.h>
#include "PacketManager.h"
#include "DeadlockDetector.h"
#include <math.h>
#include "IntlText.h"
//#include "../T4C Monitor/T4C MonitorMap.h"
#include "NPC Thread.h"
#include <process.h>
#include "PlayerManager.h"
#include "ThreadMonitor.h"


void NPCExceptionFunction(unsigned int u, EXCEPTION_POINTERS* pExp){
	TFCException *excp = new TFCException;
	excp->SetException(pExp);
	throw excp;
}

////////////////////////////////////////////////////////////////////////////////////////////
extern TFC_MAIN *TFCServer;
////////////////////////////////////////////////////////////////////////////////////////////
//extern TemplateList <Players> UsersList;
namespace{
    TemplateList <Unit> CreatureList;
};
extern Random rnd;

TemplateList <Unit>           AddCreatureList;

TemplateList <DEATHROW> tluDeathRow;		// Unit must be sent to the deathrow first
Clans *CreatureClans; // 10 clans so far.
TemplateList <SubmitNearUnit> IsNearSubmission;

DWORD GetNbNPCs( void ){
    return CreatureList.NbObjects();
}

namespace{    
/*********************************************************************************************/
inline void MonsterBlocked(Unit *ThisCreature, DIR::MOVE direction){
	
	WorldPos CreatureWL = ThisCreature->GetWL();
	WorldMap *CurrentWorld = TFCMAIN::GetWorld(CreatureWL.world);
	WorldPos newPos = {0,0,0};
	WorldPos Destination = {0,0,0};
	BOOL friendly = TRUE;

	if(CurrentWorld){
	
		switch(direction){
		case DIR::north:	newPos.X = CreatureWL.X;
							newPos.Y = CreatureWL.Y - 1;
					break;
		case DIR::south:	newPos.X = CreatureWL.X;
							newPos.Y = CreatureWL.Y + 1;
					break;
		case DIR::east:		newPos.X = CreatureWL.X + 1;
							newPos.Y = CreatureWL.Y;
					break;
		case DIR::west:		newPos.X = CreatureWL.X - 1;
							newPos.Y = CreatureWL.Y;
					break;
		case DIR::northwest:	newPos.X = CreatureWL.X - 1;
								newPos.Y = CreatureWL.Y - 1;
					break;
		case DIR::northeast:	newPos.X = CreatureWL.X + 1;
								newPos.Y = CreatureWL.Y - 1;
					break;
		case DIR::southwest:	newPos.X = CreatureWL.X - 1;
								newPos.Y = CreatureWL.Y + 1;
					break;
		case DIR::southeast:	newPos.X = CreatureWL.X + 1;
								newPos.Y = CreatureWL.Y + 1;
					break;
		}	
	
		if(newPos.X >= CurrentWorld->GetMAXX() || newPos.Y >= CurrentWorld->GetMAXY()
			|| newPos.X < 0 || newPos.Y < 0){
			return;
		}

		Unit *newTarget = CurrentWorld->ViewTopUnit( newPos );
		// if bumped into a target!!
		if(newTarget){
			if(newTarget->GetType() != U_OBJECT && newTarget->GetType() != U_HIVE && ThisCreature->GetBond() != newTarget){
				WORD ThisClan = ThisCreature->GetClan();
				WORD OtherClan = newTarget->GetClan();
				DWORD OtherID = newTarget->GetID();
				
				if(ThisClan != OtherClan || !ThisClan){
					int politic = 0;
					// Returns the mutual relation between us and the encountered unit
					if(ThisClan < Clans::GetNumberOfClans() && OtherClan < Clans::GetNumberOfClans())
						politic = CreatureClans[ThisClan].MutualRelation(OtherClan, OtherID);

					// if clan is aressive towards us
					politic += ThisCreature->GetAgressivness();
						
					if(rnd(1, 100) < politic){
						// attack the bastard!
						friendly = FALSE;
						ThisCreature->SetTarget(newTarget);
						ThisCreature->Do(fighting);
					}
				}
			}
		} 
		
		if(friendly){
			// We bumped into a natural obstacle
			// try to contour it.. (a mob is stupid..)
			int MAXX = CurrentWorld->GetMAXX();
			int MAXY = CurrentWorld->GetMAXY();
			Destination.X = MAXX + 1;
			Destination.Y = MAXY + 1;
            Destination.world = CreatureWL.world;
			while(Destination.X < 0 || Destination.X >= MAXX || Destination.Y < 0 || Destination.Y >= MAXY){
				Destination.X = rnd(CreatureWL.X - 5, CreatureWL.X + 5);
				Destination.Y = rnd(CreatureWL.Y - 5, CreatureWL.Y + 5);
				// then invite the monster to go to it's new destination

				ThisCreature->SetDestination(Destination);
				ThisCreature->SetTarget(ThisCreature->GetBond());
				ThisCreature->Do(wandering);

			}								
		}
	}
}

    typedef struct DUH{
        sockaddr_in          sockAddr;
        LPBYTE               lpBuffer;
        int                  nBufferLen;
        DWORD                dwAckDelay;
        DWORD                dwTimeout;
        DWORD                dwAckCount;
        CLock                cLock;
    } *LPDUH;
}//anonymous namespace.

void __declspec( dllexport ) BeforeNPCThread( void ){};

//////////////////////////////////////////////////////////////////////////////////////////
unsigned int CALLBACK NPCMain::NPCThread
//////////////////////////////////////////////////////////////////////////////////////////
//  This is the main NPC thread.
// 
(
 void *pParam // NULL
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("NPC Thread");
    GetInstance().NPCThreadFunc();

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void NPCMain::NPCThreadFunc( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Called by NPCThread.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

TemplateList <DEATHROW> tluElectricChair;	// the system will send them to the electric chair

START_DEADLOCK_DETECTION( hNPCThread, "NPC Thread" );

    // Sleeps until we are ready to start the thread
	int PriorityChange = 1;
	int lastsecond = 0;
	Unit *ThisCreature;
	SubmitNearUnit *nearObj;
    
	while( !boNPCThreadDone ) // Main NPC Loop
	{

        KEEP_ALIVE
        
		WorldPos playerPos;
		IsNearSubmission.Lock();

		IsNearSubmission.ToHead();
		while(IsNearSubmission.QueryNext()){	//Is Near Submission loop
			nearObj = IsNearSubmission.Object();
			ThisCreature = nearObj->target;                

			playerPos = ThisCreature->GetWL();


			WorldMap *wlWorld = TFCMAIN::GetWorld( playerPos.world );
			
			if( wlWorld ){
				// queries if there is a player near this monster.
				nearObj->IsInView = wlWorld->IsNearPlayer( playerPos );
			}else{
				// otherwise destroy the unit
				nearObj->IsInView = TRUE;//BLBLBL truc louche ici .. en théorie faudrait mettre FALSE !
			}


			// if not inview, then do whatever it has to do ;)
			if(!nearObj->IsInView){
				switch(nearObj->Submission){
				case SubmitNearUnit::ToDestroy:
                    ThisCreature->Lock();
					if( nearObj->NoticeDeletion ){
                        Broadcast::BCObjectRemoved( playerPos, _DEFAULT_RANGE,
                            ThisCreature->GetID()
                        );
					}
					TFCServer->World[playerPos.world].remove_world_unit(playerPos, ThisCreature->GetID());					    
                    ThisCreature->KillCreature();
                    ThisCreature->Unlock();
					break;
				case SubmitNearUnit::ToCreate:
					BOOL boValidate = TRUE;
					
					if( boValidate ){
						// If unit could be created.
						if( TFCServer->World[playerPos.world].create_world_unit(U_NPC, 0, playerPos, ThisCreature) != NULL ){						
							EXHAUST newExhaust = {0,0,0};
							ThisCreature->SetExhaust(newExhaust);
							ThisCreature->SetIdleTime(TFCMAIN::GetRound() + _MONSTER_LIFE_SPAN);
							TFCMAIN::AddMonster(ThisCreature);
						}else{
							ThisCreature->DeleteUnit();
						}
					}else{
						ThisCreature->DeleteUnit();					
					}
				break;
				}
			}else{ // if it WAS in view, well delete the target
				switch(nearObj->Submission){
				case SubmitNearUnit::ToDestroy:{EXHAUST newExhaust = {0,0,0};
												nearObj->target->SetExhaust(newExhaust);
												nearObj->target->SetIdleTime(TFCMAIN::GetRound() + _MONSTER_LIFE_SPAN);
												nearObj->target->Do(wandering);
												WorldPos wlNewDest = { -1, -1, -1 };
												nearObj->target->SetDestination( wlNewDest );
												nearObj->target->SetTarget( NULL );
												nearObj->target->SetBond( NULL );
											   }break;// don't destroy it, do something else
				case SubmitNearUnit::ToCreate:{						
						nearObj->target->KillCreature();
					}
					break;
				}					
			}
			IsNearSubmission.DeleteAbsolute();                
		}											//Is Near Submission loop
		IsNearSubmission.Unlock();

		/////////////////////////////////////////////////////////////////////////////////////////
		// Monster management		

        AddCreatureList.Lock();

        // Transfert the creatures to add in the creature list.
        AddCreatureList.ToHead();
        CreatureList.Lock();
        while( AddCreatureList.QueryNext() ){
            CreatureList.AddToHead( AddCreatureList.Object() );
            AddCreatureList.Remove();
        }
        CreatureList.Unlock();
        AddCreatureList.Unlock();

//        PERF_CNT( PRFDBG_NB_MONSTERS ) = CreatureList.NbObjects();//BLBLBL 17/12/2010 je vire t4c monitor

        DWORD Round = TFCMAIN::GetRound();

        // No more creature adding
        CreatureList.Lock();

        // Passes the electric chair, show prisonners to the PlayerManager
	    tluElectricChair.ToHead();
	    while(tluElectricChair.QueryNext()){
		    Unit *cuCondemned = tluElectricChair.Object()->lpuCondemned;
            // Remove any reference to this unit from the players.
            CPlayerManager::RemoveTargetReferences( cuCondemned );
        }
		
		CreatureList.ToHead();
		while(CreatureList.QueryNext())
		{ // If at end of list, end the loop
        	ThisCreature = CreatureList.Object();
            KEEP_ALIVE
			
            // Passes the electric chair, for public execution
			Unit *cuCondemned;
			tluElectricChair.ToHead();
			while(tluElectricChair.QueryNext())
			{
				cuCondemned = tluElectricChair.Object()->lpuCondemned;
				// If the creature targetted the unit that is to be killed, then dereference it			
				if(ThisCreature->GetBond() == cuCondemned)
				{
					ThisCreature->SetBond(NULL);
				}
				if(ThisCreature->GetTarget() == cuCondemned)
				{
					ThisCreature->SetTarget(ThisCreature->GetBond());
					ThisCreature->Do(wandering);
					WorldPos wlNewDest = {-1, -1, -1};
					ThisCreature->SetDestination(wlNewDest);
				}
                ThisCreature->RemoveReferenceTo( cuCondemned );
			}

            BOOL  boSystemDestroy = false;
            DWORD dwCreatureIdleTime = 0;

            boSystemDestroy = ThisCreature->SystemDestroy();
            dwCreatureIdleTime = ThisCreature->GetIdleTime();

            // Check if we can play with this monster now			
			if( dwCreatureIdleTime <= Round && boSystemDestroy )
			{
				ThisCreature->SetIdleTime(-1);
				// If this creature has been wandering for enough time, try to put it to death..!
				// Sets a new structure to be evaluated for "near" players before deletion				
				SubmitNearUnit *NewSubmission = new SubmitNearUnit;
				// sets up the structure parameters
				NewSubmission->IsInView = FALSE;			// not in view
				NewSubmission->pos = ThisCreature->GetWL(); // check for pos of creature
				NewSubmission->Submission = SubmitNearUnit::ToDestroy; // destroy of submission succeeds
				NewSubmission->NoticeDeletion = TRUE;
				NewSubmission->target = static_cast <Creatures *> (ThisCreature); // Destroy this creature
				IsNearSubmission.Lock();
                IsNearSubmission.AddToHead(NewSubmission);
                IsNearSubmission.Unlock();
			}else
			{

                // Verify that the creature's target is not a god.
                // If creature is fighting and has a target.
                if( ThisCreature->IsDoing() == fighting && ThisCreature->GetTarget() != NULL )
				{

                    // If the creature's target is a character.
                    if( ThisCreature->GetTarget()->GetType() == U_PC )
					{
                        // Down-cast to the character structure.
                        Character *lpCharacter = static_cast< Character * >( ThisCreature->GetTarget() );

                        // Get the underlying Players structure.
                        Players *lpPlayer = lpCharacter->GetPlayer();
                        
                        // If the player has the god_no_monsters flag.
                        if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_NO_MONSTERS ){
                            // Reset the creature's target.
                            ThisCreature->SetTarget( NULL );
                            // Make the creature wander.
                            ThisCreature->Do( wandering );
                            // Set a wandering destination.
                            WorldPos wlWhere = { -1, -1, -1 };
                            ThisCreature->SetDestination( wlWhere );
                        }
                    }
                }

		    	// Verify the unit's timers
    			ThisCreature->VerifyTimers();
                
                MonsterStructure *lpMonsterStructure = NULL;
				ThisCreature->SendUnitMessage( MSG_OnGetUnitStructure, ThisCreature, NULL, NULL, NULL, &lpMonsterStructure );
				
				///////////////////
                // If the creature is dead.
				if( ThisCreature->IsDead() ){
                    LPDEATHROW lpMandate;
                    lpMandate = new DEATHROW;
	    			lpMandate->lpuCondemned = CreatureList.Object();
		    		lpMandate->boDelete = TRUE;
			    	tluDeathRow.AddToTail( lpMandate );
				    CreatureList.Remove();
				}
				switch(ThisCreature->IsDoing())
				{
                ///////////////
				case fighting:
				{
					////////////////////////////////////////////////////////
					// Monster fighting
					if(ThisCreature->GetExhaust().attack < Round)
					{
					
						Unit *Target = ThisCreature->GetTarget();
						WorldPos CreatureWL =  ThisCreature->GetWL();

						
						//BERSERK MODE
						//START
						//if the creature hash low hp , let's flee
						/*const unsigned long LowHp=ThisCreature->GetMaxHP()/20;
						if (ThisCreature->GetHP()<LowHp)
						{
							if ((rand()%100)<10) {
								if (rnd(0,100)<75)
								{
									ThisCreature->Do(flee);
									//Broadcast::BCServerMessage(ThisCreature->GetWL(),10,CString("Creature switch to flee Mode"));
								}
								else
								{
									ThisCreature->Do(fightingrage);
									//Broadcast::BCServerMessage(ThisCreature->GetWL(),10,CString("Creature switch to Rage Mode"));
								}
							}
						}*/
						//END BERSERKMODE

						if(Target)
						{

                            // If the creature's target is a player.
                            if( Target->GetType() == U_PC )
							{
                                // Reset the monster's idle time so it won't be deleted.
                                ThisCreature->SetIdleTime(Round + _MONSTER_LIFE_SPAN);
                            }

							WorldPos TargetWL;
						
							//TRACE("-target-0x%x\r\n", Target);
							TargetWL = Target->GetWL(); // Monsters wants to reach its target

							// If creature hit a teleport, assign a new destination.
							if( TargetWL.world != CreatureWL.world )
							{
								TRACE( "Creature's target world isn't the same!" );
								TargetWL.X = TargetWL.Y = TargetWL.world = -1;
								ThisCreature->SetTarget( ThisCreature->GetBond() );
								ThisCreature->SetDestination( TargetWL );
								ThisCreature->Do( wandering );
							}else
							{
                                int nDeltaX = abs( CreatureWL.X - TargetWL.X );
                                int nDeltaY = abs( CreatureWL.Y - TargetWL.Y );
                                int nTargetRange = (int)::sqrt((double) (nDeltaX * nDeltaX) + (nDeltaY * nDeltaY) ); // steph ajout de (double)

                                LPMONSTER_ATTACK lpRangeAttack = NULL;
                                                        
                                // If the monster has ranged attacks.
                                if( !lpMonsterStructure->vlpRangeAttacks.empty() )
								{
                                    attackvector::iterator i;
                                    // While it hasn't found a range attack
                                    i = lpMonsterStructure->vlpRangeAttacks.begin();
                                    while( i != lpMonsterStructure->vlpRangeAttacks.end() && lpRangeAttack == NULL )
									{
                                        // If a range attack could be found for this range.
                                        if( (*i)->InRange( nTargetRange ) )
										{
                                            if( rnd( 0, 100 ) < (*i)->AttackDoingPercentage )
											{
                                                lpRangeAttack = *i;
                                            }
                                        }
                                        i++;
                                    }
                                }

                                BOOL boRangeAttack = FALSE;
                    
                                // If it found a range attack.
                                if( lpRangeAttack != NULL )
								{
                                    WorldMap *wlWorld = TFCMAIN::GetWorld( CreatureWL.world );
                                    if( wlWorld != NULL )
									{
                                        Unit *lpCollideUnit = NULL;
                                        WorldPos wlCollidePos = { -1, -1, -1 };

                                        // Get the collision unit
                                        wlWorld->GetCollisionPos( CreatureWL, TargetWL, &wlCollidePos, &lpCollideUnit );

										// If the unit which collides (in projectile pathfinding) is our target
										if( lpCollideUnit == Target ) 
										{

                                        // If the unit which collides is not our target // BLBL deactivated, seems that monsters attacks other monsters from SAME CLAN !!
										/*   if( lpCollideUnit != Target )
										{
											//test to really see if it's possible to hit the target
											if (!wlWorld->AttackBlockTest(CreatureWL, TargetWL, &wlCollidePos))
											{
												// Then attack at range!									
	    	    		    					lpRangeAttack->Attack( ThisCreature, Target );
												EXHAUST newExhaust = ThisCreature->GetExhaust();
			    	    		    			newExhaust.move = rnd.roll( lpMonsterStructure->cAttackLag ) MILLISECONDS TDELAY;
				    	    		    		ThisCreature->SetExhaust(newExhaust);						
        
												boRangeAttack = TRUE;
											} else
											if (Target->GetType()==U_PC)
											{
												if (rnd(0,100)<5) //5% chance to change target
												{
													ThisCreature->SetTarget(Target);
													ThisCreature->SetDestination( Target->GetWL());
												}
											}
							
                                            
                                        }else
										{*/
											// Then attack at range!									
	    	    		    				lpRangeAttack->Attack( ThisCreature, Target );
											EXHAUST newExhaust = ThisCreature->GetExhaust();
			    	    		    		newExhaust.move = rnd.roll( lpMonsterStructure->cAttackLag ) MILLISECONDS TDELAY;
				    	    		    	ThisCreature->SetExhaust(newExhaust);						
                    
											boRangeAttack = TRUE;	
										}
								    // Still, if monster is within physical attack range.
                                    }
                                }
                                // If no range attack occured.
                                if( !boRangeAttack )
								{      
                                    bool blockedPath = false;
                                    if( nTargetRange < 2 )
									{
	    								// Attack it!!!!!!!								
		    							EXHAUST newExhaust = ThisCreature->GetExhaust();
                                        try{
                                            newExhaust.attack = Round + TFCMAIN::Attack(ThisCreature, Target, blockedPath) * rnd(1, 3);
                                        }catch(...){
                                            try{
                                                _LOG_DEBUG
                                                    LOG_CRIT_ERRORS,
                                                    "Crashed TFCMAIN::Attack, monster %s(%u) target %s(%u) type %u.",
                                                    ThisCreature->GetName( _DEFAULT_LNG ),
                                                    ThisCreature->GetStaticReference(),
                                                    Target->GetName( _DEFAULT_LNG ),
                                                    Target->GetStaticReference(),
                                                    Target->GetType()
                                                LOG_
                                            }catch(...){
                                            }
                                            throw;
                                        }
                                        if( !blockedPath )
										{
				    					    newExhaust.move = (rnd.roll( lpMonsterStructure->cAttackLag )/50)+Round;
					    				    ThisCreature->SetExhaust(newExhaust);
                                        }
						    		}
                                    if( nTargetRange >= 2 || blockedPath )
									{
									    // Only move creature if it can actually move..!!
									    if( ThisCreature->CanMove() )
									    {
										    if(ThisCreature->GetExhaust().move < Round){
											    // else move towards the target
											    DIR::MOVE direction;	
											    if(TargetWL.X < CreatureWL.X) direction = DIR::west;
											    if(TargetWL.X > CreatureWL.X) direction = DIR::east;
											    
											    if(TargetWL.Y < CreatureWL.Y && direction == DIR::west) direction = DIR::northwest;
											    else if(TargetWL.Y < CreatureWL.Y && direction == DIR::east) direction = DIR::northeast;
											    else if(TargetWL.Y < CreatureWL.Y) direction = DIR::north;
												    if(TargetWL.Y > CreatureWL.Y && direction == DIR::west) direction = DIR::southwest;
											    else if(TargetWL.Y > CreatureWL.Y && direction == DIR::east) direction = DIR::southeast;
											    else if(TargetWL.Y > CreatureWL.Y) direction = DIR::south;
										    
                                                WorldPos newPos;
                                                // If target is within 2 squares of target.
                                                if( ::abs( TargetWL.X - CreatureWL.X ) < 2 || ::abs( TargetWL.Y - CreatureWL.Y ) < 2 ){
                                                    // Broadcast all moves
                                                    newPos = ThisCreature->MoveUnit( direction, false, false, true);
                                                }else{
                                                    // Do compressed broadcasting.
                                                    newPos = ThisCreature->MoveUnit( direction, false, true, true);
                                                }                                                        
                                                
											    if(newPos.X == CreatureWL.X && newPos.Y == CreatureWL.Y)
												    // Then check if it bumped into something
												    MonsterBlocked(ThisCreature, direction);
                                                
                                                if(!ThisCreature->IsInLimit(newPos)){
                                                    // If the monster's initial pos is ok.
                                                    if( lpMonsterStructure->InitialPos.X != -1 && lpMonsterStructure->InitialPos.Y != -1 && lpMonsterStructure->InitialPos.world != -1
                                                        && lpMonsterStructure->InitialPos.X != 0 && lpMonsterStructure->InitialPos.Y != 0 ){
                                                        // Teleport the npc to its initial position.
                                                        if( ThisCreature->Teleport( lpMonsterStructure->InitialPos, 0 ) ){
                                                            ThisCreature->Do( wandering );
                                                            WorldPos wlNoWhere = { -1, -1, -1 };
                                                            ThisCreature->SetDestination( wlNoWhere );
                                                
                                                            WorldPos nullWl = { 0, 0, 0 };
                                                            Broadcast::BCSpellEffect( CreatureWL, _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
                                                                30012,
                                                                ThisCreature->GetID(),
                                                                ThisCreature->GetID(),
                                                                nullWl,
                                                                CreatureWL,
                                                                GetNextGlobalEffectID(),
                                                                0
                                                            );

                                                            Broadcast::BCSpellEffect( CreatureWL, _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
                                                                30012,
                                                                ThisCreature->GetID(),
                                                                ThisCreature->GetID(),
                                                                nullWl,
                                                                ThisCreature->GetWL(),
                                                                GetNextGlobalEffectID(),
                                                                0
                                                            );

                                                        }
                                                    }
                                                }

											    //TRACE("Creature moved to (%u, %u)", ThisCreature->GetWL().X, ThisCreature->GetWL().Y);
											    EXHAUST newExhaust = ThisCreature->GetExhaust();										
											    if( rnd(0, 100) < lpMonsterStructure->bLagChance ){
												    newExhaust.move = rnd.roll( lpMonsterStructure->cStopLen ) /50 +Round;
											    }else{
												    newExhaust.move = ThisCreature->GetSpeedExhaust() + Round;
											    }
											    ThisCreature->SetExhaust(newExhaust);
										    }
									    }else
										{
									    }
								    }
                                }
							}
						}
					}
				} break;
				/////////////
				case talking:
					{
					/////////////////////////////////////////////////
					// Monster talking					
					// if NPC is 'talking' idle (NPC are never 'system idle', so we used it for this)
					if(TFCMAIN::GetRound() - ThisCreature->GetIdleTime() > 90 SECONDS)
					{
						Unit *lpuTalk = ThisCreature->GetTarget();

                        if( lpuTalk != NULL )
						{
                            TFCPacket sending;
	    					sending << (RQ_SIZE)RQ_BreakConversation;

			    			// Send message to client stating that we breaked conversation
				    		lpuTalk->SendPlayerMessage( sending );	
                        }						
						ThisCreature->SetTarget(ThisCreature->GetBond());
						ThisCreature->Do(wandering);
						WorldPos newPos = {-1, -1, -1};
						ThisCreature->SetDestination(newPos);
					}
				} break;
				////////////////
				case wandering:
				{
					if( !ThisCreature->CanMove() )
					{
						TRACE( "Creature will do nothing..!" );
						ThisCreature->Do( nothing );
					}else
					{
						/////////////////////////////////////////////////////
						// Monster wandering
						if(ThisCreature->GetExhaust().move < Round){
							// Check for a new place to go.
							WorldPos CreatureWL = ThisCreature->GetWL();
							WorldPos Destination = ThisCreature->Destination();
							WorldMap *CurrentWorld = TFCMAIN::GetWorld(CreatureWL.world);
							
							// If creature isn't in its original world, make it seek its last
							// teleport area
							
							if( CreatureWL.world != ThisCreature->OriginalWorldPos().world ){
								// Unit has 30% chances of getting back in the teleport
								if( rnd( 0, 100 ) < 30 ){
									Destination = ThisCreature->GetLastTeleport();
									ThisCreature->SetDestination( Destination );
								}else{
									// If current destination is out of this world
									if( Destination.world != CreatureWL.world ){
										// Reset the destination
										Destination.X = Destination.Y = Destination.world = -1;
										ThisCreature->SetDestination( Destination );
									}
								}
							}

							//TRACE("wandering, destination (%d, %d)...", CreatureWL.X, CreatureWL.Y);
								// This is a code to wander aimlessly
							if((signed)Destination.X == -1 || (signed)Destination.Y == -1){
								//TRACE("Setting a new destination...");
								// Then set a destination to a near range.							
								CurrentWorld = TFCMAIN::GetWorld(CreatureWL.world);
								if(CurrentWorld){
									int MAXX = CurrentWorld->GetMAXX();
									int MAXY = CurrentWorld->GetMAXY();
									Destination.X = -1;
									Destination.Y = -1;
									while(Destination.X < 0 || Destination.X >= MAXX || Destination.Y < 0 || Destination.Y >= MAXY){
										if(rnd(0, 1))
											Destination.X = rnd(CreatureWL.X - 15, CreatureWL.X - 5);
										else
											Destination.X = rnd(CreatureWL.X + 5, CreatureWL.X + 15);

										if(rnd(0, 1))
											Destination.Y = rnd(CreatureWL.Y - 15, CreatureWL.Y - 5);
										else 
											Destination.Y = rnd(CreatureWL.Y + 5, CreatureWL.Y + 15);
									}

									if(!ThisCreature->IsInLimit(Destination)){
										ThisCreature->GotoLimit();
									}

									Destination.world = CreatureWL.world;

									Unit *uFollow = ThisCreature->GetTarget();
									
									if(uFollow){
										WorldPos wlFollowPos = uFollow->GetWL();
										if(abs(Destination.X - wlFollowPos.X) > 5 && abs(Destination.Y - wlFollowPos.Y) > 5){
											Destination = wlFollowPos;
										}
										ThisCreature->SetDestination(Destination);
									}else if (!ThisCreature->IsInLimit(Destination)){
										// If the NPC isn't following and is out of it's limit
										ThisCreature->GotoLimit();
									}else{
										// then invite the monster to go to it's new destination
										ThisCreature->SetDestination(Destination);
									}
																			
									//TRACE("Scanning hostiles at (%u, %u)\r\n", CreatureWL.X, CreatureWL.Y);
									CurrentWorld->ScanHostiles(CreatureWL, ThisCreature->GetDetectRange(), ThisCreature);
								
								}else{
									TRACE( "Creature current world doesn't exist!" );
								}
								//TRACE("Which is (%u,%u)\r\n", ThisCreature->Destination().X, ThisCreature->Destination().Y);
							}else if(!Destination.X || !Destination.Y)
							{
								TRACE( "Creature isn't moving at all" );
								//TRACE("and not moving.\r\n");
								// if it's a "don't move" destination, well don't move ;)
							}else if(Destination.X != CreatureWL.X || Destination.Y != CreatureWL.Y)
							{
								// if monster isn't arrived at destination, move it.
								//TRACE("and choosing a direction...");
								if( Destination.world != CreatureWL.world )
								{
									Destination.X = Destination.Y = Destination.world = -1;
									ThisCreature->SetDestination( Destination );
								}else{
									
									WorldPos newPos;
									DIR::MOVE direction;	
									if(Destination.X < CreatureWL.X) direction = DIR::west;
									if(Destination.X > CreatureWL.X) direction = DIR::east;
								
									if(Destination.Y < CreatureWL.Y && direction == DIR::west) direction = DIR::northwest;
									else if(Destination.Y < CreatureWL.Y && direction == DIR::east) direction = DIR::northeast;
									else if(Destination.Y < CreatureWL.Y) direction = DIR::north;
										if(Destination.Y > CreatureWL.Y && direction == DIR::west) direction = DIR::southwest;
									else if(Destination.Y > CreatureWL.Y && direction == DIR::east) direction = DIR::southeast;
									else if(Destination.Y > CreatureWL.Y) direction = DIR::south;
								
							
									//	TRACE("\r\nMonster moved to (%u, %u)\r\n", CreatureWL.X, CreatureWL.X);							
									newPos = ThisCreature->MoveUnit(direction, false, true, true);
									// if creature didn't move (blocked) 							
									if(newPos.X == CreatureWL.X && newPos.Y == CreatureWL.Y){
										// Then check if it bumped into something
										MonsterBlocked(ThisCreature, direction);								
										
									}							
									
									EXHAUST newExhaust = ThisCreature->GetExhaust();							
									if(rnd(0, 100) < lpMonsterStructure->bLagChance){
										newExhaust.move = rnd.roll( lpMonsterStructure->cStopLen ) MILLISECONDS TDELAY;
									}else{
										newExhaust.move = ThisCreature->GetSpeedExhaust() TDELAY;
									}
									ThisCreature->SetExhaust(newExhaust);
								}
							}else{
								// and finally, monster is at destination! So set it a new
								// destination according to it's goal
								// also scan for hostiles here, when at rest																
								//TRACE("and arrived at destination...");
								WorldMap *CurrentWorld = TFCMAIN::GetWorld(CreatureWL.world);
								if(CurrentWorld) // Scan hostiles will itself set the combat features
									CurrentWorld->ScanHostiles(CreatureWL, ThisCreature->GetDetectRange(), ThisCreature);										
																
								// then set a new goal, if monster is still wandering
								if(ThisCreature->IsDoing() == wandering){
									// set a new goal
									WorldPos pos;
									pos.X = pos.Y = pos.world = -1;
									ThisCreature->SetDestination(pos);
								}
							}
						}
					}
				}break;
				/////////////////////////////////////////////////////////////////////////////////
				// Flee
				case flee:
				{
                    if( !ThisCreature->CanMove() )
					{
                        ThisCreature->Do( nothing );
                    }else
					{
					    BOOL boStillFlee = FALSE;
					    Unit *uFleeFrom = ThisCreature->GetTarget();
					    WorldPos CreatureWL = ThisCreature->GetWL();
					    WorldPos wlFleePos = {0,0,0};

					    if(uFleeFrom)
						{						
						    UINT X, Y;
						    wlFleePos = uFleeFrom->GetWL();
						    X = abs(wlFleePos.X - CreatureWL.X);
						    X *= X;
						    Y = abs(wlFleePos.Y - CreatureWL.Y);
						    Y *= Y;

						    // If NPC not further then in a ray of 40, stops fleeing
						    if((X + Y) < 1600)
							{
							    boStillFlee = TRUE;
						    }

					    }else boStillFlee = FALSE; // If it lost it's target, no use to flee!

					    WorldPos wlDestination;
					    if(boStillFlee && ThisCreature->GetExhaust().move < Round)
						{
						    // Checks in which quandran is the follower
						    if(wlFleePos.X - CreatureWL.X < 0)
							{
							    // f -> c
							    wlDestination.X = rnd(CreatureWL.X + 5, CreatureWL.X + 10);
						    }else
							{
							    // c <- f
							    wlDestination.X = rnd(CreatureWL.X - 10, CreatureWL.X - 5);
						    }
					    
						    if(wlFleePos.Y - CreatureWL.Y < 0)
							{
							    // f -> c
							    wlDestination.Y = rnd(CreatureWL.Y + 5, CreatureWL.Y + 10);
						    }else
							{
							    // c <- d
							    wlDestination.Y = rnd(CreatureWL.Y - 10, CreatureWL.Y - 5);
						    }
						    wlDestination.world = CreatureWL.world;
						    ThisCreature->SetDestination(wlDestination);
				    
						    WorldPos newPos;
						    DIR::MOVE direction;	
						    if(wlDestination.X < CreatureWL.X) direction = DIR::west;
						    if(wlDestination.X > CreatureWL.X) direction = DIR::east;
					    
						    if(wlDestination.Y < CreatureWL.Y && direction == DIR::west) direction = DIR::northwest;
						    else if(wlDestination.Y < CreatureWL.Y && direction == DIR::east) direction = DIR::northeast;
						    else if(wlDestination.Y < CreatureWL.Y) direction = DIR::north;
							    if(wlDestination.Y > CreatureWL.Y && direction == DIR::west) direction = DIR::southwest;
						    else if(wlDestination.Y > CreatureWL.Y && direction == DIR::east) direction = DIR::southeast;
						    else if(wlDestination.Y > CreatureWL.Y) direction = DIR::south;
					    
						    
						    //	TRACE("\r\nMonster moved to (%u, %u)\r\n", CreatureWL.X, CreatureWL.X);							
						    newPos = ThisCreature->MoveUnit(direction, false, true, true);
						    // if creature didn't move (blocked) 							
						    if(newPos.X == CreatureWL.X && newPos.Y == CreatureWL.Y){
							    if(!ThisCreature->IsInLimit(wlDestination)){
								    ThisCreature->Do(wandering);
								    newPos.X = newPos.Y = newPos.world = -1;
								    ThisCreature->SetDestination(newPos);
								    ThisCreature->SetTarget(ThisCreature->GetBond());
							    }
						    }

						    EXHAUST newExhaust = ThisCreature->GetExhaust();
						    newExhaust.move = Round + ((unsigned long)(ThisCreature->GetSpeedExhaust())*70)/100;
						    ThisCreature->SetExhaust(newExhaust);
					    }else{
						    wlDestination.X = wlDestination.Y = wlDestination.world = -1;
						    // Now wander!
						    ThisCreature->SetDestination(wlDestination);
						    ThisCreature->SetTarget(ThisCreature->GetBond());
						    ThisCreature->Do(wandering);
					    }
                    }
				}break;	
				case fightingrage:
					{
					////////////////////////////////////////////////////////
					// Monster fighting
					if(ThisCreature->GetExhaust().attack < Round)
					{
					
						Unit *Target = ThisCreature->GetTarget();
						WorldPos CreatureWL =  ThisCreature->GetWL();

						
						//no flee when the creature is in rage mode
						//it's its last chance to kill someone

						if(Target)
						{

                            // If the creature's target is a player.
                            if( Target->GetType() == U_PC )
							{
                                // Reset the monster's idle time so it won't be deleted.
                                ThisCreature->SetIdleTime(Round + _MONSTER_LIFE_SPAN);
                            }

							WorldPos TargetWL;
						
							//TRACE("-target-0x%x\r\n", Target);
							TargetWL = Target->GetWL(); // Monsters wants to reach its target

							// If creature hit a teleport, assign a new destination.
							if( TargetWL.world != CreatureWL.world )
							{
								TRACE( "Creature's target world isn't the same!" );
								TargetWL.X = TargetWL.Y = TargetWL.world = -1;
								ThisCreature->SetTarget( ThisCreature->GetBond() );
								ThisCreature->SetDestination( TargetWL );
								ThisCreature->Do( wandering );
							}else
							{
                                int nDeltaX = abs( CreatureWL.X - TargetWL.X );
                                int nDeltaY = abs( CreatureWL.Y - TargetWL.Y );
                                int nTargetRange = (int)::sqrt((double) (nDeltaX * nDeltaX) + (nDeltaY * nDeltaY) ); // steph ajout de (double)

                                LPMONSTER_ATTACK lpRangeAttack = NULL;
                                                        
                                // If the monster has ranged attacks.
                                if( !lpMonsterStructure->vlpRangeAttacks.empty() )
								{
                                    attackvector::iterator i;
                                    // While it hasn't found a range attack
                                    i = lpMonsterStructure->vlpRangeAttacks.begin();
                                    while( i != lpMonsterStructure->vlpRangeAttacks.end() && lpRangeAttack == NULL )
									{
                                        // If a range attack could be found for this range.
                                        if( (*i)->InRange( nTargetRange ) )
										{
                                            if( rnd( 0, 100 ) < (*i)->AttackDoingPercentage )
											{
                                                lpRangeAttack = *i;
                                            }
                                        }
                                        i++;
                                    }
                                }

                                BOOL boRangeAttack = FALSE;
                    
                                // If it found a range attack.
                                if( lpRangeAttack != NULL )
								{
                                    WorldMap *wlWorld = TFCMAIN::GetWorld( CreatureWL.world );
                                    if( wlWorld != NULL )
									{
                                        Unit *lpCollideUnit = NULL;
                                        WorldPos wlCollidePos = { -1, -1, -1 };

                                        // Get the collision unit
                                        wlWorld->GetCollisionPos( CreatureWL, TargetWL, &wlCollidePos, &lpCollideUnit );

                                        // If the unit which collides is not our target
                                        if( lpCollideUnit != Target )
										{
											//test to really see if it's possible to hit the target
											if (!wlWorld->AttackBlockTest(CreatureWL, TargetWL, &wlCollidePos))
											{
												// Then attack at range!									
	    	    		    					lpRangeAttack->Attack( ThisCreature, Target );
												EXHAUST newExhaust = ThisCreature->GetExhaust();
			    	    		    			newExhaust.move = rnd.roll( lpMonsterStructure->cAttackLag ) *30+ Round;
				    	    		    		ThisCreature->SetExhaust(newExhaust);						
        
												boRangeAttack = TRUE;
											} else
											if (Target->GetType()==U_PC)
											{
												if (rnd(0,100)<5) //5% chance to change target
												{
													ThisCreature->SetTarget(Target);
													ThisCreature->SetDestination( Target->GetWL());
												}
											}
							
                                            
                                        }else
										{
											// Then attack at range!									
	    	    		    				lpRangeAttack->Attack( ThisCreature, Target );
											EXHAUST newExhaust = ThisCreature->GetExhaust();
			    	    		    		newExhaust.move = rnd.roll( lpMonsterStructure->cAttackLag )/50+ Round;
				   
				    	    		    	ThisCreature->SetExhaust(newExhaust);						
                    
											boRangeAttack = TRUE;	
										}
								    // Still, if monster is within physical attack range.
                                    }
                                }
                                // If no range attack occured.
                                if( !boRangeAttack )
								{      
                                    bool blockedPath = false;
                                    if( nTargetRange < 2 )
									{
	    								// Attack it!!!!!!!								
		    							EXHAUST newExhaust = ThisCreature->GetExhaust();
                                        try{
                                            newExhaust.attack = Round + TFCMAIN::Attack(ThisCreature, Target, blockedPath);
                                        }catch(...){
                                            try{
                                                _LOG_DEBUG
                                                    LOG_CRIT_ERRORS,
                                                    "Crashed TFCMAIN::Attack, monster, %s(%u), target, %s(%u), type ,%u",
                                                    ThisCreature->GetName( _DEFAULT_LNG ),
                                                    ThisCreature->GetStaticReference(),
                                                    Target->GetName( _DEFAULT_LNG ),
                                                    Target->GetStaticReference(),
                                                    Target->GetType()
                                                LOG_
                                            }catch(...){
                                            }
                                            throw;
                                        }
                                        if( !blockedPath )
										{
				    					    newExhaust.move = Round + ((unsigned long)ThisCreature->GetSpeedExhaust())/100;
					    				    ThisCreature->SetExhaust(newExhaust);
                                        }
									} else
                                    if( nTargetRange >= 2 || blockedPath )
									{
									    // Only move creature if it can actually move..!!
									    if( ThisCreature->CanMove() )
									    {
										    if(ThisCreature->GetExhaust().move < Round)
											{
											    // else move towards the target
											    DIR::MOVE direction;	
											    if(TargetWL.X < CreatureWL.X) direction = DIR::west;
											    if(TargetWL.X > CreatureWL.X) direction = DIR::east;
											    
											    if(TargetWL.Y < CreatureWL.Y && direction == DIR::west) direction = DIR::northwest;
											    else if(TargetWL.Y < CreatureWL.Y && direction == DIR::east) direction = DIR::northeast;
											    else if(TargetWL.Y < CreatureWL.Y) direction = DIR::north;
												    if(TargetWL.Y > CreatureWL.Y && direction == DIR::west) direction = DIR::southwest;
											    else if(TargetWL.Y > CreatureWL.Y && direction == DIR::east) direction = DIR::southeast;
											    else if(TargetWL.Y > CreatureWL.Y) direction = DIR::south;
										    
                                                WorldPos newPos;
                                                // If target is within 2 squares of target.
                                                if( ::abs( TargetWL.X - CreatureWL.X ) < 2 || ::abs( TargetWL.Y - CreatureWL.Y ) < 2 ){
                                                    // Broadcast all moves
                                                    newPos = ThisCreature->MoveUnit( direction, false, false, true);
                                                }else{
                                                    // Do compressed broadcasting.
                                                    newPos = ThisCreature->MoveUnit( direction, false, true, true);
                                                }                                                        
                                                
											    if(newPos.X == CreatureWL.X && newPos.Y == CreatureWL.Y)
												    // Then check if it bumped into something
												    MonsterBlocked(ThisCreature, direction);
                                                
                                                if(!ThisCreature->IsInLimit(newPos))
												{
                                                    // If the monster's initial pos is ok.
                                                    if( lpMonsterStructure->InitialPos.X != -1 && lpMonsterStructure->InitialPos.Y != -1 && lpMonsterStructure->InitialPos.world != -1
                                                        && lpMonsterStructure->InitialPos.X != 0 && lpMonsterStructure->InitialPos.Y != 0 )
													{
                                                        // Teleport the npc to its initial position.
                                                        if( ThisCreature->Teleport( lpMonsterStructure->InitialPos, 0 ) )
														{
															//Broadcast::BCServerMessage(ThisCreature->GetWL(),10,"Rage->Wandering");
                                                            ThisCreature->Do( wandering );
                                                            WorldPos wlNoWhere = { -1, -1, -1 };
                                                            ThisCreature->SetDestination( wlNoWhere );
                                                
                                                            WorldPos nullWl = { 0, 0, 0 };
                                                            Broadcast::BCSpellEffect( CreatureWL, _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
                                                                30012,
                                                                ThisCreature->GetID(),
                                                                ThisCreature->GetID(),
                                                                nullWl,
                                                                CreatureWL,
                                                                GetNextGlobalEffectID(),
                                                                0
                                                            );

                                                            Broadcast::BCSpellEffect( CreatureWL, _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
                                                                30012,
                                                                ThisCreature->GetID(),
                                                                ThisCreature->GetID(),
                                                                nullWl,
                                                                ThisCreature->GetWL(),
                                                                GetNextGlobalEffectID(),
                                                                0
                                                            );

                                                        }
                                                    }
                                                }

											    //TRACE("Creature moved to (%u, %u)", ThisCreature->GetWL().X, ThisCreature->GetWL().Y);
											    EXHAUST newExhaust = ThisCreature->GetExhaust();
												
											    //newExhaust.move = (ThisCreature->GetSpeedExhaust()/8) + TFCMAIN::GetRound();
											    newExhaust.move = Round + ((unsigned long)ThisCreature->GetSpeedExhaust())/20;//BLBLBL 100 c'est trop, on met 20
												ThisCreature->SetExhaust(newExhaust);
												CString Temp="Creature exhaust : ";
												char buffer [33];
												ltoa(newExhaust.move,buffer,10);
												Temp.Append(buffer);
												//Broadcast::BCServerMessage(ThisCreature->GetWL(),10,CString());
										    }//move exhaust
									    }//can move
								    }//nTargetRange >= 2 || blockedPath
                                }
							}
						}
					}
				} break;
			
                } // switch
			}
		}
		CreatureList.Unlock();
	
        // Deletes all units on the electric chair
		tluElectricChair.ToHead();
		while(tluElectricChair.QueryNext()){
			// If we succeed in unlocking the unit's structure.

			if( tluElectricChair.Object()->boDelete ){
                _LOG_DEBUG
                    LOG_DEBUG_LVL4,
                    "Del. unit %u (tluElectricalChair)addr 0x%x, class %u, name %s, pos %u,%u,%u.",
                    tluElectricChair.Object()->lpuCondemned->GetID(),
                    tluElectricChair.Object()->lpuCondemned,
                    tluElectricChair.Object()->lpuCondemned->GetType(),
                    (LPCTSTR)tluElectricChair.Object()->lpuCondemned->GetName( _DEFAULT_LNG ),
                    tluElectricChair.Object()->lpuCondemned->GetWL().X,
                    tluElectricChair.Object()->lpuCondemned->GetWL().Y,
                    tluElectricChair.Object()->lpuCondemned->GetWL().world
                LOG_
             
    			// Makes sure that the unit isn't being processed before deleting the unit.
                tluElectricChair.Object()->lpuCondemned->Lock();
                tluElectricChair.Object()->lpuCondemned->Unlock();
                // Delete the unit from existence.
                tluElectricChair.Object()->lpuCondemned->DeleteUnit();
			}
			tluElectricChair.DeleteAbsolute();			    
		}
        
		// Then copy the death row to the electric chair
		tluDeathRow.Lock();
		tluDeathRow.ToHead();
		while(tluDeathRow.QueryNext()){
			// Removes all timers that had their parameter pointed to the condemned unit
			TFCTimerManager::RemoveTimersByParameter( tluDeathRow.Object() );

			tluElectricChair.AddToTail(tluDeathRow.Object());
			tluDeathRow.Remove();
		}
		tluDeathRow.Unlock();

		KEEP_ALIVE

    	// Verify the object timers.
        ObjectTimer::VerifyTimers();
        // Verify global timers
	    TFCTimerManager::VerifyTimers();

        Sleep(20);
	} // Main NPC Loop

	CreatureList.ToHead();
	while(CreatureList.QueryNext()){
        CreatureList.Object()->DeleteUnit();
        CreatureList.Remove();
	}

    STOP_DEADLOCK_DETECTION

}

void __declspec( dllexport ) AfterNPCThread( void ){};

//////////////////////////////////////////////////////////////////////////////////////////
NPCMain::NPCMain( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Initializes the NPCMain.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    boNPCThreadDone = false;
    hNPCThread = (HANDLE)_beginthreadex( NULL, 0, NPCThread, 0, 0, &nNPCThreadId );
}

//////////////////////////////////////////////////////////////////////////////////////////
NPCMain &NPCMain::GetInstance( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Return: NPCMain, The sole NPCMain instance.
//////////////////////////////////////////////////////////////////////////////////////////
{
    static NPCMain npcMain;
    
    return npcMain;
}

//////////////////////////////////////////////////////////////////////////////////////////
Creatures *NPCMain::GetNPC
//////////////////////////////////////////////////////////////////////////////////////////
//  Finds an NPC and returns its locked instance. Callers must call FreeNPC() when
// the NPC isn't needed anymore. WARNING: locking a NPC instances locks the
// whole NPC engine.
// 
(
 LPCTSTR npcName,  // The NPC's name
 DWORD order,      // Determines which 
 WORD  wLang       // Language
)
// Return: Creatures, A valid creatures handle or NULL if the creature wasn't found.
//////////////////////////////////////////////////////////////////////////////////////////
{
    CreatureList.Lock();

    DWORD count = 0;
    Creatures *foundCreature = NULL;
    
    CreatureList.ToHead();
    while( CreatureList.QueryNext() ){
        Creatures *thisCreature = static_cast< Creatures * >( CreatureList.Object() );
        // If the creature's name match
        if( stricmp( thisCreature->GetName( wLang ), npcName ) == 0 ){
            // Check if its the creature we want.
            count++;
            if( count > order ){
                foundCreature = thisCreature;
                break;
            }
        }

    }

    CreatureList.Unlock();
    
    return foundCreature;
}

//////////////////////////////////////////////////////////////////////////////////////////
DWORD NPCMain::CountNPC
//////////////////////////////////////////////////////////////////////////////////////////
//  Counts how many NPCs of a given name are alive in the world.
// 
(
 LPCTSTR npcName, // The NPC's name
 WORD wLang       // The language
)
// Return: DWORD, the quantity of NPC found
//////////////////////////////////////////////////////////////////////////////////////////
{
    CreatureList.Lock();

    DWORD creatureCount = 0;
    
    CreatureList.ToHead();
    while( CreatureList.QueryNext() ){
        Creatures *thisCreature = static_cast< Creatures * >( CreatureList.Object() );
        // If the creature's name match
        if( stricmp( thisCreature->GetName( wLang ), npcName ) == 0 ){
            // Increment the count.
            creatureCount++;
        }

    }

    CreatureList.Unlock();
    
    return creatureCount;
}

//////////////////////////////////////////////////////////////////////////////////////////
void NPCMain::KillAll( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroy all NPCs
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CreatureList.Lock();

    DWORD creatureCount = 0;
    
    CreatureList.ToHead();
    while( CreatureList.QueryNext() ){
        Creatures *thisCreature = static_cast< Creatures * >( CreatureList.Object() );
        WorldMap *wl = TFCMAIN::GetWorld( thisCreature->GetWL().world );
        wl->remove_world_unit( thisCreature->GetWL(), thisCreature->GetID() );
        thisCreature->KillCreature();
    }

    CreatureList.Unlock();
}

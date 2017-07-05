// Container.cpp: implementation of the Container class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Container.h"
#include "../IntlText.h"
#include "../T4CLog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Container::Container()
{

}

Container::~Container()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
void Container::OnInitialise( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Called upon initialisation
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	ObjectStructure::OnInitialise( UNIT_FUNC_PARAM );
	//self->SetFlag( __FLAG_DONT_RESPAWN, container.dwGlobalRespawn SECONDS TDELAY );//BLBLBL on met un délai de respawn d'office au lancement du serveur pour les coffres !
}

//////////////////////////////////////////////////////////////////////////////////////////
void Container::OnUse( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// When using a container, the container simply displays its content.
// 
// self:	this object.
// medium:	unit that used object
// target:	target of use ( NULL )
//////////////////////////////////////////////////////////////////////////////////////////
{
	ObjectStructure::OnUse( UNIT_FUNC_PARAM );

	DWORD &itemUsed = *(DWORD *)( valueOUT );
	itemUsed = TRUE;

	WorldPos wlPos = self->GetWL();
	WorldPos wlFoundPos;

	// Get world
	WorldMap *wlWorld = TFCMAIN::GetWorld( wlPos.world );

	// If world is valid
	if( wlWorld != NULL ){
		BOOL boUnlocked = TRUE;		
		BOOL boContentSpilled = FALSE;
        BOOL boPicklock = FALSE;

        if( valueIN != NULL ){
            boPicklock = *(LPBOOL)( valueIN );
        }

		itemUsed = TRUE;

		// First check if chest is locked.
		if( lock.key != 0 ){
			// If a key is needed, chest is locked by default
			boUnlocked = FALSE;

            // If user pick-locks
            if( boPicklock ){
				boUnlocked = TRUE;
				// Send message stating we used the item.
				CString csText;										
				csText.Format( _STR( 3, medium->GetLang() ) );

				TFCPacket sending;
				sending << (RQ_SIZE)RQ_ServerMessage;
				sending << (short)30;
				sending << (short)3;
				sending << (CString &)csText;
				sending << (long)RGB( 0, 200, 0 );
				medium->Lock();
				medium->SendPlayerMessage( sending );
				medium->Unlock();
            }else{
                // Search for key in the user's backpack
			    TemplateList< Unit > *lptlBackpack = medium->GetBackpack();
			    if( lptlBackpack != NULL ){                    
				    lptlBackpack->Lock();
				    lptlBackpack->ToHead();
				    while( lptlBackpack->QueryNext() && !boUnlocked ){
                        Objects *lpItem = static_cast< Objects * >( lptlBackpack->Object() );
					    // If key was found
					    if( lpItem->GetStaticReference() == lock.key ){

						    boUnlocked = TRUE;
						    // Send message stating we used the item.
						    CString csText;										
						    csText.Format( _STR( 5, medium->GetLang() ), lpItem->GetName( medium->GetLang() ), self->GetName( medium->GetLang()) );

						    TFCPacket sending;
						    sending << (RQ_SIZE)RQ_ServerMessage;
						    sending << (short)30;
						    sending << (short)3;
						    sending << (CString &)csText;
							sending << (long)0x000A64E0 /*RGB( 0, 100, 255 )*/;
						    medium->Lock();
						    medium->SendPlayerMessage( sending );
						    medium->Unlock();

                            int nCharges = lpItem->ViewFlag( __FLAG_CHARGES );                            
                            if( nCharges != 0 && ( nCharges - 1 ) != 0 ){
                                nCharges--;
                                if( nCharges >= 0 ){
                                    lpItem->SetFlag( __FLAG_CHARGES, nCharges );
                                }
                            }else{
                                CString str;
                                str.Format( 
                                    _STR( 7205, medium->GetLang() ),
                                    lpItem->GetName( medium->GetLang() )
                                );
                                medium->SendSystemMessage( str );

                                // Destroy the item.
                                lpItem->Remove();
                                if( lpItem->GetQty() == 0 ){
                                    lptlBackpack->Remove();
                                    lpItem->DeleteUnit();
                                }
                            }
					    }
				    }
				    lptlBackpack->Unlock();
                }
			}
			// If chest wasn't unlocked.
			if( !boUnlocked ){
				CString csText;										
				csText.Format( _STR( 6, medium->GetLang() ), self->GetName( medium->GetLang() ) );

				TFCPacket sending;
				sending << (RQ_SIZE)RQ_ServerMessage;
				sending << (short)30;
				sending << (short)3;
				sending << (CString &)csText;
				sending << (long) 0x000A64E0/*RGB( 0, 100, 255 )*/;
				medium->Lock();
				medium->SendPlayerMessage( sending );
				medium->Unlock();
			}
		}

		// Don't bother trying to open a locked chest!
		if( boUnlocked ){
			// Get all the chest's time respawn flags.
            DynamicFlags::FlagCont cFlags;
            self->GetFlags( cFlags );

			//////////////////////////////////////////////////////////////////////////////////////////	
			// Scroll through the flags to detect which ones are now obsolete.
            DynamicFlags::FlagCont::iterator w;
            for( w = cFlags.begin(); w != cFlags.end(); w++ ){
				// If flag is a no-respawn flag, or if flag is a user flag ( >1,000,000 )
				if( (*w).first == __FLAG_DONT_RESPAWN || (*w).first > 1000000 ){
					// Check if its value exceeds the time limit.
					if( (*w).second <= (int)TFCMAIN::GetRound() ){
						// If so, remove the flag.
                        self->RemoveFlag( (*w).first );
						TRACE( "\r\n--Flushing flag id#%u!", (*w).first );
					}
				}
			}	
            
            UINT i, k;
			// Check if chest can be respawned
			if( self->ViewFlag( __FLAG_DONT_RESPAWN ) == 0 ){	
				// Check if player should respawn the content of this chest.
				// The flag ID is 'PlayerID + 1,000,000' (so it won't interfere with the global flags)
				TRACE( "\r\nValue of user flag is %u vs round %u.", self->ViewFlag( medium->GetID() + 1000000 ), TFCMAIN::GetRound() );
				
				if( self->ViewFlag( medium->GetID() + 1000000 ) == 0 ){
					LPOBJECT_GROUPITEMS lpGroupItems;				

					k = 0;
					// Scroll through the object groups
					container.tlItemGroups.Lock();
					container.tlItemGroups.ToHead();			
					while( container.tlItemGroups.QueryNext() ){						
						BOOL boOK = FALSE;
						lpGroupItems = container.tlItemGroups.Object();								

						lpGroupItems->tlItemBaseReferenceID.Lock();
                        
                        if( lpGroupItems->tlItemBaseReferenceID.NbObjects() != 0 ){
                            lpGroupItems->tlItemBaseReferenceID.ToHead();
	    					// Select a random item from the group
		    				i = rnd( 1, lpGroupItems->tlItemBaseReferenceID.NbObjects() );
			    			int j;
                            for( j = 0; j < i; j++ ){
				    			boOK = lpGroupItems->tlItemBaseReferenceID.QueryNext();
					    	}
                        }

						// If last QueryNext() was successful
						if( boOK ){
							// Check a valid non-blocking spot withing 2 spaces of the chest to spill out content.

							wlFoundPos = wlPos;
							switch( k++ ){
							case 0: wlFoundPos.Y = wlPos.Y + rnd( 1, 2 ); break;
							case 1: wlFoundPos.X = wlPos.X + rnd( 1, 2 ); break;
							case 2: wlFoundPos.Y = wlPos.Y - rnd( 1, 2 ); break;
							case 3: wlFoundPos.X = wlPos.X - rnd( 1, 2 ); break;
							case 4: wlFoundPos.X = wlPos.X + rnd( 1, 2 );
									wlFoundPos.Y = wlPos.Y + rnd( 1, 2 ); break;
							case 5: wlFoundPos.X = wlPos.X + rnd( 1, 2 );
									wlFoundPos.Y = wlPos.Y - rnd( 1, 2 ); break;
							case 6: wlFoundPos.X = wlPos.X - rnd( 1, 2 ); 
									wlFoundPos.Y = wlPos.Y + rnd( 1, 2 ); break;
							case 7: wlFoundPos.X = wlPos.X - rnd( 1, 2 );
									wlFoundPos.Y = wlPos.Y - rnd( 1, 2 ); break;
							} 
							k = k > 7 ? 0 : k;
							
							// If spot isn't a valid one, make the world find it..!
							if( wlWorld->IsBlocking( wlFoundPos ) ){
								wlFoundPos = wlWorld->FindValidSpot( wlPos, 2 );
							}

							TRACE( "\r\nFound pos = %u %u %u", wlFoundPos.X, wlFoundPos.Y, wlFoundPos.world );

							// if it found a valid position
							if( wlFoundPos.X > 0 && wlFoundPos.Y > 0 ){
								// Create the item.
								Objects *lpObject = new Objects;
								TRACE( "\r\nCreating object %u!", *lpGroupItems->tlItemBaseReferenceID.Object() );
								// Create the object
								if( lpObject->Create( U_OBJECT, *lpGroupItems->tlItemBaseReferenceID.Object() ) ){									
									// Deposit the created object on the found position, if it is valid
									TRACE( " Depositing unit..!" );
                                    if( wlWorld->IsValidPosition( wlFoundPos ) ){
                                        boContentSpilled = TRUE;	// Content was spilled.
                                        wlWorld->deposit_unit( wlFoundPos, lpObject );

                                        _LOG_ITEMS
                                            LOG_MISC_1,
                                            "Container at ( %u, %u, %u ) spilled item %s ID( %u ) at ( %u, %u, %u ).",
                                            wlPos.X,
                                            wlPos.Y,
                                            wlPos.world,
                                            (LPCTSTR)lpObject->GetName( medium->GetLang() ),
                                            lpObject->GetStaticReference(),
                                            wlFoundPos.X,
                                            wlFoundPos.Y,
                                            wlFoundPos.world
                                        LOG_

									    //TRACE("\r\n\r\nObject Type=%u\r\n\r\n\r\n", temp_obj->GetAppearance());
                                        lpObject->BroadcastPopup( wlFoundPos );
                                    }else{
                                        lpObject->DeleteUnit();
                                    }
								}else{
									lpObject->DeleteUnit();
								}
							}
						}

                        lpGroupItems->tlItemBaseReferenceID.Unlock();
					}

					container.tlItemGroups.Unlock();

                    // If the chest gives gold.
                    if( container.dwGold != 0 ){
                        // Add gold to user.
                        DWORD dwGold = medium->GetGold();
                        dwGold += container.dwGold;
                        medium->SetGold( dwGold );
                    }

					// Reset the chest's user respawn time.
					if( container.dwUserRespawn != 0 ){
						// Sets a new user timeout
						self->SetFlag( medium->GetID() + 1000000, container.dwUserRespawn SECONDS TDELAY );
					}
					// Reset the chest's respawn time
					if( container.dwGlobalRespawn != 0 ){
						// dwGlobalRespawn is in 'minutes'
						self->SetFlag( __FLAG_DONT_RESPAWN, container.dwGlobalRespawn SECONDS TDELAY );
					}
				}
			}            

			// If the container's content wasn't spilled, say it
			if( !boContentSpilled ){
				CString csText;										
				csText.Format( _STR( 7, medium->GetLang() ), (LPCTSTR)self->GetName( medium->GetLang() ) );

				TFCPacket sending;
				sending << (RQ_SIZE)RQ_ServerMessage;
				sending << (short)30;
				sending << (short)3;
				sending << (CString &)csText;
				sending << (long)0x000A64E0/*RGB( 0, 100, 255 )*/;
				medium->Lock();
				medium->SendPlayerMessage( sending );
				medium->Unlock();
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
ObjectStructure *Container::CreateObject( void ){
	return new Container;
}
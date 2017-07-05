// TFCInit.cpp : implementation file
//

#include "stdafx.h"
#include "TFC Server.h"
#include "TFCInit.h"
#include "TFC_MAIN.h"
//#include "StaticObjects.h"
#include "Character.h"
#include "Players.h"
#include "SharedStructures.h"
#include "Clans.h"
#include "TFC World.h"
#include "DynObjManager.h"
#include "WeatherEffect.h"
//////////////////////////////////
// Recordsets
#include "SpellEFfectManager.h"
#include "SpellMessageHandler.h"
#include "InitDBSpellRequirements.h"
#include "SimpleMonster.h"
#include "RegKeyHandler.h"

extern CTFCServerApp theApp;

//#define NO_DAO_SUPPORT

#undef Lock
#undef Unlock
#undef PickLock

#include "TraceLogger.h"
#include "WDAAreaLinks.h"
#include "WDAClans.h"
#include "WDAHives.h"
#include "WDAObjects.h"
#include "WDASpells.h"
#include "WDAWorlds.h"
#include "WDACreatures.h"
#include "WDAHeader.h"

// Disable conversion errors for this module.
#pragma warning( disable : 4244 )

/////////////////////////////////////////////////////////////////////////////
// TFCInit dialog

extern TFC_MAIN *TFCServer;

//extern CString ServerPath;
extern Clans *CreatureClans;

#include "Character.h"

extern BOOL InService;

class T4C_Initialization{
public:
    void WDAInitAreaLinks( WDAAreaLinks &wdaFile );
    void WDAInitClans(     WDAClans &wdaFile );
    void WDAInitSpells(    WDASpells &wdaFile );
    void WDAInitObjects(   WDAObjects &wdaFile );
    void WDAInitWorlds(    WDAWorlds &wdaFile );
    void WDAInitHives(     WDAHives &wdaFile );
    void WDAInitCreatures( WDACreatures &wdaFile );
    void WDAInitNPC();
};

//////////////////////////////////////////////////////////////////////////////////////////
void T4C_Initialization::WDAInitSpells
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes all spells.
// 
(
 WDASpells &wdaSpells // The WDAFile to load the spells from.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    BOOL boError;
    
    // Get the list of spells.
    vector< WDASpells::SpellData > &vSpells = wdaSpells.GetSpells();
    
    // Scroll through the spells
    vector< WDASpells::SpellData >::iterator i;    
    for( i = vSpells.begin(); i != vSpells.end(); i++ )
	{
        WDASpells::SpellData &cSpell = (*i);
        
        // No error by default.
        boError = FALSE;

        // Create a new spell structure
        LPSPELL_STRUCT lpSpell = new SPELL_STRUCT;

        // Assign values to spell structure.
        lpSpell->SetName( cSpell.csName.c_str() );
        lpSpell->wSpellID   = static_cast< WORD >( cSpell.dwSpellID );
        
        if( !lpSpell->bfManaCost.SetFormula( cSpell.bsManaCost.c_str() ) ){
            boError = TRUE;
        }
        if( !lpSpell->bfDuration.SetFormula( cSpell.bsDuration.c_str() ) ){
            boError = TRUE;
        }
        if( !lpSpell->bfTimerFrequency.SetFormula( cSpell.bsTimerFrequency.c_str() ) ){
            boError = TRUE;
        }

        // Assign exhaustion formulas.
        if( !lpSpell->sInducedExhaust.bfAttack.SetFormula( cSpell.csAttackExhaust.c_str() ) ){
            boError = TRUE;
        }
        if( !lpSpell->sInducedExhaust.bfMove.SetFormula( cSpell.csMoveExhaust.c_str() ) ){
            boError = TRUE;
        }
        if( !lpSpell->sInducedExhaust.bfMental.SetFormula( cSpell.csMentalExhaust.c_str() ) ){
            boError = TRUE;
        }

        

        // Assing the rest.
        lpSpell->attackSpell      = cSpell.boAttackSpell;
        lpSpell->bElementType     = static_cast< BYTE >( cSpell.dwElement );
        lpSpell->bDamageType      = static_cast< BYTE >( cSpell.dwAttackType );
        lpSpell->bTarget          = static_cast< BYTE >( cSpell.dwTargetType );
        lpSpell->bRange           = static_cast< BYTE >( cSpell.dwAreaRange );
        lpSpell->wVisualEffect    = static_cast< WORD >( cSpell.dwVisualEffect );        
        lpSpell->wRangeVisualEffect = static_cast< WORD >( cSpell.dwRangeVisualEffect );
        lpSpell->dwNextEffectID   = cSpell.dwSpellID * 1000;
        lpSpell->saAttrib.WIS     = cSpell.dwMinWis;
        lpSpell->saAttrib.INT     = cSpell.dwMinInt;
        lpSpell->saAttrib.Level   = cSpell.dwMinLevel;
        lpSpell->nLineOfSight     = cSpell.boLineOfSight;
        lpSpell->boPVPcheck       = cSpell.boPVPcheck;
		lpSpell->SetDesc(           cSpell.csDesc );
        lpSpell->dwIcon           = cSpell.dwIcon;
        if( !lpSpell->successPercentage.SetFormula( cSpell.csSuccessPercentage.c_str() ) ){
            _LOG_DEBUG
                LOG_DEBUG_LVL2,
                "Spell %s ID#%u uses an invalid success percentage. It has been reset to 100%.",
                cSpell.csName.c_str(),
                cSpell.dwSpellID
            LOG_
               
            lpSpell->successPercentage.SetFormula( "100" );
        }

        // Load the spell's requirements
        {
            vector< WDASpellRequirements > &vReqs = cSpell.vSpellRequirements;
            
            // Scroll through all requirements
            vector< WDASpellRequirements >::iterator j;
            for( j = vReqs.begin(); j != vReqs.end(); j++ ){
                LPUSER_SKILL lpUserSkill = new USER_SKILL;

                // Fetch the requirements
                lpUserSkill->SetSkillID( (*j).GetRequiredSpellID() );
                lpUserSkill->SetSkillPnts( 0 );

                // Add the requirement to the spell.
                lpSpell->saAttrib.tlSkillRequired.AddToTail( lpUserSkill );
            }
        }

        // Load the spell effects.
        {
            vector< WDASpellEffects > &vEffects = cSpell.vSpellEffects;

            // Scroll through all effects.
            vector< WDASpellEffects >::iterator j;
            for( j = vEffects.begin(); j != vEffects.end(); j++ ){        
                WDASpellEffects &cEffect = (*j);
                
                // Get an object of type wEffect from the SpellEffectManager
                SpellEffect *lpSpellEffect = 
                    SpellEffectManager::GetEffectObject( static_cast< WORD >( cEffect.GetEffectStructureID() ), lpSpell );

                // If the spell effect structure is valid.
                if( lpSpellEffect != NULL ){                
                    
                    // Get its parameters.
                    vector< WDASpellEffectParameters > &vParams = cEffect.GetParams();
                    
                    // If the list of parameters is not empty.
                    if( !vParams.empty() ){
                        // Scroll through the list of parameter.
                        vector< WDASpellEffectParameters >::iterator k;
                        for( k = vParams.begin(); k != vParams.end(); k++ ){
                            WDASpellEffectParameters &cParam = (*k);
                            // If parameter was not acknowledged by the effect.
                            if( !lpSpellEffect->InputParameter( cParam.GetParamValue().c_str(), static_cast< WORD >( cParam.GetParamID() ) ) ){
                                boError = TRUE;
                                _LOG_DEBUG
                                    LOG_DEBUG_LVL2,
                                    "Spell %s ID#%u uses an effect type %u."
                                    " This effect has a parameter ID#%u which is set to an invalid value '%s'.",
                                    cSpell.csName.c_str(),
                                    cSpell.dwSpellID,
                                    cEffect.GetEffectStructureID(),
                                    cParam.GetParamID(),
                                    cParam.GetParamValue().c_str()
                                LOG_                                                               
                            }
                        }
                    }else{
                        // If no parameters were found, ask effect if this is OK.
                        if( !lpSpellEffect->InputParameter( "", 0 ) ){
                            // If not OK.
                            boError = TRUE;
                            _LOG_DEBUG
                                LOG_DEBUG_LVL2,
                                "Spell %s ID#%u uses an effect type %u. This effect requires parameters and none have been set.",
                                cSpell.csName.c_str(),
                                cSpell.dwSpellID,
                                cEffect.GetEffectStructureID()                                
                            LOG_                                                                
                        }
                    }
                    // If no error occured while processing the effect
                    if( !boError ){
                        // Add the effect to the spell
                        lpSpell->tlEffects.AddToTail( lpSpellEffect );
                    }else{
                       // delete lpSpellEffect;
                    }
                }
                // If spell structure is not valid.
                else{
                    boError = TRUE;
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Spell %s ID#%u uses an unsupported effect type %u.",
                        cSpell.csName.c_str(),
                        cSpell.dwSpellID,
                        cEffect.GetEffectStructureID()
                    LOG_
                }
            }// for vEffects ...
        } // Load the spell effects
        
        // If no error occured
        if( !boError ){
            // Register spell for use!
            SpellMessageHandler::RegisterSpell( lpSpell->wSpellID, lpSpell );
        }else{
            _LOG_DEBUG
                LOG_DEBUG_LVL2,
                "An error occured while loading spell %s ID#%u. Spell will be inactive.",
                cSpell.csName.c_str(),
                cSpell.dwSpellID
            LOG_

            // Destroy any loaded effects
            lpSpell->tlEffects.AnnihilateList();
            // Delete the spell.
            lpSpell->Delete();
        }            
    } // for( vSpell.begin() ... 
}
//////////////////////////////////////////////////////////////////////////////////////////
void T4C_Initialization::WDAInitWorlds
//////////////////////////////////////////////////////////////////////////////////////////
//  Initializes the worlds from a WDAFile.
// 
(
 WDAWorlds &wdaWorlds // The WDAFile to load the worlds from.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD dwHighestID = 0;
	
    vector< WDAWorlds::WorldData > &vWorlds = wdaWorlds.GetWorlds();
    vector< WDAWorlds::WorldData >::iterator i;

    // Scroll through the worlds to find the highest worldID;
    for( i = vWorlds.begin(); i != vWorlds.end(); i++ ){
        // If a new world ID was found.
        if( (*i).wWorldID > dwHighestID ){
			dwHighestID = (*i).wWorldID;
        }
	}

	// Although the variable name is not significant, set the quantity of worlds.
    TFCServer->world_number = dwHighestID + 1;
	
	// Initialize space for the worlds.
	TFCServer->World = new WorldMap[ TFCServer->world_number ];

    // Re-scroll through the worlds to load them.
    for( i = vWorlds.begin(); i != vWorlds.end(); i++ ){
        WDAWorlds::WorldData &cWorld = (*i);
        WORD wlMAXX = cWorld.wWorldSizeX;
		WORD wlMAXY = cWorld.wWorldSizeY;		
				
		// Create this world.
		TFCServer->World[ cWorld.wWorldID ].Create( 
            wlMAXX, 
            wlMAXY, 
            cWorld.wWorldID, 
            cWorld.lpbData 
        );
    }
}
namespace{
    struct CONTAINER_ITEM_GROUP{
	    LPWORD lpwBaseReferenceID;	// Pointer to BaseReferenceID to set.
	    CString csID;				// String ID of item to get.
	    CString csObjectID;			// ID of binded object (debug)
    };
};
//////////////////////////////////////////////////////////////////////////////////////////
void T4C_Initialization::WDAInitObjects
//////////////////////////////////////////////////////////////////////////////////////////
//  Initializes the items.
// 
(
 WDAObjects &cObjects // The WDAFile from which we create the items.
)
//////////////////////////////////////////////////////////////////////////////////////////
{

    TemplateList <ObjectStructure>			tlKeyReference;
	TemplateList <CString>					tlKeyReferenceName;
    TemplateList <CONTAINER_ITEM_GROUP>		tlContainerGroup;

    // Get the list of loaded items
    vector< WDAObjects::ObjectData > &vObjects = cObjects.GetObjects();

    // Scroll through the list of objects.
    vector< WDAObjects::ObjectData >::iterator i;
    for( i = vObjects.begin(); i != vObjects.end(); i++ ){
        WDAObjects::ObjectData &cItem = (*i);

        WORD previousExistingBindedID =
            Unit::GetIDFromName( cItem.csID.c_str(), U_OBJECT, TRUE );


        WORD dualRegistrationID = 0;
        if( previousExistingBindedID != 0 ){
            _LOG_DEBUG
                LOG_DEBUG_LVL1,
                "Found duplicate item ID %s, unregistring previous one. (overriding it)",
                cItem.csID.c_str()
            LOG_

            Unit::UnregisterUnit( previousExistingBindedID );

            dualRegistrationID = cItem.dwBindedID;
            cItem.dwBindedID = previousExistingBindedID;
        }
                
        // Create the object instance.
	    ObjectStructure *lpObject = 
            DynObjManager::GetRegisteredUnit(
                static_cast< WORD >( cItem.dwStructureID ),
				static_cast< WORD >( cItem.dwBindedID ),
				cItem.csID.c_str()
            );
        
        if( dualRegistrationID != 0 ){
            Unit::RegisterUnitMessageHandler(
                dualRegistrationID,
                lpObject,
                cItem.csID.c_str(),
                U_OBJECT,
                FALSE,
                TRUE
            );
        }

        // If the object structure could be created.
        if( lpObject != NULL )
		{
			// Initialize the objects' members.
			lpObject->appearance		= static_cast< WORD >( cItem.dwAppearance );
            switch( cItem.dwStructureID ){           
            // Sword structure
            case 13: // bows
            case 12: // quivers
            case 1:  lpObject->item_type = WEAPON; break;
            case 2:  lpObject->item_type = ARMOR;  break;
            case 7:  lpObject->item_type = POTION; break;
            default: lpObject->item_type = 0;      break;
            }
            lpObject->itemStructureId   = cItem.dwStructureID;
            lpObject->sell_type         = cItem.dwSellType;
			lpObject->equip_position	= cItem.dwEquipPos;
			lpObject->cost				= cItem.dwSellPrice;
			lpObject->size				= cItem.dwSize;
			lpObject->armor.AC			= cItem.dblArmor_AC;
			lpObject->armor.Dod			= cItem.dwArmor_DodgeMalus;
			lpObject->armor.End			= cItem.dwArmor_MinEnd;
			lpObject->weapon.Att		= cItem.dwWeapon_Attack;
			lpObject->weapon.Str		= cItem.dwWeapon_Str;
            lpObject->weapon.ranged     = cItem.boWeapon_Ranged;
            lpObject->weapon.infiniteAmmo = cItem.boWeapon_RangedInfiniteAmmo;
			lpObject->container.dwUserRespawn =	  cItem.dwContainer_UserRespawn;
			lpObject->container.dwGlobalRespawn = cItem.dwContainer_GlobalRespawn;
			lpObject->container.dwGold = cItem.dwContainer_Gold;
			lpObject->magic.charges    = cItem.lCharges;
            lpObject->magic.nMinWis    = cItem.dwMinWis;
            lpObject->magic.nMinInt    = cItem.dwMinInt;
            TRACE( "\r\nLoading %u charges", lpObject->magic.charges );
            lpObject->lock.key			= 0;
            lpObject->lock.wDifficulty  = cItem.dwLockDifficulty;
			lpObject->weapon.Agi	    = cItem.dwWeapon_Agi;				
			lpObject->text.csText		= cItem.csBook_Text.c_str();
            lpObject->dwDropFlags       = cItem.dwDropFlags;
            lpObject->GmItemLocation    = cItem.csGmItemLocation;
            lpObject->uniqueItem        = cItem.boUnique;
            lpObject->canSummon         = cItem.boCanSummon;
            			
			lpObject->cRadiance			= cItem.dwRadiance;
			lpObject->name = new char[ cItem.csName.size() + 1 ];
			strcpy( lpObject->name, cItem.csName.c_str() );
			
			// If there is a key item binded
			if( !cItem.csLock_KeyID.empty() ){
				CString *lpcsKey = new CString;
				(*lpcsKey) = cItem.csLock_KeyID.c_str();
				tlKeyReference.AddToTail( lpObject );
				tlKeyReferenceName.AddToTail( lpcsKey );
			}

            if( cItem.csWeapon_Exhaust != "0" ){
                TRACE( "\nFound %s exhaust formula.", cItem.csWeapon_Exhaust.c_str() );
            }
            if( !lpObject->weapon.cDealtExhaust.SetFormula( cItem.csWeapon_Exhaust.c_str() ) ){
				// Log error and set damage to 0.
				_LOG_DEBUG 
                    LOG_DEBUG_LVL2, 
                    "Error parsing weapon exhaust for item ID %s, string='%s'.", 
                    cItem.csID.c_str(), 
                    cItem.csWeapon_Exhaust.c_str()
				LOG_
            }                         

			// Set the damage formula
            if( !lpObject->weapon.cDamage.SetFormula( cItem.csWeapon_DmgRoll.c_str() ) ){
				// Log error and set damage to 0.
				_LOG_DEBUG 
                    LOG_DEBUG_LVL2, 
                    "Error parsing damage roll for item ID %s, damage string='%s'.", 
                    cItem.csID.c_str(), 
                    cItem.csWeapon_DmgRoll.c_str()
				LOG_

				TRACE( "\r\nError parsing damage roll for item ID %s, damage string='%s'.", 
				    cItem.csID.c_str(), 
                    cItem.csWeapon_DmgRoll.c_str()
				);
			}

			// Load the object's spells
            {
                vector< WDAObjectsSpells >::iterator s;
			
                // Scroll through the object's spells.
                for( s = cItem.vSpells.begin(); s != cItem.vSpells.end(); s++ ){
			    	WDAObjectsSpells &cSpell = (*s);

    			    // Create a new object spell structure
	    			LPOBJECT_SPELL lpObjectSpell = new OBJECT_SPELL;
		    		lpObjectSpell->wSpellID = cSpell.GetSpellID();
			    	lpObjectSpell->wHook	= cSpell.GetMessageHook();
				
    				// Add the object spell to the object.
	    			lpObject->tlSpells.AddToTail( lpObjectSpell );
		    	}
            }
			
			// Load the object's attribute boosts.
            {
                vector< WDAObjectsAttrBoosts >::iterator a;
                for( a = cItem.vAttrBoosts.begin(); a != cItem.vAttrBoosts.end(); a++ ){
                    WDAObjectsAttrBoosts &cBoost = (*a);

					LPOBJECT_BOOST lpObjectBoost = new OBJECT_BOOST;

					lpObjectBoost->wStat	=  cBoost.GetStat();
					lpObjectBoost->dwBoostID = cBoost.GetID();
					lpObjectBoost->bfBoost.SetFormula( cBoost.GetBoost().c_str() );
					lpObjectBoost->nMinWIS	=  cBoost.GetMinWis();
					lpObjectBoost->nMinINT	=  cBoost.GetMinInt();

					// Add the object boost to the object.
					lpObject->tlBoosts.AddToTail( lpObjectBoost );
				}
			}

			// Load each groups of items.
            {
                // Scroll through all containers.
                vector< WDAObjectsContainerGroups >::iterator c;
                for( c = cItem.vContainers.begin(); c != cItem.vContainers.end(); c++ ){
                    WDAObjectsContainerGroups &cContainer = (*c);

					// Create new group of item.
					LPOBJECT_GROUPITEMS lpGroupItems = new OBJECT_GROUPITEMS;

                    // Scroll through all items in this container.
                    vector< WDAObjectsContainerItems >::const_iterator k;
                    for( k = cContainer.GetItems().begin(); k != cContainer.GetItems().end(); k++ ){
                        const WDAObjectsContainerItems &cContItem = (*k);
						// Create a container item group for later resolving IDs.
						CONTAINER_ITEM_GROUP *lpCon = new CONTAINER_ITEM_GROUP;

						// Create a new WORD to add to item list.
						LPWORD lpwID = new WORD;
						*lpwID = 0;	// 0, for now
						// Add this ID to this item group.								
						lpGroupItems->tlItemBaseReferenceID.AddToTail( lpwID );

						// Add ID to resolve when finished loading.
						lpCon->lpwBaseReferenceID = lpwID;
						lpCon->csID = (*k).GetItemID().c_str();
						lpCon->csObjectID = cItem.csID.c_str();

						// Add it to the resolve list
						tlContainerGroup.AddToTail( lpCon );
					}
					// Add group items to container
					lpObject->container.tlItemGroups.AddToTail( lpGroupItems );
				}
			}
		}
        // If the object structure could not be found.
        else{
			_LOG_DEBUG 
                LOG_DEBUG_LVL2, 
                "Could not instantiate object structure %u, name %s, ID %u.", 
				cItem.dwStructureID, 
                cItem.csID.c_str(),
                cItem.dwBindedID
			LOG_
		}		
    } // for( vObjects.begin() ...

	// After all objects have been loaded, set the key references.
	tlKeyReference.ToHead();
	tlKeyReferenceName.ToHead();	
	
	// Loop through the key references
	while( tlKeyReference.QueryNext() ){
		tlKeyReferenceName.QueryNext();

		WORD wID = Unit::GetIDFromName( (LPCTSTR)( *tlKeyReferenceName.Object() ), U_OBJECT, TRUE );
		if( wID != 0 ){
			// Set key ID to corresponding numerical ID.
			tlKeyReference.Object()->lock.key = wID;			
		}else{
			_LOG_DEBUG LOG_DEBUG_LVL2, "Undefined key reference %s on object display named %s", 
				(LPCTSTR)( *tlKeyReferenceName.Object() ), tlKeyReference.Object()->name
			LOG_

			TRACE( "\r\nUndefined key reference %s on object display named %s", 
				(LPCTSTR)( *tlKeyReferenceName.Object() ),tlKeyReference.Object()->name 
			);				
		}
		tlKeyReferenceName.DeleteAbsolute();
	}

	// Loop through the references to resolve
	tlContainerGroup.ToHead();
	while( tlContainerGroup.QueryNext() ){
		CONTAINER_ITEM_GROUP *lpGroupID = tlContainerGroup.Object();

		// Change value of item
		*(lpGroupID->lpwBaseReferenceID) = Unit::GetIDFromName( lpGroupID->csID, U_OBJECT, TRUE );
		// If the function could not find the ID
		if( *lpGroupID->lpwBaseReferenceID == 0 ){
			// Log the error
			_LOG_DEBUG 
				LOG_DEBUG_LVL2, 
				"Undefined item reference %s in object in container item %s",
				(LPCTSTR)lpGroupID->csID,
				(LPCTSTR)lpGroupID->csObjectID
			LOG_
		}

		// Delete this request
		tlContainerGroup.DeleteAbsolute();
	}
    DynObjManager::PostInitDestroy();

    // Loads the world objects
    {
        vector< WDAObjectsWorldObjects >::iterator z;

        // Scroll through all locations.
        for( z = cObjects.GetLocations().begin(); z != cObjects.GetLocations().end(); z++ ){
            WDAObjectsWorldObjects &cLoc = (*z);

            // Get the object's ID.
            WORD wID = Unit::GetIDFromName( cLoc.GetItemID().c_str(), U_OBJECT, TRUE );
			// If the object exists.
            if( wID != 0 ){
				//TFCServer->World[rsWorlds.m_ID].create_world_unit(U_OBJECT, wBaseReferenceID, wlObj);
				BOOL boInvalidPos = FALSE;
				WorldMap *wlWorld = TFCMAIN::GetWorld( cLoc.GetPos().world );

				if( wlWorld != NULL ){
					WorldPos wlPos = { 
				        cLoc.GetPos().X,
					    cLoc.GetPos().Y,
					    cLoc.GetPos().world
					};
					
					if( wlWorld->IsValidPosition( wlPos ) ){
						// Create the world unit.
						if( wlWorld->create_world_unit( U_OBJECT, wID, wlPos, NULL, FALSE ) == NULL ){
							_LOG_DEBUG
								LOG_DEBUG_LVL2,
								"Object ID %s at ( %u, %u, %u ) couldn't be created.",
								cLoc.GetItemID().c_str(),
								cLoc.GetPos().X,
								cLoc.GetPos().Y,
								cLoc.GetPos().world
							LOG_
						}
					}else{
						boInvalidPos = TRUE;
					}
				}else{
					boInvalidPos = TRUE;
				}

				if( boInvalidPos ){
					_LOG_DEBUG
						LOG_DEBUG_LVL2,
						"Object ID %s at ( %u, %u, %u ) is at an invalid position.",
						cLoc.GetItemID().c_str(),
						cLoc.GetPos().X,
						cLoc.GetPos().Y,
						cLoc.GetPos().world
					LOG_
				}														
			}else{
				_LOG_DEBUG
					LOG_DEBUG_LVL2,
					"Object at position ( %u, %u, %u ) has an invalid objectID.",
					cLoc.GetPos().X,
					cLoc.GetPos().Y,
					cLoc.GetPos().world
				LOG_
			}
        }
    }
}

namespace{
struct HIVE{
	WORD wMinEmergeTime;
	WORD wMaxEmergeTime;
	WORD wMaxChildren;
	WORD wEmergenceRange;
	TemplateList < LARVA > tlLarvae;
};
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD GetItemAppearance
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the appearance of a given item static Id.
// 
(
 DWORD itemId // The item's static id
)
// Return: WORD, the item's appearance.
//////////////////////////////////////////////////////////////////////////////////////////
{
    Objects *obj = new Objects;
    if( !obj->Create( U_OBJECT, itemId ) ){
        obj->DeleteUnit();
        return 0;
    }
    WORD appearance = obj->GetAppearance();
    obj->DeleteUnit();
    return appearance;
}

//////////////////////////////////////////////////////////////////////////////////////////
void T4C_Initialization::WDAInitCreatures
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes the creature.
// 
(
 WDACreatures &cCreatures // The file.
)
//////////////////////////////////////////////////////////////////////////////////////////
{

    // Get the loaded creatures.
    vector< WDACreatures::CreatureData > &vCreatures = cCreatures.GetCreatures();
    vector< WDACreatures::CreatureData >::iterator i;
    for( i = vCreatures.begin(); i != vCreatures.end(); i++ ){
        WDACreatures::CreatureData &cCreature = *i;
        SimpleMonster *newMob = new SimpleMonster;
        MonsterStructure *mob = newMob->GetMonsterStructure();
        
        WORD previousExistingID =
            Unit::GetIDFromName( cCreature.csID.c_str(), U_NPC, TRUE );
        if( previousExistingID != 0 ){
            _LOG_DEBUG
                LOG_DEBUG_LVL1,
                "Found duplicate creature ID %s. Unregistering previous one (overriding it).",
                cCreature.csID.c_str()
            LOG_

            Unit::UnregisterUnit( previousExistingID );

            cCreature.dwBindedID = previousExistingID;
        }

        char *name = new char[ cCreature.csName.size() + 1 ];
        strcpy( name, cCreature.csName.c_str() );
        mob->name = name;
        mob->STR = cCreature.dwSTR;       
        mob->END = cCreature.dwEND;
        mob->AGI = cCreature.dwAGI;
        mob->INT = cCreature.dwINT;
        mob->WIL = cCreature.dwWIL;
        mob->WIS = cCreature.dwWIS;        
        mob->LCK = cCreature.dwLCK;
        mob->AirResist = cCreature.dwAirResist;
        mob->EarthResist = cCreature.dwEarthResist;
        mob->WaterResist = cCreature.dwWaterResist;
        mob->FireResist = cCreature.dwFireResist;
        mob->DarkResist = cCreature.dwDarkResist;
        mob->LightResist = cCreature.dwLightResist;
        mob->AirPower = cCreature.dwAirPower;
        mob->EarthPower = cCreature.dwEarthPower;
        mob->WaterPower = cCreature.dwWaterPower;
        mob->FirePower = cCreature.dwFirePower;
        mob->DarkPower = cCreature.dwDarkPower;
        mob->LightPower = cCreature.dwLightPower;
        mob->level = cCreature.dwLevel;
        mob->HP = cCreature.dwHP;
        mob->DodgeSkill = cCreature.dwDodgeSkill;
        mob->AC = cCreature.dblAC;
        mob->appearance = cCreature.dwAppearance;
        mob->Corpse = cCreature.dwAppearance + 5000;
        mob->wBody = GetItemAppearance( cCreature.dwDressBody );
        mob->wFeet = GetItemAppearance( cCreature.dwDressFeet );
        mob->wGloves = GetItemAppearance( cCreature.dwDressGloves );
        mob->wHelm = GetItemAppearance( cCreature.dwDressHelm );
        mob->wLegs = GetItemAppearance( cCreature.dwDressLegs );
        mob->wWeapon = GetItemAppearance( cCreature.dwDressWeapon );
        mob->wShield = GetItemAppearance( cCreature.dwDressShield );
        mob->wCape = GetItemAppearance( cCreature.dwDressCape );
        mob->agressive = cCreature.dwAggressivness;
        mob->clan = cCreature.dwClanID;
        mob->speed = cCreature.dwSpeed;
        mob->XPperHit = cCreature.dblXPperHit;
        mob->XPperDeath = cCreature.dblXPperDeath;
        mob->MinGold = cCreature.dwMinGiveGold;
        mob->MaxGold = cCreature.dwMaxGiveGold;
        mob->boCanAttack = cCreature.boCanAttack;
        mob->speed = 25;
        mob->cAttackLag = dice( 1, 1500, 750);
        mob->bLagChance = 20;
        mob->cStopLen = dice( 1, 1000, 400);

        // Scroll through all monster attacks.
        {
            vector< WDACreatures::CreatureAttack >::iterator i;
            for( i = cCreature.vAttacks.begin(); i != cCreature.vAttacks.end(); i++ ){
                WDACreatures::CreatureAttack &cAttack = *i;
            
                LPMONSTER_ATTACK monsterAttack;

                // If this is a spell attack
                if( cAttack.dwAttackSpell != 0 ){                
                    // Create a spell attack.
                    monsterAttack = new MONSTER_SPELL_ATTACK;

                    // Fill-in spell specific information.
                    static_cast< LPMONSTER_SPELL_ATTACK >( monsterAttack )
                        ->wSpellID = cAttack.dwAttackSpell;
                }
                // If this is a physical attack.
                else{
                    // Create an ordinary attack.
                    monsterAttack = new MONSTER_ATTACK;
                }

                monsterAttack->AttackDoingPercentage = cAttack.dwAttackPercentage;
                monsterAttack->AttackSkill = cAttack.dwAttackSkill;
                if( !monsterAttack->DamageRoll.SetFormula( cAttack.csDmgRoll.c_str() ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL1,
                        "Wrong formula on db monster %s.",
                        cCreature.csName.c_str()
                    LOG_
                }
                monsterAttack->nMaxRange = cAttack.dwAttackMaxRange;
                monsterAttack->nMinRange = cAttack.dwAttackMinRange;                

                // Add attack to monster structure.
                if( cAttack.dwAttackSpell != 0 ){
                    mob->vlpRangeAttacks.push_back( monsterAttack );
                }else{
                    mob->vlpMonsterAttacks.push_back( monsterAttack );
                }
            }
        }
        // Scroll through all death items
        {
            vector< WDACreatures::CreatureDeathItem >::iterator i;
            for( i = cCreature.vItems.begin(); i != cCreature.vItems.end(); i++ ){
                WDACreatures::CreatureDeathItem &cItem = *i;

                ItemToGive sItem; 
                sItem.ItemID = cItem.dwItemID;
                sItem.ItemGivePercentage = cItem.dblDropPercentage;
                
                mob->vDeathItems.push_back( sItem );
            }
        }
        // Scroll through all death flags
        {
            vector< WDACreatures::CreatureDeathFlag >::iterator i;
            for( i = cCreature.vDeathFlags.begin(); i != cCreature.vDeathFlags.end();)
			{
                WDACreatures::CreatureDeathFlag &cFlag = *i;

                sDeadFlag sFlag;


                sFlag.nDeathGiveFlag       = cFlag.dwFlag;
                sFlag.nDeathFlagValue      = cFlag.dwFlagValue;
                sFlag.boDeathFlagIncrement = cFlag.boIncrement;
				mob->vOnDeathFlag.push_back(sFlag);

                // Terminate loop (only one death flag supported as of now).
                i++;// = cCreature.vDeathFlags.end();
            }
        }

        // Register the monster.
        mob->wBaseReferenceID = 
            Unit::RegisterUnitMessageHandler( 
                cCreature.dwBindedID, 
                newMob, 
                cCreature.csID.c_str(), 
                U_NPC, 
                TRUE 
            );
    }    



}

//////////////////////////////////////////////////////////////////////////////////////////
void T4C_Initialization::WDAInitHives
//////////////////////////////////////////////////////////////////////////////////////////
//  Initializes the hives.
// 
(
 WDAHives &cHives // The WDAFile from which we load the hives.
)
//////////////////////////////////////////////////////////////////////////////////////////
{    
    // Load the hives.
    vector< WDAHives::HiveData >::iterator i;
    for( i = cHives.GetHives().begin(); i != cHives.GetHives().end(); i++ ){
        WDAHives::HiveData &cHive = (*i);

        // Position the hive.
        {
            // Get all possible positions for this hive.
            vector< WDAHives::WorldPos >::iterator l;
            for( l = cHive.vLocations.begin(); l != cHive.vLocations.end(); l++ ){
                WDAHives::WorldPos &hivePos = (*l);

				Hive *lpHive = new Hive;

				// Create the hive.
				lpHive->Create( 
					cHive.dwMinEmergeTime, 
					cHive.dwMaxEmergeTime,
					cHive.dwMaxChildren,
					cHive.dwEmergenceRange
				);

                // Put all larvae into this hive.
                vector< WDALarvae >::iterator h;
                for( h = cHive.vLarvae.begin(); h != cHive.vLarvae.end(); h++ ){
                    WDALarvae &cLarva = (*h);
        
		            WORD wMonsterID = 0;
		            
                    // Create a new larva.
                    if( !cLarva.GetLarvaID().empty() ){				
                        // Get the larva's numerical ID
                        TRACE( "\r\nFound larva %s", cLarva.GetLarvaID().c_str() );
                        wMonsterID = Unit::GetIDFromName( cLarva.GetLarvaID().c_str(), U_NPC, TRUE );
                    }
					            
                    // If no error occured
                    if( wMonsterID != 0 ){
                        LARVA *lpLarva = new LARVA;
                        lpLarva->wMonsterID = wMonsterID;
                        
                        // Add the monster ID to the hive.
                        lpHive->AddLarva( lpLarva );
                    }else{
                        TRACE( "*ERROR*" );
				        _LOG_DEBUG
					        LOG_DEBUG_LVL2,
					        "Invalid monster ID '%s' in larvae group.",
					        cLarva.GetLarvaID().c_str()
				        LOG_
                    }
                }
                
				BOOL boInvalidPos = FALSE;

				// Deposit the unit.
				WorldMap *wlWorld = TFCMAIN::GetWorld( hivePos.world );
				// If world isn't null.
				if( wlWorld != NULL ){
					WorldPos wlPos = {
					    hivePos.X,
						hivePos.Y,
						hivePos.world
					};
					
					// If position is valid within the world
					if( wlWorld->IsValidPosition( wlPos ) ){
					
						// Set the hive's position and deposit it.
						lpHive->SetWL( wlPos );						

						TRACE( "\r\nPlacing hive at ( %u, %u, %u ).",
							wlPos.X,
							wlPos.Y,
							wlPos.world
						);

						wlWorld->deposit_unit( wlPos, lpHive );

					}else{
						boInvalidPos = TRUE;
					}
				}else{
					boInvalidPos = TRUE;
				}

				if( boInvalidPos ){
					_LOG_DEBUG
						LOG_DEBUG_LVL2,
						"World hive at %u, %u, %u is at an invalid position.",
						hivePos.X,
						hivePos.Y,
						hivePos.world
					LOG_
				}
            }
        }        
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void T4C_Initialization::WDAInitAreaLinks
//////////////////////////////////////////////////////////////////////////////////////////
//  Initialize all area links
// 
(
 WDAAreaLinks &cAreaLinks // The WDAFile to load the area links from.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    vector< WDAAreaLinks::AreaLinkData >::iterator i;
    for( i = cAreaLinks.GetAreaLinks().begin(); i != cAreaLinks.GetAreaLinks().end(); i++ ){
        WDAAreaLinks::AreaLinkData &cLink = (*i);      
        WorldMap *lpWorld = TFCMAIN::GetWorld( cLink.wlSourcePos.world );
	    if( lpWorld ){
            WorldPos wlPos;
            wlPos.X = cLink.wlTargetPos.X;
            wlPos.Y = cLink.wlTargetPos.Y;
            wlPos.world = cLink.wlTargetPos.world;
				
            lpWorld->add_effect( 
                cLink.wlSourcePos.X, 
                cLink.wlSourcePos.Y, 
                cLink.wlSourcePos.X,
                cLink.wlSourcePos.Y,
                __AREA_TELEPORT,
                &wlPos,
                sizeof( WorldPos )
            );				
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void T4C_Initialization::WDAInitClans
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes all clans.
// 
(
 WDAClans &cClans // The WDAFile to load the clans from
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Create the new clan array and initialize the clans.
    Clans::SetNumberOfClans( cClans.GetHighestClan() + 1 );
    CreatureClans = Clans::InitClans( );

    vector< WDAClans::ClanRelation >::iterator i;
    for( i = cClans.GetClanRelations().begin(); i != cClans.GetClanRelations().end(); i++ ){
        WDAClans::ClanRelation &cRelation = (*i);

        // If both clans in relation are valid
		if( cRelation.wFirstClanID <= cClans.GetHighestClan() && cRelation.wSecondClanID <= cClans.GetHighestClan() ){
			TRACE( "Setting up relation %d between clans %u and %u", 
				cRelation.sClanRelation,
				cRelation.wFirstClanID,
				cRelation.wSecondClanID
			);
				    
			CreatureClans[ cRelation.wFirstClanID ].SetClanRelation( 
			    static_cast< short >( cRelation.wSecondClanID ),                 
                static_cast< char > ( cRelation.sClanRelation )
            );
            CreatureClans[ cRelation.wSecondClanID ].SetClanRelation(
                static_cast< short >( cRelation.wFirstClanID ),
                static_cast< char > ( cRelation.sClanRelation )
            );
		}else{
			_LOG_DEBUG
				LOG_DEBUG_LVL2,
				"Impossible clan relation between out-of-bound clans %u and %u",
				cRelation.wFirstClanID,
				cRelation.wSecondClanID
			LOG_
		}
    }
}

#define LOGEXCEPTION( txt )\
                _LOG_DEBUG\
                    LOG_CRIT_ERRORS,\
                    "Crashed initializing " txt "."\
                LOG_\
                throw;

#define CATCHDB()\
    catch(CDaoException *e ){\
            char err[ 1024 ];\
            e->GetErrorMessage( err, 1024 );\
            printf( "\r\n[Database Error: %s]", err );\
            _LOG_DEBUG\
                LOG_CRIT_ERRORS,\
                "Error in DAO database( %s ): %s.",\
                csDBname.c_str(),\
                err\
            LOG_;\
            throw;\
        }

class WorldLogger : public Logger{
public:
    void SetLogLevel( DEBUG_LEVEL dl ){
        dlDebugLevel = dl;
    }

private:
    void LogAnsi( DEBUG_LEVEL dl, char *szText ){
        if( dl & dlDebugLevel ){
            printf( "\n   - %s", szText );
        }
    }
    void LogUnicode( DEBUG_LEVEL dl, wchar_t *szText ){
    }

};


//////////////////////////////////////////////////////////////////////////////////////////
void TFCInitMaps( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Initializes the server worlds.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    T4C_Initialization cInit;

    /*if( !theApp.sLicense.loadDb ){
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "Could not open T4C Edit.WDA."
        LOG_
        exit( CANNOT_OPEN_T4C_EDIT_WDA );
	}*/

    TraceLogger cTraceLogger;
    cTraceLogger.SetLogLevel( DL_INFO );

    // Opens the WDAFile
    WDAFile wdaFile;
    WDAFile editorFile;

	std::string sBaseFolder(TFCMAIN::GetHomeDir());
	sBaseFolder += "WDA\\";

	std::vector<std::string> vWDAFilenames;
	std::vector<std::string>::const_iterator fni;
	vWDAFilenames.push_back(sBaseFolder+"T4C Worlds.WDA");
	//vWDAFilenames.push_back(sBaseFolder+"DialsoftV2Edit.WDA"); // steph désactivation
	vWDAFilenames.push_back(sBaseFolder+"T4C Edit.WDA");

	std::vector<WDAFile*> vWDAFiles;
	std::vector<WDAFile*>::const_iterator fi;

	for (fni=vWDAFilenames.begin(); fni!=vWDAFilenames.end(); fni++) {
		WDAFile *file = new WDAFile;
		if ( file->Open( *fni ) ) {
			WDAHeader header;
			if( !header.CreateFrom( *file ) ){                
				_LOG_DEBUG
					LOG_CRIT_ERRORS,
					"There was an error opening the WDA file %s",
					(*fni).c_str()
				LOG_

				printf( "\r\nThere is an error in the WDA file %s.",
					(*fni).c_str()
				);

				if( !header.IsVersionOK() ){
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"Wrong file version."
					LOG_
					printf( "Wrong file version." );
				}
				exit( CANNOT_OPEN_T4C_EDIT_WDA );
			}
			vWDAFiles.push_back( file );
		} else {
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Could not open wda file : %s.",
				(*fni).c_str()
			LOG_
			exit( CANNOT_OPEN_T4C_EDIT_WDA );
		}
	}


    // Initialize all sub-systems.
    printf( "\n- Loading Spells" );
    try{
        WDASpells cSpells( cTraceLogger );                

		for (fi=vWDAFiles.begin(); fi!=vWDAFiles.end(); fi++) {
			cSpells.CreateFrom( **fi, true );
		}

        cInit.WDAInitSpells( cSpells );

    }catch(...){ LOGEXCEPTION( "spells" ) }

    printf( "\n- Loading Worlds Data" );
    try{
        WorldLogger cWorldLogger;
        cWorldLogger.SetLogLevel( DL_DEBUG );
        WDAWorlds wdaWorlds( cWorldLogger );

        // Creates the worlds from the wdaFile
		for (fi=vWDAFiles.begin(); fi!=vWDAFiles.end(); fi++) {
			wdaWorlds.CreateFrom( **fi, true );
        }

        cInit.WDAInitWorlds( wdaWorlds );
    }catch(...){ LOGEXCEPTION( "worlds" ) }

    printf( "\n- Loading Items" );
    try{
        WDAObjects cObjects( cTraceLogger );

		for (fi=vWDAFiles.begin(); fi!=vWDAFiles.end(); fi++) {
	        cObjects.CreateFrom( **fi, true);
        }

        cInit.WDAInitObjects( cObjects );
    }catch(...){ LOGEXCEPTION( "objects" ) }

    printf( "\n- Loading Creatures" );
    try{
        WDACreatures cCreatures( cTraceLogger );

		for (fi=vWDAFiles.begin(); fi!=vWDAFiles.end(); fi++) {
	        cCreatures.CreateFrom( **fi, true );
		}

        cInit.WDAInitCreatures( cCreatures );
    }catch(...){ LOGEXCEPTION( "creatures" ) }

    cInit.WDAInitNPC();

    printf( "\n- Loading Hives" );
    try{
        WDAHives cHives( cTraceLogger );

		for (fi=vWDAFiles.begin(); fi!=vWDAFiles.end(); fi++) {
	        cHives.CreateFrom( **fi, true );
        }

        cInit.WDAInitHives( cHives );
    }catch(...){ LOGEXCEPTION( "hives" ) }

    printf( "\n- Loading Area Links" );
    try{
        WDAAreaLinks cAreaLinks( cTraceLogger );

		for (fi=vWDAFiles.begin(); fi!=vWDAFiles.end(); fi++) {
			cAreaLinks.CreateFrom( **fi, true );
		}

        cInit.WDAInitAreaLinks( cAreaLinks );
    }catch(...){ LOGEXCEPTION( "area links" ) }

    printf( "\n- Loading Clans" );
    try{
        WDAClans cClans( cTraceLogger );

		for (fi=vWDAFiles.begin(); fi!=vWDAFiles.end(); fi++) {
	        cClans.CreateFrom( **fi, true );
		}

        cInit.WDAInitClans( cClans );
    }catch(...){ LOGEXCEPTION( "clans" ) }
	
	// Desboys: Fixing the WDA-related issue.
	for (fi = vWDAFiles.begin(); fi != vWDAFiles.end(); fi++)
	{
		WDAFile *wdaFilePtr = *fi;
		// First, close the file.
		wdaFilePtr->Close();
		// Then, de-allocate the memory.
		delete wdaFilePtr;
	}
	
	// Load the Weather map //BLBLBL ça bouffe trop de ram 28mo par carte
	//printf( "\n- Loading Weather Maps" );
	//WeatherEffect::GetInstance()->LoadWeatherMaps();
}


#undef Command
#include "dbnpc.h"
#include "SimpleNPC.h"
#include "NPC_Editor/NPCManager.h"
//////////////////////////////////////////////////////////////////////////////////////////
void T4C_Initialization::WDAInitNPC( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes any NPC loaded through a .npc file
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( !theApp.sLicense.loadDb ){
        return;
    }

    printf( "\n- Loading NPCs" );

    RegKeyHandler regKey;
    regKey.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\T4C Editors" );
    
    string sBaseFolder = TFCMAIN::GetHomeDir();
	sBaseFolder += "WDA\\";
	string sNPCsWDA(sBaseFolder);
	sNPCsWDA += "NPCs.WDA";
	
	std::vector<std::string>::const_iterator fi;
	std::vector<std::string> vFilesToLoad;
	//vFilesToLoad.push_back( sBaseFolder + "DialsoftV2NPCS.WDA" ); // steph désactivation
	vFilesToLoad.push_back( regKey.GetProfileString( "NPCFile", sNPCsWDA.c_str() ) );

	NPC_Editor::NPCManager *npcMan = NPC_Editor::NPCManager::GetInstance();

	for ( fi=vFilesToLoad.begin(); fi!=vFilesToLoad.end(); fi++) {
	
		WDAFile f;
		if( f.Open( *fi ) ){
       
			npcMan->Load( f );        

		}else{
			_LOG_DEBUG
				LOG_DEBUG_LVL1,
				"Could not find %s",
				(*fi).c_str()
			LOG_
		}
	}

	list< NPC_Editor::NPC * > npcList;
	npcMan->GetNPCList( npcList );

	list< NPC_Editor::NPC * >::iterator i;
	for( i = npcList.begin(); i != npcList.end(); i++ ){
		NPC_Editor::NPC *theNpc = *i;

		SimpleNPC *simpleNpc = new SimpleNPC;
		Creatures *creature = new Creatures;

		WORD creatureId = Unit::GetIDFromName( 
			theNpc->GetCreatureId().c_str(), 
			U_NPC,
			TRUE
		);

		if( creature->Create( U_NPC, creatureId ) ){
			simpleNpc->theNpc = theNpc;
        
			// Get the basic monster structure of the creature.
			MonsterStructure *lpMob;
			creature->SendUnitMessage( MSG_OnGetUnitStructure, creature, NULL, NULL, NULL, &lpMob );

			// Copy the data from the monster.
			*simpleNpc->npc.GetMonsterStructure() = *lpMob;

			simpleNpc->npc.name = new char[ theNpc->GetName().size() + 1 ];\
			strcpy( simpleNpc->npc.name, theNpc->GetName().c_str() );
            simpleNpc->npc.InitialPos.X = 0;
			simpleNpc->npc.InitialPos.Y = 0;
			simpleNpc->npc.InitialPos.world = 0;			
			simpleNpc->npc.boInit = true;
        
			if( Unit::RegisterUnitMessageHandler( 30000, simpleNpc, theNpc->GetId().c_str(), U_NPC, TRUE ) == 0 ){
				_LOG_DEBUG
					LOG_DEBUG_LVL1,
					"Could not register NPC with ID %s.",
					theNpc->GetId().c_str()
				LOG_
			}
		}else{
			_LOG_DEBUG
				LOG_DEBUG_LVL1,
				"Could not bind npc %s to creature Id=%s.",
				theNpc->GetId().c_str(),
				theNpc->GetCreatureId().c_str()
			LOG_
		}
		creature->DeleteUnit();
	}

}

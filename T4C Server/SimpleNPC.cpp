// SimpleNPC.cpp: implementation of the SimpleNPC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "SimpleNPC.h"
#include "NPCMacroScriptLng.h"

#undef Command

#include "NPC_Editor/NPC.h"
#include "NPC_Editor/Keyword.h"
#include "NPC_Editor/Command.h"
#include "NPC_Editor/IfFlow.h"
#include "NPC_Editor/Assign.h"
#include "NPC_Editor/ForFlow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


using namespace NPC_Editor;

namespace{
    typedef list< Instruction * > InstructionList;
    //typedef NPC_Editor::NPC NPC;

};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SimpleNPC::SimpleNPC()
{

}

SimpleNPC::~SimpleNPC()
{

}

#define SETUP_COMMAND( numParam )\
    Command *cmd = static_cast< Command * >( thisIns );\
    vector< string > val;\
    cmd->GetValues( val );\
    if( val.size() < numParam ){\
        return;\
    }

#define INTERPRET_FORMULA( value, var )\
    double var = 0;\
    {::BoostFormula foo;\
    foo.SetFormula( value.c_str() );\
    var = foo.GetBoost( self, target, 0, 0, 0, &varMap );}


#define PROCESS_SUB_INSTRUCTIONS\
    InstructionList subIns;\
    thisIns->GetSubInstructions( subIns );\
    InstructionList::iterator i;\
    for( i = subIns.begin(); i != subIns.end(); i++ ){\
        InterpretContainer( npc, self, target, *i, output, varMap );\
    }

//////////////////////////////////////////////////////////////////////////////////////////
void InterpretContainer
//////////////////////////////////////////////////////////////////////////////////////////
// Interprets the given keyword.
// 
(
 SimpleNPC *npc,
 Unit *self,      // The NPC
 Unit *target,   // The player
 Instruction *thisIns,     // The keyword to interpret.
 CString &output,
 BoostFormula::VarMap &varMap
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    bool xSendBackpackUpdate;

    Character *lpChar = static_cast< Character * >( target );

    // Interpret this instruction.
    switch( thisIns->GetId() ){
    case InsIf:{
        IfFlow *ifFlow = static_cast< IfFlow * >( thisIns );
        ::BoostFormula cond;
        cond.SetFormula( ifFlow->GetCondition().c_str() );
        if( cond.GetBoost( self, target, 0, 0, 0, &varMap ) != 0 ){
            PROCESS_SUB_INSTRUCTIONS;
        }else{
            // Verify if any ElseIFs trigger.
            InstructionList elseIfs;
            ifFlow->GetElseIfs( elseIfs );
            InstructionList::iterator i;
            for( i = elseIfs.begin(); i != elseIfs.end(); i++ ){
                ElseIfFlow *eif = static_cast< ElseIfFlow * >( *i );
                cond.SetFormula( eif->GetCondition().c_str() );
                if( cond.GetBoost( self, target, 0, 0, 0, &varMap ) != 0 ){
                    // Interpret this command.
                    InterpretContainer( npc, self, target, eif, output, varMap );
                    return;
                }
            }
            // If the elseifs did not trigger, try the else flow.
            ElseFlow *elseFlow = ifFlow->GetElseFlow();
            if( elseFlow != NULL ){
                InterpretContainer( npc, self, target, elseFlow, output, varMap );
            }
        }
    } break;
    case InsKeyword:
    case InsElseIf:
    case InsElse:{
        PROCESS_SUB_INSTRUCTIONS;
    } break;
    case InsFor:{
        ForFlow *forFlow = static_cast< ForFlow * >( thisIns );
        
        INTERPRET_FORMULA( forFlow->GetStartValue(), startValue );
        INTERPRET_FORMULA( forFlow->GetEndValue(), endValue );

        string varName = forFlow->GetAssignedVar();
        int i;
        for( i = 0; i < varName.size(); i++ ){
            varName[ i ] = toupper( varName[ i ] );
        }

        double &var = varMap[ varName ];
        for( var = startValue; var < endValue+1; var++ ){
            PROCESS_SUB_INSTRUCTIONS;
        }
    } break;
    case InsWhile:{
        ::BoostFormula cond;
        while( cond.GetBoost( self, target, 0, 0, 0, &varMap ) != 0 ){
            PROCESS_SUB_INSTRUCTIONS;
        }
     } break;
    case InsGiveItem:{
        SETUP_COMMAND( 1 );
        GiveItem( Unit::GetIDFromName( val[ 0 ].c_str(), U_OBJECT, TRUE ) );        
    } break;
    case InsGiveXP:{
        SETUP_COMMAND( 1 );
        INTERPRET_FORMULA( val[ 0 ], xp );
        GiveXP( xp );
    } break;
    case InsSetFlag:{
        SETUP_COMMAND( 2 );
        INTERPRET_FORMULA( val[ 1 ], value );
        GiveFlag( atoi( val[ 0 ].c_str() ), value );
    } break;
    case InsHealPlayer:{
        SETUP_COMMAND( 1 );
        INTERPRET_FORMULA( val[ 0 ], hp );
        HealPlayer( hp );
    } break;
    case InsSayText:{
        SETUP_COMMAND( 1 );
		output += BoostFormula::TranslateStringFormula(val[0].c_str(), self, target, &varMap);
    } break;
    case InsBreakConversation:{
        BREAK;
    } break;
    case InsFightPlayer:{
        FIGHT;
    } break;
    case InsTakeItem:{
        SETUP_COMMAND( 1 );                
        TakeItem( Unit::GetIDFromName( val[ 0 ].c_str(), U_OBJECT, TRUE ) );
    } break;
    case InsTeleport:{
        SETUP_COMMAND( 3 );
        INTERPRET_FORMULA( val[ 0 ], x );
        INTERPRET_FORMULA( val[ 1 ], y );
        INTERPRET_FORMULA( val[ 2 ], w );
        TELEPORT( x, y, w );
    } break;
    case InsCastSpell:{
        SETUP_COMMAND( 1 );        
        CastSpellTarget( atoi( val[ 0 ].c_str() ) );
    } break;
    case InsCastSpellSelf:{
        SETUP_COMMAND( 1 );
        CastSpellSelf( atoi( val[ 0 ].c_str() ) );
    } break;
    case InsGiveGold:{
        SETUP_COMMAND( 1 );
        INTERPRET_FORMULA( val[ 0 ], gold );
        GiveGold( gold );
    } break;
    case InsTakeGold:{
        SETUP_COMMAND( 1 );
        INTERPRET_FORMULA( val[ 0 ], gold );
        TakeGold( gold );
    } break;
    case InsAssign:{
        Assign *ass = static_cast< Assign * >( thisIns );
        INTERPRET_FORMULA( ass->GetValue(), assignedValue );
        string varName = ass->GetVar();
        int i;
        for( i = 0; i < varName.size(); i++ ){
            varName[ i ] = toupper( varName[ i ] );
        }
        varMap[ varName ] = assignedValue;
    } break;
    case InsSendSoldItemList:{


		//////////////////////////////////////////////////////////////////////////////////////////
		// steph ajout de NPC_Editor::
		//////////////////////////////////////////////////////////////////////////////////////////
        std::list< ::NPC::SoldItem > itemList;
        std::list< ::NPC::SoldItem >::iterator i;


        npc->theNpc->GetSoldItemList( itemList );
        CreateItemList
            for( i = itemList.begin(); i != itemList.end(); i++ ){
                AddBuyItem( (*i).price, Unit::GetIDFromName( (*i).itemId.c_str(), U_OBJECT, TRUE ) )
            }
        SendBuyItemList
    } break;
    case InsSendBoughtItemList:{


		//////////////////////////////////////////////////////////////////////////////////////////
		// steph ajout de NPC_Editor::
		//////////////////////////////////////////////////////////////////////////////////////////
        std::list< ::NPC::BoughtItem > itemList;
        std::list< ::NPC::BoughtItem >::iterator i;


        npc->theNpc->GetBoughtItemList( itemList );
        CreateItemList
            for( i = itemList.begin(); i != itemList.end(); i++ ){
                AddSellItem( (*i).sellType, (*i).minPrice, (*i).maxPrice )
            }
        SendSellItemList(INTL( 1963, "I do not see anything interesting in your inventory."))
    } break;
    case InsSendTrainSkillList:{


		//////////////////////////////////////////////////////////////////////////////////////////
		// steph ajout de NPC_Editor::
		//////////////////////////////////////////////////////////////////////////////////////////
        std::list< ::NPC::TrainedSkill > skillList;
        std::list< ::NPC::TrainedSkill >::iterator i;


        npc->theNpc->GetTrainedSkillList( skillList );

        CreateSkillList
            for( i = skillList.begin(); i != skillList.end(); i++ ){
	            AddTrainSkill( (*i).skillId, (*i).maxSkillPnts, (*i).price )
            }
        SendTrainSkillList
    } break;
    case InsSendTeachSkillList:{


		//////////////////////////////////////////////////////////////////////////////////////////
		// steph ajout de NPC_Editor::
		//////////////////////////////////////////////////////////////////////////////////////////
        std::list< ::NPC::TaughtSkill > skillList;
        std::list< ::NPC::TaughtSkill >::iterator i;



        npc->theNpc->GetTaughtSkillList( skillList );

        CreateSkillList
            for( i = skillList.begin(); i != skillList.end(); ++i ){
	            AddTeachSkill( i->skillId, i->skillPnts, i->price )
            }
        SendTeachSkillList
    } break;
	case InsPrivateSystemMessage: {
		SETUP_COMMAND( 1 );

		PRIVATE_SYSTEM_MESSAGE( BoostFormula::TranslateStringFormula( val[0].c_str(), self, target, &varMap) );
		} break;
	case InsGlobalSystemMessage: {
		SETUP_COMMAND( 1 );

		GLOBAL_SYSTEM_MESSAGE( BoostFormula::TranslateStringFormula(val[0].c_str(), self, target, &varMap) );
		} break;
	case InsShoutMessage: {
		SETUP_COMMAND( 2 );

		NEW_CHATTER_SHOUT( val[0].c_str(), BoostFormula::TranslateStringFormula( val[1].c_str(), self, target, &varMap ) );
		} break;
	case InsSetGlobalFlag:{
        SETUP_COMMAND( 2 );
        INTERPRET_FORMULA( val[ 1 ], value );
        GiveGlobalFlag( atoi( val[ 0 ].c_str() ), value );
		} break;
	case InsGiveKarma:{
		SETUP_COMMAND( 1 );
		INTERPRET_FORMULA( val[ 0 ], karma );
        GiveKarma( karma );
		} break;
	case InsSetStats:
		{
			SETUP_COMMAND( 2 );
			INTERPRET_FORMULA( val[1], value );

			// Strength
			if( strcmp( val[0].c_str(), "strength" ) == 0 )			
			{
				SET_STR( value )				
			}
			// Endurance
			else if( strcmp( val[0].c_str(), "endurance" ) == 0 )
			{
				SET_END( value )				
			}
			// Agility
			else if( strcmp( val[0].c_str(), "agility" ) == 0 )
			{
				SET_AGI( value )				
			}
			// Wisdom
			else if( strcmp( val[0].c_str(), "wisdom" ) == 0 )
			{
				SET_WIS( value )				
			}
			// Intelligence
			else if( strcmp( val[0].c_str(), "intelligence" ) == 0 )
			{
				SET_INT( value )				
			}
			// Appearance
			else if( strcmp( val[0].c_str(), "appearance" ) == 0 )
			{
				SET_APPEARANCE( value )				
			}
			// Air Power
			else if( strcmp( val[0].c_str(), "air" ) == 0 )
			{
				SET_AIR_POWER( value )				
			}
			// Dark Power
			else if( strcmp( val[0].c_str(), "dark" ) == 0 )
			{
				SET_DARK_POWER( value )				
			}
			// Earth Power
			else if( strcmp( val[0].c_str(), "earth" ) == 0 )
			{
				SET_EARTH_POWER( value )				
			}
			// Fire Power
			else if( strcmp( val[0].c_str(), "fire" ) == 0 )
			{
				SET_FIRE_POWER( value )				
			}
			// Light Power
			else if( strcmp( val[0].c_str(), "light" ) == 0 )
			{
				SET_LIGHT_POWER( value )				
			}
			// Water Power
			else if( strcmp( val[0].c_str(), "water" ) == 0 )
			{
				SET_WATER_POWER( value )				
			}
			// Air Resist
			else if( strcmp( val[0].c_str(), "air resist" ) == 0 )
			{
				SET_AIR_RESIST( value )				
			}
			// Dark Resist
			else if( strcmp( val[0].c_str(), "dark resist" ) == 0 )
			{
				SET_DARK_RESIST( value )				
			}
			// Earth Resist
			else if( strcmp( val[0].c_str(), "earth resist" ) == 0 )
			{
				SET_EARTH_RESIST( value )				
			}
			// Fire Resist
			else if( strcmp( val[0].c_str(), "fire resist" ) == 0 )
			{
				SET_FIRE_RESIST( value )				
			}
			//Light Resist
			else if( strcmp( val[0].c_str(), "light resist" ) == 0 )
			{
				SET_LIGHT_RESIST( value )				
			}
			// Air Resist
			else if( strcmp( val[0].c_str(), "water resist" ) == 0 )
			{
				SET_WATER_RESIST( value )				
			}

			break;
		}
    };
}


//////////////////////////////////////////////////////////////////////////////////////////
void InterpretKeyword
//////////////////////////////////////////////////////////////////////////////////////////
// Interprets the given keyword.
// 
(
 SimpleNPC *npc,
 Unit *self,
 Unit *target,
 Keyword *kw,
 BoostFormula::VarMap &varMap
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CString output;

    // Interpret this keyword's contained items.
    InterpretContainer( npc, self, target, kw, output, varMap );

    // If text is to be sent to the player.
    if( !output.IsEmpty() ){
        if( self->IsPrivateTalk() ){
            target->SendPrivateMessage( output, self, npc->npc.dwTextColor );
        }else{
            self->Talk( (LPCTSTR)output, npc->npc.dwTextColor, target );
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
void SimpleNPC::OnTalk
//////////////////////////////////////////////////////////////////////////////////////////
// Talk to a simple NPC.
// 
(
 UNIT_FUNC_PROTOTYPE // The NPC prototype.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    InitTalk

    Keyword *defKw = NULL;

    BoostFormula::VarMap varMap;
 
    RootInstruction *root = theNpc->GetRootInstruction();
    InstructionList subIns;
    root->GetSubInstructions( subIns );

    InstructionList::iterator i;
    for( i = subIns.begin(); i != subIns.end(); i++ ){
        Instruction *ins = *i;

        // Non keywords on the 1st level are never interpreted in OnTalk.
        if( ins->GetId() != InsKeyword ){
            continue;
        }
        
        Keyword *kw = static_cast< Keyword * >( ins );		
        
        // If this is the intro statement and we're in the NPC opening statement
        if( kw->IsInitKw() && ( msg == "  " || boOpenStatement ) ){
            
            // Interpret this keyword
            InterpretKeyword( this, self, target, kw, varMap );

            return;
        }else 
        // If this is the default text, cache it.
        if( kw->IsDefaultKw() ){
            defKw = kw;
            continue;
        }

		//if this is an event that must not be considered as a keyword, then skip
		if( kw->IsTriggerKw() )
		{
			continue;
		}

        // If this item doesn't have any keyword.
        list< string > lkw;
        kw->GetKw( lkw );
        if( lkw.size() == 0 ){
            continue;
        }else 
        // If the item has a single keyword    
        if( lkw.size() == 1 && NPCKeyWord( msg, ( *lkw.begin() ).c_str() ) ){
            // Interpret this keyword.
            InterpretKeyword( this, self, target, kw, varMap );

            return;
        }

        list< string >::iterator z;

        switch( kw->GetKwRelation() ){
        /////////////////
        case Or:{
            // If any of the keywords is ok
            for( z = lkw.begin(); z != lkw.end(); z++ ){
                if( NPCKeyWord( msg, (*z).c_str() ) ){                    
                    // Interpret the keyword.
                    InterpretKeyword( this, self, target, kw, varMap );
                                        
                    return;
                }
            }
        } break;
        /////////////////
        case And:{
            bool ok = true;
            // If any of the keywords is wrong
            for( z = lkw.begin(); z != lkw.end(); z++ ){
                if( !NPCKeyWord( msg, (*z).c_str() ) ){
                    ok = false;
                    break;
                }
            }
            if( ok ){
                // Interpret the keyword.
                InterpretKeyword( this, self, target, kw, varMap );
                return;
            }
        } break;
        /////////////////
        case InOrder:{
            const char *param1 = NULL;
            const char *param2 = NULL;
            const char *param3 = NULL;
            const char *param4 = NULL;
            const char *param5 = NULL;
            
            // Fetch the keywords as individual parameters
            z = lkw.begin();
            if( z == lkw.end() ){ goto checkKw; }
            param1 = (*z).c_str();

            z++;
            if( z == lkw.end() ){ goto checkKw; }
            param2 = (*z).c_str();

            z++;
            if( z == lkw.end() ){ goto checkKw; }
            param3 = (*z).c_str();
            
            z++;
            if( z == lkw.end() ){ goto checkKw; }
            param4 = (*z).c_str();

            z++;
            if( z == lkw.end() ){ goto checkKw; }
            param5 = (*z).c_str();

checkKw:
            // If the keywords are arranged in order.
            if( _ORDER( msg, param1, param2, param3, param4, param5 ) ){
                // Interpret keyword.
                InterpretKeyword( this, self, target, kw, varMap );


                return;
            }
        } break;
        } // switch( kw->GetRelation() )
    } // for( i = script.begin(); i != script.end(); i++ )

    // If the default keyword was not found and cached.
    if( defKw == NULL ){
        return;
    }

    // Interpret the default keyword.
    InterpretKeyword( this, self, target, defKw, varMap );
}

//////////////////////////////////////////////////////////////////////////////////////////
void SimpleNPC::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // The ugly backgrounds show up in the simple NPC ;-)
    LPNPC_DATA dataIN  = (LPNPC_DATA)valueIN;
    LPNPC_DATA dataOUT = (LPNPC_DATA)valueOUT;
    bool xSendBackpackUpdate = false;    
    
    std::list< NPC_Editor::NPC::SoldItem > soldItems;    
    theNpc->GetSoldItemList( soldItems );

    std::list< NPC_Editor::NPC::BoughtItem > boughtItems;    
    theNpc->GetBoughtItemList( boughtItems );

    std::list< NPC_Editor::NPC::TrainedSkill > trainedSkills;
    theNpc->GetTrainedSkillList( trainedSkills );

    std::list< NPC_Editor::NPC::TaughtSkill > taughtSkills;    
    theNpc->GetTaughtSkillList( taughtSkills );
   
    // If this is a merchant query.
    if( dataIN->DataID == __SHOP_DATA  ){
		// Initialize shop data.
		LPSHOP_DATA shop = (LPSHOP_DATA)dataIN->Data;
        
        if( shop->Action == __BUY ){
            std::list< NPC_Editor::NPC::SoldItem >::iterator i;
            for( i = soldItems.begin(); i != soldItems.end(); i++ ){
                WORD itemId = Unit::GetIDFromName( (*i).itemId.c_str(), U_OBJECT, TRUE );
                // If the item to buy was found.
                if( shop->Item == itemId ){
					// Try to buy as much items as specified.
                    int qty = 0;
					while( qty < shop->wQuantity ){
						if(Gold >= (*i).price){
                            if( GiveItemNoUpdateNotAbsolute( itemId ) ){
                                TakeGoldNoEcho( (*i).price )
                            }else{
                                break;
                            }
						}
                        qty++;
					};
                    
                    return;
                }
            }            
        }else 
        if( shop->Action == __SELL ){
            std::list< NPC_Editor::NPC::BoughtItem >::iterator j;
            for( j = boughtItems.begin(); j != boughtItems.end(); j++ ){
                int fooMoneyData = 0;
                NPC_BUYFunc( 
                    self, 
                    target, 
                    (*j).sellType, 
                    (*j).minPrice, 
                    (*j).maxPrice, 
                    fooMoneyData, 
                    shop 
                );
            }
        }
        // Do not process trainers.
        return;
    }else if( dataIN->DataID == __TEACH_DATA ){
        LPTEACH_DATA TeachData = (LPTEACH_DATA)dataIN->Data;        
        
        // Find the skill that is to be taught.
        std::list< NPC_Editor::NPC::TaughtSkill >::iterator l;
        for( l = taughtSkills.begin(); l != taughtSkills.end(); l++ ){
            if( (*l).skillId == TeachData->wSkillID ){
                DWORD skillId = TeachData->wSkillID;
	            
	            if( skillId < SPELL_ID_OFFSET ){
		            // If the skill does not exist or cannot be learned.
                    SKILL *lpSkill = Skills::GetSkill( skillId );
		            if( lpSkill == NULL ){
                        return;
                    }
                    CString foo;
			        if( !Skills::IsSkillLearnable( skillId, target, foo ) ){
                        return;
			        }
	            }else{ 
                    // If its a spell and it does not exist or cannot be learned.
		            LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpell( skillId );
		            if( lpSpell == NULL ){
                        return;
                    }
                    CString foo;
			        if( !SpellMessageHandler::IsSpellLearnable( skillId, target, foo ) ) {
                        return;
                    }
	            }
				__TeachSkill( 
                    target, 
                    skillId, 
                    (*l).skillPnts, 
                    (*l).price 
                );

                return;
            }
        }
    }else if( dataIN->DataID == __TRAIN_DATA ){
        LPTRAIN_DATA TrainData = (LPTRAIN_DATA)dataIN->Data;

        std::list< NPC_Editor::NPC::TrainedSkill >::iterator k;
        for( k = trainedSkills.begin(); k != trainedSkills.end(); k++ ){

            if( (*k).skillId ==	TrainData->wSkillID ){
                __TrainSkill(
                    target, 
                    TrainData->wSkillID, 
                    TrainData->wSkillPnts, 
                    (*k).price, 
                    (*k).maxSkillPnts 
                );
            }
        }
    }
}

//////////////////////////////////////
// Called when the NPC dies
void SimpleNPC::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		Keyword *deathKw = NULL;

		BoostFormula::VarMap varMap;
 
		RootInstruction *root = theNpc->GetRootInstruction();
		InstructionList subIns;
		root->GetSubInstructions( subIns );

		InstructionList::iterator i;
		for( i = subIns.begin(); i != subIns.end(); i++ )
		{
			Instruction *ins = *i;

			// Non keywords on the 1st level are never interpreted in OnTalk.
			if( ins->GetId() != InsKeyword ){
				continue;
			}
        
			Keyword *kw = static_cast< Keyword * >( ins );
        
			// If this is the death statement, get it		
			if( kw->IsDeathKw() )
			{            
				deathKw = kw;

				break;
			}
		}
		
		// Interpret the death keyword only if it exists
		if( deathKw != NULL )
		{
			InterpretKeyword( this, self, target, deathKw, varMap );
		}
	}
	
	NPCstructure::OnDeath( UNIT_FUNC_PARAM );

	return;
}

//////////////////////////////////////
// Called when NPC gets attacked
void SimpleNPC::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	Keyword *attackedKw = NULL;

    BoostFormula::VarMap varMap;
 
    RootInstruction *root = theNpc->GetRootInstruction();
    InstructionList subIns;
    root->GetSubInstructions( subIns );

    InstructionList::iterator i;
    for( i = subIns.begin(); i != subIns.end(); i++ )
	{
        Instruction *ins = *i;

        // Non keywords on the 1st level are never interpreted in OnTalk.
        if( ins->GetId() != InsKeyword ){
            continue;
        }
        
        Keyword *kw = static_cast< Keyword * >( ins );
        
        // If this is the OnAttacked statement, get it		
        if( kw->IsAttackedKw() )
		{            
            attackedKw = kw;

            break;
        }
	}
	
    // Interpret the OnAttacked keyword only if it exists
	if( attackedKw != NULL )
	{
		InterpretKeyword( this, self, target, attackedKw, varMap );
	}
	
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );

	return;
}

//////////////////////////////////////
// Called when NPC attacks an unit
void SimpleNPC::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	Keyword *attackKw = NULL;

    BoostFormula::VarMap varMap;
 
    RootInstruction *root = theNpc->GetRootInstruction();
    InstructionList subIns;
    root->GetSubInstructions( subIns );

    InstructionList::iterator i;
    for( i = subIns.begin(); i != subIns.end(); i++ )
	{
        Instruction *ins = *i;

        // Non keywords on the 1st level are never interpreted in OnTalk.
        if( ins->GetId() != InsKeyword ){
            continue;
        }
        
        Keyword *kw = static_cast< Keyword * >( ins );
        
        // If this is the OnAttack statement, get it		
        if( kw->IsAttackKw() )
		{            
            attackKw = kw;

            break;
        }
	}
	
    // Interpret the death keyword only if it exists
	if( attackKw != NULL )
	{
		InterpretKeyword( this, self, target, attackKw, varMap );
	}
	
	NPCstructure::OnAttack( UNIT_FUNC_PARAM );

	return;
}

//////////////////////////////////////
// Called when NPC is created
void SimpleNPC::OnInitialise( UNIT_FUNC_PROTOTYPE )
{
	self->SetCanMove( theNpc->GetCanMove() );
	self->SetPrivateTalk( theNpc->GetPrivateTalk() );

	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	return;
}
#include "stdafx.h"
#include "InstructionFactory.h"

#include "IfFlow.h"
#include "ElseIfFlow.h"
#include "ElseFlow.h"
#include "ForFlow.h"
#include "WhileFlow.h"
#include "Command.h"
#include "Keyword.h"
#include "Assign.h"

using namespace std;
using namespace NPC_Editor;

namespace{
    typedef list< Instruction * > InstructionList;
    InstructionList instructionList;

};

namespace NPC_Editor
{

#define ADD_FLOW( theType ){\
    theType *ins = new theType;\
    instructionList.push_back( ins );\
}

#define ADD_COMMAND( theName, theHelp, theId ){\
    newCmd = new Command( GetAppString( theName ), GetAppString( theHelp ), theId );\
    instructionList.push_back( newCmd );}

#define ADD_MISC( theName, theHelp, theId, theType ){\
    theType *ins = new theType( GetAppString( theName ), GetAppString( theHelp ), theId );\
    instructionList.push_back( ins );}


#define ADD_COMMAND_PARAM( theType, theName ){\
    Command::Attribute attrib;\
    attrib.type = theType;\
    attrib.paramName = GetAppString( theName );\
    newCmd->AddAttribute( attrib );\
}

InstructionFactory::InstructionFactory()
{
    // Build the instruction list.
    Command *newCmd;

    // Control flows.
    ADD_FLOW( IfFlow );
    ADD_FLOW( ElseIfFlow );
    ADD_FLOW( ElseFlow );
    ADD_FLOW( ForFlow );
    ADD_FLOW( WhileFlow );
    ADD_MISC( 
        IDS_INST_ASSIGN,        IDS_INST_ASSIGN_HELP,   InsAssign, Assign );

    ADD_COMMAND(    
        IDS_INST_GIVEITEM,      IDS_INST_GIVEITEM_HELP, InsGiveItem );
    ADD_COMMAND_PARAM( Item, IDS_PARAM_GIVEITEM );

    ADD_COMMAND(    
        IDS_INST_GIVEXP,        IDS_INST_GIVEXP_HELP,   InsGiveXP );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_GIVEXP );

    ADD_COMMAND(    
        IDS_INST_SETFLAG,       IDS_INST_SETFLAG_HELP,  InsSetFlag );
    ADD_COMMAND_PARAM( Flag, IDS_PARAM_SETFLAG_FLAG );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_SETFLAG_VALUE );

    ADD_COMMAND(    
        IDS_INST_HEALPLAYER,    IDS_INST_HEALPLAYER_HELP, InsHealPlayer );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_HEALPLAYER );

    ADD_COMMAND(    
        IDS_INST_SAYTEXT,       IDS_INST_SAYTEXT_HELP, InsSayText );    
    ADD_COMMAND_PARAM( Text, 0 );

    ADD_COMMAND(    
        IDS_INST_BREAKCONVERSATION, IDS_INST_BREAKCONVERSATION_HELP, InsBreakConversation );

    ADD_COMMAND(    
        IDS_INST_FIGHTPLAYER,   IDS_INST_FIGHTPLAYER_HELP, InsFightPlayer );
    
    ADD_COMMAND(    
        IDS_INST_TAKEITEM,      IDS_INST_TAKEITEM_HELP, InsTakeItem );
    ADD_COMMAND_PARAM( Item, IDS_PARAM_TAKEITEM );

    ADD_COMMAND(    
        IDS_INST_TELEPORT,      IDS_INST_TELEPORT_HELP, InsTeleport );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_TELEPORT_X );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_TELEPORT_Y );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_TELEPORT_WORLD );

    ADD_COMMAND(    
        IDS_INST_CASTSPELL,     IDS_INST_CASTSPELL_HELP, InsCastSpell );
    ADD_COMMAND_PARAM( Spell, IDS_PARAM_CASTSPELL );

    ADD_COMMAND(    
        IDS_INST_CASTSPELLSELF, IDS_INST_CASTSPELLSELF_HELP, InsCastSpellSelf );
    ADD_COMMAND_PARAM( Spell, IDS_PARAM_CASTSPELL );

    ADD_COMMAND(    
        IDS_INST_GIVEGOLD,      IDS_INST_GIVEGOLD_HELP, InsGiveGold );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_GIVEGOLD );

    ADD_COMMAND(    
        IDS_INST_TAKEGOLD,      IDS_INST_TAKEGOLD_HELP, InsTakeGold );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_TAKEGOLD );

    ADD_COMMAND(
        IDS_INST_SENDSOLDITEMLIST, IDS_INST_SENDSOLDITEMLIST_HELP, InsSendSoldItemList );

    ADD_COMMAND(
        IDS_INST_SENDBOUGHTITEMLIST, IDS_INST_SENDBOUGHTITEMLIST_HELP, InsSendBoughtItemList );

    ADD_COMMAND(
        IDS_INST_SENDTRAINSKILLLIST, IDS_INST_SENDTRAINSKILLLIST_HELP, InsSendTrainSkillList );

    ADD_COMMAND(
        IDS_INST_SENDTEACHSKILLLIST, IDS_INST_SENDTEACHSKILLLIST_HELP, InsSendTeachSkillList );

	ADD_COMMAND(    
        IDS_INST_PRIVATESYSTEMMESSAGE,   IDS_INST_PRIVATESYSTEMMESSAGE_HELP, InsPrivateSystemMessage );
	ADD_COMMAND_PARAM( Text, 0 );

	ADD_COMMAND( 
        IDS_INST_GLOBALSYSTEMMESSAGE,   IDS_INST_GLOBALSYSTEMMESSAGE_HELP, InsGlobalSystemMessage );
	ADD_COMMAND_PARAM( Text, 0 );

	ADD_COMMAND(    
        IDS_INST_SHOUTMESSAGE,   IDS_INST_SHOUTMESSAGE_HELP, InsShoutMessage );
	ADD_COMMAND_PARAM( Text, IDS_PARAM_SHOUTMESSAGE_CHAN );
	ADD_COMMAND_PARAM( Text, IDS_PARAM_SHOUTMESSAGE_TXT );

	ADD_COMMAND(    
        IDS_INST_SETGLOBALFLAG,       IDS_INST_SETGLOBALFLAG_HELP,  InsSetGlobalFlag );
    ADD_COMMAND_PARAM( Flag, IDS_PARAM_SETGLOBALFLAG_FLAG );
    ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_SETGLOBALFLAG_VALUE );

	ADD_COMMAND(    
        IDS_INST_GIVEKARMA,       IDS_INST_GIVEKARMA_HELP,  InsGiveKarma );
	ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_GIVEKARMA );	

	ADD_COMMAND(
		IDS_INST_SETSTATS,	IDS_INST_SETSTATS_HELP, InsSetStats );
	ADD_COMMAND_PARAM( Stats, IDS_PARAM_SETSTATS_STAT );
	ADD_COMMAND_PARAM( BoostFormula, IDS_PARAM_SETSTATS_VALUE );
}

InstructionFactory::~InstructionFactory()
{
    // Destroy all instructions.
    InstructionList::iterator i;
    for( i = instructionList.begin(); i != instructionList.end(); i++ ){
        delete *i;
    }
}
/////////////////////////////////////////////////////////////////////////////
Instruction *InstructionFactory::CreateInstruction
/////////////////////////////////////////////////////////////////////////////
// 
//
(
InstructionIds id
)
// Return: Instruction *, an instruction corresponding to the given Id.
//         NULL if the instruction doesn't exist.
/////////////////////////////////////////////////////////////////////////////
{
    // Keywords aren't added in the normal instruction list.
    if( id == InsKeyword ){
        return new Keyword;
    }

    // Find the correct instance.
    InstructionList::iterator i;
    for( i = instructionList.begin(); i != instructionList.end(); i++ ){
        if( id == (*i)->GetId() ){
            return (*i)->Clone();
        }
    }
    
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
InstructionFactory *InstructionFactory::GetInstance( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
    static InstructionFactory instance;
    return &instance;
}

//////////////////////////////////////////////////////////////////////////////////////////
void InstructionFactory::GetInstructionList
//////////////////////////////////////////////////////////////////////////////////////////
// Fills-in the supplied list with all instructions supported by the factory.
// 
(
 std::list< Instruction * > &iList // The list of instructions.
) const
//////////////////////////////////////////////////////////////////////////////////////////
{
    InstructionList::iterator i;
    for( i = instructionList.begin(); i != instructionList.end(); i++ ){
        iList.push_back( *i );
    }

}

} // NPC_Editor


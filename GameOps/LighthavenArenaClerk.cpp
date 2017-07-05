#pragma hdrstop
#include "LighthavenArenaClerk.h"

LighthavenArenaClerk::LighthavenArenaClerk()
{}

LighthavenArenaClerk::~LighthavenArenaClerk()
{}

extern NPCstructure::NPC ArenaClerkNPC;

void LighthavenArenaClerk::Create( ){
	npc = ArenaClerkNPC;
	SET_NPC_NAME( "[7399]A busy clerk" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
//	npc.InitialPos.X = 2859;
//	npc.InitialPos.Y = 1129;
	npc.InitialPos.world = 0;
}
void LighthavenArenaClerk::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}

void LighthavenArenaClerk::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void LighthavenArenaClerk::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin						   
""
IF(USER_NAME == INTL( 7381, "Drake"))
	Conversation
	INTL( 4015, "Yes? What do you want?")
ELSE
	Conversation
	INTL( 7382, "Can't you see I'm very busy? Go on, get out of here!")
	BREAK
ENDIF
;YesNo = 0;

Command(INTL( 7383, "ARENA"))
INTL( 7384, "Ahhh, so you wish to try your skills in the arena eh? There are currently 3 arenas "
"available for duels. You can fight in the \"church\", the \"basement\" or the \"island\". Well, "
"which shall it be?")
;YesNo = 1;




/*
// ParamCmd
;} else if(( SysopCmd::GetParameters( __cmd, parammsg, lpcsParams ) ) && YesNo == 1){

// Command
;} else if( msg.Find( cmd ) != -1 && !YesNo) { output += 
*/

;} else if( ( msg.Find( INTL( 2379, "CHURCH") ) != -1 ) && YesNo == 1) { ;YesNo = 0;
Conversation
INTL( 7385, "The church eh? Very well then. Just tell me when you are \"ready\" and you will be transported there to await "
"your opponent.")

;} else if( ( msg.Find( INTL( 7386, "BASEMENT") ) != -1 ) && YesNo == 1) {;
Conversation
INTL( 7387, "I'm terribly sorry, but it seems the basement has not yet been completed. I'm afraid you'll have to choose "
"another arena for your battle. In which arena will you fight?")

;} else if( ( msg.Find( INTL( 755, "ISLAND") ) != -1 ) && YesNo == 1) { ;YesNo = 0;
Conversation
INTL( 7388, "It seems that the island you wish to use as your private battleground no longer exists. I'll be sure to tell "
"the technician about it. In the mean time, you'll have to fight somewhere else. Where will you fight your battle?")
;YesNo = 1;

;} else if(( SysopCmd::GetParametersForNPC( INTL( 6211, "RIGHT $"), parammsg, lpcsParams ) ) && YesNo == 1){
	IF(NUM_PARAM(0) == 69)
		Conversation
		INTL( 10083, "Splendid! You've just said the magic word! You are now out of the loop!")
		;YesNo = 0;
	ELSE
		Conversation
		INTL( 10084, "Right what? What are you saying? Anyway, just pick a location will you? I'm a very busy man. Which will "
		"it be?")
	ENDIF

;} else if(YesNo == 1) { ;YesNo = 0;
Conversation
INTL( 7389, "As you can see, I have little time to waste, so please choose a location for your battle amongst the valid choices. "
"I'll ask you again, where will you fight?")
;YesNo = 1;

Command(INTL( 7390, "READY"))
INTL( 7391, "Very well, good luck then.")
//GiveFlag(__FLAG_DEATH_LOCATION_BEFORE_ARENA, target->ViewFlag(__FLAG_DEATH_LOCATION))
SetDeathLocation( 1600, 800, 0 )
//GiveFlag(__FLAG_USER_XP_BEFORE_ARENA, target->GetXP())
//GiveFlag(__FLAG_USER_HP_BEFORE_ARENA, USER_HP)
HealPlayer(USER_MAXHP)
CHATTER_SHOUT(INTL( 7392, "Drake has just entered the church arena and is waiting for a challenger!"))
PRIVATE_SYSTEM_MESSAGE(INTL( 7393, "Your wounds have been temporarily healed for the fight."))
TELEPORT(1600, 800, 0)
BREAK

Command5(INTL( 518, "BYE"), INTL( 7346, "STOP"), INTL( 521, "EXIT"), INTL( 519, "LEAVE"), INTL( 520, "QUIT"))
INTL( 973, "Goodbye.")
BREAK

Default
INTL( 7394, "Unless you have something specific to ask me, then I suggest you leave.")

EndTalk

}
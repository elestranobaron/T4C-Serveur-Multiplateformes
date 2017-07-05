#pragma hdrstop
#include "SanctuaryGuardian.h"

SanctuaryGuardian::SanctuaryGuardian()
{}

SanctuaryGuardian::~SanctuaryGuardian()
{}

extern NPCstructure::NPC OlinHaad1NPC;

void SanctuaryGuardian::Create(){
  npc = OlinHaad1NPC;
  SET_NPC_NAME( "[12771]A gate keeper");
  npc.InitialPos.X = 695;
  npc.InitialPos.Y = 1323;
	npc.InitialPos.world = 0;
}

void SanctuaryGuardian::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void SanctuaryGuardian::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void SanctuaryGuardian::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT LetMePass = 1; 

InitTalk

Begin
INTL( 12545, "The mausoleum beyond leads to the sanctuary of the ancient God of Corruption, Gluriurl. "
"I guard its entrance and only those who speak the \"word\" \"of\" \"power\" are "
"allowed to pass.") 

CmdAND(INTL( 12546, "WORD"),INTL( 10379, "POWER"))
INTL( 12547, "Speak the word of power now and I shall grant you passage to the mausoleum.") 

Command(INTL( 12548, "ETHEREAL")) 
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 33)
	Conversation
	INTL( 12549, "You spoke the word of power and I am therefore instructed to let you pass. "
	"However, I must first warn you of the dangers you will face. Even though the "
	"God of Corruption is no more, its dreadful influence can still be felt throughout "
	"the endless corridors of the tainted sanctuary. You will encounter Gluriurl's "
	"followers who were once entombed alive and who are still devoted to him, even in "
	"their unlife. Thus, I must ask you if you still desire access to this foul place?") 
	SetYesNo(LetMePass) 	
ELSE
	Conversation
	INTL( 12550, "Although you indeed spoke the word of power, I do not feel you capable "
	"of handling what lies beneath in the sanctuary just yet.")  
ENDIF

YES(LetMePass) 
	Conversation
	INTL( 12551, "Very well then, you may pass.") 
	TELEPORT(691,1319,0) 
	BREAK 

NO(LetMePass)
	Conversation
	INTL( 12552, "A wise decision.")
	
YesNoELSE(LetMePass) 
	Conversation
	INTL( 12553, "Do you want to be granted access to the mausoleum or not?") 
	SetYesNo(LetMePass) 
	
Command(INTL( 489, "WORK"))
INTL( 12554, "I have been given the task of guarding the mausoleum's entrance.")

Command(INTL( 483, "NAME")) 
INTL( 12555, "I see not why this would concern you.") 

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12556, "Until we meet again...")
BREAK

Command(INTL( 3771, "?"))
INTL( 12557, "I am here to guard the gate, not to provide answers.") 

Default
"" 
IF(rnd.roll(dice(1,2))) 
	Conversation
	INTL( 12558, "Perhaps...")
ELSE
	Conversation
	INTL( 1623, "I cannot help you with this.")
ENDIF 

EndTalk
}
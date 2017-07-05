#pragma hdrstop
#include "Tristan.h"

Tristan::Tristan()
{}

Tristan::~Tristan()
{}

extern NPCstructure::NPC WandererNPC;

void Tristan::Create( ){
	npc = WandererNPC;
	SET_NPC_NAME( "[12777]Tristan");
	npc.InitialPos.X = 295; 
	npc.InitialPos.Y = 738;
	npc.InitialPos.world = 0;
}

void Tristan::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT FirstQuestion = 1; 
CONSTANT SecondQuestion = 2;
CONSTANT ThirdQuestion = 3;  
;static CString csLastUserID;  

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_SERAPH_ARMOR_QUEST) == 1) 
	Conversation
	INTL( 12627, "You again? I really think you should investigate the caravan. As I've said, they took off with "
	"the remains taken from a corpse that bore wings just like yours. They went further East of "
	"Stonecrest, toward the edge of the creeping forest.") 	
ELSEIF((CheckFlag(__FLAG_NUMBER_OF_REMORTS)>= 1)&&(CheckFlag(__FLAG_ADDON_SERAPH_ARMOR_QUEST)==0))
	Conversation
	INTL( 12628, "Wow! It's the first time I see someone with wings. They're truly beautiful! Are you some kind of an angel?") 
	SetYesNo(FirstQuestion) 
ELSE 
	IF ((USER_NAME == csLastUserID)||(csLastUserID == ""))
		Conversation
		INTL( 12629, "Hello there.")
	ELSE
		Conversation
		FORMAT(INTL( 12630, "Hiya, I met %s recently. A nice person, really. I was wondering if you'd know that person...?"), csLastUserID)
		;csLastUserID = USER_NAME;
		SetYesNo(ThirdQuestion)
	ENDIF 
ENDIF 

YES(FirstQuestion)
Conversation
INTL( 12631, "Ohhhh! I'm talking to an angel! That's sooo exiciting! Can I touch your wings?")
SetYesNo(SecondQuestion) 

NO(FirstQuestion)
Conversation
INTL( 12632, "Ah. Can I touch your wings anyways?")
SetYesNo(SecondQuestion) 

YesNoELSE(FirstQuestion)
Conversation
INTL( 12633, "Well are you an angel or not?")
SetYesNo(FirstQuestion) 

YES(SecondQuestion)
Conversation
INTL( 12634, "Impressive... They're made of real feathers! Thinking about it, they remind me of something " 
"I saw \"recently\"...") 

NO(SecondQuestion)
Conversation
INTL( 12635, "You're quite a rude being. You remind me of some people I saw in the forest \"recently\"...") 

YesNoELSE(SecondQuestion) 
Conversation
INTL( 12636, "So can I touch them?")
SetYesNo(SecondQuestion) 

YES(ThirdQuestion)
Conversation
INTL( 12637, "Ah, that's good to hear. I hope you're good friends.") 

NO(ThirdQuestion)
Conversation
INTL( 12638, "Ah, too bad. You might be missing on a good ally.") 

YesNoELSE(ThirdQuestion) 
Conversation
INTL( 12639, "So, do you know that person?") 
SetYesNo(ThirdQuestion) 

Command(INTL( 12640, "RECENTLY"))
""
IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS)>= 1) 
	Conversation
	INTL( 12641, "As I was saying, I was walking down a path on a wilderness trek when I spotted a band of "
	"rude men clad in obsidian robes \"digging\" up some remains.") 
ELSE
	IF (rnd.roll( dice(1,2) ) == 1)
		Conversation
		INTL( 10453, "I'm afraid I cannot help you with this.")
	ELSE
		Conversation
		INTL( 11825, "I don't understand what you mean.")
	ENDIF
ENDIF 

Command(INTL( 12642, "DIGGING")) 
""
IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS)>= 1) 
	Conversation
	INTL( 12643, "Yes, two of them dug the ground using shovels. After awhile they finally uncovered a "
	"corpse... and it bore wings on its back just like yours! Then they loaded their caravan with "
	"the remains and went further east along with a band of heavily mercenaries and spellslingers. "
	"Do you think the corpse could possibly be one of your kin? Anyway, as much as I enjoy your "
	"company, I must now return to my chores.")
	IF(CheckFlag(__FLAG_ADDON_SERAPH_ARMOR_QUEST) == 0) 
		GiveFlag(__FLAG_ADDON_SERAPH_ARMOR_QUEST, 1) 
	ENDIF 
ELSE 
	IF (rnd.roll( dice(1,2) ) == 1)
		Conversation
		INTL( 10453, "I'm afraid I cannot help you with this.")
	ELSE
		Conversation
		INTL( 11825, "I don't understand what you mean.")
	ENDIF
ENDIF 

Command(INTL( 12644, "MORDRED")) 
""
IF(CheckFlag(__FLAG_ADDON_SERAPH_ARMOR_QUEST) == 1) 
	Conversation
	INTL( 12645, "So, the leader of the band was a man named Mordred? It's nice to hear again from you and "
	"your adventures but I'm not really interested quite frankly.")  
ELSE
	IF (rnd.roll( dice(1,2) ) == 1)
		Conversation
		INTL( 10453, "I'm afraid I cannot help you with this.")
	ELSE
		Conversation
		INTL( 11825, "I don't understand what you mean.")
	ENDIF
ENDIF


Command(INTL( 483, "NAME"))
INTL( 12646, "My name is Tristan.")

Command(INTL( 12647, "TRISTAN")) 
INTL( 12648, "That's my name alright.") 

Command2(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"))
INTL( 12649, "These days, I enjoy walking in the forest even though they are many dangerous creatures out there.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
""
IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS)>= 1) 
	Conversation
	INTL( 12650, "Farewell, celestial one.")
ELSE
	Conversation
	INTL( 1075, "Farewell.")
	;csLastUserID = USER_NAME;
ENDIF 
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 10453, "I'm afraid I cannot help you with this.")
ELSE
	Conversation
	INTL( 11825, "I don't understand what you mean.")
ENDIF

EndTalk
}


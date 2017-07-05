//////////////////////////////////////////////////////////////////////
// BastienMilandra.cpp: 
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "BastienMilandra.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BastienMilandra::BastienMilandra()
{}

BastienMilandra::~BastienMilandra()
{} 

extern NPCstructure::NPC BastienMilandraNPC;

void BastienMilandra::Create( ){
	npc = BastienMilandraNPC;
	SET_NPC_NAME(   "[10826]Bastien Milandra" );
	npc.InitialPos.X = 420;
	npc.InitialPos.Y = 1255; 
	npc.InitialPos.world = 0;
}

void BastienMilandra::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Believe = 1;
CONSTANT Believe2 = 2;
CONSTANT Believe3 = 3;
CONSTANT FixIt = 4;
CONSTANT Seraph = 5; 

InitTalk

Begin
INTL( 9259, "Hiya!!! Guess what my \"name\" is! *grin*")
GiveNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE, 0)

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9260, "My name's Bastien Milandra. I \"work\" here. I know I look big, but would you "
"believe I'm only twelve?")
SetYesNo(Believe)

YES(Believe)
	Conversation
	INTL( 9261, "Hey, thanks! Most people don't believe me!")	
	GiveNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE, CheckNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE)+1) 

NO(Believe)
	Conversation
	INTL( 9262, "Yah, most people don't either.")
	GiveNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE, 0)	
	
YesNoELSE(Believe)
	Conversation
	INTL( 9263, "Uh... What?")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 9264, "Um... Well, I don't do much, I just \"help\" folks around this town. Y'know, I have "
"great magical powers. D'you believe me?")
SetYesNo(Believe2)

YES(Believe2)
	Conversation
	INTL( 9261, "Hey, thanks! Most people don't believe me!")
	GiveNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE, CheckNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE)+1) 

NO(Believe2)
	Conversation
	INTL( 9262, "Yah, most people don't either.")
	GiveNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE, 0)	

YesNoELSE(Believe2)
	Conversation
	INTL( 9263, "Uh... What?")

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 9265, "Oh, sure, I could help you! Did I ever tell you my mother was a \"Seraph\" and she taught "
"me all sorts of neat things. You believe me, right?")
SetYesNo(Believe3) 

YES(Believe3)
	Conversation
	INTL( 9261, "Hey, thanks! Most people don't believe me!")
	GiveNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE, CheckNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE)+1) 

NO(Believe3)
	Conversation
	INTL( 9262, "Yah, most people don't either.")
	GiveNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE, 0)	

YesNoELSE(Believe3)
	Conversation
	INTL( 9263, "Uh... What?")

Command(INTL( 1898, "SERAPH")) 
INTL( 10481, "Yes, my mom's a Seraph. She has nice wings now. Have you seen her?") 
SetYesNo(Seraph) 

YES(Seraph)
	Conversation
	INTL( 10482, "Someday, I'll see her too, y'know.") 

NO(Seraph)
	Conversation
	INTL( 10483, "Oh, I see.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 10484, "Bastien sighs.")) 

YesNoELSE(Seraph)
	Conversation
	INTL( 10485, "So... did you see her?")
	SetYesNo(Seraph) 

CmdAND(INTL( 5010, "ETHER"),INTL( 8191, "KEY"))
""
IF(CheckItem(__OBJ_BROKEN_ETHEREAL_KEY) > 0)
	Conversation
	INTL( 9266, "Hey, you got one of my mom's keys! But awww, it's broken. Want me to fix it?")
	SetYesNo(FixIt)
ELSE
	Conversation
	INTL( 9267, "Yup, those are neat keys that take you to mom's house. Sometimes, people bring me "
	"broken keys they got from Daran and I fix them, but only if they're nice to me.")
ENDIF

YES(FixIt) 
	IF((CheckNPCFlag(__NPC_FLAG_DO_YOU_BELIEVE) >= 3) AND (CheckItem(__OBJ_BROKEN_ETHEREAL_KEY) > 0))
		Conversation
		INTL( 9268, "Okay!")
		TakeItem(__OBJ_BROKEN_ETHEREAL_KEY) 
		GiveItem(__OBJ_FIXED_ETHEREAL_KEY)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9269, "Bastien gives you a shiny Ethereal Key."))
	ELSEIF (CheckItem(__OBJ_BROKEN_ETHEREAL_KEY) == 0) 
		Conversation
		INTL( 10486, "Hey, your broken key is gone! How can that be?") 
	ELSE
		Conversation
		INTL( 9270, "Um... On second thought, you haven't been \"nice\" to me, so f'get it.")
	ENDIF

NO(FixIt)
	Conversation
	INTL( 9271, "'Kay... It's like you want...")

YesNoELSE(FixIt)
	Conversation
	INTL( 9272, "Um... Izzat a \"yes\" or a \"no\"?")
	SetYesNo(FixIt)

Command(INTL( 9273, "NICE"))
INTL( 9274, "I like nice people. I like it when people believe me. I don't lie, y'know?")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 9275, "AAAAH! You said a bad word!")
BREAK

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
INTL( 9276, "B'bye, now!")
PRIVATE_SYSTEM_MESSAGE(INTL( 9277, "Bastien makes a friendly farewell gesture."))
BREAK

Default
INTL( 3771, "?")

EndTalk
}

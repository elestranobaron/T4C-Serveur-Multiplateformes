#pragma hdrstop
#include "Evelyn.H"


Evelyn::Evelyn()
{}

Evelyn::~Evelyn()
{}
 
extern NPCstructure::NPC EvelynNPC; 

void Evelyn::Create( void )
{
	npc = ( EvelynNPC );
	SET_NPC_NAME( "[11716]Evelyn" );
  npc.InitialPos.X = 830; 
  npc.InitialPos.Y = 1825;
	npc.InitialPos.world = 0;
}

void Evelyn::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	CastSpellSelf(__SPELL_MOB_RADIANCE_SPELL);
}

void Evelyn::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT WILLOWISP = 1; 

InitTalk

Begin
""
IF (TFCTime::IsNight())
	Conversation
	INTL( 11682, "It's getting pretty dark, eh? Luckily for me, I have my \"willowisp\" "
	"\"ring\" that I use as a light source to guide my way.") 
ELSE
	Conversation
	INTL( 11683, "Hiya!")
ENDIF 

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
FORMAT(INTL( 11684, "I'm Evelyn. And you are...%s? It's really nice to meet you."), USER_NAME) 

Command(INTL( 11685, "EVELYN"))
INTL( 11686, "Yup, that's me alright.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 11687, "My, my, aren't we curious today? I simply like to walk in the forest even " 
"though there are some vile \"creatures\" around here.") 
PRIVATE_SYSTEM_MESSAGE(INTL( 11688, "Evelyn giggles.")) 

Command(INTL( 2038, "CREATURE")) 
INTL( 11689, "Oh, don't worry! It's nothing I can't handle. Appearances can be truly "
"deceiving you know. I have a trick or two up my sleeve if needed be.") 

CmdAND(INTL( 8053, "WILL"),INTL( 8039, "RING")) 
INTL( 11690, "I made it from a \"willowisp\" that I caught myself. If you need a ring, " 
"perhaps I could sell you one. Alas, I'd have to put a hefty price tag on it "
"for all the troubles I have to go through to catch a willowisp. Ah, I "
"know, I'll make a ring if you can bring me back a \"pouch\" \"of\" \"willow\" "
"\"bark\". I'll also need that you bring back a plain iron ring.") 
	IF ((CheckItem(__OBJ_IRON_RING) >= 1) && (CheckItem(__OBJ_POUCH_OF_WILLOW_BARK) >= 1)) 
		Conversation
		INTL( 11691, " Ah, I see that you have already everything that I need. So, do you "
		"want me to make a willowisp ring for you?")
		SetYesNo(WILLOWISP) 
	ENDIF 

Command2(INTL( 11692, "WILLOWISP"),INTL( 11693, "WILL-O-WISP")) 
INTL( 11694, "They're pretty hard to find. They try to lure you into the depth of the "
"woods but when you get to the point where they were standing, they are "
"no where to be seen. Hrm, I don't want to sound mean but I doubt you'll "
"ever find one on your own. You'd best leave this to me.") 

YES(WILLOWISP) 
	IF(CheckItem(__OBJ_IRON_RING) == 0) 
		Conversation
		INTL( 11695, "I cannot make a willowisp ring if I don't have an iron ring to start "
		"with. Find one and return it to me.") 
	ELSEIF (CheckItem(__OBJ_POUCH_OF_WILLOW_BARK) == 0) 
		Conversation
		INTL( 11696, "You got the ring and I got the willowisp right here trapped in my "
		"pocket. However, you don't have the pouch of willow bark you agreed "
		"to bring me in exchange for my help.") 
	ELSE
		TakeItem(__OBJ_POUCH_OF_WILLOW_BARK) 
		TakeItem(__OBJ_IRON_RING) 
		GiveItem(__OBJ_WILLOWISP_RING) 
		Conversation
		INTL( 11697, "Here you go. Enjoy!") 
		PRIVATE_SYSTEM_MESSAGE(INTL( 11698, "Evelyn creates a willowisp ring and gives it to you.")) 
	ENDIF 

NO(WILLOWISP) 
	IF ((CheckItem(__OBJ_IRON_RING) == 1) && (CheckItem(__OBJ_POUCH_OF_WILLOW_BARK) == 1)) 
		Conversation
		INTL( 11699, "Okay, if you say so.") 
	ELSE
		Conversation
		INTL( 11700, "That's fine. I'll wait until you return with the pouch and the ring.") 
	ENDIF 
	
YesNoELSE(WILLOWISP)
	Conversation
	INTL( 11701, "I'm sorry. Was that a \"yes\" or a \"no\"?") 
	SetYesNo(WILLOWISP) 

CmdAND(INTL( 11702, "WILLOW"),INTL( 11703, "BARK")) 
INTL( 11704, "Willow bark is an all-around cough medecine. There are no willows up here. "
"I'm fairly sure that the druids have some. Afterall, they do live in "
"\"Willow\" \"Woods\".") 
PRIVATE_SYSTEM_MESSAGE(INTL( 11705, "Evelyn smiles.")) 

CmdAND(INTL( 11702, "WILLOW"),INTL( 10210, "WOOD")) 
INTL( 11706, "The Willow Woods are located on the southern part of the island.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 11707, "Okay, that does it! I'll show you some manners!")
FIGHT

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 11708, "See ya.")
PRIVATE_SYSTEM_MESSAGE(INTL( 11709, "Evelyn waves to you goodbye.")) 
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 11710, "I'm sorry, I don't quite understand what you've just said.")
ELSE
   Conversation
   INTL( 11711, "That's quite fascinating.")
ENDIF

EndTalk
}

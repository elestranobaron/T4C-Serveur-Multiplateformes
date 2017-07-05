/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "AnrakBrownbark.H"

AnrakBrownbark::AnrakBrownbark()
{}

AnrakBrownbark::~AnrakBrownbark()
{}

extern NPCstructure::NPC AnrakNPC;

void AnrakBrownbark::Create( void )
{
      npc = ( AnrakNPC );
      SET_NPC_NAME( "[2915]Anrak" );  
      npc.InitialPos.X = 1270; 
      npc.InitialPos.Y = 1621;
      npc.InitialPos.world = 0;
}

void AnrakBrownbark::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT MAKEDRUM = 1; 
	
InitTalk

Begin
INTL( 4052, "Uh? Who are you? What do you want?")
 
CmdAND(INTL( 4080, "DRUM"), INTL( 10097, "FATE")) 
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 16)
	Conversation
	INTL( 10098, "I have already given you the two Drums of Fate that you need.")
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 15)
	Conversation
	INTL( 10099, "I learned from my father how to make these drums. Although, he never told me the story behind them. It's an "
	"old family craft, passed from father to son, and since I'm the last of my line, I guess it'll die with me. " 
	"But anyways, enough nostalgia, yes, I can make those drums for you if you have the right components. "
	"I will need four \"hourglasses\" \"of\" \"essence\", four \"gems\" \"of\" \"the\" \"immortal\" and one \"finely\" \"crafted\" \"drum\". Oh, and if "
	"it isn't too much trouble, I'll need 60,000 gold pieces for my services. It's not that I need the money for "
	"myself but I am trying to restore this house and it is somewhat expensive.")
	IF ((CheckItem(__OBJ_FINELY_CRAFTED_DRUM) >= 1) && (CheckItem(__OBJ_GEM_OF_THE_IMMORTAL) >= 4) && (CheckItem(__OBJ_HOURGLASS_OF_ESSENCE) >= 4))
		Conversation
		INTL( 10100, " Hmmm. It seems that you have all the components required. Shall I craft a drum of fate for you?")
		SetYesNo(MAKEDRUM) 
	ENDIF 
ELSE
	Conversation
	INTL( 10101, "I don't think you need a drum of fate. I am sorry but I won't spend my time working for "
	"nothing.")
ENDIF
	
YES(MAKEDRUM) 
	IF ((CheckItem(__OBJ_FINELY_CRAFTED_DRUM) >= 1) && (CheckItem(__OBJ_GEM_OF_THE_IMMORTAL) >= 4) && (CheckItem(__OBJ_HOURGLASS_OF_ESSENCE) >= 4))
		IF (Gold < 60000) 	  
			Conversation
			INTL( 10102, "I am sorry but you lack the 60000 gold fee I asked for.")
		ELSE
			Conversation
			INTL( 10103, "I'll get to work right away... Done! You're the proud owner of a brand new drum of fate!")
			PRIVATE_SYSTEM_MESSAGE(INTL( 10104, "You give 60000 gold and the required components to Anrak.")) 
			PRIVATE_SYSTEM_MESSAGE(INTL( 10105, "Anrak gives you a drum of fate.")) 
			TakeGold(60000) 
			TakeItem(__OBJ_FINELY_CRAFTED_DRUM)
			FOR(0,4) 
				TakeItem(__OBJ_GEM_OF_THE_IMMORTAL)
			ENDFOR
			FOR(0,4) 
				TakeItem(__OBJ_HOURGLASS_OF_ESSENCE)
			ENDFOR
			GiveItem(__OBJ_DRUM_OF_FATE) 
			GiveFlag( __FLAG_COUNTER_DRUM_OF_FATE, (CheckFlag(__FLAG_COUNTER_DRUM_OF_FATE)+1) ) 	
			IF (CheckFlag(__FLAG_COUNTER_DRUM_OF_FATE) == 2)		
				GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 16) 
				SUMMON("MOBGEHENNAREAVER", FROM_USER(1, X), FROM_USER(1, Y) ) 
				PRIVATE_SYSTEM_MESSAGE(INTL( 9750, "You sense some evil lurking nearby, sending shivers up your spine."))
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 10106, "Hey, I said that I need four \"hourglasses\" \"of\" \"essence\", four \"gems\" \"of\" \"the\" \"immortal\" and one \"finely\" \"crafted\" \"drum\". "
		"In addition, I will also require 60000 gold for my services.") 
	ENDIF 

NO(MAKEDRUM) 
	Conversation
	INTL( 8220, "Come back if you ever change your mind.")

YesNoELSE(MAKEDRUM)
	Conversation
	INTL( 10107, "Do you want a Drum of Fate?")
	SetYesNo(MAKEDRUM)

CmdAND(INTL( 4639, "GEM"),INTL( 6268, "IMMORTAL"))
INTL( 10443, "The only place I've been told you can find one is in a dungeon where dark warlords lurk "
"in the shadows.") 

CmdAND3(INTL( 10108, "FINELY"),INTL( 10109, "CRAFT"),INTL( 4080, "DRUM"))
INTL( 10110, "You should ask a musician or even a bard where they get their instruments. That would "
"probably be the first place where I'd start looking if I were you.")

CmdAND(INTL( 10111, "HOURGLASS"),INTL( 10112, "ESSENCE")) 
INTL( 10113, "I think you should ask the chronicler who resides in Raven's Dust. He is the only one " 
"that I know who has some. However, he'll probably expect something in return...")
 
Command(INTL( 4053, "ANRAK"))
INTL( 2535, "Yes?")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 4054, "I do what I can to keep this house from crumbling.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4055, "I am Anrak.")

CmdAND(INTL( 4056, "LUMBER"),INTL( 4057, "AXE"))
INTL( 4058, "It is a great tool for cutting trees indeed. You would be surprised "
"how good it can be used as a weapon too.") 

Command2(INTL( 1492, "DESERT"),INTL( 3865, "VULTURE'S DEN"))
INTL( 4059, "The desert? Surely you do not want to go there. I almost prefer to stay "
"in this damned forest then going into this infernal oven.")

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 4060, "Over here, King Theodore XIII has no powers.")

Command2(INTL( 4061, "MORINDIN"),INTL( 4062, "ARROWMIST"))
INTL( 4063, "Morindin Arrowmist is a skilled hunter.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1864, "...") 
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 4064, "You are always welcome in my small home.")
BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
    Conversation
    INTL( 4012, "Perhaps others would like to know about that.")
ELSE
    Conversation
    INTL( 1929, "That's nonsense!")
ENDIF

EndTalk
}


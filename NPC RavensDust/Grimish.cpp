#pragma hdrstop
#include "Grimish.H"

Grimish::Grimish()
{}

Grimish::~Grimish()
{}

extern NPCstructure::NPC GrimishNPC;

void Grimish::Create( void )
{
        npc = ( GrimishNPC );
        SET_NPC_NAME( "[2953]Grimish" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void Grimish::OnDeath( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
      SHOUT(INTL( 5177, "Oyyyh! *whine* Why me?"))
	}
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Grimish::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
    NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
    switch(rnd(0, 4)){
    case 0: SHOUT(INTL( 5178, "Argh!")); break;
    case 1: SHOUT(INTL( 5179, "Ouch! You mean!")); break;
    case 2:break;
    case 3:break;
    case 4:break;
	}
}

void Grimish::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT RAT = 1; 
CONSTANT PRISON = 2;
CONSTANT INGREDIENT = 3; 

InitTalk

Begin
INTL( 5180, "Pssst! Come talk with Grimish!")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
""
IF (rnd.roll(dice(1,2)) == 1)
    Conversation
   INTL( 5058, "Hullo!")
ELSE
    Conversation
    INTL( 5181, "Shhh! No talk or bad orc come!")     
ENDIF

Command(INTL( 4115, "GRIMISH"))
INTL( 5182, "Yup! Me Grimish!")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 5183, "Me no work! Me trapped here. When stomach grumble, "
"me catch \"rats\" and eat. You want some? ")
SetYesNo(RAT)

YES(RAT)
Conversation
INTL( 5184, "No more rats. Grimish eat them all already! *smile*")

NO(RAT)
Conversation
INTL( 5185, "Too bad. \"Rats\" good! Funny feeling when rats go down stomach though.")

YesNoELSE(RAT)
Conversation
INTL( 5186, "Too bad. Rats good. Funny feeling when rats go down stomach though.")

Command(INTL( 5187, "RAT"))
INTL( 5188, "Rats taste good. Try tail. Very good!") 

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 5189, "Me not remember... Ah! Me now remember... me Grimish!")

Command(INTL( 5190, " RICH "))
INTL( 5191, "Yes! Grimish no rich!")

Command(INTL( 541, "JARKO"))
INTL( 5192, "Varto? Grimish no care. Me no like.") 

Command(INTL( 5193, "HOME"))
INTL( 5194, "Home not here! Not here! Not here Grimish say! Home that way! Or that way!") 

Command(INTL( 554, "HELP"))
INTL( 5195, "Me want to go out. See big orc leader.")

Command(INTL( 744, "ORC"))
INTL( 5196, "They bigger than you. Better looking too and stronger methinks.")

Command2(INTL( 4185, "GHUNDARG"),INTL( 4186, "RUMBLEFOOT"))
INTL( 5197, "Dumb orc hit Grimish on head. See? Big bump on head. Then, Grimish wake "
"up here. You here like Grimish? You prisoner too?")
SetYesNo(PRISON)

YES(PRISON)
Conversation
INTL( 5198, "Oh! Grimish see. You can not help me then. *sigh* No steal my rats or me " 
"bite you!")

NO(PRISON)
Conversation
INTL( 5199, "Oh? You come save Grimish? Grimish happy here. Go away.")

YesNoELSE(PRISON)
Conversation
INTL( 5200, "Grimish do not understand. You prisoner or not?")
SetYesNo(PRISON)

Command(INTL( 4117, "DOREMAS"))
""
IF(CheckFlag(__QUEST_KILL_THE_PIGS_COMPLETED) == 2)
	SWITCH(CheckFlag(__FLAG_HAVE_MET_GRIMISH))
		CASE(0)
			Conversation
			INTL( 5201, "Doremas is a thief in Silversky. He used to like Grimish unlike other humans. I "
			"was to meet Doremas somewhere but Grimish do not remember anymore.")
			GiveFlag(__FLAG_HAVE_MET_GRIMISH, 1)
		ENDCASE
		CASE(1)
			Conversation
			INTL( 5202, "Doremas is a thief in Silversky. He used to like Grimish unlike other humans. I "
			"was to meet Doremas somewhere but Grimish do not remember anymore.")		
		ENDCASE
		CASE(2)
			Conversation	
			INTL( 5203, "Grimish no care about Doremas's problems. Happy here, food everywhere. Doremas hurt "
			"Grimish when not happy. Grimish no like him anymore. Me play \"game\" with you "
			"instead. If win, me tell.")
			GiveFlag(__FLAG_HAVE_MET_GRIMISH, 3)
		ENDCASE
		CASE(3)
			Conversation	
			INTL( 5204, "Grimish no care about Doremas's problems. Happy here, food everywhere. Doremas hurt "
			"Grimish when not happy. Grimish no like him anymore. Me play \"game\" with you "
			"instead. If win, I will tell!")
		ENDCASE
		CASE(4)
			Conversation
			INTL( 5205, "You dumb? Me said to you word pass already. It the Alliance is renewed.")
		ENDCASE
	ENDSWITCH
ELSE
	Conversation
	INTL( 5206, "Doremas said me no talk to no one. So, me no talk. You not friend of Grimish.")
ENDIF

Command(INTL( 5207, "GAME"))
""
IF (CheckFlag(__FLAG_HAVE_MET_GRIMISH) == 3)
	Conversation
	INTL( 5208, "Grimish play game. Simple. You tell, me tell. Tell me now what better than raw rats "
	"yet more ugly than Doremas?")
ELSE
	Conversation // Do you want a McFurry?
	INTL( 5209, "Grimish do not want to play. Grimish play alone with himself with the furry rats.")
ENDIF

Command(INTL( 5210, "NOTHING"))
""
IF (CheckFlag(__FLAG_HAVE_MET_GRIMISH) == 3) 
	Conversation
	INTL( 5211, "Nothing? You right! You good at riddles. Fine. You earn prize. Doremas want "
	"to know word pass. Or was it pass-word? Me know not. What you want to know is "
        "the Alliance is renewed.") 
	GiveFlag(__FLAG_HAVE_MET_GRIMISH, 4) 
ELSEIF (CheckFlag(__FLAG_HAVE_MET_GRIMISH) == 4)
	Conversation
   INTL( 5212, "You dumb? Me said to you word pass already. It is the Alliance is renewed!")       
ELSE
    Conversation
    INTL( 5213, "You help or you go!")     
ENDIF

Command(INTL( 4119, "ALLIANCE IS RENEWED"))
""
IF (CheckFlag(__FLAG_HAVE_MET_GRIMISH) >= 3) 
	Conversation
	INTL( 5214, "Me think so.")
ELSE
	Conversation
	INTL( 5213, "You help or you go!")
ENDIF

Command(INTL( 2806, "HEMOGOBLIN"))
""
IF (CheckItem(__OBJ_VAMPIRE_BAT_WINGS) >= 3 ) 
	Conversation
	INTL( 5215, "You have three pairs of vampire bat wings? They are vampires like Count Hemogoblin, ya know. "
	"Would you give them to me? Grimish be happy!")
	SetYesNo(INGREDIENT)
ELSE
	Conversation
	INTL( 5216, "You see Count Hemogoblin? He is a goblin vampire. Grimish only a goblin. *sigh* "
	"Me wonder what is a vampire. You know? If you could bring Grimish three pair "
	"vampire bat wings, Grimish be happy!")
ENDIF

YES(INGREDIENT)
IF (CheckItem(__OBJ_VAMPIRE_BAT_WINGS) >= 3 ) 
	TakeItem(__OBJ_VAMPIRE_BAT_WINGS)
	TakeItem(__OBJ_VAMPIRE_BAT_WINGS) 
	GiveItem(__OBJ_RING_OF_ACCURACY) 
	Conversation
	INTL( 5217, "You friend! Grimish like you. You ugly but not mean. "
	"You take!")
	;int nExpReward = 6000; 		
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 5218, "You mean. You try to fool Grimish but me not dat dumb.")
ENDIF

NO(INGREDIENT)
Conversation
INTL( 5219, "You mean, you go!")

YesNoELSE(INGREDIENT)
Conversation
INTL( 5220, "Me not understand. You give wings to Grimish or not?")
SetYesNo(INGREDIENT)

Command(INTL( 539, "GOBLIN"))
INTL( 5221, "Yes. Grimish goblin. You keen eyes! You seen \"Count\" \"Hemogoblin\" "
"on \"Arakas\"? Me would like to.")

Command(INTL( 515, "ARAKAS"))
INTL( 5222, "Arararas? Grimish no care.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 5223, "Grimish know about that. Grimish think it that way. Uh.. nonono! That way! "
"Yes. Grimish sure!")

Command(INTL( 514, "WINDHOWL"))
INTL( 5224, "Win all? Grimish never win. Grimish not lucky.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 5225, "Funny wizard. Grimish able to do magic tricks too. You see lil' rat? *glurp* Now you don't!")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5226, "Grimish no like you anymore. You too mean.")
BREAK

Command4(INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5227, "What? You go? *whine*")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
    Conversation
    INTL( 5228, "Me no care!")
ELSE
    Conversation
    INTL( 5229, "Uh?")     
ENDIF

EndTalk
}

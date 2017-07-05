#pragma hdrstop
#include "MirakNira.h"

MirakNira::MirakNira()
{}

MirakNira::~MirakNira()
{}

extern NPCstructure::NPC MirakNiraNPC;

void MirakNira::Create( void )
{
    npc = MirakNiraNPC;
	SET_NPC_NAME( "[3017]Mirak Nira" );
    npc.InitialPos.X = 1641;
    npc.InitialPos.Y = 1181;
	npc.InitialPos.world = 0;       
}

void MirakNira::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
INTL( 2618, "Greetings traveller, what do you need from our fair \"town\"?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2619, "I am Mirak Nira, nice of you to ask.  I am \"working\" now, so please "
"be \"brief\", unless you seek \"information\" about the town, of course.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2620, "I am an assistant for his lordship.  I guess you could say that I work for "
"the \"town\".")

Command(INTL( 523, "ANNABELLE"))
INTL( 2621, "Annabelle? I heard she is a lovely lady but somewhat odd, even though I have never " 
"seen her myself.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command(INTL( 541, "JARKO"))
INTL( 2622, "I do not want to hear about that dreaded necromancer.")

Command(INTL( 556, "OLD HERMIT"))
""
IF (CheckFlag(__FLAG_TALKED_TO_HERMIT) == 0)
	Conversation
	INTL( 2823, "See if I care.")
ELSE
	IF (CheckFlag(__FLAG_DAUGHTER_OF_THE_HERMIT) == 1)
		Conversation
		INTL( 2623, "*ahem* You already know that the Old Hermit is actually my father.  "
	    "Even though he has left me on my own, I do not bear him any hatred. "
		"He has a life to fufill, even if that means to be in constant exile. He "
		"shuns everybody... except me. Before you gain his \"trust\", you'll have "
		"to gain mine.")
	ELSE
		IF (CheckFlag(__FLAG_HERMIT_COUNTER) == 1) 
			Conversation
			INTL( 2624, "I already told you I do not know anything about him!")
			GiveFlag(__FLAG_HERMIT_COUNTER,2)
		ELSEIF (CheckFlag(__FLAG_HERMIT_COUNTER) == 2)
			Conversation
			INTL( 2625, "All right! All right! I admit it. The Old Hermit is actually "
			"Theorn Lemnearan... my father! I changed my name a long time ago "
			"to live my own life. He distrusts everybody.. unless you gain "
			"his \"trust\", and for that, you'll have to win mine first.")
			GiveFlag( __FLAG_DAUGHTER_OF_THE_HERMIT, 1)
	      RemFlag(__FLAG_HERMIT_COUNTER)
	   ELSE
			Conversation
			INTL( 2626, "I do not know about who this \"Old Hermit\" is.")
			GiveFlag(__FLAG_HERMIT_COUNTER,1)	
		ENDIF
	ENDIF
ENDIF

Command2(INTL( 990, "THEORN"),INTL( 991, "LEMNEARAN"))
INTL( 2627, "Shhhh! Keep it down!")

Command(INTL( 632, "TRUST"))
""
IF (CheckFlag(__FLAG_DAUGHTER_OF_THE_HERMIT) == 1)

 IF (CheckFlag( __FLAG_FIRST_TIME_TRUST) == 0)
        Conversation
        INTL( 2628, "I will only trust one who helps Windhowl. If you kill a hundred goblins, "
        "then surely you are trustworthy. And even if you are not, you will have "
        "at least rid us of some of these annoying monsters. Either way, you will "
        "deserve a reward.")  
        GiveFlag(__FLAG_FIRST_TIME_TRUST, 1) 
        GiveFlag(__GOBLINS_KILLED_BY_HERO, 0)
 ELSE   // already talked with the bitch
 
     IF (CheckFlag(__GOBLINS_KILLED_BY_HERO) == 0 )
        Conversation
        INTL( 2629, "I will only trust one who helps Windhowl. If you kill a hundred goblins, "
        "then surely you are trustworthy. And even if you are not, you will have "
        "at least rid us of some of these annoying monsters. Either way, you will "
        "deserve a reward.")  
     ELSEIF (CheckFlag(__GOBLINS_KILLED_BY_HERO) >= 100)  
        IF (CheckFlag(__FLAG_RING_OF_TRUST_GIVEN) == 1) 
            Conversation
            INTL( 2630, "Oh it's you, Goblin Slayer. Go see my father, the \"Old\" \"Hermit\" "
            "and he will help you with whatever you want from him.")
        ELSE
            Conversation
            INTL( 2631, "You truly are fighting for the side of good and you deserve "
            "my trust. Father owes me much, so go to him bearing this ring "
            "of trust and he will help you further on your journey.")
            GiveItem(__OBJ_RING_OF_TRUST)
            GiveFlag(__FLAG_RING_OF_TRUST_GIVEN, 1) 
			IF (USER_KARMA<(100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
				GiveKarma(10*(500-USER_KARMA)/500)
			ENDIF
        ENDIF
     ELSE
        int nCurrentGoblinsKilled = 100 - CheckFlag(__GOBLINS_KILLED_BY_HERO); 
        Conversation
        FORMAT(INTL( 2632, "You have killed only %u goblins and you will have to kill at "
        "least %u more of these disgusting pests before I consider you worthy of my trust."), CheckFlag(__GOBLINS_KILLED_BY_HERO ),nCurrentGoblinsKilled)
     ENDIF
 ENDIF
ELSE
     Conversation
     INTL( 2633, "I do not see a single reason why I should give you my trust and why you would actually need it.")
ENDIF

Command(INTL( 1869, "TOWN"))
INTL( 2634, "Our town has many treasures, and my task is to keep track of all of "
"them. Food supplies, water supplies and the town's finances must also all be "
"accounted for.")

Command(INTL( 597, "INFORMATION"))
INTL( 2635, "I am truly sorry, but all information concerning town supplies are "
"confidential at the moment, as well as the financial state of the town.")

Command(INTL( 2636, "BRIEF"))
INTL( 2637, "Lord Sunrock asks a lot from us, and we are always kept very busy. As a result, "
"we don't have much time to talk with people. *sigh* How I wish that one day "
"I will have enough money to go far away from here. The world is so vast, and to "
"be confined inside a small place such as Windhowl is very frustrating.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2638, "Thank you for coming.") BREAK

Default
INTL( 2639, "Pardon me?")

EndTalk

}

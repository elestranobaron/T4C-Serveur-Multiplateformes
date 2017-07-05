#pragma hdrstop
#include "GhundargRumblefoot.h"

GhundargRumblefoot::GhundargRumblefoot()
{}

GhundargRumblefoot::~GhundargRumblefoot()
{}

extern NPCstructure::NPC GhundargRumblefootNPC;

void GhundargRumblefoot::Create()
{
   npc = GhundargRumblefootNPC;
   SET_NPC_NAME( "[2950]Ghundarg Rumblefoot" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void GhundargRumblefoot::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
   if( target != NULL )
   {
		IF (CheckFlag(__FLAG_TITLE_MORDRICK) != 2)

		GiveFlag( __FLAG_KILLED_THE_ORC_LEADER, 3) 
		 GiveItem(__OBJ_PLANS)
		SHOUT(INTL( 5075, "Argh..{You} {found} {a} {scroll} {on} {his} {corpse!}"))
		ENDIF

	}
   CLOSE_HANDLER
	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void GhundargRumblefoot::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
      SWITCH (rnd.roll(dice(1,100)))
         CASE (1)
            SHOUT(INTL( 5076, "*grunt* Tonight, I dine on human soup!"))
         ENDCASE
         CASE (2)
            SHOUT(INTL( 5077, "You're...*grunt* bleeding? Good. *snort*"))
         ENDCASE
         CASE (3)
            SHOUT(INTL( 5078, "*grunt* You cannot *snort* win!"))
         ENDCASE
         CASE (4)
            SHOUT(INTL( 5079, "...your head on a spike after this! *grunt*"))
         ENDCASE
         CASE (5)
            SHOUT(INTL( 5080, "*grunt*"))
         ENDCASE
         CASE (6)
            SHOUT(INTL( 1863, "*snort*"))
         ENDCASE
         CASE (7)
            SHOUT(INTL( 5081, "Bleed!"))
         ENDCASE
         OTHERWISE
         ENDCASE
      ENDSWITCH
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );

}

void GhundargRumblefoot::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
       int nRandomNumber;
      SWITCH (rnd.roll(dice(1,65))) 
         CASE (1)
            SHOUT(INTL( 5082, "*grunt* Arrgh!"))
         ENDCASE
         CASE (2)       // **** Orc Guardian ****
            SHOUT(INTL( 10125, "*grunt* Now, you die."))
				;nRandomNumber = rnd.roll(dice(1,2)); 
            FOR( 0, nRandomNumber)
               SUMMON( "Orc Guardian", FROM_NPC(-4,X), FROM_NPC(-4,Y))
            ENDFOR
         ENDCASE
         CASE (3)       // **** Failed summon ****
            SHOUT(INTL( 10126, "ARGH! The summon spell went wrong again! *snort*"))
				;nRandomNumber = rnd.roll(dice(1,2)); 
            FOR( 0, nRandomNumber)                        
               SUMMON( "Failed Summon", FROM_NPC(-4,X), FROM_NPC(-4,Y))
            ENDFOR
         ENDCASE
         CASE (4)       // **** Snakes **** 
            SHOUT(INTL( 5083, "Arggh!! Sticks to snakes!"))
            SUMMON( "Poisonous Snake", FROM_NPC(-3,X), FROM_NPC(-3,Y))
         ENDCASE
         CASE (5)       // **** Snakes ****
            SHOUT(INTL( 5083, "Arggh!! Sticks to snakes!"))
				;nRandomNumber = rnd.roll(dice(1,4)); 
            FOR( 0, nRandomNumber)                        
               SUMMON( "Poisonous Snake", FROM_NPC(-3,X), FROM_NPC(-3,Y))
            ENDFOR
         ENDCASE
         CASE (6)       // **** Snakes ****
            SHOUT(INTL( 5083, "Arggh!! Sticks to snakes!"))
				;nRandomNumber = rnd.roll(dice(1,3)); 
            FOR( 0, nRandomNumber)            
               SUMMON( "Poisonous Snake", FROM_NPC(-3,X), FROM_NPC(-3,Y))
            ENDFOR
         ENDCASE
         OTHERWISE
         // Do nothing
         ENDCASE
      ENDSWITCH
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );

}

void GhundargRumblefoot::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT INGREDIENT = 1; 
CONSTANT FOOT = 2;

InitTalk

Begin
""
IF (CheckFlag(__FLAG_KILLED_THE_ORC_LEADER) > 0)
   Conversation
   INTL( 5084, "You again? *grunt* Prepare to die!")
   GiveFlag(__FLAG_KILLED_THE_ORC_LEADER, (CheckFlag(__FLAG_KILLED_THE_ORC_LEADER) - 1))
   FIGHT
ELSE
   Conversation
   INTL( 5085, "*snort* I always wondered if a human would be bold enough to "
   "come into our domain. *grunt*") 
ENDIF

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 5086, "Me Ghundarg Rumblefoot. *snort* Me will to take over \"Silversky\"!")

Command3(INTL( 5087, "CONQUEST"), INTL( 5088, "UP TO"), INTL( 4202, "PLAN"))
INTL( 5089, "Dumb hummie think I would tell you this? HA! Me die before talk.")

Command(INTL( 998, "SILVERSKY"))
INTL( 5090, "Small town filled with dumb hummies! We soon crush them!")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 5091, "Me orc leader. We crush humans. *snort* And we conquer what "
"is rightfully ours! You can help me! You find some \"ingredients\" me "
"need and me spare your puny life! *grunt*")

Command(INTL( 2076, "INGREDIENT"))
""
IF	((CheckItem(__OBJ_POUCH_OF_DANDELION_LEAVES) >= 1) &&	(CheckItem(__OBJ_TARANTULA_EYES) >= 2))
	Conversation
	INTL( 5092, "*grunt* You have the dandelion leaves and two pairs of tarantula eyes? You give to me?")	
	SetYesNo(INGREDIENT)
ELSE
	Conversation
	INTL( 5093, "*grunt* If you wants to help Ghundarg, you go and get 2 pair of tarantula eyes and *snort* "
	"one pouch of dandelion leaves. *snort* Now you go!")
ENDIF

YES(INGREDIENT)
IF ((CheckItem(__OBJ_POUCH_OF_DANDELION_LEAVES) >= 1) && (CheckItem(__OBJ_TARANTULA_EYES) >= 2))
	TakeItem(__OBJ_POUCH_OF_DANDELION_LEAVES)
	TakeItem(__OBJ_TARANTULA_EYES)
	TakeItem(__OBJ_TARANTULA_EYES)
	GiveItem(__OBJ_ORCISH_WRISTBAND)
	Conversation
	INTL( 5094, "You give, me take! *grunt* Me give you this orcish wristband. You keep. If "
	"you want to help me more, *snort* perhaps you could "
	"bring me a \"human's\" \"foot\". Not yours, you too smelly! *grunt*")
	;int nExpReward = 4000; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 5095, "*snort* You won't fool tis orc! Tonight, Ghundarg eat you!")
	FIGHT
ENDIF

NO(INGREDIENT)
Conversation
INTL( 5096, "Ghundarg always get what he want! *grunt*")
FIGHT

YesNoELSE(INGREDIENT) 
Conversation
INTL( 5097, "*snort* You make no sense!? Was that a yes or a no?")
SetYesNo(INGREDIENT)

CmdAND(INTL( 6344, "HUMAN"),INTL( 7124, "FOOT"))
""
IF (CheckItem(__OBJ_HUMAN_FOOT) >= 1) 
	Conversation
	INTL( 5099, "*grunt* You have one human's foot? Me take! Will you give it "
	"to me?")
	SetYesNo(FOOT)
ELSE
	Conversation
	INTL( 5100, "You do not have a human's foot. *grunt* Perhaps me take "
	"one of yours?! *snort*")
ENDIF

Command(INTL( 5098, "HUMAN'S FOOT"))
""
IF (CheckItem(__OBJ_HUMAN_FOOT) >= 1) 
	Conversation
	INTL( 5099, "*grunt* You have one human's foot? Me take! Will you give it "
	"to me?")
	SetYesNo(FOOT)
ELSE
	Conversation
	INTL( 5100, "You do not have a human's foot. *grunt* Perhaps me take "
	"one of yours?! *snort*")
ENDIF

YES(FOOT)
IF (CheckItem(__OBJ_HUMAN_FOOT) >= 1) 
	Conversation
	INTL( 5101, "Me take hummie's foot!! I give you these gold pieces for "
	"*grunt* your small errand. *snort*")
	;int nExpReward = 13000; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
	GiveGold(rnd.roll(dice(2, 15000))) 
	TakeItem(__OBJ_HUMAN_FOOT)
ELSE
	Conversation
	INTL( 5102, "You do not have a human's foot. *grunt* Perhaps me take "
	"one of yours?! *snort*")
ENDIF

NO(FOOT)
Conversation
INTL( 5103, "*snort* I'm tired of your little game. I'll take one of yours instead!")
FIGHT
BREAK

YesNoELSE(FOOT)
Conversation
INTL( 5104, "You can't even speak your language clearly? *grunt* Did you say "
"yes or no? *snort*")
SetYesNo(FOOT)

Command(INTL( 744, "ORC"))
INTL( 5105, "We are invincible *grunt*. Silversky cannot resists us. *snort* King "
"Theodore XIII's crown be mine and his head be over the *grunt* fireplace.")

Command(INTL( 4115, "GRIMISH"))
INTL( 5106, "*grunt* Grimish is an annoying slimy goblin spy. *snort* We took care of him.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5107, "*grunt* Methinks it's time for me to teach you a lesson.")
GiveFlag( __FLAG_KILLED_THE_ORC_LEADER, 3) // at least 3 friendly visits :)
FIGHT

Command2(INTL( 5108, " BANE "),INTL( 3863, "BLACKBLOOD"))
INTL( 5109, "He is only a feeble human. *grunt* All human are weaklings. *snort*") 

Command3(INTL( 5110, "VUNTERTAG"),INTL( 2183, "GUNTERTAG"),INTL( 1037, "MURMUNTAG"))
INTL( 5111, "Traitors! ARRRrrgh!!!! They have been brain-washed by the humans. *grunt*")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 5112, "Soon, Raven's Dust will be ours! *snort*") 

Command(INTL( 7294, "ARAF'KUL") )   // That's the orc leader on the 1st island
INTL( 5113, "*snort* Weakling he is. Me much powerful than him.") 

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 5114, "*snort* Humans always welcome when we hunger for flesh. *grunt*")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 5115, "*grunt* That is pure human nonsense!")
ELSE
   Conversation
   INTL( 5116, "*snort* Duh! And you say me the dumb one.")
ENDIF

EndTalk
}

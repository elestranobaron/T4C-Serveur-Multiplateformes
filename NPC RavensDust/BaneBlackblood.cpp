////////////////////////////////f/////////////////////////////////////////////
#pragma hdrstop
#include "BaneBlackblood.H"

BaneBlackblood::BaneBlackblood()
{}

BaneBlackblood::~BaneBlackblood()
{}
   
extern NPCstructure::NPC BlackBloodNPC;

void BaneBlackblood::Create( void )
{
      npc = ( BlackBloodNPC );
      SET_NPC_NAME( "[2917]Bane Blackblood");  
      npc.InitialPos.X = 0; 
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0;
}
			     
void BaneBlackblood::OnAttack( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnAttack( UNIT_FUNC_PARAM );
    switch(rnd(0, 8)){
    case 0: SHOUT(INTL( 2029, "Die!")); break;
    case 1: SHOUT(INTL( 4147, "Does that hurt? AHAHAHAHA!")); break;
    case 2: SHOUT(INTL( 4148, "Get ready to meet your maker!")); break;
    case 3: SHOUT(INTL( 4149, "This will hurt you more than it hurts me.")); break;
    case 4: SHOUT(INTL( 4150, "Hope you like pain!")); break;
    case 5: break;
    case 6: break;
    case 7: break;
    case 8: break;
	}
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void BaneBlackblood::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
   switch(rnd(0, 8)){
    case 0: SHOUT(INTL( 4151, "Ouch! Now you die!")); break;
    case 1: SHOUT(INTL( 2032, "Ow!")); break;
    case 2: SHOUT(INTL( 4152, "What do you think you're doing!?!")); break;
    case 3: break;
    case 4: break;
    case 5: break;
    case 6: break;
    case 7: break;
    case 8: break;
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void BaneBlackblood::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT KRAANIAN = 1;
CONSTANT INGREDIENT = 2;

InitTalk

Begin
""
IF (CheckFlag(__QUEST_DWARTHON_STONEFACE) == 5) 
   Conversation
   INTL( 4153, "What do you want now? Know that if you displease me, I shall discard you swiftly.")
ELSE
   Conversation
   INTL( 4154, "I do not see why I should talk to you. Talk to \"Dwarthon\" \"Stoneface\" "
   "and disturb me no more!")
   BREAK
ENDIF

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 1864, "...")

Command(INTL( 4155, "LORD BANE"))
INTL( 4156, "That's better. You learn quite fast. This is good for it could save "
"your sorry life.")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 4157, "If you must talk to me, do it properly! I am \"Lord\" \"Bane\"!")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 4158, "That is none of your business. I have but one fate for those "
"who are too curious. Still, perhaps you can be useful. I need some rare "
"\"ingredients\" normally used for magic.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4159, "Bane Blackblood is the name. And soon, you and everyone shall bow down "
"before me when you will hear it.") 

CmdAND(INTL( 4160, "KRAANIAN"),INTL( 3955, "EYE"))
""
IF ((CheckFlag(__QUEST_KRAANIAN_EYES) == 0) || (CheckFlag(__QUEST_KRAANIAN_EYES) == 1))
   Conversation
   INTL( 4161, "I don't have a clue about what you are talking about.")
ELSE // __QUEST_KRAANIAN_EYES is worth 2, then. 
   Conversation
   INTL( 4162, "Heh. Yes, my \"nightblades\" have brought me quite valuable "
   "spell components. You say you want some of the kraanian eyes "
   "I've got? Good. I'll sell you a pair of kraanian eyes for "
   "5000 gold pieces. Does that seem enough fair for you?")
   SetYesNo(KRAANIAN)
ENDIF

YES(KRAANIAN)
IF (Gold >= 5000)
   TakeGold(5000)
   GiveItem(__OBJ_KRAANIAN_EYES)
   Conversation
   INTL( 4163, "AH! These kraanian eyes are WORTHLESS! You've been screwed! Heh! Heh!") 
ELSE
   Conversation
   INTL( 4164, "FOOL! You do not even have the gold pieces! Get out of my face *N*O*W* "
   "of feel my WRATH!")
ENDIF

NO(KRAANIAN)
Conversation
INTL( 4165, "Your lost.")

YesNoELSE(KRAANIAN)
Conversation
INTL( 4166, "Uh? Whatever.")

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY4) >= 3) //If PC has talked to Moonrock about the royal keys...
	IF ((CheckFlag(__QUEST_ROYAL_KEY4) % 3) == 2) // Must have fought to Bane twice already:
		Conversation
		INTL( 4167, "All right, already! I've had enough of you! Here's your blasted key. You can "
		"bet it won't be so easy next time!")
		IF (CheckItem(__OBJ_ROYAL_KEY_4) == 0)
			GiveItem(__OBJ_ROYAL_KEY_4)
		ENDIF
	ELSE // Bane gives the key only once out of three encounters... Must fight him twice first.
		Conversation
		INTL( 4168, "I have it on me at all times, but I'll be damned if I'll give it to the likes "
		"of you.")
		GiveFlag(__QUEST_ROYAL_KEY4,CheckFlag(__QUEST_ROYAL_KEY4)+1)
		FIGHT
	ENDIF
ELSE
	Conversation
	INTL( 4169, "Mind your own business!")
	BREAK
ENDIF

Command(INTL( 514, "WINDHOWL"))
INTL( 4170, "Windhowl? ")
IF (CheckFlag(__BLACK_MARKET) == 2)
   Conversation
   INTL( 4171, "I see that you are aware of the little black market that is "
   "controlled by \"Asarr\" and his thugs.")
ELSE
   Conversation
   INTL( 4172, " Yet another boring town filled with fools.")
ENDIF

Command(INTL( 2076, "INGREDIENT"))
""
IF ((CheckItem(__OBJ_POUCH_OF_BLUE_COHOSH) >= 1) && (CheckItem(__OBJ_MANASTONE) >=1))
	Conversation
	FORMAT(INTL( 4173, "Aah, finally, you are back, %s! You have brought me the two components I need? Do you agree to "
	"give me a pouch of blue cohosh and a manastone?"), USER_NAME) 
	SetYesNo(INGREDIENT)
ELSE
	Conversation
	INTL( 4174, "Ah, you are willing to help me, eh? I need a small pouch of blue cohosh and a manastone. "
	"Uh? Where will you find these? That's your problem!")
ENDIF

YES(INGREDIENT)
IF ((CheckItem(__OBJ_POUCH_OF_BLUE_COHOSH) >= 1) && (CheckItem(__OBJ_MANASTONE) >=1))
	TakeItem(__OBJ_MANASTONE) 
	TakeItem(__OBJ_POUCH_OF_BLUE_COHOSH)
    GiveItem(__OBJ_BLOOD_DAGGER) 
	Conversation
	FORMAT(INTL( 4175, "You have done well, %s. And now... your reward... I give you this "
	"Blood Dagger. This dagger is not to be used as a weapon, consider it as a symbol "
    "of your loyalty to me."), USER_NAME)
	;int nExpReward = 5000; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 4177, "Are you trying to trick me?")
ENDIF

NO(INGREDIENT)
Conversation
INTL( 4178, "I shall not take no for an answer.")
GiveFlag(__FLAG_BLACKBLOOD_WANTS_YOU, (CheckFlag(__FLAG_BLACKBLOOD_WANTS_YOU) + 1) )
FIGHT

YesNoELSE(INGREDIENT) 
Conversation
INTL( 4179, "What did you just say? Yes or no?")
SetYesNo(INGREDIENT)

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 4180, "Lighthaven is a small town in the northern \"Arakas\".")

Command(INTL( 515, "ARAKAS"))
INTL( 4181, "Arakas is an island located north from here. The brigand leader "
"\"Asarr\" controls everything up there.")

Command(INTL( 958, "ASARR"))
INTL( 4182, "It has been a while since we have met.")

Command2(INTL( 4183, "BALDRIC"),INTL( 4070, "SILVERKNIFE"))
INTL( 4184, "Baldric Silverknife would do well to not interfere with us.") 

Command2(INTL( 4185, "GHUNDARG"),INTL( 4186, "RUMBLEFOOT"))
INTL( 4187, "Even the orc leader and its allies won't stand in my way!")

Command2(INTL( 4188, "DWARTHON"),INTL( 4189, "STONEFACE"))
INTL( 4190, "He is the only one around here I truly trust.")

Command2(INTL( 3865, "VULTURE'S DEN"),INTL( 1492, "DESERT"))
INTL( 4191, "Who cares about the desert? Surely not me!")

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 4192, "The royal crown shall be mine someday.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 4193, "You're standing on it, you maggot-pie!") 

Command(INTL( 4194, "HARBINGER"))
INTL( 4195, "I have heard of these fairy-tales told to frighten the farmers. "
"May all the fools on \"Raven's\" \"Dust\" consider me as "
"the Harbinger.")

Command2(INTL( 741, "4TH COMING"),INTL( 1882, "FOURTH COMING"))
INTL( 4196, "If the \"Harbinger\" ever shows up, he'll have to face ME.")

Command(INTL( 541, "JARKO"))
INTL( 4197, "You've met with Jarko, haven't you? He is but a weakling. His "
"little dabbling with necromancy is nothing compared to the "
"raw power of my offensive spells.") 

Command(INTL( 3848, "ZHAKAR"))
INTL( 4198, "This old wizard can cause me some headaches. Although I rarely "
"admit any weaknesses of mine, mainly because I have few, I must "
"say that Zhakar's knowledge in the arcane arts is much more "
"pronounced than mine. He could be a real threat to my plans...")

Command(INTL( 3868, "ALTHEA"))
INTL( 4199, "This is the name of our world.")

Command(INTL( 998, "SILVERSKY"))
INTL( 4200, "This is where the castle of King Theodore XIII is located.")

Command(INTL( 3854, "RAVENWOOD"))
INTL( 4201, "I rarely send \"nightblades\" for they sometimes do not return...")

Command(INTL( 4202, "PLAN"))
INTL( 4203, "And you think I'll reveal them to you? You must be a FOOL!")

Command2(INTL( 509, "BALORK"),INTL( 510, "BRAND"))
INTL( 4204, "Have you been cursed by that Balork? Are you feeling ill? Do "
"I care? No. Quit mumbling about your problems or you'll get more.")

Command(INTL( 1243, "ARTHERK"))
INTL( 4205, "Ho-Ho! If Artherk, the god of healing and mending, does not approve "
"of my actions, then why doesn't he stop me?")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4206, "I think you deserve a lesson.")                                   
GiveFlag(__FLAG_BLACKBLOOD_WANTS_YOU, (CheckFlag(__FLAG_BLACKBLOOD_WANTS_YOU) + 1) )
FIGHT

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 4207, "Be on your way.") BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
	Conversation
	INTL( 1929, "That's nonsense!")
ELSE
	Conversation
	INTL( 4208, "I don't have time for this nonsense.")
ENDIF

EndTalk

}


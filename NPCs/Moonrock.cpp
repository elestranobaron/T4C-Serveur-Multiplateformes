// Moonrock.cpp: implementation of the Moonrock class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Moonrock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Moonrock::Moonrock()
{}

Moonrock::~Moonrock()
{}


extern NPCstructure::NPC MoonrockNPC;

void Moonrock::Create(){
	npc = MoonrockNPC;
	SET_NPC_NAME( "[3051]Moonrock" );
	npc.InitialPos.X = 2947;
	npc.InitialPos.Y = 1043;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void Moonrock::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}


void Moonrock::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT HEAL = 1;
CONSTANT PEARLWISDOM = 5; 		  


InitTalk

Begin
""
IF (CheckFlag(__FLAG_ADDON_CRIMSONSCALE_LETTER)==0)
	Conversation
	INTL( 11772, "Priestess Kilhiam has received something from a messenger for you. I "
	"think you should go talk to her.") 
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 19)
	Conversation
	INTL( 11773, "The High Priest? I'm afraid he had to leave. Brother Kiran can tell you more about it if you "
	"talk to him.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 20)
	Conversation
	INTL( 11774, "You should talk to Brother Kiran again if you need more information.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11775, "Welcome to the temple, child. If you need help coping with these difficult times, you can always "
	"take shelter within these walls.")
ELSE
	Conversation
	FORMAT(INTL( 11776, "Oh %s! Thank you so much for all you've done!"), USER_NAME)
ENDIF
 
Command2(INTL( 1006, "HIGH PRIEST"),INTL( 11737, "GUNTHAR")) 
""
IF((CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 19)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 20)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21))
	Conversation
	INTL( 11777, "The High Priest? I'm afraid he had to leave. Brother Kiran can tell you more about "
	"it if you talk to him.")
ELSE
	Conversation
	INTL( 11765, "High Priest Gunthar is probably in his study room behind the temple.") 
ENDIF 


Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1793, "I go by the name of Moonrock. I \"work\" in this temple to serve the great "
"god of mending, \"Artherk\". A long time ago, I used to wander the world to "
"help those in need, but now, I am content to just stay here and pray.")

Command(INTL( 7700, "STONECREST"))
INTL( 7701, "This is the name of a coastal town located on \"Stoneheim\".")

Command(INTL( 6251, "STONEHEIM"))
INTL( 7702, "Stoneheim is a distant island where the town of \"Stonecrest\" is located.") 

CmdAND(INTL( 7707, "PSALM"),INTL( 1243, "ARTHERK")) 
INTL( 7708, "Unfortunately, most of the original copies have been stolen by pilferers on Stoneheim. "
"There are 5 pages that you must retrieve to have a complete set of the Psalms of Artherk.") 

Command(INTL( 5008, "CHAMPION OF LIGHT"))
INTL( 7709, "A Champion of Light is a person who has decided to follow the path of Light. ")

Command(INTL( 7710, "LIGHTBRINGER")) 
INTL( 7711, "To become a Lightbringer, you must be a \"Champion\" \"of\" \"Light\". If you are, then "
"all you have to do is to seek a paladin such as Sir Beltigan of \"Stoneheim\".")

Command(INTL( 11328, "TEAR-SHAPED PEARL")) 
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 0) 
	Conversation
	INTL( 10822, "I am sorry but there is nothing I have to say about that to you.")
ELSE
	Conversation
	INTL( 10823, "An old friend of mine, \"Annithae\" \"Teardrop\", had a nice collection of these as I recall.")
ENDIF

CmdAND3(INTL( 7703, "TEAR"),INTL( 10821, "SHAPE"),INTL( 7705, "PEARL")) 
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 0) 
	Conversation
	INTL( 10822, "I am sorry but there is nothing I have to say about that to you.")
ELSE
	Conversation
	INTL( 10823, "An old friend of mine, \"Annithae\" \"Teardrop\", had a nice collection of these as I recall.")
ENDIF

Command2(INTL( 8323, "ANNITHAE"),INTL( 8326, "TEARDROP")) 
INTL( 10824, "I think she resides in Stonecrest now. If you ever see her, tell her I said hello.")

CmdAND(INTL( 7705, "PEARL"),INTL( 7712, "WISDOM"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 0) 
	Conversation
	INTL( 7713, "Only a \"Lightbringer\" can bear the overwhelming wisdom infused by Artherk in "
	"a pearl of wisdom.")	
ELSE
	Conversation
	INTL( 7714, "Only the purest of souls can bear the presence of a pearl of wisdom for Artherk's "
	"wisdom is far too overwhelming for mere mortals. The creation of a pearl of wisdom " 
	"requires the complete \"Psalms\" \"of\" \"Artherk\" and a \"tear-shaped\" \"pearl\". The "
	"ceremony involves me reciting the Psalms of Artherk and then, burning them in front "
	"of a tear-shaped pearl. ")
	IF ((CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P1) >= 1) && (CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P2) >= 1) && (CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P3) >= 1) && (CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P4) >= 1) && (CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P5) >= 1) && (CheckItem(__OBJ_TEAR_SHAPED_PEARL) >= 1) )
		Conversation
		INTL( 7715, "I see that you have all the required components. Do you wish me to perform the ritual now?")
		SetYesNo(PEARLWISDOM) 
	ELSE
		Conversation
		INTL( 7716, "If you can gather all the components, come back and I shall perform the necessary ritual.")
	ENDIF
ENDIF 
	  
YES(PEARLWISDOM)
IF ((CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P1) == 0) || (CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P2) == 0) || (CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P3) == 0) || (CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P4) == 0) || (CheckItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P5) == 0))
	Conversation
	INTL( 7717, "Are you trying to deceive me? You do not have all the pages of the \"Psalms\" \"of\" \"Artherk\".")
ELSEIF (CheckItem(__OBJ_TEAR_SHAPED_PEARL) == 0) 
	Conversation
	INTL( 7718, "The most vital component required for the ritual is a \"tear-shaped\" \"pearl\" and "
	"you don't seem to have one. Come back when you find one.")	
ELSE
	Conversation
	INTL( 7719, "Let's begin, then. Artherk, hear thy daughter and bless this \"tear-shaped\" \"pearl\". Instill it with your "
	"infinite wisdom and let us rejoice with a pearl of wisdom. It is done! Here, this pearl of "
	"wisdom is yours. May Artherk light thy path.")	
	CastSpellSelf(__SPELL_NPC_CANTRIP_BLUE_WIPE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7720, "You give the Lost Psalms of Artherk and the tear-shaped pearl to Moonrock.")) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 7721, "Moonrock recites the Psalms and then, burn them in front of the tear-shaped pearl.")) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 7722, "The tear-shaped pearl glows in a soft bluish light and you feel overwhelmed by a divine presence.")) 	
	PRIVATE_SYSTEM_MESSAGE(INTL( 7723, "Moonrock gives you a pearl of wisdom.")) 	
	TakeItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P1) 
	TakeItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P2) 
	TakeItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P3) 
	TakeItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P4) 
	TakeItem(__OBJ_LOST_PSALMS_OF_ARTHERK_P5) 
	TakeItem(__OBJ_TEAR_SHAPED_PEARL)
	GiveItem(__OBJ_PEARL_OF_WISDOM) 
ENDIF 

NO(PEARLWISDOM)
Conversation																		 
INTL( 7724, "Come back if you change your mind.")

YesNoELSE(PEARLWISDOM)
Conversation
INTL( 7725, "Do you want me to perform the holy ritual required to create a pearl of wisdom?")
SetYesNo(PEARLWISDOM) 

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY4) >= 1) // If PC has already talked to Thea...
	IF (USER_KARMA >= 150) //...and is worthy:
		Conversation
		INTL( 1795, "I had one such key, a long time ago, yes. It wasn't for myself, but was "
		"necessary to save the life of a friend who had been taken hostage by Bane "
		"Blackblood, on Raven's Dust. I guess he still has it, although some people "
		"have already asked me about it.")
		IF (CheckFlag(__QUEST_ROYAL_KEY4) <= 2)
			GiveFlag(__QUEST_ROYAL_KEY4, 3)
		ENDIF
	ELSE //...but isn't worthy enough:
		Conversation
		INTL( 1796, "I have some doubt as to your intentions... Please perform more good deeds "
		"so that I know I can confide in you in absolute trust. These are not matters "
		"that I can discuss with just anyone.")
	ENDIF
ELSE // IF PC hasn't talked to Thea yet about the Royal Keys.
	Conversation
	INTL( 1797, "Some day, I'll tell you about an adventure I had, in my younger days...")
ENDIF

Command(INTL( 509, "BALORK"))
INTL( 1798, "Balork dwells in a \"dungeon\" under the temple of Artherk.")

Command(INTL( 882, "DUNGEON"))
INTL( 1799, "I do not really like filthy dungeons.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1800, "I am the Bishop of this church. I can \"heal\" your wounds using powerful \"magic\".")

Command(INTL( 523, "ANNABELLE"))
INTL( 7183, "Annabelle has a powerful healing touch.")

Command(INTL( 1833, "HEAL "))
""
IF (USER_MAXHP == USER_HP)
 Conversation
 INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (USER_LEVEL < 6)
		Conversation
		INTL( 1834, "Since you are not strong enough to acquire gold pieces on your own, "
		"I shall heal your wounds. You are now healed, my friend.")
		HealPlayer(USER_MAXHP)
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
	ELSE
		Conversation
		FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"), (USER_MAXHP-USER_HP) / 2)
		SetYesNo(HEAL)
	ENDIF
ENDIF

YES(HEAL)
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (Gold < ((USER_MAXHP-USER_HP)/2))
		IF (Gold > 0) 
			Conversation
			INTL( 1835, "You did not have enough gold pieces, but I have healed a few of your wounds "
			"nonetheless for what you could spare.")			
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7521, "You give %u gold to Moonrock."), Gold) ) 
			PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 
			HealPlayer(Gold*2) 			
			TakeGold(Gold)
			CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
  ELSE
			Conversation
			INTL( 1836, "You do not have enough gold pieces to be healed. You will have to find "
			"have to find the gold first.")
		ENDIF
 ELSE
		Conversation
		INTL( 1837, "Thank you for this generous donation. Your wounds are now healed. "
		"Please feel free to come back if you need more healing.")
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7521, "You give %u gold to Moonrock."), ((USER_MAXHP-USER_HP) /2) ) ) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		TakeGold( ( (USER_MAXHP-USER_HP) / 2) )
		HealPlayer(USER_MAXHP)		
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
	ENDIF
ENDIF

NO(HEAL)
Conversation
INTL( 1239, "As you wish. Ask me again if you change your mind.")

YesNoELSE(HEAL)
Conversation
INTL( 1838, "I think your wounds are not only of the body, but of the mind as well. I will "
"pray for your spirit to heal so you can better answer my question next time.")

Command(INTL( 1243, "ARTHERK"))
INTL( 1839, "Artherk is the greatest deity of them all. He is the god of mending and "
"truth. It is an honor for me to be able to serve him.")

Command(INTL( 1096, "MAGIC"))
INTL( 1840, "I am one with the elements of light and earth. With the knowledge that I possess, I "
"am able to heal one's wounds. If you have time, I can share that knowledge "
"and \"teach\" you a few spells.")

Command3(INTL( 700, "SPELL"),INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 7522, "Very well. This is what I can teach you.")
CreateSkillList
	AddTeachSkill (__SPELL_HEAL_LIGHT, 9, 897)
	AddTeachSkill (__SPELL_CURE_POISON, 6, 1825)
	AddTeachSkill (__SPELL_PROTECTION, 7, 3712)
	AddTeachSkill (__SPELL_HEAL_SERIOUS, 14, 8177)
SendTeachSkillList

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 1245, "May Artherk protect you.") BREAK

Default
INTL( 1842, "Perhaps Artherk would know about this.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Moonrock::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
		   TEACH_SKILL(__SPELL_HEAL_LIGHT, 9, 897)
			TEACH_SKILL(__SPELL_CURE_POISON, 6, 1825)
			TEACH_SKILL(__SPELL_PROTECTION, 7, 3712)
		   TEACH_SKILL(__SPELL_HEAL_SERIOUS, 14, 8177)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE



//////////////////////////////////////////////////////////////////////
// Iraltok.cpp: implementation of the Iraltok class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Iraltok.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Iraltok::Iraltok()
{}

Iraltok::~Iraltok()
{}

extern NPCstructure::NPC Mage;

void Iraltok::Create(){
	npc = Mage;
	SET_NPC_NAME( "[3040]Iraltok" );
    npc.InitialPos.X = 2998;
    npc.InitialPos.Y = 952;
	npc.InitialPos.world = 0;	
}

void Iraltok::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Iraltok::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT HEAL = 1;

InitTalk

Begin
INTL( 1380, "I, the seeker of \"knowledge\", greet you, my friend. Perhaps I could \"heal\" "
"your wounds if you are in pain. I am also a great \"arcane\" \"scribe\" and may be "
"of assistance if you are interested in magical lore.")

Command(INTL( 1381, "KNOWLEDGE"))
INTL( 1382, "I have the unending task of collecting knowledge and transcribing it "
"to books so that others may later \"learn\" from them.")


Command(INTL( 1383, "ARCANE SCRIBE"))
INTL( 1384, "Arcane scribes such as myself use \"runic\" \"scripting\" \"kits\" in order to "
"create \"blank\" \"magic\" \"scrolls\" that are later used to inscribe powerful "
"magics.")

Command(INTL( 1385, "RUNIC SCRIPTING KIT"))
INTL( 1386, "In order to create such a kit, I need a pouch of yellow powder, a vial of "
"spider venom, a flask of goblin blood, a diamond, and a feather. I ask a "
"modest fee of 1,000 gold pieces to make the kit for you. Please gather all "
"I need and mention \"make\" \"runic\" \"kit\" when you're all set.")

Command(INTL( 1175, "BLANK MAGIC SCROLL"))
INTL( 1387, "I cannot make such scrolls myself, but I heard that some wizards in Windhowl "
"could help you with this.")

Command(INTL( 1388, "MAKE RUNIC KIT"))
""
IF (CheckItem(__OBJ_POUCH_OF_YELLOW_POWDER)>=1 AND (CheckItem(__OBJ_DIAMOND)>=1) AND (CheckItem(__OBJ_FLASK_OF_GOBLIN_BLOOD)>=1) AND (CheckItem(__OBJ_FEATHER)>=1) AND (CheckItem(__OBJ_VIAL_OF_SPIDER_VENOM)>=1) AND (Gold>=1000))
	TakeItem(__OBJ_POUCH_OF_YELLOW_POWDER)
	TakeItem(__OBJ_DIAMOND)
	TakeItem(__OBJ_FLASK_OF_GOBLIN_BLOOD)
	TakeItem(__OBJ_FEATHER)
	TakeItem(__OBJ_VIAL_OF_SPIDER_VENOM)
	TakeGold(1000)
	GiveItem(__OBJ_RUNIC_SCRIPTING_KIT)
	Conversation
	INTL( 1389, "There we go. You're all set, now. Thanks for doing business with me. Please tell "
	"all your friends about me, I'd love to help them too.")
ELSE
	Conversation
	INTL( 1390, "You're missing some components, I'm afraid. Perhaps you should draw a checklist: "
	"a pouch of yellow powder, a diamond, a feather, a flask of goblin blood and a "
	"vial of spider venom. Oh, and a thousand gold pieces wouldn't hurt either, if "
	"it's all the same to you. Please come again.")
ENDIF

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
    Conversation
    INTL( 1147, "You do not need healing, you have no wounds.")
ELSEIF (USER_LEVEL <= 10)
    Conversation
    INTL( 1391, "I have healed all your wounds my friend. Remember that once you will "
    "be over level 10, I will charge you a small amount of gold pieces for "
    "this service.")
    CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
    HealPlayer(USER_MAXHP)
	 PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
ELSE
    Conversation
	    FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"),(USER_MAXHP-USER_HP) / 2)
    SetYesNo(HEAL)
ENDIF

 
YES(HEAL)
IF (USER_MAXHP == USER_HP)
    Conversation
    INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
    IF (Gold < ((USER_MAXHP-USER_HP)/2))
        IF (Gold > 0) 
            Conversation
            INTL( 1392, "You did not have enough gold pieces but I have healed a few of your wounds "
            "nonetheless for what you could spare.")            				
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7513, "You give %u gold to Iraltok."), Gold) ) 
				PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 	
				CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
				HealPlayer(Gold*2)              
				TakeGold(Gold) 				
			ELSE
            Conversation
            INTL( 1393, "You do not have enough gold pieces to be healed. You will have to find "
            "have to find the gold first.")
        ENDIF
    ELSE        
        Conversation
        INTL( 1394, "Thank you for this generous donation. Your wounds are now healed.  "
        "Please feel free to come back if you need more healing.")		  
		  PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7513, "You give %u gold to Iraltok."), ((USER_MAXHP-USER_HP) /2) ) ) 
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
     INTL( 1239, "As you wish. Ask me again if you change your mind.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1395, "I am known as Iraltok, mage of \"Urtanar\", and the seeker of \"knowledge\".")

Command3(INTL( 489, "WORK"),INTL( 485, "WHO ARE YOU"),INTL( 487, "OCCUPATION"))
INTL( 1396, "My task is as endless as time itself. I seek all \"knowledge\" and transcribe "
"it into \"books\".")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1397, "Balork? Where? Where? Runnnn!")

Command(INTL( 523, "ANNABELLE"))
INTL( 1398, "Who's that?")

Command(INTL( 1399, "URTANAR"))
INTL( 1400, "Urtanar is a great place. Many say it is the greatest tower of magic.  "
"I was trained there and learned much about the ways of \"magic\". Even "
"\"Uranos\" was once an apprentice there. Urtanar is in the middle of a "
"great continent southwest of here. Perhaps one day you will be able to "
"travel there.")

Command(INTL( 1096, "MAGIC"))
INTL( 1401, "I'm always happy to help an initiate with his spells. There are several "
"\"spells\" I can teach you.")

Command3(INTL( 700, "SPELL"),INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 7514, "Yes, I would be glad to teach you a spell or two.")
CreateSkillList
	AddTeachSkill (__SPELL_FIRE_DART, 5, 532)
	AddTeachSkill (__SPELL_FLAMING_ARROW, 8, 5300)
SendTeachSkillList

Command(INTL( 1424, "URANOS"))
INTL( 1425, "Uranos is one of the greatest wizards in the kingdom of \"Goldmoon\".  He is "
"also the oldest.")

Command(INTL( 753, "GOLDMOON"))
INTL( 1426, "Goldmoon is the kingdom regrouping the islands of Arakas, which is the one "
"you are currently on, and Raven's Dust, where the king's castle is.")

Command(INTL( 1427, "BOOK"))
INTL( 1428, "Yes, we have hundreds of them in our \"library\". In fact, we have so many "
"we cannot count them all.")

Command(INTL( 1429, "LIBRARY"))
INTL( 1430, "It is located in the northwest corner of the tower.")

Command3(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"))
INTL( 961, "Farewell, friend.") BREAK

Default
INTL( 1431, "Others should know.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Iraltok::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_FIRE_DART, 5, 532)
         TEACH_SKILL(__SPELL_FLAMING_ARROW, 8, 5300)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
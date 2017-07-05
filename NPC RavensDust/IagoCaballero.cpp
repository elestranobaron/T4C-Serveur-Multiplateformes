#pragma hdrstop
#include "IagoCaballero.h"

IagoCaballero::IagoCaballero()
{}

IagoCaballero::~IagoCaballero()
{}

extern NPCstructure::NPC IagoCaballeroNPC;

void IagoCaballero::OnInitialise( UNIT_FUNC_PROTOTYPE )
{																	 
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	GiveGlobalFlag(__QUEST_GLOBAL_CABALLERO_ALIVE, 0);
}

void IagoCaballero::OnDeath( UNIT_FUNC_PROTOTYPE ){
    NPCstructure::OnDeath( UNIT_FUNC_PARAM );

    GiveGlobalFlag( __QUEST_GLOBAL_CABALLERO_ALIVE, 1 );
}

void IagoCaballero::OnAttack( UNIT_FUNC_PROTOTYPE ){
    switch(rnd(0, 7)){
    case 0: SHOUT(INTL( 6351, "I shall purify your soul!")); break;
    case 1: SHOUT(INTL( 6352, "The pain purifies the sins!")); break;
    case 2:break;
    case 3:break;
    case 4:break;
    case 5:break;
    case 6:break;
    case 7:break;    
	}
	NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void IagoCaballero::OnAttacked( UNIT_FUNC_PROTOTYPE ){
    switch(rnd(0, 7)){
    case 0: SHOUT(INTL( 6353, "Argh! Artherk, grant me strength!")); break;
    case 1: SHOUT(INTL( 2032, "Ow!")); break;
    case 2:break;
    case 3:break;
    case 4:break;
	 case 5:break;
    case 6:break;
	 case 7:break;    		 	 
	 }
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void IagoCaballero::Create( void )
{
    npc = IagoCaballeroNPC;
    SET_NPC_NAME( "[2955]Iago Caballero" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
	GiveGlobalFlag(__QUEST_GLOBAL_CABALLERO_ALIVE, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////
void IagoCaballero::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
{
CONSTANT HEAL = 1;

InitTalk

Begin
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 3) 
	Conversation
	FORMAT(INTL( 6354, "%s, you are working for Shadeen? What have you done? I must now purify your sins!"), USER_NAME)
	FIGHT	
ELSE
	Conversation
	FORMAT(INTL( 6355, "Greetings, %s."), USER_NAME) 
ENDIF

Command4(INTL( 2034, "HELLO"),INTL( 2035, " HI "),INTL( 6356, "GREETING"),INTL( 6357, "HAIL"))
FORMAT(INTL( 6358, "What can I do for you, %s?"), USER_NAME)

Command2(INTL( 6359, "IAGO"),INTL( 6360, "CABALLERO"))
INTL( 6361, "Yes? If you need me to \"heal\", you simply have to ask.")

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 6362, "I am Iago Caballero, paladin of the God of \"Healing\" and Mending, \"Artherk\".")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 6363, "I follow the path set by my God, \"Artherk\". I spread seeds of righteousness throughout "
"the realm, hoping to purify the sins done by other humans.")

Command(INTL( 569, "HEAL"))
""
IF ((CheckNPCFlag(__NPC_CABALLERO_HEAL) < CurrentRound) && (CheckNPCFlag(__NPC_CABALLERO_HEAL) != 0))
   Conversation
   INTL( 6364, "Our God, \"Artherk\", has not yet answered my holy prayers.")
ELSE
   Conversation
   INTL( 6365, "The God of Healing and Mending, Artherk, have granted me with the "
   "power to heal the wounds of the injured. Do you wish to be healed?")
   SetYesNo(HEAL)
ENDIF

YES(HEAL)
IF (USER_MAXHP == USER_HP)
   Conversation
   INTL( 6366, "You do not need healing.")
ELSEIF( USER_GENDER == GENDER_MALE )
   Conversation
   FORMAT(INTL( 6367, "Hear mine prayers, \"Artherk\", heal this man's wounds and protect "
   "him as thee protect me. Done! You are healed, %s."), USER_NAME)
	CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
	HealPlayer(USER_MAXHP)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
   GiveNPCFlag(__NPC_CABALLERO, rnd.roll(dice(3,5)) TDELAY MINUTES) 
ELSE
   Conversation
   FORMAT(INTL( 6368, "Hear mine prayers, \"Artherk\", heal this woman's wounds and protect "
   "her as thee protect me. Done! You are healed, %s."), USER_NAME)
	CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
	HealPlayer(USER_MAXHP)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!"))    
   GiveNPCFlag(__NPC_CABALLERO_HEAL, rnd.roll(dice(3,5)) TDELAY MINUTES) 
ENDIF
   
NO(HEAL)
Conversation
INTL( 6369, "Fine, then.")

YesNoELSE(HEAL)
Conversation
INTL( 6370, "I will take this a no.")

Command(INTL( 1243, "ARTHERK"))
INTL( 6371, "Artherk is the God of \"Healing\" and Mending. It is He who I pray to light my path and protect "
"me of the influence of \"evil\".")

Command(INTL( 1220, "EVIL"))
INTL( 6372, "\"Shadeen\" is one evil woman. If you happen to see her, do not follow her orders for it will "
"be your downfall into the path of sins.")

Command(INTL( 5008, "CHAMPION OF LIGHT"))
INTL( 6373, "Ah ha! You have heard of us! Yes, I am such a champion, and there are many more that walk "
"this land, and other lands in the west. If you seek to become one of us, I suggest you "
"do only good deeds, then swear fealty to our righteous cause.")

Command(INTL( 4576, "SWEAR FEALTY"))
INTL( 6374, "So you truly desire this? Then speak to Chamberlain Thomar, he shall help you.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 6375, "Zhakar, despite his odd manners, is a wizard who follows the Path of Light.")

Command(INTL( 1581, "SHADEEN"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) != 0) 
	Conversation
	INTL( 6376, "I see that you have heard of this evil lady before. Do not ever trust her for she is "
	"a very manipulative person gifted with a skill for lies and deceits. The local "
	"thieves are known to be her allies.")
ELSE
	Conversation
	INTL( 6377, "Do not ever trust her for she is a very manipulative person gifted with a skill for "
	"lies and deceits. The local thieves are known to be her allies.") 
ENDIF

Command2(INTL( 4183, "BALDRIC"),INTL( 4070, "SILVERKNIFE"))
INTL( 6378, "You could say that Baldric Silverknife is the thieves' leader in \"Raven's\" \"Dust\" but "
"\"Shadeen\" doesn't trust him as he shares a mentality similar to hers.")

Command2(INTL( 4185, "GHUNDARG"),INTL( 4186, "RUMBLEFOOT"))
INTL( 6379, "Ghundarg Rumblefoot is the orc leader. You should do best to not underestimate his "
"shamanic powers.")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 6380, "Bane Blackblood is a shadowy person blinded by his lust for power. He wishes the throne ")

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 6381, "King Theodore XIIIth is the current ruler of the Kingdom of \"Goldmoon\".")  

Command(INTL( 753, "GOLDMOON"))
INTL( 6382, "The Kingdom of Goldmoon regroups the islands of \"Arakas\" and \"Raven's\" \"Dust\".")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 6383, "Lighthaven is located on \"Arakas\".")

Command(INTL( 514, "WINDHOWL"))
INTL( 6384, "Windhowl is \"Lighthaven\"'s sister town in \"Arakas\".")

Command(INTL( 998, "SILVERSKY"))
INTL( 6385, "Silversky is the small town located in the south-eastern part of \"Raven's\" \"Dust\".")

Command(INTL( 515, "ARAKAS"))
INTL( 6386, "Arakas is the island located north of \"Raven's\" \"Dust\".")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 6387, "Raven's Dust is the island's name.")

Command2(INTL( 3865, "VULTURE'S DEN"),INTL( 1492, "DESERT"))
INTL( 6388, "Kalir and Jamir are often wandering in the desert. Quite frankly, I "
"do not have a clue how they do it or why.")

Command(INTL( 3868, "ALTHEA"))
INTL( 5692, "Althea is the name of the world in which you are.")

Command(INTL( 3771, "?"))
INTL( 6389, "I am sorry but I cannot answer this question of yours.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 6390, "Such foul words coming out of your mouth shows how much politeness you lack.")
BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
FORMAT(INTL( 6391, "Farewell, %s. Follow the path of Light and ye shall be protected."), USER_NAME) 
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 1327, "Pardon?")
ELSE
   Conversation
   FORMAT(INTL( 6392, "%s, clarify your thoughts. I do not understand what you are saying."), USER_NAME)
ENDIF

EndTalk
}


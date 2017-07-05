/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "DariusMoonglow.H"

DariusMoonglow::DariusMoonglow()
{}

DariusMoonglow::~DariusMoonglow()
{}

extern NPCstructure::NPC Lower_Rank_Druid;

void DariusMoonglow::Create( void )
{
      npc = ( Lower_Rank_Druid );
      SET_NPC_NAME( "[2941]Darius Moonglow" );  
      npc.InitialPos.X = 1466; 
      npc.InitialPos.Y = 2888;
      npc.InitialPos.world = 0;
}

void DariusMoonglow::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT HEAL = 1;

InitTalk

Begin
FORMAT(INTL( 4625, "It is you again, %s! It is nice to see you again, my friend."), USER_NAME)

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 4626, "Hello! What can I do for you?")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4627, "I am known amongst our \"order\" as Darius Moonglow.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 4628, "I have many chores to do, we all do if we want to survive as a community. "
"I am currently busy searching for some \"gems\"...")

Command(INTL( 4629, "NATURE'S GARB"))
INTL( 4630, "The Nature's garb is our ceremonial robes.")

Command(INTL( 680, "ORDER OF NATURE"))
INTL( 4631, "The sole purpose of the Order of Nature is to protect the nature around "
"us lest we want it to be destroyed and seal our fate as well.")

Command(INTL( 4632, "ORDER"))
INTL( 4633, "Our druidic order's name is the \"Order\" \"of\" \"Nature\".")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 4634, "He is insane and must be stopped.")

Command(INTL( 836, "FOREST GUARDIAN"))
INTL( 4635, "They are nearly as old as Althea itself and they have great powers.")

Command(INTL( 3868, "ALTHEA"))
INTL( 4636, "In case you weren't aware already, this is the name of the world.")

Command(INTL( 4271, "CUTHANA"))
INTL( 4637, "I don't know much about that. If it's some kind of herb, you should ask "
"Celestina Waterbreeze.")

Command(INTL( 3844, "NIGHTBLADE"))
INTL( 4638, "The nightblades sometimes attempt to enter in our sanctuary but the "
"Forest Guardians are able to keep them at bay.")

Command(INTL( 4639, "GEM")) 
""
IF (CheckFlag(__QUEST_COMPLETED_GEM) == 0 )
	Conversation
	INTL( 4640, "You look like someone who could help me. I need four rare colored gems. I need a red, "
   "a green, a yellow and a blue gem. Retrieve them and bring them to me "
   "and you shall be rewarded.")
	GiveFlag(__QUEST_COMPLETED_GEM, 1)
ELSEIF (CheckFlag(__QUEST_COMPLETED_GEM) == 1) 
	IF ((CheckItem(__OBJ_RED_GEM) >= 1) AND (CheckItem(__OBJ_GREEN_GEM) >= 1) AND (CheckItem(__OBJ_BLUE_GEM) >= 1) AND (CheckItem(__OBJ_YELLOW_GEM) >= 1))	
		TakeItem(__OBJ_RED_GEM)
		TakeItem(__OBJ_GREEN_GEM)
		TakeItem(__OBJ_YELLOW_GEM)
		TakeItem(__OBJ_BLUE_GEM)
		Conversation
      INTL( 4641, "I see that you have been able to gather all four gems. Take this Nature's garb "
      "Perhaps it will help you on your journey.")
      GiveItem(__OBJ_NATURE_GARB)
		GiveFlag(__QUEST_COMPLETED_GEM, 2)
	ELSE
		Conversation
		INTL( 4642, "You do not have the 4 gems I require! Remember, I need a red, a green, a yellow and a blue one.")	
	ENDIF
ELSE
	Conversation
	INTL( 4643, "Thank you for your help with the 4 colored gems.")
ENDIF

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
    Conversation
    INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
IF (USER_LEVEL < 5)
   Conversation
   INTL( 4644, "Since you are not strong enough to acquire gold pieces on your own, "
   "I shall heal your wounds. You are now healed, my friend.")
	CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
   HealPlayer(USER_MAXHP)
ELSE
    Conversation
    FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"),((USER_MAXHP-USER_HP)) )
    SetYesNo(HEAL)
ENDIF
ENDIF

YES( HEAL )
IF (USER_MAXHP == USER_HP)
    Conversation
    INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
    IF (Gold < ((USER_MAXHP-USER_HP)))
        IF (Gold > 0) 
            Conversation
            INTL( 4645, "You did not have enough gold pieces but I have healed a few of your wounds "
            "nonetheless for what you could spare.")
				CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
				HealPlayer(Gold)				
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7551, "You give %u gold to Darius Moonglow."), Gold)) 
				PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 
            TakeGold(Gold)
        ELSE
            Conversation
            INTL( 4646, "You do not have enough gold pieces to be healed. You will have to find "
            "have to find the gold first.")
        ENDIF
    ELSE
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7551, "You give %u gold to Darius Moonglow."), USER_MAXHP-USER_HP)) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)		 
      TakeGold( ( (USER_MAXHP-USER_HP) ) ) 
		HealPlayer(USER_MAXHP)		
      Conversation
      INTL( 4647, "Thank you for this generous donation. Your wounds are now healed.  "
      "Please feel free to come back if you need more healing.")
    ENDIF
ENDIF

NO( HEAL )
     Conversation
    INTL( 1239, "As you wish. Ask me again if you change your mind.")

YesNoELSE( HEAL )
     Conversation
     INTL( 2230, "It seems difficult to answer a simple question.")

Command(INTL( 4648, "APPLE"))
INTL( 4649, "Apples are not as common as in our sister island. That is why we have to "
"sell them at such an expensive price.")

Command2(INTL( 682, "YRIAN"),INTL( 683, "EARTHSONG"))
INTL( 4650, "Yrian Earthsong is the elder and leader of the druidic \"Order\" \"of\" \"Nature\" "
"located in northern Arakas.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4651, "I'm sure you could find a long piece of wood covered with squirrel's oil "
"somewhere that could suit your needs.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 4652, "It was nice talking to you.")
BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
    Conversation
    INTL( 4019, "I don't have time for this.")
ELSE
    Conversation
    INTL( 4653, "Sorry, I do not know anything about that.")
ENDIF

EndTalk
}


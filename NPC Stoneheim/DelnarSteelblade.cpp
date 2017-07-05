#pragma hdrstop
#include "DelnarSteelblade.h"

DelnarSteelblade::DelnarSteelblade()
{}

DelnarSteelblade::~DelnarSteelblade()
{}

extern NPCstructure::NPC DelnarSteelbladeNPC;

void DelnarSteelblade::Create(){
   npc = DelnarSteelbladeNPC;
   SET_NPC_NAME( "[10847]Delnar Steelblade" );
   npc.InitialPos.X = 315; 
   npc.InitialPos.Y = 700; 
	npc.InitialPos.world = 0;
}									 

void DelnarSteelblade::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
   switch(rnd(0, 20))    
	{		
   case 0: SHOUT(INTL( 8544, "Stonecrest is under my protection! Leave or DIE!")); break;
   case 1: SHOUT(INTL( 2030, "You're bleeding? Come to me and bleed some more!")); break; 
   case 2: SHOUT(INTL( 8545, "Isn't it a nice day to die?")); break;
   default: break;
	}
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void DelnarSteelblade::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
   switch(rnd(0, 20))    
	{
      case 0: SHOUT(INTL( 2032, "Ow!")); break;
      case 1: SHOUT(INTL( 8546, "You got lucky on that one!")); break;
      case 2: SHOUT(INTL( 8547, "You're starting to make me mad!")); break;
		default: break;
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void DelnarSteelblade::OnDeath( UNIT_FUNC_PROTOTYPE )
{
   switch(rnd(0, 2))    
	{	
      case 0: SHOUT(INTL( 1860, "Urgh!")); break;
		default: break; 
	 }	
NPCstructure::OnDeath( UNIT_FUNC_PARAM );    
}

void DelnarSteelblade::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT SKULLS = 1;

InitTalk

BYTE bRewardRandomNumber = 0;

Begin
INTL( 8548, "Yes? Unless you have specific business with me, I must ask that you find someone else to talk to. I am quite busy keeping watch over "
"this gate, as you can see.")

CmdAND3(INTL( 8549, " I "), INTL( 8550, "HAVE"), INTL( 8551, "BUSINESS"))
INTL( 8552, "Oh? Have you come to turn in some \"skulls\"?")
SetYesNo(SKULLS)

CmdAND(INTL( 8128, "VILLAIN"), INTL( 8129, "SKULL"))
""
IF(CheckFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN) == 0)
	Conversation
	INTL( 8553, "I collect the skulls of villains from throughout the land. If you ever come upon one, keep it and bring it here. I will reward you "
	"well for your efforts. ")
	IF(CheckItem(__OBJ_VILLAIN_SKULL) == 1)
		Conversation
		INTL( 8554, "Ahh, I see you already have one. Would you care to give it to me so that I may reward you?")
		SetYesNo(SKULLS)
	ELSEIF(CheckItem(__OBJ_VILLAIN_SKULL) > 1)
		Conversation
		INTL( 8555, "Ahh, I see you have already gathered a few skulls there. Would you care to turn them in now to receive your reward?")
		SetYesNo(SKULLS)
	ELSE
		Conversation
		INTL( 8556, "Return here when you have at least one skull.")
	ENDIF
ELSE
	Conversation
	INTL( 8557, "Ahh, have you come to turn in some skulls?")
	SetYesNo(SKULLS)
ENDIF

YES(SKULLS)
IF (CheckItem(__OBJ_VILLAIN_SKULL) == 0)
	Conversation
	INTL( 10474, "It doesn't look like you have any skulls of villains. Stop wasting my time!")
ELSE
    int nNumSkulls = 0;
	IF(CheckItem(__OBJ_VILLAIN_SKULL) > 10)
		Conversation
		INTL( 10767, "My, you have quite a few of them. I will take 10 of them for now. Here is your reward, as promised.")
		;nNumSkulls = 10;
	ELSE
		Conversation
		INTL( 8558, "Splendid! Here is your reward then, as promised!")
		;nNumSkulls = CheckItem(__OBJ_VILLAIN_SKULL);
	ENDIF
	FOR(0, nNumSkulls)
		TakeItem(__OBJ_VILLAIN_SKULL)
		GiveFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN, CheckFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN) + 1)
		IF(CheckFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN) != 10 && CheckFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN) != 25 &&	CheckFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN) != 100)
			GiveXP(10000)
			PRIVATE_SYSTEM_MESSAGE(INTL( 8559, "You receive 10000 experience points!"))
			;bRewardRandomNumber = rnd(0, 181);
			IF(bRewardRandomNumber <= 9)
				GiveItem(__OBJ_CHAINMAIL)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8560, "You receive a chainmail!"))
			ELSEIF(bRewardRandomNumber <= 44)
				GiveItem(__OBJ_CHAINMAIL_GLOVES)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8561, "You receive some chainmail gloves!"))
			ELSEIF(bRewardRandomNumber <= 74)
				GiveItem(__OBJ_CHAINMAIL_COIF)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8562, "You receive a chainmail coif!"))
			ELSEIF(bRewardRandomNumber <= 116)
				GiveItem(__OBJ_CHAINMAIL_GIRDLE)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8563, "You receive a chainmail girdle!"))
			ELSEIF(bRewardRandomNumber <= 146)
				GiveItem(__OBJ_CHAINMAIL_LEGGINGS)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8564, "You receive some chainmail leggings!"))
			ELSE
				GiveItem(__OBJ_CHAINMAIL_BOOTS)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8565, "You receive some chainmail boots!"))
			ENDIF
		ELSE
			IF(CheckFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN) == 10)
				Conversation
				INTL( 8566, " Since this is the 10th skull you have brought me, I will give you a special reward.")
				GiveXP(25000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8567, "You receive 25000 experience points!"))
				GiveItem(__OBJ_CHAINMAIL_BOOTS)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8565, "You receive some chainmail boots!"))
			ELSEIF(CheckFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN) == 25)
				Conversation
				INTL( 8568, " Since this is the 25th skull you have brought me, I will give you a special reward.")
				GiveXP(100000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8569, "You receive 100000 experience points!"))
				GiveItem(__OBJ_CHAINMAIL_BOOTS)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8565, "You receive some chainmail boots!"))
			ELSE
				Conversation
				INTL( 8570, " Since this is the 100th skull you have brought me, I will give you a special reward.")
				GiveXP(500000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8571, "You receive 500000 experience points!"))
				GiveItem(__OBJ_CHAINMAIL_BOOTS)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8565, "You receive some chainmail boots!"))
			ENDIF
		ENDIF
	ENDFOR
ENDIF 
NO(SKULLS)
	Conversation
	INTL( 8572, "Then I have no business with you. Please leave.")
	BREAK
YesNoELSE(SKULLS)
	Conversation
	INTL( 8573, "I collect the skulls of villains from throughout the land. If you ever come upon one, keep it and bring it here. I will reward you "
	"well for your efforts.")

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8574, "Good day to you then.")
BREAK

Default
INTL( 8575, "I don't have time for this. Either state your business or leave me to my work.")


EndTalk

}
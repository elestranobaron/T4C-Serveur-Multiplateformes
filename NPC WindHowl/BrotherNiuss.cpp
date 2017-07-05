//////////////////////////////////////////////////////////////////////
// BrotherNiuss.cpp: implementation of the BrotherNiuss class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "BrotherNiuss.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BrotherNiuss::BrotherNiuss()
{}

BrotherNiuss::~BrotherNiuss()
{}
 
extern NPCstructure::NPC BrotherNiussNPC;

//Nom: Brother Niuss.
//Statistique: Windhowl Priest.
//Position: (2211, 568)
//World: 0
//Description: Happy priest.
//Body: Priest.

//////////////////////////////////////////////////////////////////////////////////////////
void BrotherNiuss::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of BrotherNiuss
//
{
	npc = BrotherNiussNPC;
	SET_NPC_NAME( "[2998]Brother Niuss" );
	npc.InitialPos.X = 1693;
	npc.InitialPos.Y = 1176;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void BrotherNiuss::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of BrotherNiuss
//
{

CONSTANT HEAL = 1;

InitTalk

Begin
INTL( 2221, "What can I do for you?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2222, "I am Brother Niuss. I am a priest of Artherk's church.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2223, "I am a priest of Artherk. How lucky I am to be in such a great organization "
"that is dedicated to helping others. How about you, stranger, do you have "
"any wounds that need to be \"healed\"?")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
""
IF (CheckFlag(__BALORK_BRAND) == 1)
Conversation
INTL( 2224, "I see you bear the \"Balork\"'s \"brand\" upon your brow my friend. ")
ELSE
Conversation
INTL( 820, "Balork's curse? That's horrible!")
ENDIF

Command(INTL( 523, "ANNABELLE"))
INTL( 2225, "I heard that she has elven blood running in her veins. Methinks it is untrue "
"because we all know that Elves have been wiped out a long time ago. Or "
"were they?") 

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (USER_LEVEL < 5)
		Conversation
		INTL( 2226, "Since you are not strong enough to acquire gold pieces on your own, "
		"I shall heal your wounds. You are now healed, my friend.")		
		HealPlayer(USER_MAXHP)
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
	ELSE
		Conversation
		FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"), ((USER_MAXHP-USER_HP) / 2))
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
				INTL( 2227, "You did not have enough gold pieces, but I have healed a few of your wounds "
				"nonetheless for what you could spare.")			
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7532, "You give %u gold to Brother Niuss."), Gold) )
				PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 
				CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
				HealPlayer(Gold*2) 
				TakeGold(Gold)
			ELSE
				Conversation
				INTL( 2228, "You do not have enough gold pieces to be healed. You will have to find "
				"have to find the gold first.")
			ENDIF
		ELSE
			Conversation
			INTL( 2229, "Thank you for this generous donation. Your wounds are now healed. "
			"Please feel free to come back if you need more healing.")
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7532, "You give %u gold to Brother Niuss."), ((USER_MAXHP-USER_HP) /2) ) ) 
			TakeGold( ( (USER_MAXHP-USER_HP) / 2) )
			HealPlayer(USER_MAXHP)			 			
			CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
			PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		ENDIF
	ENDIF
	
NO(HEAL)
  Conversation
 INTL( 1239, "As you wish. Ask me again if you change your mind.")

YesNoELSE(HEAL)
  Conversation
  INTL( 2230, "It seems difficult to answer a simple question.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2231, "Artherk will protect you as much as he will be able to.") BREAK

Default
INTL( 2220, "Only Artherk could help you.")

EndTalk

}

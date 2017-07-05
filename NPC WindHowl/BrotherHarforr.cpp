//////////////////////////////////////////////////////////////////////
// BrotherHarforr.cpp: implementation of the BrotherHarforr class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "BrotherHarforr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BrotherHarforr::BrotherHarforr()
{}

BrotherHarforr::~BrotherHarforr()
{}
 
extern NPCstructure::NPC BrotherHarforrNPC;

//Nom: Brother Harforr.
//Statistique: Windhowl Priest.
//Position: (2158, 563)
//World: 0
//Description: Robed priest.
//Body: Priest.

//////////////////////////////////////////////////////////////////////////////////////////
void BrotherHarforr::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of BrotherHarforr
//
{
	npc = BrotherHarforrNPC;
	SET_NPC_NAME( "[2997]Brother Harforr" );
	npc.InitialPos.X = 1653;
	npc.InitialPos.Y = 1171;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void BrotherHarforr::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of BrotherHarforr
//
{

CONSTANT HEAL = 1;
CONSTANT SANCTUARY = 2;
CONSTANT DONATION = 3;

InitTalk

Begin
INTL( 2200, "Greetings stranger. How can I be of service?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2201, "I am called Brother Harforr, a priest of \"Artherk\".")

Command(INTL( 1243, "ARTHERK"))
INTL( 2202, "Don't you know about Artherk? The god Artherk? I have worshipped him for "
"many years now.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2203, "I am a priest of \"Artherk\". I consider myself very lucky to be part of "
"those who devote their lives to helping others in the name of our god. "
"What about you, stranger? Perhaps I could help you by \"healing\" your wounds or "
"by setting your \"sanctuary\" place into our beautiful temple, right here "
"in Windhowl.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
""
IF (CheckFlag(__BALORK_BRAND) == 1)
Conversation
INTL( 2204, "Pray for Artherk, my friend, for you have been cursed by the foul Balork. "
"Whenever he is defeated, he brands yet another victim, hoping to own his or her "
"soul in the abyss. He then returns from his demonic plane to plague us "
"again with his malevolent presence.")
ELSE
Conversation
INTL( 2205, "He is a monster, and the people do what they can to get rid of him.")
ENDIF

Command(INTL( 523, "ANNABELLE"))
INTL( 2206, "Young, lovely Annabelle, how we miss her! She could heal the sick and comfort "
"the downtrodden. She would hear your plight and help you, no doubt. If she "
"were still alive, that is.")

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
  Conversation
  INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
IF (USER_LEVEL < 5)
  Conversation
  INTL( 2207, "Since you are not strong enough to acquire gold pieces on your own, "
  "I shall heal your wounds. You are now healed, my friend.")
  CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
  HealPlayer(USER_MAXHP)
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
      INTL( 2208, "You did not have enough gold pieces, but I have healed a few of your wounds "
      "nonetheless for what you could spare.")		
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7530, "You give %u gold to Brother Harforr."), Gold) ) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 		
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
      HealPlayer(Gold*2) 
      TakeGold(Gold)
    ELSE
      Conversation
      INTL( 2209, "You do not have enough gold pieces to be healed. You will have to find "
      "have to find the gold first.")
    ENDIF
  ELSE
    
    Conversation
    INTL( 2210, "Thank you for this generous donation. Your wounds are now healed. "
    "Please feel free to come back if you need more healing.")	 
    TakeGold( ( (USER_MAXHP-USER_HP) / 2) )
	 CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)		 
	 PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7530, "You give %u gold to Brother Harforr."), ((USER_MAXHP-USER_HP) /2) ) ) 
	 PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!"))
	 HealPlayer(USER_MAXHP)
  ENDIF
ENDIF

NO(HEAL)
   Conversation
  INTL( 1239, "As you wish. Ask me again if you change your mind.")

YesNoELSE(HEAL)
   Conversation
   INTL( 2211, "So be it, my friend.")

Command3(INTL( 1609, "DEATH"),INTL( 1610, "DIE"),INTL( 1611, "KILLED"))
INTL( 2212, "It is always unfortunate to face death, but those who wear a "
"Gem of Destiny can set a \"Sanctuary\" where they will reappear "
"when they get killed.")

Command(INTL( 1613, "SANCTUARY"))
INTL( 2213, "The Sanctuary is where your body and soul are restored by the "
"Gem of Destiny if you have been killed. Do you wish to set "
"the Temple of Windhowl as your sanctuary?")
SetYesNo(SANCTUARY)

YES(SANCTUARY)
IF (Gold < 5000 )
  Conversation
  INTL( 2214, "I would be glad to comply, but my order would require a donation "
  "of 5000 gold pieces, which you do not appear to have. Perhaps you "
  "should come again later, when you are more fortunate.")
ELSE
  Conversation
  INTL( 2215, "Very well. My order requires a donation of 5000 gold pieces, however. "
  "Do you accept to pay that amount?")
  SetYesNo(DONATION)
ENDIF

NO(SANCTUARY)
Conversation
INTL( 1617, "Ah. Very well, then.")

YesNoELSE(SANCTUARY)
Conversation
INTL( 1617, "Ah. Very well, then.")

YES(DONATION)
IF (Gold < 5000) // Had to put another check to prevent a user from 
  Conversation  // dropping gold after the 1st check. 
  INTL( 2216, "I would be glad to comply, but my order would require a donation "
  "of 5000 gold pieces, which you do not appear to have. Perhaps you "
  "should come again later, when you are more fortunate.")
ELSE
  Conversation
  INTL( 2217, "It is done, then. Your body and soul shall return here if you "
  "unfortunately happen to die.")
  TakeGold(5000)
  SetDeathLocation( 1682,1163,0 ) // Temple of Windhowl
  CastSpellTarget(__SPELL_NPC_CANTRIP_BLUE_WIPE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7531, "You give 5000 gold to Brother Harforr.")) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 7519, "Your spirit is now anchored here.")) 
ENDIF
 
NO(DONATION)
Conversation
INTL( 2218, "I understand, you need to think about this further. Come back "
"when you are ready.")

YesNoELSE(DONATION)
Conversation
INTL( 1621, "I... Um... Was that a yes or a no?")
SetYesNo(DONATION)

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2219, "May Artherk protect you in your travels.") BREAK

Default
INTL( 2220, "Only Artherk could help you.")

EndTalk


}

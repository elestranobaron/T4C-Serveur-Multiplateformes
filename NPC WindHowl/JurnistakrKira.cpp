//////////////////////////////////////////////////////////////////////
// JurnistakrKira.cpp: implementation of the JurnistakrKira class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "JurnistakrKira.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

JurnistakrKira::JurnistakrKira()
{}

JurnistakrKira::~JurnistakrKira()
{}

extern NPCstructure::NPC Priest;

//Nom: Jurnistakr Kira.
//Statistique: Windhowl Priest.
//Position: (2216, 544)
//World: 0
//Description: Priest.
//Body: Priest.

//////////////////////////////////////////////////////////////////////////////////////////
void JurnistakrKira::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of JurnistakrKira
//
{
	npc = Priest;
	SET_NPC_NAME( "[3009]Jurnistakr Kira" );
	npc.InitialPos.X = 1698;
	npc.InitialPos.Y = 1152;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void JurnistakrKira::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of JurnistakrKira
//
{

CONSTANT DONATION = 1;

InitTalk

Begin
INTL( 2369, "Hello.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2370, "My name is Jurnistakr Kira. Greetings to you.")

Command4(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"),INTL( 2371, "ARCHBISHOP"))
INTL( 2372, "I bear the title of Archbishop of \"Artherk\".")


Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2373, "But Balork's dead... Isn't he? No?!? Heavens!")

Command(INTL( 523, "ANNABELLE"))
INTL( 2374, "Annabelle? I heard she is a lovely lady, but somewhat odd, even though I've never " 
"seen her myself.")

Command(INTL( 1243, "ARTHERK"))
INTL( 2375, "Artherk is without a doubt the greatest of all the gods. I follow his ways "
"faithfully and will certainly continue to do so until my life's end. Because "
"of the importance of my work and the \"responsibilities\" I carry, I do not "
"have much time to answer your questions. I will therefore ask that you be "
"brief.")

Command(INTL( 2376, "RESPONSIBILIT"))
INTL( 2377, "The duty of an archbishop is to help troops in combat. I must accompany "
"the soldiers and follow closely behind during battle against the evil "
"\"goblin\" army. The wounded are brought to me and I do my best to get them "
"back into the fray or to make sure they can survive the trip back home.")

Command(INTL( 539, "GOBLIN"))
INTL( 2378, "Not many towns are as lucky as we are to have an army capable of resisting "
"the continuous onslaught of goblins.")

Command(INTL( 2379, "CHURCH"))
INTL( 2380, "I am but one of many who have chosen to use their healing spells for the "
"greater good of civilization. If you wish to help further the ambitions of "
"the church, a small \"donation\" of 200 gold will be rewarded with the healing "
"of your wounds.")

Command(INTL( 2381, "DONAT"))
INTL( 2382, "I see, you are interested in helping us with our cause? Well if you have "
"enough money to pay, I will heal your wounds without further delay. Do you "
"still wish to be healed?")

SetYesNo (DONATION)
YES (DONATION)
	IF (Gold >= 200)
		TakeGold (200)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7533, "You give 200 gold to Jurnistakr Kira.")) 
		HealPlayer (USER_MAXHP)
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		Conversation
		INTL( 2383, "I call forth the powers of the light to heal your wounds! You have "
		"been healed! Go forth in peace, my friend.")
   ELSE
     Conversation
INTL( 2384, "You do not have enough money, I fear.")
   ENDIF
NO (DONATION)
  Conversation
  INTL( 2385, "Very well, I will be here if you ever change your mind.")
YesNoELSE (DONATION)
  Conversation
  INTL( 2386, "I would appreciate a simple yes or no.")
  SetYesNo (DONATION)

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2387, "Good day.") BREAK

Default
INTL( 2220, "Only Artherk could help you.")

EndTalk

}

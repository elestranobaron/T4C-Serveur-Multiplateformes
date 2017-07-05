//////////////////////////////////////////////////////////////////////
// Leana.cpp: implementation of the Leana class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Leana.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Leana::Leana()
{}

Leana::~Leana()
{}

extern NPCstructure::NPC LeanaNPC;

void Leana::Create( ){
    npc = LeanaNPC;
	SET_NPC_NAME( "[2965]Leana" );
    npc.InitialPos.X = 1596;
    npc.InitialPos.Y = 2572;
	npc.InitialPos.world = 0;
}

void Leana::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT SHOP = 1;
		  
InitTalk

Begin
INTL( 5409, "Greetings, have you come here to \"shop\"?")
SetYesNo(SHOP)

YES(SHOP)
	Conversation
	INTL( 5410, "I apologize for the state the shop is in. We haven't finished setting everything up yet.")
NO(SHOP)
	Conversation
	INTL( 5411, "Oh... well we're not ready for any customers anyway.")
YesNoELSE(SHOP)
	Conversation
	INTL( 5412, "Maybe you could come back once we're actually open.")

Command(INTL( 3694, " NAME"))
INTL( 5413, "I am Leana, proud wife of the acclaimed \"Drardos\".")

Command(INTL( 4895, "LEANA"))
INTL( 5414, "Yes, that's right.")

Command(INTL( 4873, "DRARDOS"))
INTL( 5415, "I'm not really that proud to tell you the truth, but my husband only wants me to talk this way "
"when we see potential customers.")

Command(INTL( 4875, "ANTIQUE"))
INTL( 5416, "My husband is very proud of his business, a little too proud perhaps. We are not quite ready to open "
"up shop yet, but once we are, you will be able to buy most of the antiques on display here.")

Command(INTL( 489, "WORK"))
INTL( 5417, "As soon as we are finished setting up the shop, we can start selling antiques.")

Command(INTL( 1960, "SHOP"))
INTL( 5418, "My husband believes he will have the best antiques store in the land. That should not be too difficult "
"since there aren't any others around.")

Command(INTL( 3918, "VISITOR"))
INTL( 5419, "I have been much too occupied to notice anyone out of the ordinary.")

Command(INTL( 4882, "WIFE"))
INTL( 5420, "Yes, I am Drardos's wife.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 1326, "Goodbye now.") BREAK

Default
INTL( 5421, "You'll have to ask my husband, maybe he would know more about that.")

EndTalk

}

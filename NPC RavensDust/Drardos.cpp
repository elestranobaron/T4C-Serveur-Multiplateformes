//////////////////////////////////////////////////////////////////////
// Drardos.cpp: implementation of the Drardos class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Drardos.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Drardos::Drardos()
{}

Drardos::~Drardos()
{}

extern NPCstructure::NPC DrardosNPC;

void Drardos::Create( ){
    npc = DrardosNPC;
	SET_NPC_NAME( "[2944]Drardos" );
    npc.InitialPos.X = 1598;
    npc.InitialPos.Y = 2575;
	npc.InitialPos.world = 0;
}

void Drardos::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT TAN = 1;
CONSTANT GiveRing = 2;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 5)
	Conversation
	INTL( 10116, "They sent you away you say? The ring is evil? Oh my... I had no idea. If I had known that I would have thought "
	"better than to send you to the temple. Oh well, there is nothing to be done about it now. Alright... keep this "
	"between you and me now. When I get an object such as this, I sometimes seek the advice of one who deals with "
	"dark powers. I have found one such person who can feel for an object's aura and can sometimes tell me what it does. "
	"The strange thing is that the man I speak of is blind.")
	GiveFlag(__FLAG_QUEST_FOR_BONES, 6)	
ELSE
	Conversation
	INTL( 4871, "Hello, what can I do for you?")
ENDIF
	
Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4872, "I am the renowned Drardos!")

Command(INTL( 4873, "DRARDOS"))
INTL( 4874, "You have not heard of me before? I am the most famous \"antiques\" collector in all of Althea!")

Command(INTL( 4875, "ANTIQUE"))
INTL( 4876, "I have several shops on the mainland, and I'm just now moving into this new one.")

Command(INTL( 8039, "RING"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 3)
	Conversation
	INTL( 10117, "What's that you got there? Hmm, what a strange looking piece this is. May I see it?")
	SetYesNo(GiveRing)
ELSEIF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 4)
	Conversation
	INTL( 10118, "I told you before, I cannot identify the ring... it has some sort of power and I can't tell what it does. Perhaps the "
	"priests at the temple will know more. Try asking Brother Thorkas about it.")
ELSEIF(CheckFlag(__FLAG_QUEST_FOR_BONES) >= 6)
	Conversation
	INTL( 10119, "Seek the blind man. He might be able to read the ring's aura to tell you something useful about it.")
ELSE
	Conversation
	INTL( 4898, "I'm afraid I really don't know what you mean by that.")
ENDIF

YES(GiveRing)
	Conversation
	INTL( 10120, "Thank you. Now let's have a look at it... I must say I have never seen such a fine piece. This ring was crafted by a \"master\" "
	"\"jeweler\" I believe.")
NO(GiveRing)
	Conversation
	INTL( 10121, "Oh... well then, what else can I do for you?")
YesNoELSE(GiveRing)
	Conversation
	INTL( 10122, "May I see the ring?")
	SetYesNo(GiveRing)

CmdAND(INTL( 5726, "MASTER"), INTL( 10123, "JEWEL"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) >= 3)
	Conversation
	INTL( 10124, "Yes, only someone of great skill could've created this ring. There is something else too, the ring seems to be imbued with "
	"some strange power and I don't know what it does. Perhaps the priests at the temple will know more.")
	GiveFlag(__FLAG_QUEST_FOR_BONES, 4)
ELSE
	Conversation
	INTL( 4898, "I'm afraid I really don't know what you mean by that.")
ENDIF

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 4877, "Well, at the moment we're rather busy unpacking and setting the \"shop\" up.")

Command(INTL( 1960, "SHOP"))
INTL( 4878, "Yes, I collect antiques, but I also sell them. You didn't know? Well, I guess I can't be famous everywhere.")

Command(INTL( 3918, "VISITOR"))
INTL( 4879, "My \"wife\" and I have been too busy unpacking that we haven't had time to look around the city. "
"You're one of the few people who came in today.")

Command(INTL( 4880, "SWORD"))
INTL( 4881, "Yes, I have many swords in my beautiful collection. I will have to do an inventory of all of them later on.")

Command(INTL( 4882, "WIFE"))
INTL( 4883, "My beautiful wife Leana works with me night and day to turn this into one of the best shops "
"around!")

Command2(INTL( 4884, "TANNED"),INTL( 4885, "TAN"))
""
IF (CheckItem(__OBJ_ANTELOPE_SKIN) >= 1)
	Conversation
   INTL( 4886, "Samuel told you that I could tan this skin? Well, he was right. "
   "I'll tan this antelope skin for 1400 gold pieces. Is that alright?")
   SetYesNo(TAN)
ELSE
   Conversation
   INTL( 4887, "I bet that Samuel told you that I have some skills for tanning "
   "animal skin. Bring me an antelope's skin and I'll see what I can "
   "do for you, my friend.")
ENDIF

YES(TAN)
IF (CheckItem(__OBJ_ANTELOPE_SKIN) >= 1)
   IF (Gold < 1400)
      Conversation
      FORMAT(INTL( 4888, "You do not have enough gold pieces. You need %u more.") ,(1400 - Gold))
   ELSE
      Conversation
      INTL( 4889, "Let's get to work... ")
      IF (rnd.roll(dice(1,8)) == 1)
         TakeItem(__OBJ_ANTELOPE_SKIN)
         Conversation
         INTL( 4890, "ARGH! I failed again! I am truly sorry but I've ruined "
         "this skin badly. Perhaps you'd like me to try again with a new skin?")
         SetYesNo(TAN)
      ELSE
         TakeItem(__OBJ_ANTELOPE_SKIN)
         GiveItem(__OBJ_TANNED_ANTELOPE_SKIN)
         TakeGold(1400)
         Conversation
         INTL( 4891, "Ah... perfectly done! I hope you like it.")
      ENDIF
   ENDIF
ELSE
   Conversation
   INTL( 4892, "Where's the antelope's skin?")
ENDIF

NO(TAN)
Conversation
INTL( 4893, "Fine.")

YesNoELSE(TAN)
Conversation
INTL( 4894, "Erm.. was that a yes or a no?")
SetYesNo(TAN)

Command(INTL( 4895, "LEANA"))
INTL( 4896, "That's her name.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 4897, "Come again!") BREAK

Default
INTL( 4898, "I'm afraid I really don't know what you mean by that.")

EndTalk

}

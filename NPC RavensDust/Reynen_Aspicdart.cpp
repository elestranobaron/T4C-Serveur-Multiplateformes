// Reynen_Aspicdart.cpp: implementation of the Reynen_Aspicdart class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Reynen_Aspicdart.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Reynen_Aspicdart::Reynen_Aspicdart()
{}

Reynen_Aspicdart::~Reynen_Aspicdart()
{}

extern NPCstructure::NPC Reynen_AspicdartNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void Reynen_Aspicdart::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Reynen Aspicdart
//
{
    npc = Reynen_AspicdartNPC;
    SET_NPC_NAME( "[2976]Reynen Aspicdart" );
    npc.InitialPos.X = 870;          // HIS CHEST IS AT 944,549,2
    npc.InitialPos.Y = 800; 
    npc.InitialPos.world = 2; 
}

//////////////////////////////////////////////////////////////////////////////////////////
void Reynen_Aspicdart::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Reynen Aspicdart
//
{

InitTalk

Begin
INTL( 5639, "Hey! A visitor! Think you could point me to the door outta here? Nah, didn't "
"think so.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5640, "I'm called Reynen Aspicdart, but most people used to call me "
"'\"The\" \"Dart\"' back in my *ahem* earlier career.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 5641, "Right now, I'm looking for a way out of this cave, but the illusions "
"keep on bringing me back here. Bloody darn annoying, if y'ask me. But if "
"you're asking what I used to do for a living, I was a con artist. I've "
"reformed, though, so you don't have to worry right now.")

Command(INTL( 5642, "THE DART"))
INTL( 5643, "That's what they used to call me, back when I was a younger, more dashing "
"rogue and hero. Now, I'm just Reynen, and I'd like nothing more than to get "
"out of this cavern...")

Command2(INTL( 3880, "ADRIANA"),INTL( 5644, "ADRIANNA"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY1) >= 4)
	Conversation
	INTL( 5645, "How is she doing?")
ELSE
	INTL( 5646, "Hm. You know more than you're telling. In any case, it's none of your business.")
ENDIF

Command(INTL( 1794, "ROYAL KEY"))
""
SWITCH(CheckFlag(__QUEST_ROYAL_KEY1))
	CASE(0)
		Conversation
		INTL( 5647, "I've never heard of it!")
	ENDCASE
	CASE(1)
		Conversation
		INTL( 5648, "Not my business!")
	ENDCASE
	CASE(2)
		Conversation
		INTL( 5649, "A strange question...")
	ENDCASE
	CASE(3)
		Conversation
		INTL( 3743, "I don't know what you're talking about.")
	ENDCASE
	CASE(4)
		Conversation
		INTL( 5650, "Ah... I see someone's told you about my past adventures. No use denying "
		"the obvious, then. Yes, I used to have such a key, but I hid it in a chest "
		"in these caverns, and got lost before I could return to get it. It's yours, "
      "if you can find it. I wonder if I locked the chest though...")
		GiveFlag(__QUEST_ROYAL_KEY1,5)
	ENDCASE
	CASE(5)
		Conversation
		INTL( 5651, "Didn't I just answer that? It's in a chest somewhere around here.")
	ENDCASE
	OTHERWISE
		Conversation
		INTL( 5652, "How many times will I have to repeat myself? Look around, you'll find it.")
	ENDCASE
ENDSWITCH

CmdAND(INTL( 5653, "CHEST"),INTL( 5654, "LOCK"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY1) == 5) // If Reynen already told PC about the chest...
	Conversation
	INTL( 5655, "Heh heh... I'm sorry, I forgot to mention that the chest could be locked... ")
	IF (CheckItem(__OBJ_REYNEN_KEY) == 0) // ...and PC doesn't have a key...
		Conversation
		INTL( 5656, "Here's the key. You don't have to bring it back, I got copies to spare.")
		GiveItem(__OBJ_REYNEN_KEY)
	ELSE
		Conversation
		INTL( 5657, "But it looks like you've got the key, so that shouldn't be a problem.")
	ENDIF
ELSE
	Conversation
	INTL( 5658, "So, some chests are locked... What of it?")
ENDIF

Command(INTL( 5659, "LOCKED"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY1) == 5) // If Reynen already told PC about the chest...
	Conversation
   INTL( 5655, "Heh heh... I'm sorry, I forgot to mention that the chest could be locked... ")
	IF (CheckItem(__OBJ_REYNEN_KEY) == 0) // ...and PC doesn't have a key...
		Conversation
		INTL( 5656, "Here's the key. You don't have to bring it back, I got copies to spare.")
		GiveItem(__OBJ_REYNEN_KEY)
	ELSE
		Conversation
		INTL( 5657, "But it looks like you've got the key, so that shouldn't be a problem.")
	ENDIF
ELSE
	Conversation
   INTL( 5660, "You sound as lost as I am.")
ENDIF

Command(INTL( 5653, "CHEST"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY1) == 5) // If Reynen already told PC about the chest...
   Conversation
   INTL( 11404, "What is the problem with the chest?")
ELSE                                     // Trying to force the user to say that the chest is locked.
   Conversation
   INTL( 5660, "You sound as lost as I am.")
ENDIF

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 5661, "Pah! I am not *that* lost.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5662, "Keep this up and you'll end up losing more than money! *smile*")
IF (Gold >= 100)
	target->SetGold(Gold * 0.9)
ENDIF
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 5663, "If you ever find a map of this cave, don't forget to bring it to me.")
BREAK

Default
INTL( 5660, "You sound as lost as I am.")

EndTalk
}


//////////////////////////////////////////////////////////////////////
// LiurnClar.cpp: implementation of the LiurnClar class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "LiurnClar.h"
 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LiurnClar::LiurnClar()
{}

LiurnClar::~LiurnClar()
{}

extern NPCstructure::NPC Wizard_Liurn_Clar;

//Nom: Liurn Clar.
//Statistique: Windhowl Mage.
//Position: (2118, 645)
//World: 0									   
//Description: Mage.
//Body: Mage.

//////////////////////////////////////////////////////////////////////////////////////////
void LiurnClar::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of LiurnClar
//
{
	npc = Wizard_Liurn_Clar;
	SET_NPC_NAME( "[3012]Liurn Clar" );
	npc.InitialPos.X = 1599;
	npc.InitialPos.Y = 1250;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void LiurnClar::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of LiurnClar
//
{
CONSTANT PORTAL = 1;
CONSTANT PAYMENT = 2;
CONSTANT FORM  = 3;
CONSTANT SEND  = 4;
CONSTANT TPORT  = 5;
CONSTANT TOME_OF_VALOR = 6; 

int nTeleportFee = USER_LEVEL * 100;

InitTalk

Begin
INTL( 2410, "Can I help you?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2411, "I go by the name of Liurn Clar. Perhaps you have heard of me?")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2412, "I am a Warwizard. Usually, I \"teach\" \"spells\", but lately I have been "
"rather preoccupied with completing my great \"portal\".")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command(INTL( 10053, "CHAOS PORTAL"))
INTL( 10054, "The chaos portal is another project of mine. I am trying to build a portal that will bring me into "
"a parallel world. No one has ever been there but I swear I'll succeed eventually. Alas, for each "
"of my failed attempts, a \"chaos\" \"key\" is consumed and that is the reason why I need every key I can get. " 
"I won't let failure discourage me.")

Command(INTL( 10055, "CHAOS KEY")) 
INTL( 10056, "You can find a chaos key on a creature called \"Chaos\" \"Spawn\"." )
	  
Command(INTL( 10057, "CHAOS SPAWN"))
INTL( 10058, "They are located somewhere on \"Stoneheim\". I am not sure exactly where they are "
"located but you should begin your search near the fortress in the middle of the island.") 

Command(INTL( 6251, "STONEHEIM")) 
INTL( 11323, "I can \"send\" you to Raven's Dust but unfortunately, I have not completed the Stoneheim portal.")

CmdAND(INTL( 10774, "TOME"),INTL( 10775, "VALOR"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 0) 
	Conversation
	INTL( 10059, "Do not ask of me such services if you are not a Lightbringer.")
ELSE
	IF (CheckFlag(__QUEST_LIURN_TOME_OF_VALOR) == 0) 
		Conversation
		INTL( 10060, "If you want a Tome of Valor, I'll ask for some components and you'd better listen real good. First, I need a \"blank\" \"magical\" \"tome\" and a \"magic\" "
		"\"scripting\" \"kit\" that will allow me to scribe your Tome of Valor. Furthermore, I require an object in return "
		"for my services. I am currently working on a \"chaos\" \"portal\" and I need a \"chaos\" \"key\" for my portal.") 
		IF ((CheckItem(__OBJ_MAGIC_SCRIPTING_KIT) >= 1) && (CheckItem(__OBJ_CHAOS_KEY) >= 1) && (CheckItem(__OBJ_BLANK_MAGICAL_TOME) >= 1))
			Conversation
			INTL( 10061, " I see that you already have all the required components. Do you want me to scribe your Tome of Valor?")	
			SetYesNo(TOME_OF_VALOR) 
		ELSE
			Conversation
			INTL( 10062, " Come back when you gather all the components.")
		ENDIF
	ELSE
		IF (CurrentRound < (CheckFlag(__QUEST_TIMER_TOME_OF_VALOR)-72000)) // There was a server crash messing up the timer:
			IF (CurrentRound > 72000) // ...and server crashed more than an hour ago:
				Conversation
				INTL( 7534, "Okay, here's your precious Tome of Valor. I apologize for the length of time it required but "
				"arcane scribing has to be perfect. Now, I can get back to my portals.") 						       				
				PRIVATE_SYSTEM_MESSAGE(INTL( 7536, "Liurn gives you a Tome of Valor.")) 
				GiveItem(__OBJ_TOME_OF_VALOR)
				RemFlag(__QUEST_LIURN_TOME_OF_VALOR)
				RemFlag(__QUEST_TIMER_TOME_OF_VALOR)
			ELSE //...server crashed, but less than an hour ago:
				;int nTimeLeft = (72000 - CurrentRound) / (1 MINUTE);
				Conversation
				FORMAT(INTL( 5028, "Sorry, I made a mess and had to start all over. Please come back in %u minutes."),nTimeLeft)
			ENDIF
		ELSE // Server hasn't crashed, everything proceeding as normal...
			IF ((CheckFlag(__QUEST_TIMER_TOME_OF_VALOR) < (CurrentRound )) && (CheckFlag(__QUEST_LIURN_TOME_OF_VALOR) != 0))
				Conversation
				INTL( 7535, "Okay, here's your precious Tome of Valor. I apologize for the length of time it required but "
				"arcane scribing has to be perfect. Now, I can get back to my portals.") 		
				PRIVATE_SYSTEM_MESSAGE(INTL( 7536, "Liurn gives you a Tome of Valor.")) 
				GiveItem(__OBJ_TOME_OF_VALOR)
				RemFlag(__QUEST_LIURN_TOME_OF_VALOR)
				RemFlag(__QUEST_TIMER_TOME_OF_VALOR)
			ELSE
				;int nTimeLeft = ((CheckFlag(__QUEST_TIMER_TOME_OF_VALOR) - CurrentRound) / (1 MINUTE));
				Conversation
				FORMAT(INTL( 7537, "I haven't completed the Tome of Valor yet. Please come back in %u minutes."),nTimeLeft)
			ENDIF
		ENDIF
	ENDIF
ENDIF

YES(TOME_OF_VALOR)
	IF ((CheckItem(__OBJ_MAGIC_SCRIPTING_KIT) >= 1) && (CheckItem(__OBJ_CHAOS_KEY) >= 1) && (CheckItem(__OBJ_BLANK_MAGICAL_TOME) >= 1))
		Conversation
		INTL( 7538, "You've gathered all the components required? Then, I shall fulfill my part of the bargain. Even with the "
		"aid of the \"magic\" \"scripting\" \"kit\", it will take some time for me to complete the Tome of Valor. Come back "
		"in about one hour and I should have completed it by then.")
		PRIVATE_SYSTEM_MESSAGE(INTL( 7693, "You give the magic scripting kit, the chaos key and a blank magical tome to Liurn Clar.")) 
		TakeItem(__OBJ_MAGIC_SCRIPTING_KIT) 
		TakeItem(__OBJ_CHAOS_KEY) 
		TakeItem(__OBJ_BLANK_MAGICAL_TOME) 
		GiveFlag(__QUEST_LIURN_TOME_OF_VALOR , 1) 
		GiveFlag(__QUEST_TIMER_TOME_OF_VALOR, 1 HOURS TDELAY)
	ELSE
	Conversation
	INTL( 7539, "You're missing some components, I'm afraid. If you want me to scribe a Tome of Valor, I'll "
		"require a \"magic\" \"scripting\" \"kit\", a \"blank\" \"magical\" \"tome\". Also, as payment for my services, I want "
		"you to find a \"chaos\" \"key\" for me. Please come back when you've gathered everything.")	
	ENDIF

NO(TOME_OF_VALOR)
	Conversation
	INTL( 7540, "That is too bad. Come back if you change your mind.")

YesNoELSE(TOME_OF_VALOR) 
	Conversation
	INTL( 7541, "If you don't need a Tome of Valor afterall, simply answer 'no'.")
	YesNoELSE(TOME_OF_VALOR)

Command(INTL( 8103, "MAGIC SCRIPTING KIT"))
INTL( 10818, "There is a scholar I'v encountered once who was specialized in arcane scribing and probably "
"has a magic scripting kit or two lying around. I hope this helps you. Now, if you'll excuse me, I'll go back to my portals.") 

Command(INTL( 10819, "BLANK MAGICAL TOME"))
INTL( 10820, "I'm afraid I cannot help you as I'm all out of blank magical tomes.")									 

Command(INTL( 523, "ANNABELLE"))
INTL( 2406, "I wonder where she lives nowadays.")

Command(INTL( 2413, "CONDITION"))
""
IF (CheckFlag (__FLAG_HERMIT_TELEPORT) == 1)
	Conversation
	INTL( 2414, "Ah, well, yes, you didn't really expect me to do this just for free, right? "
	"Now, let's get down to business. You must first sign a few discharges and "
	"non-disclosure \"forms\". Then, there's the issue of \"payment\".")
ELSE
	Conversation
	INTL( 2415, "Conditions? What are you talking about?")
ENDIF

Command(INTL( 1046, "TELEPORT"))
""
IF (CheckFlag(__QUEST_ISLAND_ACCESS) >= 1)
	int nTeleportFee = 100 * USER_LEVEL
	Conversation
	FORMAT(INTL( 2416, "Well, seeing as you've already been to Raven's Dust, I can't very well pretend "
	"that I can't send you... I charge %u gold pieces for that trip, however. Will "
	"you pay the sum?"), nTeleportFee)
	SetYesNo(TPORT)
ELSE
	IF (CheckFlag(__QUEST_KALASTOR_MISSION) >= 1)
		Conversation
		INTL( 2417, "I truly wish I could help you with that, but if I help someone like you, I "
		"doubt Lord Sunrock will keep on sponsoring my research, and that would be the "
		"end of me, wouldn't it? But perhaps I can still help you. There's this orc leader "
		"somewhere northeast from here who has teleportation scrolls... Ask him.")
	ELSE
		Conversation
		INTL( 2418, "Indeed, teleportation is feasible. I've done it a few times myself... Requires "
		"a great deal of concentration and money, mind you, and the further you go, the "
		"more likely you are to suffer traumatic organic desynchronization--in other words, "
		"lots of pain.")
	ENDIF
ENDIF

YES(TPORT)
IF (Gold >= nTeleportFee)
	Conversation
	INTL( 2419, "Excellent. Here we go!")
	TakeGold(nTeleportFee)		
	TELEPORT( 1495, 2470, 0)
	BREAK
ELSE
	Conversation
	INTL( 2420, "You are not being honest. Come back when you truly have the money.")
ENDIF	

NO(TPORT)
Conversation
INTL( 2421, "All right, then.")

YesNoELSE(TPORT)
Conversation
INTL( 2422, "Huh?")

Command(INTL( 990, "THEORN"))
""
IF (CheckFlag (__FLAG_HERMIT_TELEPORT) == 1)
	Conversation
	INTL( 2423, "Theorn is known as the old hermit, a good friend of mine.") 
ELSE
	Conversation
	INTL( 2424, "I won't tell you who he really is if you don't know him personally.")
ENDIF

Command(INTL( 2425, "QUID PRO QUOS"))
""
IF (CheckFlag (__FLAG_QUID) == 1)
	Conversation
	INTL( 2426, "Learned a new word today, haven't you? How do you like feeling those mental "
	"gears at work? Ooh, I can almost hear the cogs turning in your head, here. "
	"Funny, that.")
ELSE
	Conversation
	INTL( 2427, "Hmm?")
ENDIF

Command(INTL( 793, "RAVEN'S DUST"))
""
IF (CheckFlag (__FLAG_HERMIT_TELEPORT) == 1)
	Conversation
	INTL( 2428, "Well, certainly, I could send you there, but there are certain \"conditions\" "
	"that must be met, certain \"quid\" \"pro\" \"quos\" to discuss...")
	GiveFlag(__FLAG_QUID, 1)
ELSE
	Conversation
	INTL( 2429, "I hear it's pretty over there at this time of year. When I've perfected my "
	"teleportation spell, I'll certainly go there for a well-deserved vacation.")
ENDIF

Command(INTL( 2430, "FORM"))
""
IF (CheckFlag (__FLAG_HERMIT_TELEPORT) == 1)

	IF ( (CheckFlag(__FLAG_FORM_SIGNED) == 1) && (CheckFlag(__FLAG_FEE_PAID) == 1) )
		Conversation
		INTL( 2431, "You have already gone through all the formalities. I am ready to \"send\" "
		"you on your way.")
	ELSEIF (CheckFlag(__FLAG_FORM_SIGNED) == 1)
		Conversation
		INTL( 2432, "You have signed the forms, but you still have to make your \"payment\".")
	ELSE
		Conversation
		INTL( 2433, "Um... Just sign here... and here... and there. What is this all about? Ah... "
		"ahem... Well, it's just that teleportation isn't exactly the safest procedure, "
		"you know... You might get, well... a little hurt in the process, if you get "
		"my meaning. Are you ready?")
		SetYesNo( FORM )
	ENDIF
ELSE
	Conversation
	INTL( 2434, "I don't think I know what you're talking about.")
ENDIF

YES ( FORM )
IF (CheckFlag(__FLAG_FEE_PAID) == 1)
	Conversation
	INTL( 2435, "Splendid! Let us \"send\" you on your way, then.")
	GiveFlag(__FLAG_FORM_SIGNED, 1)
ELSE
	Conversation	
	INTL( 2436, "Wonderful! Excellent. Now, would you care to make a full \"payment\" for the trip? "
	"I'd like to be paid.. *before* I \"send\" you on your way... just in case ya know?")
	GiveFlag(__FLAG_FORM_SIGNED, 1)
ENDIF

NO ( FORM )
Conversation
INTL( 2437, "I understand, but it's not like signing your testament... Heh heh!")

YesNoELSE ( FORM ) 
Conversation
INTL( 2438, "Come back when you have made up your mind.")

Command(INTL( 2439, "PAYMENT"))
""
IF (CheckFlag (__FLAG_HERMIT_TELEPORT) == 1)

	IF ( (CheckFlag(__FLAG_FORM_SIGNED) == 1) && (CheckFlag(__FLAG_FEE_PAID) == 1) )
		Conversation
		INTL( 2440, "You have already signed all the require forms and have paid your payment. We "
		"are ready to \"send\" you on your way to \"Raven's\" \"Dust\".")
	ELSEIF (CheckFlag(__FLAG_FEE_PAID) == 1)
		Conversation
		INTL( 2441, "You have already made the required payment, but you still have to fill the \"forms\".")
	ELSE
		Conversation				   
		FORMAT(INTL( 2442, "I'm not a rich man, my friend, and my innovative research in this domain cost me "
		"a great deal. I must ask that you make a payment of %u gold pieces before "
		"I can \"send\" you there. Is that agreeable?"), nTeleportFee) 
		SetYesNo( PAYMENT )
	ENDIF
ELSE
	Conversation
	INTL( 2443, "Hmmmm... I owe you money or something? Lemme check.... Hey! You're a fraud! I don't owe "
	"you anything!")
ENDIF

YES ( PAYMENT )

IF (Gold < nTeleportFee)
	Conversation
	FORMAT( INTL( 2444, "You do not have the required %u gold pieces!") , nTeleportFee)
ELSE
	IF (CheckFlag(__FLAG_FORM_SIGNED) == 1)
		Conversation
		INTL( 2445, "Splendid! Let us \"send\" you on your way, then.")
		GiveFlag(__FLAG_FEE_PAID, 1)
		TakeGold( nTeleportFee )
	ELSE
		Conversation
		INTL( 2446, "Smashing! Now, if you'll just fill these \"forms\"...")
		GiveFlag(__FLAG_FEE_PAID, 1)		
		TakeGold( nTeleportFee )
	ENDIF
ENDIF

NO ( PAYMENT ) 
Conversation
INTL( 2447, "No? I guess you're as poor as I am.")

YesNoELSE ( PAYMENT )
Conversation
INTL( 2448, "Clear your mind of any doubts and then come back to answer my question.")

Command(INTL( 2449, "SEND"))
""
IF (CheckFlag(__QUEST_ISLAND_ACCESS) >= 1)
	Conversation
	INTL( 7542, "If you want me to \"teleport\" you somewhere, just say so.")
ELSE
	IF (CheckFlag (__FLAG_HERMIT_TELEPORT) == 1)
		IF ( (CheckFlag(__FLAG_FORM_SIGNED) == 1) && (CheckFlag(__FLAG_FEE_PAID) == 1) )
			IF(USER_LEVEL >= 25)
				Conversation
				INTL( 2450, "Are you certain you do not wish to reconsider? I cannot offer you a refund, "
				"but perhaps you are having second thoughts... Still want to go?")
				SetYesNo ( SEND )
			ELSE
				Conversation
				INTL( 7161, "Hmm, on second thought, I don't think you are strong enough to survive the trip. As I have "
				"said before, I cannot reimburse you, but your trip will still be paid for. I suggest you return "
				"when you have gained a little more experience. {You} {must} {be} {at} {least} {level} {25} {to} "
				"{visit} {Raven's} {Dust.}")
			ENDIF
		ELSEIF (CheckFlag(__FLAG_FORM_SIGNED) == 1)
			Conversation
			INTL( 2451, "You still have to make the \"payment\".")
		ELSEIF (CheckFlag(__FLAG_FEE_PAID) == 1)
			Conversation
			INTL( 2452, "You will have to fill these \"forms\" before I can \"send\" you on your way.")
		ELSE
			Conversation
			INTL( 2453, "You will have to fufill certain \"conditions\" before I can send you on your way.")
		ENDIF
	ELSE
		Conversation
		INTL( 2454, "Send? Send you where? Oh, I see... but I'm sorry, my project is secret and "
		"I can't help you unless you know my good friend \"Theorn\"...")
	ENDIF
ENDIF

YES ( SEND )
Conversation
INTL( 3633, "Might hurt a bit... Very well... Here goes nothing...")
;target->SetHP( USER_MAXHP - (rnd.roll( dice( 1, 100 ) )), true ) 
IF (CheckFlag(__QUEST_ISLAND_ACCESS) == 0) 
	GiveFlag(__QUEST_ISLAND_ACCESS, 1)
ENDIF
TELEPORT( 1495, 2470, 0) 

NO ( SEND )
Conversation
INTL( 2456, "Very well, I understand. It takes great courage to face the unknown. Please "
"come back when you're ready.")

YesNoELSE ( SEND ) 
Conversation
INTL( 2448, "Clear your mind of any doubts and then come back to answer my question.")

Command(INTL( 2457, "PORTAL"))
INTL( 2458, "The portal is perhaps the most ambitious project anyone has ever undertaken. It is "
"designed to reduce the time it takes to travel between two towns. I have "
"encountered several problems, though, and I can't seem to figure out what's going "
"wrong. Because of this, I'm afraid I will not have enough time to teach you "
"any spells. At least, I have almost mastered the art of translocating a "
"living target to another place. Perhaps even as far as \"Raven's\" \"Dust\".")

Command(INTL( 2459, "ART"))
INTL( 2460, "The art of magic must be learned carefully. It takes a lot of intelligence, "
"patience and most of all, money to pay for your teachers!")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 2461, "Out of my face!")
BREAK

Command3(INTL( 700, "SPELL"),INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 7543, "Here are the spells I can teach you.")
CreateSkillList
	AddTeachSkill (__SPELL_FIRE_BOLT, 12, 20372)
	AddTeachSkill (__SPELL_FIREBALL, 14, 29457)
SendTeachSkillList

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 2485, "Thank you for passing by.") BREAK

Default
INTL( 2486, "I do not have time for this.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void LiurnClar::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
     TEACH_SKILL(__SPELL_FIRE_BOLT, 12, 20372)
     TEACH_SKILL(__SPELL_FIREBALL, 14, 29457)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE

#pragma hdrstop
#include "OldHermit.H"

OldHermit::OldHermit()
{}

OldHermit::~OldHermit()
{}

extern NPCstructure::NPC Old_Bald_Hermit;

void OldHermit::Create( void )
{
	npc = ( Old_Bald_Hermit );
	SET_NPC_NAME( "[2905]Old Hermit" );
	npc.InitialPos.X = 2813; 
	npc.InitialPos.Y = 686;
	npc.InitialPos.world = 0;
}


void OldHermit::OnTalk( UNIT_FUNC_PROTOTYPE )

{
InitTalk

Begin
INTL( 975, "So... You've come to seek an old man in his haven of peace... You must be "
"truly desperate.")
IF (CheckFlag(__FLAG_TALKED_TO_HERMIT) == 0)
	GiveFlag(__FLAG_TALKED_TO_HERMIT, 1)
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 976, "You can call me the \"Old\" \"Hermit\".") 

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 977, "That's none of your business.")

Command(INTL( 556, "OLD HERMIT"))
INTL( 978, "Yes... That would be me. Please be on your way and trouble me no more.")

Command2(INTL( 979, "GUIDANCE"),INTL( 554, "HELP") )
INTL( 980, "Hmpf... They shun me, then seek me out... *sigh* Very well, what would you "
"need from me?")

Command2(INTL( 496, "TEACH"),INTL( 502, "TRAIN"))
INTL( 981, "Read my lips, young pup: N*O*W*A*Y. I'm done with teaching. Seek a tutor "
"elsewhere.")

Command(INTL( 982, "PROVE"))
INTL( 983, "I know not of any way to prove to me that you are a good person, but I "
"trust my \"daughter\" and her alone. If she says you are trustworthy, "
"then I will \"trust\" you. If not, then begone and stay gone.")

Command(INTL( 984, "DAUGHTER"))
INTL( 985, "She lives in \"Windhowl\". Now go and leave me be.")

Command(INTL( 523, "ANNABELLE"))
INTL( 986, "You know of her? Few people are aware that she has Elven ancestors... "
"A very long-lived, comely lass, she was.")

Command2(INTL( 987, "ELVES"),INTL( 988, "ELF"))
INTL( 989, "Ah, wish that I could have lived in the old days, that I could have seen "
"them, walked with them. What a grand time I would have had. But they be "
"long gone, now, cursed by the gods and all but extinct.")

Command2(INTL( 990, "THEORN"),INTL( 991, "LEMNEARAN"))
INTL( 992, "Hmmm... So you know my real name. That is not bad for one so young as you "
"are. But you'll have to do better than that if you want to impress me.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 993, "Raven's Dust is the island located to the south.")

Command2(INTL( 994, "KINGDOM"),INTL( 753, "GOLDMOON"))
INTL( 995, "The kingdom of Goldmoon regroups the island of \"Arakas\" and \"Raven's\" \"Dust\".")

Command2(INTL( 513, "LIGHTHAVEN"),INTL( 514, "WINDHOWL"))
INTL( 996, "Lighthaven and Windhowl are the two towns located on this island.")

Command(INTL( 515, "ARAKAS"))
INTL( 997, "Arakas? If you do not know where it is, lemme tell you this my friend.. "
"you're LOST! *cackle*")

Command(INTL( 998, "SILVERSKY"))
INTL( 999, "Silversky is a small town located on \"Raven's\" \"Dust\" near \"Theodore\"'s castle.")

Command(INTL( 754, "THEODORE"))
INTL( 1000, "King Theodore? I hear he cannot do anything other than sleep.")

Command4(INTL( 509, "BALORK"),INTL( 543, "CURSE"),INTL( 510, "BRAND"),INTL( 1001, "MARK"))
""
IF (CheckFlag(__BALORK_BRAND) == 0)
	Conversation
	INTL( 3640, "Seeing as you bear no such curse upon you, this is hardly a concern of yours, is it?")
ELSEIF (CheckFlag(__FLAG_HERMIT_TRUST) == 1) 
	Conversation				 /* With Trust Flag */
	INTL( 1002, "Yes, that's right. You did mention that last time you were here, didn't "
	"you? A tragedy, really... No, I really mean that. And there is no cure for you "
	"on this island. You will have to seek \"High\" \"Priestess\" \"Delilah\", daughter "
	"of \"King\" \"Theodore\" \"XIII\".")
ELSEIF (CheckFlag(__FLAG_ANNABELLE) == 1) 
	Conversation /* w/ Annabelle flag */
	INTL( 1003, "I see... And who sends you to me? Annabelle, you say? Pfah! Now I know you "
	"lie! Annabelle the Blessed is long dead! I do not \"trust\" you!")
ELSE
	Conversation			 /* w/o Annabelle flag */
	INTL( 1004, "I'm sorry to hear that. That's terrible news indeed. *yawn* Anything else?")
ENDIF

Command2(INTL( 1005, "DELILAH"),INTL( 1006, "HIGH PRIEST"))
""
IF (CheckFlag(__FLAG_HERMIT_TRUST) == 1) 
	Conversation
	INTL( 1007, "Easier said that done, I'm afraid she lives on \"Raven's\" \"Dust\", not on "
	"this... But one as resourceful as you are should not be deterred by "
	"hundreds of leagues of water... Perhaps you could \"swim\" there...")
ELSE
	Conversation
	INTL( 1008, "You speak nonsense. Clarify your thoughts and try again.")
ENDIF

Command(INTL( 1009, "SWIM"))
""
IF (CheckFlag(__FLAG_HERMIT_TRUST) == 1) 
	Conversation
	INTL( 1010, "Just kidding, my friend. Must you take everything so seriously? "
	"Er... Don't answer that. You probably should. Take everything seriously, "
	"I mean. You youngsters are so flighty... Anyway, swimming's not really "
	"an option. Perhaps a \"boat\"?")
ELSE
	Conversation
	INTL( 1008, "You speak nonsense. Clarify your thoughts and try again.")
ENDIF

Command(INTL( 1011, "BOAT"))
""
IF (CheckFlag(__FLAG_HERMIT_TRUST) == 1) 
	Conversation
	INTL( 1012, "Nah, let's strike that out, boats aren't a very good idea at this time of "
	"year. Plus, there's the pirates... How about \"flying\" there?")
ELSE
	Conversation
	INTL( 1008, "You speak nonsense. Clarify your thoughts and try again.")
ENDIF

Command(INTL( 1013, "FLYING"))
""
IF (CheckFlag(__FLAG_HERMIT_TRUST) == 1) 
	Conversation
	INTL( 1014, "No, wait, that's not good either... The giant rocs are all but extinct, and "
	"Dwarvinci's flying machine is nothing more than a pipedream. Even that feeble-"
	"minded thief who thinks he had flying boots is way off the track. I guess "
	"it would take a miracle to take you to \"Raven's\" \"Dust\"... Too bad.")
ELSE
	Conversation
	INTL( 1008, "You speak nonsense. Clarify your thoughts and try again.")
ENDIF

Command(INTL( 1015, "MIRACLE"))
""
IF (CheckFlag(__FLAG_HERMIT_TRUST) == 1) 
	Conversation
	INTL( 1016, "Asking for a miracle, hmm? Well, I do not know about that, but have you "
	"considered \"wizardry\"? Perhaps that would work.")
ELSE
	Conversation
	INTL( 1008, "You speak nonsense. Clarify your thoughts and try again.")
ENDIF

Command(INTL( 632, "TRUST"))
""
IF (CheckFlag(__BALORK_BRAND) == 0)
	Conversation
	INTL( 3641, "I fail to see why you would need the trust of an old man.")
ELSEIF (CheckFlag(__FLAG_HERMIT_TRUST) > 0)
	Conversation
	INTL( 1017, "I believe we've already gone through this, haven't we? Just ask me what you need "
	"to know.")
ELSEIF ((CheckItem(__OBJ_RING_OF_TRUST) >= 1) && (CheckFlag(__FLAG_RING_OF_TRUST_GIVEN) == 1) && (CheckFlag(__FLAG_HERMIT_TRUST) != 1))
	Conversation
	INTL( 1018, "Aaah! What a worthy fellow we have here! Pardon my mocking words, I see so many people "
	"calling themselves worthy, these days... I will take my daughter's ring of trust in "
	"exchange for this amulet of precision. {You} {have} {been} {awarded} "
	"{4000} {experience} {points.} So tell me, now... What is it that you want from me ?")
	GiveFlag(__FLAG_HERMIT_TRUST, 1)
	TakeItem(__OBJ_RING_OF_TRUST) 
	GiveItem(__OBJ_AMULET_OF_PRECISION) 
	GiveXP(4000) 
ELSEIF (CheckFlag(__FLAG_RING_OF_TRUST_GIVEN) == 1) // Received (but lost) ring from Mirak Nira
	Conversation
	INTL( 1019, "You have proven yourself trustworthy, I hear, yet you lost the simple ring "
	"my daughter gave you as a token for your bravery. A pity. But you have "
	"proven yourself worthy of my help nonetheless.")
	GiveFlag(__FLAG_HERMIT_TRUST, 1)
	GiveXP(1000)
ELSEIF (CheckItem(__OBJ_RING_OF_TRUST) >= 1) // Has ring, but didn't do the quest.
	Conversation
	INTL( 1020, "So you stole or bought one of my daughter's ring? Big deal! I won't be fooled that easily. "
	"Earn my \"daughter\"'s trust and we will speak again.")
ELSE // Has nothing.
	Conversation
	INTL( 1021, "Trust is earned through deeds, not just words. That is the basis of \"worth\". You may come "
	"to understand these words, some day.")
ENDIF

Command(INTL( 1022, "WIZARDRY"))
""
IF (CheckFlag(__FLAG_HERMIT_TRUST) == 1) 
	Conversation
	INTL( 1023, "*laugh* Excellent! That's the spirit! Heh heh.. I like someone with a sense "
	"of adventure. If you're not afraid of dying, you could try teleportation. "
	"Speak to Liurn Clar, a wizard in \"Windhowl\". He needs test subjects. "
	"*grin* Now go, I'm tired and your company bores me.")
	GiveFlag(__FLAG_HERMIT_TELEPORT, 1)
ELSE
	Conversation
	INTL( 1008, "You speak nonsense. Clarify your thoughts and try again.")
ENDIF

Command(INTL( 1024, "WORTH"))
INTL( 1025, "Being worthy is great achievement, one that may one day save humankind. "
"Would you not agree? But no matter, youngsters such as you have no care "
"for an old man's \"drivel\".")

Command(INTL( 1026, "DRIVEL"))
INTL( 1027, "So you would have me speak of this nonetheless? Don't you have something "
"better to do with your time. Methinks you should find another way to "
"\"prove\" your \"worth\".")

Command(INTL( 1028, "MIRAK NIRA"))
""
IF (CheckFlag(__FLAG_HERMIT_TRUST) == 1) 
	Conversation
	INTL( 1029, "Is that her new name? It stinks! *cough* Oh, don't tell her that. Eh Eh!")
ELSE
	Conversation
	INTL( 1008, "You speak nonsense. Clarify your thoughts and try again.")
ENDIF

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1030, "Don't get lost on your way back home.")
BREAK

Default
INTL( 1008, "You speak nonsense. Clarify your thoughts and try again.")

EndTalk
}


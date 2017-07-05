#pragma hdrstop
#include "Vargus.h"

Vargus::Vargus()
{}

Vargus::~Vargus()
{}

extern NPCstructure::NPC VargusNPC;

void Vargus::Create( ){
	npc = VargusNPC;
	SET_NPC_NAME( "[10933]Vargus");
	npc.InitialPos.X = 582;		   
	npc.InitialPos.Y = 233;
	npc.InitialPos.world = 0;
}

void Vargus::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT ReceiveBlood = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_USER_HAS_BLOOD_OF_OGRIMAR) == 0 && CheckItem(__OBJ_DEMONIC_BLOOD) >= 3 && CheckItem(__OBJ_FOUL_POTION) >= 2 && CheckItem(__OBJ_BLACK_WIDOW_VENOM) >= 5)
	Conversation
	INTL( 9090, "What's that you say? How can you possibly have gathered everything I asked? Oh well, I guess I must hold to my end of the "
	"bargain. Tell me then, is it still your desire to receive the Blood of Ogrimar?")
	SetYesNo(ReceiveBlood)
ELSEIF(CheckFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN) == 1)
	GiveFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN, 2)
	Conversation
	INTL( 9091, "Oh?! A visitor? Ahh er, I will be with you in a few moments.")
	BREAK
ELSE
	IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
		Conversation
		INTL( 9092, "Ahh yes, welcome my friend. What can I do for you?")
	ELSE
		Conversation
		INTL( 9093, "Yes? What do you want from me?")
	ENDIF
ENDIF

YES(ReceiveBlood)
	IF(CheckItem(__OBJ_DEMONIC_BLOOD) >= 3 && CheckItem(__OBJ_FOUL_POTION) >= 2 && CheckItem(__OBJ_BLACK_WIDOW_VENOM) >= 5)
		TakeItem(__OBJ_DEMONIC_BLOOD)
		TakeItem(__OBJ_DEMONIC_BLOOD)
		TakeItem(__OBJ_DEMONIC_BLOOD)
		TakeItem(__OBJ_FOUL_POTION)
		TakeItem(__OBJ_FOUL_POTION)
		TakeItem(__OBJ_BLACK_WIDOW_VENOM)
		TakeItem(__OBJ_BLACK_WIDOW_VENOM)
		TakeItem(__OBJ_BLACK_WIDOW_VENOM)
		TakeItem(__OBJ_BLACK_WIDOW_VENOM)
		TakeItem(__OBJ_BLACK_WIDOW_VENOM)
		GiveItem(__OBJ_BLOOD_OF_OGRIMAR)
		GiveFlag(__FLAG_USER_HAS_BLOOD_OF_OGRIMAR, 1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9094, "You give Vargus 3 vials of demonic blood."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9095, "You give Vargus 2 foul potions."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9096, "You give Vargus 5 vials of nephil spider venom."))
		Conversation
		INTL( 9097, "Yes, this is what I asked for I suppose. Here you are then, as promised.")
		PRIVATE_SYSTEM_MESSAGE(INTL( 9098, "Vargus gives you the Blood of Ogrimar."))
	ELSE
		Conversation
		INTL( 9099, "What manner of trickery is this? You do not have what I require.")
	ENDIF
NO(ReceiveBlood)
	Conversation
	INTL( 9100, "Oh really? I'm glad, err, sorry to hear that. I'm sure you'll find some other use for all these great things though.")
YesNoELSE(ReceiveBlood)
	Conversation
	INTL( 9101, "Well, hurry up before I change my mind. Do you still want the Blood of Ogrimar or not?")
	SetYesNo(ReceiveBlood)

Command(INTL( 8931, "BLOOD OF OGRIMAR"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_BLOOD_OF_OGRIMAR) == 1)
		Conversation
		INTL( 9102, "I have already given you the Blood of Ogrimar, what else do you want from me?")
	ELSE
		IF(CheckFlag(__FLAG_USER_HAS_SKULL_OF_OGRIMAR) == 1)
			Conversation
			INTL( 9103, "Yes, I am in possession of the Blood of Ogrimar. In fact, I have several other relics of power although I seem to "
			"have misplaced one of them. I would be willing to part with the blood, in exchange for a few \"choice\" \"items\".")
		ELSE
			Conversation
			INTL( 9104, "Yes, I am in possession of the Blood of Ogrimar. In fact, I have several other relics of power in my collection. I would "
			"be willing to part with the blood, in exchange for a few \"choice\" \"items\".")
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

Command(INTL( 9106, "CHOICE ITEMS"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9107, "I have much need for poisons and toxins of all kinds. If you could bring me 3 vials of \"demonic\" \"blood\", 2 \"foul\" \"potions\" "
	"and 5 vials of \"nephil\" \"spider\" \"venom\", I would be obliged to give you the Blood of Ogrimar.")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF
	
Command(INTL( 8733, "DEMONIC BLOOD"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9108, "Well, I don't quite know exactly where to find some, but I would imagine it is something used in \"tribal\" \"magic\".")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

Command(INTL( 9109, "TRIBAL MAGIC"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9110, "Tribal magic is usually used by primitive races such as orcs and skraugs.")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

Command(INTL( 9111, "FOUL POTION"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9112, "I have heard tell that a powerful necromancer has the knowledge to create such atrocious concoctions. I cannot say who or where "
	"this person is for the simple reason that I do not know.")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

Command(INTL( 9113, "NEPHIL SPIDER VENOM"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9114, "This isn't the actual venom of a nephil spider mind you. It is actually the name of a very deadly man-made poison. Julian had "
	"a very great potential in the field of alchemy the last time I saw him. Perhaps he could help you with this task.")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

CmdAND(INTL( 10231, "BONES"), INTL( 8606, "OGRIMAR"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 1)
	Conversation
	INTL( 10232, "Hmm, you wish to know about the Bones of Ogrimar, do you? There is only so much I can tell you. The Bones are a powerful "
	"relic that must be kept hidden from the hands of the common man. If a commoner were ever to find them, he would be forever "
	"changed by my master's powerful taint. For this reason, the Bones were placed deep within a cavern far to the east of here. "
	"There is one who knows more on this subject in the town of Stonecrest who might be able to help you.")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
ENDIF

Command(INTL( 9115, "JULIAN"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9116, "I believe you can find him in the outskirts of the town of Stonecrest, or possibly even inside.")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

Command2(INTL( 483, "NAME"), INTL( 485, "WHO ARE YOU"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9117, "I am known as Vargus, dark bishop of Ogrimar.")
ELSE
	Conversation
	INTL( 9118, "I am really not inclined to tell my name to someone like you.")
ENDIF

Command2(INTL( 489, "WORK"), INTL( 488, "WHAT DO YOU"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9119, "I am here to care for the \"temple\".")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

Command(INTL( 1365, "TEMPLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9120, "This temple is dedicated to the great Ogrimar.")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

Command(INTL( 8606, "OGRIMAR"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9121, "The Dark Lord of the night has many followers, but I am one of his most devoted servants.")
ELSE
	Conversation
	INTL( 9105, "I really think you should leave now.")
	BREAK
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9122, "I will not tolerate such language within these temple walls!")
ELSE
	Conversation
	INTL( 9123, "Don't think that because I am a priest I will hesitate to kill you!")
ENDIF
FIGHT

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9124, "I bid you farewell, and a safe journey.")
ELSE
	Conversation
	INTL( 9125, "Good riddance to you then.")
ENDIF
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
		Conversation
		INTL( 9126, "Followers of Ogrimar, unite!")
	ELSE
		Conversation
		INTL( 9127, "Your kind is not welcome here. Leave now.")
		BREAK
	ENDIF
ELSE
	IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
		Conversation
		INTL( 9128, "Praise his majesty the Dark Lord!")
	ELSE
		Conversation
		INTL( 9129, "You have outlasted your welcome, if you ever had any.")
		BREAK
	ENDIF
ENDIF

EndTalk
}



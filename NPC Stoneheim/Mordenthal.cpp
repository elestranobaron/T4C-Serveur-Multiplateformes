#pragma hdrstop
#include "Mordenthal.h"

Mordenthal::Mordenthal()
{}

Mordenthal::~Mordenthal()
{}

extern NPCstructure::NPC MordenthalNPC;

void Mordenthal::Create( ){
	npc = MordenthalNPC;
	SET_NPC_NAME( "[10899]Sir Mordenthal" );
	npc.InitialPos.X = 342;
	npc.InitialPos.Y = 248;
	npc.InitialPos.world = 0;
}

void Mordenthal::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT FOLLOWER = 2;
CONSTANT Allegiance = 3;	
CONSTANT WhoToldUserAboutBones = 4;
CONSTANT ASSEMBLE = 5;	
CONSTANT TakeRings = 6;
CONSTANT TakeGrimBlades = 7;
CONSTANT UpholdOgrimar = 8;
CONSTANT COLOR = 35;	

InitTalk

Begin
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 2)
	Conversation
	INTL( 10228, "What have you there? Well well, what a peculiar ring that is. Oh, I'm afraid I don't know anything about it, but perhaps "
	"I know someone who does. I once knew a man who had a knack at identifying strange objects such as this. His name was Drardos. "
	"Why don't you go look for him and ask him about the ring?")
	GiveFlag(__FLAG_QUEST_FOR_BONES, 3)
ELSE
	Conversation
	INTL( 5805, "What do you want?")
ENDIF
IF(CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) < 5)
	GiveFlag(__FLAG_TIMES_ASKED_FOR_BONES, 0)
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9470, "Whence I came, they called me Sir Mordenthal.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 9471, "A \"dark\" \"knight\" I am, and mayhaps something more.")

Command(INTL( 9472, "DARK KNIGHT"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9473, "I was once foremost amongst the great generals in \"Ogrimar\"'s army.")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 8584, "DWINDLED"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9475, "Since the past few thousand years, there has been one whose power has grown steadily. Since a balance must be kept, "
	"what is gained must be lost somewhere else. Fortunately, there is \"another\" whose power has also been decreasing.")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

CmdAND(INTL( 8039, "RING"),INTL( 8040, "LION"))
""
IF(USER_KARMA > 100)
	Conversation
	INTL( 8587, "I would rather not discuss this with you, if you don't mind. Individuals of your ilk disgust me.")
ELSE
	IF (CheckItem(__OBJ_RING_OF_THE_LION)<3)
		Conversation
		INTL( 9476, "Those rings would help raise the courage and morale of my warriors. Should you have three to spare, "
		"I would reward you handsomely.")
	ELSE
		Conversation
		INTL( 9477, "I see you have brought me three Rings of the Lion! Shall you trade them for a reward?")
		SetYesNo(TakeRings)
	ENDIF
ENDIF

YES(TakeRings)
	IF (CheckItem(__OBJ_RING_OF_THE_LION) < 3)
		Conversation
		INTL( 9478, "Something odd has happened, you suddenly do not have enough rings on you.")
	ELSE
		Conversation
		INTL( 9479, "The forces of evil rejoice at your decision! ")
		FOR(0,3)
			TakeItem(__OBJ_RING_OF_THE_LION)
		ENDFOR
		IF (rnd.roll(dice(1,2))==1)
			Conversation
			INTL( 9480, "Here's a \"Great\" \"Axe\" \"of\" \"the\" \"Crow\" for your troubles.")
			GiveItem(__OBJ_GREAT_AXE_OF_THE_CROW)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9481, "You receive a Great Axe of the Crow.")) 
		ELSE
			Conversation
			INTL( 9482, "Here's a \"Cloak\" \"of\" \"Armageddon\" for your troubles.")
			GiveItem(__OBJ_CLOAK_OF_ARMAGEDDON)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9483, "You receive a Cloak of Armageddon.")) 
		ENDIF
		;int nExpReward = USER_LEVEL*6000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF

NO(TakeRings)
	Conversation
	INTL( 8596, "Needless to say, I am disappointed.")

YesNoELSE(TakeRings)
	Conversation
	INTL( 9484, "I didn't quite get that. Did you say \"yes\" or \"no\"?")
	SetYesNo(TakeRings)

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 9485, "If you would assist me, I could use some \"Rings\" \"of\" \"the\" \"Lion\". King Aedenas Gravesoul, ruler of the "
"Centaurs, should have some, but you might need to give him something in return.")

Command(INTL( 9486, "ANOTHER"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9487, "Artherk, the god of Peace, curse his name, has also been affected by the uprise of the \"Dark\" \"One\".")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

CmdAND3(INTL( 7988, "GRIM"),INTL( 7985, "BLADE"),INTL( 7989, "WAR"))
""
IF(CheckItem(__OBJ_GRIM_BLADE_OF_WAR) >= 4)
	Conversation
	INTL( 9488, "I have a dire need for such blades. Would you part with yours in exchange for a \"Dark\" "
	"\"Gem\"?")
	SetYesNo(TakeGrimBlades)
ELSE
	Conversation
	INTL( 9489, "Should you have a foursome of these precious blades, I will take them from you and reward "
	"you with a \"Dark\" \"Gem\".")
ENDIF

YES(TakeGrimBlades)
	IF(CheckItem(__OBJ_GRIM_BLADE_OF_WAR) < 4)
		Conversation
		INTL( 9490, "What treachery is this? How dare you waste my time!")
		FIGHT
	ELSE
		Conversation
		INTL( 9479, "The forces of evil rejoice at your decision! ")
		FOR(0,4)
			TakeItem(__OBJ_GRIM_BLADE_OF_WAR)
		ENDFOR
		IF((rnd.roll(dice(1,100)) == 100) AND (CheckItem(__OBJ_DARK_GEM) >= 25))
			Conversation
			INTL( 9491, "Since I am feeling particularly generous today, here is a \"Dark\" \"Gemblade\"!")
			GiveItem(__OBJ_DARK_GEMBLADE)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9492, "You receive a Dark Gemblade."))
			;int nExpReward = USER_LEVEL*5000;
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
			GiveXP(nExpReward)
		ELSE
			Conversation
			INTL( 9493, "Here is your prize.")
			GiveItem(__OBJ_DARK_GEM)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9494, "You receive a Dark Gem."))
			;int nExpReward = USER_LEVEL*1500;
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
			GiveXP(nExpReward)
		ENDIF
	ENDIF

NO(TakeGrimBlades)
	Conversation
	INTL( 9495, "I have half a mind to take the blades from you anyway, but I have no time to kill "
	"you just now. Be on your way, then.")

YesNoELSE(TakeGrimBlades)
	Conversation
	INTL( 9496, "I do not understand what you said. \"Yes\" or \"no\"?")
	SetYesNo(TakeGrimBlades)

CmdAND(INTL( 1183, "DARK"),INTL( 9497, "GEMBLADE"))
INTL( 9498, "Such artifacts are very rare, very hard to find, and they are useless if you do not carry "
"with you a high number of \"Dark\" \"Gems\".")

CmdAND(INTL( 1183, "DARK"),INTL( 4639, "GEM"))
INTL( 9499, "While it does little in and of itself, this item is a vital source of power for the \"Dark\" "
"\"Gemblade\" artifact.")

Command(INTL( 8601, "DARK ONE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9500, "The one I am referring to is none other than \"Makrsh\" \"P'tangh\".")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 738, "MAKRSH"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9501, "Most wretched of men is he, the Dark One will stop at nothing to gain whatever power he can have. His strength is so "
	"great that it rivals that of the \"gods\"!")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 9502, "GODS"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9503, "So profound is their need that the gods are hard-pressed to take action. My god is searching for \"followers\" to help him "
	"vanquish this threat.")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 9504, "FOLLOWERS"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9505, "You are already one of my lord's followers. You should seek to \"uphold\" him in all you do.")
ELSE
	IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
		Conversation
		INTL( 9506, "Without knowing it, you have already been helping to further my lord's cause. Were you to become one of his \"servants\", I am certain "
		"you would acquire much fame and renown.")
	ELSE
		Conversation
		INTL( 9474, "That is no concern of yours, light-dweller!")
	ENDIF
ENDIF

Command(INTL( 4532, "SERVANT"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9507, "You are already one of my lord's followers.")
ELSE
	IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
		Conversation
		INTL( 9508, "To become a servant of Ogrimar, you need only swear an oath. Be advised that this oath will be bound by your life, and should you "
		"ever fail to abide by it, your life will be forfeit and your soul will forever be tortured by him. Do you still wish to become a "
		"follower of Ogrimar?")
		SetYesNo(FOLLOWER)
	ELSE
		Conversation
		INTL( 9474, "That is no concern of yours, light-dweller!")
	ENDIF
ENDIF

YES(FOLLOWER)
	Conversation
	INTL( 9509, "Then you need only swear allegiance to him and you will be bound forever.")
	;YesNo = Allegiance;
NO(FOLLOWER)
	Conversation
	INTL( 9510, "I see, then I have wasted my time in talking to you.")
	BREAK
YesNoELSE(FOLLOWER)
	Conversation
	INTL( 9511, "Well, do you wish to become a follower of Ogrimar or not?")
	SetYesNo(FOLLOWER)

;} else if( ( msg.Find( INTL( 9512, "I SWEAR ALLEGIANCE TO OGRIMAR") ) != -1 ) && YesNo == Allegiance) {;YesNo = 0;
Conversation
INTL( 9513, "Yes, it will do. Well, now that you are a follower, would you like to know how you can \"uphold\" your lord?")
GiveFlag(__FLAG_FOLLOWER_OF_OGRIMAR, 1)
SetYesNo(UpholdOgrimar)

;} else if(YesNo == Allegiance) {;
GiveFlag(__FLAG_FAILED_TO_SWEAR, CheckFlag(__FLAG_FAILED_TO_SWEAR) + 1)
IF(CheckFlag(__FLAG_FAILED_TO_SWEAR) != 5)
	Conversation
	INTL( 9514, "I will accept no other oath. You must swear allegiance to Ogrimar, and no other god.")
ELSE
	Conversation
	INTL( 9515, "Urgh! Must I do everything for you? Just say '\"I\" \"swear\" \"allegiance\" \"to\" \"Ogrimar\"' and be done with it!")
	GiveFlag(__FLAG_FAILED_TO_SWEAR, 0)
ENDIF

YES(UpholdOgrimar)
	Conversation
	INTL( 9517, "I will not lie to you by telling you that your task is none other than \"vanquishing\" the Dark One himself.")
NO(UpholdOgrimar)
	Conversation
	INTL( 10780, "If you will not uphold the lord of the dark, then what use are you?")
YesNoELSE(UpholdOgrimar)
	Conversation
	INTL( 10781, "Well, would you like to know how you can uphold your lord or not?")
	SetYesNo(UpholdOgrimar)

Command(INTL( 9516, "UPHOLD"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9517, "I will not lie to you by telling you that your task is none other than \"vanquishing\" the Dark One himself.")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 8630, "VANQUISH"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9518, "Oh never fear, there are many others that have been charged with the same task as you. You will of course have to gather "
	"much power before you are capable of confronting him. You must first find the location of his \"stronghold\" and that alone will "
	"prove to be a most difficult endeavor. Nevertheless, I'm certain that if you strive hard enough to better yourself, "
	"you will prevail.")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 8633, "STRONGHOLD"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9519, "There is one who would know of its location, but he cannot be found on this plane of existence. He is known as the \"oracle\".")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9520, "The oracle resides in his own realm, a place rumored to be nearly inaccessible. To reach him, you will need the \"Key\" \"of\" "
	"\"Ogrimar\".")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 9521, "KEY OF OGRIMAR"))
""
IF(CheckFlag(__FLAG_USER_HAS_KEY_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9522, "You have the key now, it is up to you to use it.")
ELSEIF(CheckItem(__OBJ_SKULL_OF_OGRIMAR) >= 1)
	IF(CheckItem(__OBJ_BLOOD_OF_OGRIMAR) >= 1)
		IF(CheckItem(__OBJ_BONES_OF_OGRIMAR) >= 1)
			Conversation
			INTL( 9523, "You have done well to gather all the pieces of the key. I commend you for your services. I assure you that your faith will "
			"be much rewarded in the end. Well now, if there is nothing further, I shall attempt to merge the three parts together. "
			"Is it your wish for me to do so?")
			SetYesNo(ASSEMBLE)
		ELSE
			Conversation
			INTL( 9524, "You seem to be missing a crucial part of the key. Without the \"Bones\" \"of\" \"Ogrimar\", I'm afraid there can be no key.")
		ENDIF
	ELSE
		Conversation
		INTL( 9525, "You have only found the Skull of Ogrimar. I cannot help you until you get the \"Blood\" \"of\" \"Ogrimar\" and the \"Bones\" \"of\" \"Ogrimar\".")
	ENDIF
ELSE
	IF(CheckItem(__OBJ_BLOOD_OF_OGRIMAR) >= 1)
		Conversation
		INTL( 9526, "You have only found the Blood of Ogrimar. I cannot help you until you get the \"Skull\" \"of\" \"Ogrimar\" and the \"Bones\" \"of\" \"Ogrimar\".")
	ELSEIF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
		Conversation
		INTL( 9527, "The Key of Ogrimar is needed to gain entry into the \"heart\" \"of\" \"destiny\".")
	ELSE
		Conversation
		INTL( 9474, "That is no concern of yours, light-dweller!")
	ENDIF
ENDIF

YES(ASSEMBLE)
	IF(CheckItem(__OBJ_SKULL_OF_OGRIMAR) >= 1)
		IF(CheckItem(__OBJ_BLOOD_OF_OGRIMAR) >= 1)
			IF(CheckItem(__OBJ_BONES_OF_OGRIMAR) >= 1)
				TakeItem(__OBJ_SKULL_OF_OGRIMAR)
				TakeItem(__OBJ_BLOOD_OF_OGRIMAR)
				TakeItem(__OBJ_BONES_OF_OGRIMAR)
				GiveItem(__OBJ_KEY_OF_OGRIMAR)
				GiveFlag(__FLAG_USER_HAS_KEY_OF_OGRIMAR, 1)
				Conversation
				INTL( 9528, "Very well, I shall begin the ritual to combine the three parts at once. ")
				PRIVATE_SYSTEM_MESSAGE(INTL( 9529, "You give the Skull, Blood and Bones of Ogrimar to Mordenthal."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 9530, "Mordenthal begins to utter some strange incantations..."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 9531, "and the three parts converge into one to form the Key of Ogrimar."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 9532, "Mordenthal gives you the Key of Ogrimar."))
			ELSE
				Conversation
				INTL( 9533, "You are a fool if you think to deceive me.")
			ENDIF
		ELSE
			Conversation
			INTL( 9533, "You are a fool if you think to deceive me.")
		ENDIF
	ELSE
		Conversation
		INTL( 9533, "You are a fool if you think to deceive me.")
	ENDIF
NO(ASSEMBLE)
	Conversation
	INTL( 9534, "Why not? There is nothing else you can do with these objects.")
YesNoELSE(ASSEMBLE)
	Conversation
	INTL( 9535, "Do you want me to assemble the parts to create the Key of Ogrimar?")
	SetYesNo(ASSEMBLE)

Command(INTL( 8656, "HEART OF DESTINY"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9536, "You may have seen it while wandering. It is a great \"fortress\" surrounded by a body of water.")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 8659, "FORTRESS"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9537, "I say so because there is no apparent point of entry. However, with the Key of Ogrimar one may be able to enter the \"portal\" located "
	"inside the \"Chamber\" \"of\" \"Providence\".")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 2457, "PORTAL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) == 1)
		Conversation
		INTL( 9538, "Now that you have the key, all that is left is to find the Chamber of Providence and enter the portal.")
	ELSE
		Conversation
		INTL( 9539, "I do not believe you can use the portal without first acquiring the key.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 8665, "CHAMBER OF PROVIDENCE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) == 1)
		Conversation
		INTL( 9540, "The chamber is located on a well hidden island to the east near the Sunken Woods forest. There lies a path below the surface "
		"of the water, and one can walk on it as if walking on the water itself. The pathway is marked by two spires. Once you step "
		"through the portal, you will arrive in the Oracle's realm. I cannot tell you anything beyond this point because I have never "
		"been there myself.")
	ELSE
		Conversation
		INTL( 9541, "The chamber is protected by four spires, and is very well hidden. Once you have acquired all the \"pieces\" of the Key of Ogrimar and "
		"it has been \"assembled\", I shall tell you how to find it.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command2(INTL( 8669, "PIECES"), INTL( 9542, "ASSEMBLED"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) == 1)
		Conversation
		INTL( 9543, "You already have the Key of Ogrimar. You need not trouble yourself with these questions any longer.")
	ELSE
		Conversation
		INTL( 9544, "What, you thought to find the key just waiting for you to pick it up? Nonsense! The key will require several \"parts\" which you "
		"will have to locate and acquire for yourself. Once you have gathered all the parts, you may return here and I will assemble them.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 8674, "PARTS"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) == 1)
		Conversation
		INTL( 9545, "As you well know, the three parts required to fashion the key are the Skull of Ogrimar, the Blood of Ogrimar and the Bones of Ogrimar.")
	ELSE
		Conversation
		INTL( 9546, "The three parts required to fashion the key are the \"Skull\" \"of\" \"Ogrimar\", the \"Blood\" \"of\" \"Ogrimar\" and the "
		"\"Bones\" \"of\" \"Ogrimar\". Once you have located and gathered all three parts, return here and I will combine them to form "
		"the Key of Ogrimar.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 9547, "SKULL OF OGRIMAR"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) == 0)
		IF(CheckItem(__OBJ_SKULL_OF_OGRIMAR) == 1)
			Conversation
			INTL( 9548, "You already have this piece of the key.")
		ELSE
			Conversation
			INTL( 9549, "The Skull of Ogrimar is truly an object of power that can only be obtained by the most determined of my lord's followers. "
			"I should warn you that this will be a very long and arduous task. However, I can shorten it somewhat by telling you where "
			"to start looking for it. Travel first to the village of the centaurs. There you should seek out the one who calls himself "
			"Zion Thunderheart. Ask him about the skull and tell him that I sent you, he may decide to help you.")
		ENDIF
	ELSE
		Conversation
		INTL( 9550, "You already have the Key of Ogrimar, you have no need for the skull.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 8931, "BLOOD OF OGRIMAR"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) == 0)
		IF(CheckItem(__OBJ_BLOOD_OF_OGRIMAR) == 1)
			Conversation
			INTL( 9548, "You already have this piece of the key.")
		ELSE
			Conversation
			INTL( 9551, "Unfortunately, I know not where or how to get the Blood of Ogrimar. This you will have to find out for yourself I'm afraid. "
			"Perhaps my \"assistant\" can help you in the matter.")
		ENDIF
	ELSE
		Conversation
		INTL( 9552, "You already have the Key of Ogrimar, you have no need for the blood.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 1454, "ASSISTANT"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	IF(CheckFlag(__FLAG_USER_HAS_MET_JULIAN) == 1)
		Conversation
		INTL( 9553, "You have already met with him I believe... his name is Julian. I sent him to investigate the town of Stonecrest. Were you "
		"to look for him, that is where you would probably find him.")
	ELSE
		Conversation
		INTL( 9554, "His name is Julian. He is currently on an assignment in the town of Stonecrest. Seek him out there if you are to speak with him.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 9115, "JULIAN"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	IF(CheckFlag(__FLAG_USER_HAS_MET_JULIAN) == 1)
		Conversation
		INTL( 9555, "Yes, I see you've met with my assistant. That boy is full of promise I tell you. He has served me well these past few years.")
	ELSE
		Conversation
		INTL( 9556, "That's what I said, his name is Julian.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command(INTL( 8934, "BONES OF OGRIMAR"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) == 0)
		IF(CheckItem(__OBJ_BONES_OF_OGRIMAR) == 1)
			Conversation
			INTL( 9548, "You already have this piece of the key.")
		ELSE
			IF(CheckItem(__OBJ_SKULL_OF_OGRIMAR) == 0 || (CheckItem(__OBJ_BLOOD_OF_OGRIMAR) == 0) )
				Conversation
				INTL( 9557, "I will tell you how to obtain the Bones of Ogrimar when and only when you have gathered both of the other parts of the key.")
			ELSE
				IF (CheckFlag(__FLAG_QUEST_FOR_BONES) == 0)
					GiveFlag(__FLAG_QUEST_FOR_BONES, 1)
				ENDIF 
				Conversation
				INTL( 9558, "The Bones of Ogrimar can be found somewhere on this island. I tell you the truth, once you have discovered the man who "
				"possesses them, you need only ask for the bones and he will give them to you. With that said, you had best be on your way "
				"since this is the last part of the key. Once you have found it, return here and I will assemble them together.")
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 9559, "You already have the Key of Ogrimar, you have no need for the bones.")
	ENDIF
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Command2(INTL( 9560, "GIVE ME THE BONES"), INTL( 9561, "I WANT THE BONES"))
""
IF(CheckFlag(__FLAG_USER_KNOWS_MORDENTHAL_HAS_BONES) == 2)
	IF(CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) == 0)
		Conversation
		INTL( 624, "What are you talking about?")
		GiveFlag(__FLAG_TIMES_ASKED_FOR_BONES, CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) + 1 )
	ELSEIF(CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) == 1)
		Conversation
		INTL( 9562, "I really don't know what you are talking about.")
		GiveFlag(__FLAG_TIMES_ASKED_FOR_BONES, CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) + 1 )
	ELSEIF(CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) == 2)
		Conversation
		INTL( 9563, "Fellow worshipper of Ogrimar or not, you are starting to get on my nerves!")
		GiveFlag(__FLAG_TIMES_ASKED_FOR_BONES, CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) + 1 )
	ELSEIF(CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) == 3)
		Conversation
		INTL( 9564, "Oh very well! I have the bones you ask for... so tell me, who was it that told you I had them?")
		GiveFlag(__FLAG_TIMES_ASKED_FOR_BONES, CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) + 1 )
		;YesNo = WhoToldUserAboutBones;
	ELSEIF(CheckFlag(__FLAG_TIMES_ASKED_FOR_BONES) == 4)
		GiveItem(__OBJ_BONES_OF_OGRIMAR)
		GiveFlag(__FLAG_TIMES_ASKED_FOR_BONES, 5)
		TakeItem(__OBJ_ANCIENT_RING) 
		Conversation
		INTL( 9565, "Oh, yes... of course. You want the bones now. Well, here they are then. "
		"In return, I ask that you give me the ancient ring as it is of no use to you anymore.") 				
		PRIVATE_SYSTEM_MESSAGE(INTL( 11521, "You give the ancient ring to Mordenthal.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 9566, "Mordenthal gives you the Bones of Ogrimar."))		
	ELSE
		Conversation
		INTL( 9567, "I have already given you the bones.")
	ENDIF
ELSE
	Conversation
	INTL( 9568, "Your words make little sense.")
ENDIF

;} else if( ( msg.Find( INTL( 3744, "XANTH") ) != -1 ) && YesNo == WhoToldUserAboutBones) {;YesNo = 0;
Conversation
INTL( 9569, "Hah, that fool. I should have better covered my tracks.")

;} else if(YesNo == WhoToldUserAboutBones) {;YesNo = 0;
Conversation
INTL( 9570, "You can't remember? How convenient for them.")

Command(INTL( 6167, "RETURN"))
""
IF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) >= 2)
	Conversation
	INTL( 9571, "Ahh yes, I thought you might return soon. I sense that my \"help\" you could use.")
ELSE
	Conversation
	INTL( 9568, "Your words make little sense.")
ENDIF

Command(INTL( 554, "HELP"))
""
IF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) == 2)
	Conversation
	INTL( 9572, "Yes, I would be willing to help you. Mayhaps the addition of the soul steal \"spell\" to your repertoire will make "
	"your journeys a little less harsh.")
ELSEIF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) >= 3)
	Conversation
	INTL( 9573, "I have taught you all that I could, I'm afraid.")
ELSE
	Conversation
	INTL( 9568, "Your words make little sense.")
ENDIF

Command3(INTL( 700, "SPELL"), INTL( 496, "TEACH"), INTL( 495, "LEARN"))
INTL( 9574, "I am certain this spell will help you.")
CreateSkillList
	AddTeachSkill (__SPELL_SOUL_STEAL, 41, 166192)
SendTeachSkillList

Command(INTL( 9575, "SOUL STEAL"))
INTL( 9576, "The soul steal spell damages your opponent by draining his life force with the power of darkness.")

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
""
IF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) == 2)
	Conversation
	INTL( 9577, "Methinks you shall \"return\", some day.")
ELSE
	Conversation
	INTL( 9578, "It would best if you were on your way.")
ENDIF
BREAK

Command(INTL( 4873, "DRARDOS"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 2)
	Conversation
	INTL( 11336, "Drardos is an antiques collector who resides with his wife in Silversky on "
	"Raven's Dust.")	
ELSE
	Conversation
	INTL( 9568, "Your words make little sense.")
ENDIF

CmdAND(INTL( 10782, "ANCIENT"), INTL( 8039, "RING"))
""
IF(CheckFlag(__FLAG_USER_KNOWS_MORDENTHAL_HAS_BONES) == 1)
	GiveFlag(__FLAG_USER_KNOWS_MORDENTHAL_HAS_BONES, 2)
	Conversation
	INTL( 10783, "So you know about the ring now, do you? Very well, I guess there is no use denying it now. Yes, the "
	"ring is mine... what of it?")
ELSEIF(CheckFlag(__FLAG_USER_KNOWS_MORDENTHAL_HAS_BONES) == 2)
	Conversation
	INTL( 10784, "I have already told you that the ring belongs to me. What else do you want from me?")
ELSE
	Conversation
	INTL( 9568, "Your words make little sense.")
ENDIF

Command(INTL( 8606, "OGRIMAR"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 9579, "He is the god of Night, and represents terror and chaos. His power has \"dwindled\" over the years, however.")
ELSE
	Conversation
	INTL( 9474, "That is no concern of yours, light-dweller!")
ENDIF

Default
INTL( 9568, "Your words make little sense.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Mordenthal::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_SOUL_STEAL, 41, 166192)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
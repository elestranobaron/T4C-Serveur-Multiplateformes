#pragma hdrstop
#include "BeltiganWhitesword.h"
					  
BeltiganWhitesword::BeltiganWhitesword()
{}

BeltiganWhitesword::~BeltiganWhitesword()
{}

extern NPCstructure::NPC BeltiganWhiteswordNPC;

void BeltiganWhitesword::Create( void )
{
    npc = BeltiganWhiteswordNPC;
    SET_NPC_NAME( "[10827]Sir Beltigan" );
    npc.InitialPos.X = 395;
    npc.InitialPos.Y = 1265;
    npc.InitialPos.world = 0;
}

void BeltiganWhitesword::OnAttacked( UNIT_FUNC_PROTOTYPE )
{   
    switch(rnd(0, 9)){
    case 0: SHOUT(INTL( 8576, "Artherk, grant me strength!")); break;
    case 1: SHOUT(INTL( 8577, "This really hurts!")); break;
    default: break;
	 } 
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void BeltiganWhitesword::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT LIGHTBRINGER = 1; 
CONSTANT Pledge = 2;
CONSTANT MergeItems = 3; 
CONSTANT TakeRings = 4;


InitTalk

Begin
INTL( 8578, "Welcome to my castle.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8579, "I am Sir Beltigan Whitesword.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 8580, "I am a holy \"paladin\" who watches over the land.")

Command(INTL( 8581, "PALADIN"))
INTL( 8582, "I follow the path of Light set for me by my god, \"Artherk\".")
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	INTL( 8583, " However, I do not expect you to understand this for your soul is shrouded in darkness.")
ENDIF
 
Command(INTL( 8584, "DWINDLED")) 
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 8585, "Since the past few thousand years, there has been one who's evil power has grown steadily. Since a balance has to be kept, "
	"what is gained must be lost somewhere. So great his power has become that he poses a serious \"threat\" to everybody, even to "
	"Artherk himself.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

CmdAND(INTL( 8039, "RING"),INTL( 8040, "LION"))
""
IF((USER_KARMA < 100) || (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1))
	Conversation
	INTL( 8587, "I would rather not discuss this with you, if you don't mind. Individuals of your ilk disgust me.")
ELSE
	IF (CheckItem(__OBJ_RING_OF_THE_LION)<2)
		Conversation
		INTL( 8588, "Those rings would help raise the courage and morale of my warriors. Should you have two to spare, "
		"I would reward you handsomely.")
	ELSE
		Conversation
		INTL( 8589, "I see you have brought me two Rings of the Lion! Shall you trade them for a reward?")
		SetYesNo(TakeRings)
	ENDIF
ENDIF

YES(TakeRings)
	IF (CheckItem(__OBJ_RING_OF_THE_LION) < 2)
		Conversation
		INTL( 8590, "Something odd has happened, you suddenly do not have enough rings on you!")
	ELSE
		Conversation
		INTL( 8591, "The forces of good rejoice at your decision! ")
		FOR(0,2)
			TakeItem(__OBJ_RING_OF_THE_LION)
		ENDFOR
		IF (rnd.roll(dice(1,2)) == 1)
			Conversation
			INTL( 8592, "Here's a crystal sword of might for your troubles.")
			GiveItem(__OBJ_CRYSTAL_SWORD_OF_MIGHT)
			PRIVATE_SYSTEM_MESSAGE(INTL( 8593, "You receive a Crystal Sword of Might.")) 
		ELSE
			Conversation
			INTL( 8594, "Here's an Eye of the Tiger for your troubles.")
			GiveItem(__OBJ_EYE_OF_THE_TIGER)
			PRIVATE_SYSTEM_MESSAGE(INTL( 8595, "You receive an Eye of the Tiger.")) 
		ENDIF
		;int nExpReward = USER_LEVEL*4000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF

NO(TakeRings)
	Conversation
	INTL( 8596, "Needless to say, I am disappointed.")

YesNoELSE(TakeRings)
	Conversation
	INTL( 8597, "I didn't quite get that. Did you say \"yes\" or \"no\"?")
	SetYesNo(TakeRings)

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 8598, "If you would assist me, I could use some \"Rings\" \"of\" \"the\" \"Lion\". King Aedenas Gravesoul, ruler of the "
"Centaurs, should have some, but you might need to give him something in return.")

Command(INTL( 8599, "THREAT"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8600, "The \"Dark\" \"One\" has to be destroyed no matter what, as he will stop at nothing to gain whatever power he can have.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF
  
Command(INTL( 8601, "DARK ONE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 8602, "The one I am referring to is none other than \"Makrsh\" \"P'Tangh\", the elven lich.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command3(INTL( 738, "MAKRSH"),INTL( 739, "P'TANGH"),INTL( 737, "LICH"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8603, "The elven Lich's power has grown steadily over the past few thousand years. His strength is so great that it "
	"rivals that of the gods themselves. Fortunately, Artherk is not the sole god to be affected by the \"uprise\" of "
	"Makrsh P'Tangh.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8604, "UPRISE"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8605, "The uprise of the Dark One has also left the foul \"Ogrimar\", god of the night, partially drained of his powers "
	"as well.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8606, "OGRIMAR"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8607, "The god of the night, Ogrimar, represents terror and chaos but he is also an unlikely ally in the war "
	"versus to Makrsh P'Tangh. In fact, some of his \"disciples\" are gathering followers to launch an assault "
	"against the lich itself.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8608, "DISCIPLES")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8609, "One of his disciples, \"Mordenthal\", is a dark knight who resides in northern Stoneheim. He is extremely deceitful "
	"and must not be trusted.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8610, "MORDENTHAL"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8611, "He is a dark knight and was once foremost amongst the great generals in Ogrimar's army. Even as "
	"we speak, he is recruiting followers of the dark path to further his master's \"cause\".")		
ELSEIF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
 	FORMAT(INTL( 8612, "Hmmmm. I see that you have Mordenthal's leash tied around your neck, %s. There is nothing to say about your "
	"master except that he'll eventually have to face me and meet his demise at last."), USER_NAME) 
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8613, "CAUSE")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	FORMAT(INTL( 8614, "The god Ogrimar seeks the demise of the Dark One. It is also our main "
	"concern, as followers of Artherk. %s, I'll make this short for both you and I. "
	"You have been granted the title of Champion of Light back in Raven's Dust. It is "
	"now time to \"fulfill\" your destiny and prove that you are indeed worthy of this honor."),USER_NAME) 	
ELSE																						   
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8615, "FULFILL"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8616, "The first step toward the fulfillment of your destiny is to become a \"Lightbringer\" of Artherk.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF 

Command(INTL( 7710, "LIGHTBRINGER")) 
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 8617, "Lightbringer, it is time for you to learn about the \"task\" that has to be done.")
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8618, "To become a Lightbringer of Artherk, you need only to pledge to serve Artherk. This is "
	"an important decision that you are about to choose. Do you feel within your soul that "
	"you are ready for such commitment?")
	SetYesNo(LIGHTBRINGER) 
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

YES(LIGHTBRINGER)
	Conversation
	INTL( 8619, "Then, you simply have to pledge to serve Artherk.")
	;YesNo = Pledge;
	
NO(LIGHTBRINGER)
	Conversation
	INTL( 8620, "I see that you are not ready yet. Come back when you feel within your soul that you are.")

YesNoELSE(LIGHTBRINGER)
	Conversation
	INTL( 8621, "Well, do you wish to become a Lightbringer of Artherk or not?") 	
	SetYesNo(LIGHTBRINGER)

;} else if( ( msg.Find( INTL( 8622, "I PLEDGE TO SERVE ARTHERK") ) != -1 ) && YesNo == Pledge) {;YesNo = 0;
Conversation
INTL( 8623, "As the stars and Artherk himself are witnesses, you are now a Lightbringer of Artherk. This is the first "
"step toward the fulfillment of your destiny. It is now time for you to learn about the \"task\" that lies ahead.") 
PRIVATE_SYSTEM_MESSAGE(INTL( 8624, "A tingling sensation washes over you briefly!"))
PRIVATE_SYSTEM_MESSAGE(INTL( 8625, "You are now a Lightbringer!"))
;int nExpReward = 25000; 	
PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
GiveXP(nExpReward)
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 0) 
	GiveFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK, 1) 
ENDIF

;} else if(YesNo == Pledge) {;
Conversation
INTL( 8626, "To become a Lightbringer, all you have to do is say \"I\" \"pledge\" \"to\" \"serve\" \"Artherk\" and "
"you will be one step closer to becoming a Seraph.")

Command(INTL( 8627, "TASK"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 8628, "The task that is set for you is no small one. You will have to \"vanquish\" the Dark One, Makrsh P'Tangh himself!")
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8629, "The task does not concern you for only a \"Lightbringer\" could possibly hope of completing it.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF 

Command(INTL( 8630, "VANQUISH")) 
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 8631, "Even though this seems nearly impossible, do not despair. There are many others that have been "
	"charged with the same task as you. However, even though Mordenthal and his underlings are also "
	"trying to defeat the Dark One, they are *not* to be trusted. They will do everything within their "
	"power to thwart your own advance. If one of Mordenthal's pupils were to succeed in stopping the lich, "
	"the dark knight would be exalted into Ogrimar's most favored disciple. You will, of course, have to gather "
	"much power before you are capable of confronting him. You must first find the location of his \"stronghold\" "
	"and that alone will prove to be a most difficult endeavor. Nevertheless, I'm certain that if you strive hard "
	"enough to better yourself, you will prevail.")
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8632, "You stand no chance of vanquishing the Dark One unless you become a \"Lightbringer\" of Artherk.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF 

Command(INTL( 8633, "STRONGHOLD"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 8634, "There is one who would know of its location, but he cannot be found on this plane of existence. He is known as the \"oracle\".")
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8635, "Only \"Lightbringers\" of Artherk need to hear about this.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 5628, "ORACLE"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 8636, "The oracle resides in its own realm, a place rumored to be nearly inaccessible. It is a being of immense power, yet not allowed "
	"to interfere in the affairs of gods and the normal course of events. To reach his plane, you will need the \"Key\" \"of\" "
	"\"Artherk\".") 	
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8637, "Only \"Lightbringers\" of Artherk need to hear about this.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8638, "KEY OF ARTHERK"))
""
IF(CheckFlag(__FLAG_USER_HAS_KEY_OF_ARTHERK) == 1)
	Conversation
	INTL( 8639, "Now that you have fought many perils to obtain this key and proved your worthiness, all that "
	"is left is to find the \"Chamber\" \"of\" \"Providence\" and enter the portal that will "
	"lead you to your destiny.")
ELSEIF (CheckItem(__OBJ_SOUL_OF_ARTHERK) >=1) 
	IF (CheckItem(__OBJ_HEART_OF_ARTHERK) >=1) 
		IF (CheckItem(__OBJ_WILL_OF_ARTHERK) >=1) 
			Conversation
			INTL( 8640, "You have performed well so far by gathering all the parts required for the Key. "						
			"Unfortunately, there are still many perils that you will have to face before the "
			"completion of your journey but I have faith in you. This being said, shall I combine "
			"these parts into the Key of Artherk right away?")
			SetYesNo(MergeItems) 
		ELSE
			Conversation
			INTL( 8641, "Unfortunately, the Key of Artherk cannot be complete without the Will.")
		ENDIF
	ELSE
		IF (CheckItem(__OBJ_WILL_OF_ARTHERK) >=1) 	
			Conversation
			INTL( 8642, "Alas, you are missing the Heart. The Key of Artherk cannot exist without it.")
		ELSE
			Conversation
			INTL( 8643, "You need the Will and the Heart to complete the Key of Artherk.")
		ENDIF 
	ENDIF 
ELSEIF (CheckItem(__OBJ_HEART_OF_ARTHERK) >=1) 
	IF (CheckItem(__OBJ_WILL_OF_ARTHERK) >=1) 
		Conversation
		INTL( 8644, "The Key of Artherk cannot be complete without the Soul.")
	ELSE
		Conversation
		INTL( 8645, "You need the Will and the Soul to complete the Key of Artherk.")
	ENDIF 
ELSE 	
	IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
		Conversation
		INTL( 8646, "The Key of Artherk is required to gain entrance into the \"Heart\" \"of\" \"Destiny\".")
	ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
		Conversation
		INTL( 8647, "You need not to concern about the Key of Artherk for you are not a \"Lightbringer\".")
	ELSE 
		Conversation
		INTL( 8586, "That is no concern of yours, spawn of darkness!")
	ENDIF
ENDIF

YES(MergeItems)
	IF ((CheckItem(__OBJ_SOUL_OF_ARTHERK) >=1) && (CheckItem(__OBJ_HEART_OF_ARTHERK) >=1) && (CheckItem(__OBJ_WILL_OF_ARTHERK) >=1)) 	
		Conversation
		INTL( 8648, "Excellent. I shall then begin the holy ritual that will combine the three parts into "
		"the Key right away.")	
		TakeItem(__OBJ_HEART_OF_ARTHERK)
		TakeItem(__OBJ_SOUL_OF_ARTHERK)
		TakeItem(__OBJ_WILL_OF_ARTHERK)
		GiveItem(__OBJ_KEY_OF_ARTHERK)
		GiveFlag(__FLAG_USER_HAS_KEY_OF_ARTHERK, 1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8649, "You give the Heart, Soul and Will of Artherk to Beltigan.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 8650, "Beltigan carefully places them on a small altar and recites a holy prayer.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 8651, "The three parts converge into one to form the Key of Artherk!")) 		
		PRIVATE_SYSTEM_MESSAGE(INTL( 8652, "You receive the Key of Artherk!")) 
	ELSE
		Conversation
		INTL( 8653, "Are you trying to fool me? I cannot help you create a Key of Artherk you do not "
		"have the Heart, the Soul and the Will. Come back once you have them.")
	ENDIF 

NO(MergeItems)
	Conversation
	FORMAT(INTL( 8654, "That's an answer that I cannot accept coming from a Lightbringer. This is not the "
	"time to lose hope, %s. That being said, shall I merge the three parts now?"), USER_NAME) 
	SetYesNo(MergeItems) 

YesNoELSE(MergeItems) 
	Conversation
	INTL( 8655, "Do you want me to merge the parts to create the Key of Artherk?")
	SetYesNo(MergeItems) 

Command(INTL( 8656, "HEART OF DESTINY"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 8657, "You may have seen it while wandering. It is a great \"fortress\" surrounded by a body of water "
	"located in the center of Stoneheim.") 
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8658, "Only \"Lightbringers\" of Artherk need to hear about this.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8659, "FORTRESS"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 8660, "I say so because there is no apparent point of entry. However, with the Key of Artherk one may be able to enter the \"portal\" located "
	"inside the \"Chamber\" \"of\" \"Providence\".")
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8661, "Only \"Lightbringers\" of Artherk need to hear about this.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 2457, "PORTAL"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	IF(CheckItem(__OBJ_KEY_OF_ARTHERK) == 1)
		Conversation
		INTL( 8662, "Now that you have fought many perils to obtain this key and proved your worthiness, all that "
		"is left is to find the \"Chamber\" \"of\" \"Providence\" and enter the portal that will "
		"lead you to your destiny.")
	ELSE
		Conversation
		INTL( 8663, "You cannot use the portal unless you have the \"Key\" \"of\" \"Artherk\".")		
	ENDIF	
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8664, "Only \"Lightbringers\" of Artherk need to hear about this.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8665, "CHAMBER OF PROVIDENCE"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	IF(CheckItem(__OBJ_KEY_OF_ARTHERK) == 1)
		Conversation
		INTL( 8666, "The chamber is located on a well hidden island to the east near the Sunken Woods forest. There lies a path below the surface "
		"of the water, and one can walk on it as if walking on the water itself. The pathway is marked by two spires. Once you step "
		"through the \"portal\", you will arrive in the Oracle's realm. I cannot tell you anything beyond this point because I have never "
		"been there myself.")
	ELSE
		Conversation
		INTL( 8667, "The chamber is protected by four spires, and is very well hidden. Once you have acquired all the \"pieces\" of the Key of "
		"Artherk and it has been \"assembled\", I shall tell you how to find it.")		
	ENDIF	
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8668, "Only \"Lightbringers\" of Artherk need to hear about this.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command2(INTL( 8669, "PIECES"),INTL( 8670, "ASSEMBLE"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	IF(CheckItem(__OBJ_KEY_OF_ARTHERK) == 1)
		Conversation
		INTL( 8671, "You already have the Key of Artherk. All that is left is to find the Chamber of Providence and enter the portal.")
	ELSE
		Conversation
		INTL( 8672, "The key will require several \"parts\" that are scattered across Stoneheim and it is your task to gather them. Once you "
		"have gathered all the required parts, you may return here and I will assemble them.")		
	ENDIF 
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8673, "Only \"Lightbringers\" of Artherk need to hear about this.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 8674, "PARTS"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	IF(CheckItem(__OBJ_KEY_OF_ARTHERK) == 1)
		Conversation
		INTL( 8671, "You already have the Key of Artherk. All that is left is to find the Chamber of Providence and enter the portal.")
	ELSE
		Conversation
		INTL( 8675, "The parts required to fashion the key are the \"Soul\" \"of\" \"Artherk\", the \"Heart\" \"of\" \"Artherk\" and the "
		"\"Will\" \"of\" \"Artherk\". Once you have gathered all three parts, return here and I will combine them to form "
		"the Key of Artherk.")
	ENDIF
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8676, "Only \"Lightbringers\" of Artherk need to hear about this.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command(INTL( 9207, "WILL OF ARTHERK"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	IF (CheckFlag(__FLAG_USER_HAS_KEY_OF_ARTHERK) == 1)
		Conversation
		INTL( 10762, "You already have the Key of Artherk, you have no need for the will.")
	ELSE
		IF (CheckFlag(__QUEST_FLAG_ARTHERK_WILL) == 1) 
			Conversation 
			INTL( 8677, "You already have this piece of the Key.")	
		ELSEIF ((CheckFlag(__QUEST_FLAG_ARTHERK_HEART) != 1) || (CheckFlag(__QUEST_FLAG_ARTHERK_SOUL) != 1)) 
			Conversation
			INTL( 8678, "Before you can undertake the quest to obtain the Will of Artherk, you must first possess both the "
			"Soul and the Heart of Artherk lest you fail miserably in your quest.") 
		ELSE
			Conversation	
			FORMAT(INTL( 8679, "%s, you must now seek the counsel of Aedenas Gravesoul, wise king of the proud Centaurs. He will tell you what "
			"you need to know to undertake your perilous quest to obtain the sacred Will of Artherk. However, I must "
			"warn you for you're nearing the end of these tasks. The foul Mordenthal has undoubtedly heard of what "
			"you are doing and will most certainly attempt to thwart you. You must prepare yourself for some harsh "
			"times, friend."), USER_NAME) 
			IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 0)
				GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 1) 
			ENDIF
		ENDIF
	ENDIF 
ELSE
	IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
		Conversation
		INTL( 8680, "Only a \"Lightbringer\" can obtain the Will of Artherk.")
	ELSE
		Conversation
		INTL( 8586, "That is no concern of yours, spawn of darkness!")
	ENDIF
ENDIF

Command(INTL( 9592, "HEART OF ARTHERK"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1)
	IF (CheckFlag(__FLAG_USER_HAS_KEY_OF_ARTHERK) == 1) 
		Conversation
		INTL( 10763, "You already have the Key of Artherk, you have no need for the heart.")
	ELSE
		IF (CheckFlag(__QUEST_FLAG_ARTHERK_HEART) == 1)
			Conversation
			INTL( 8677, "You already have this piece of the Key.")
		ELSE
			Conversation
			INTL( 8681, "Unfortunately, I cannot help you in finding the Heart of Artherk for I do not know where or how "
			"to obtain it. You will have to find this out by yourself, I'm afraid.")
		ENDIF
	ENDIF
ELSE
	IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
		Conversation
		INTL( 8682, "Only a \"Lightbringer\" can obtain the Heart of Artherk.")
	ELSE
		Conversation
		INTL( 8586, "That is no concern of yours, spawn of darkness!")
	ENDIF
ENDIF 
										   
Command(INTL( 9710, "SOUL OF ARTHERK"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1)
	IF (CheckFlag(__FLAG_USER_HAS_KEY_OF_ARTHERK) == 1) 
		Conversation
		INTL( 10764, "You already have the Key of Artherk, you have no need for the soul.") 
	ELSE
		IF (CheckFlag(__QUEST_FLAG_ARTHERK_SOUL) == 1)
			Conversation
			INTL( 8677, "You already have this piece of the Key.")
		ELSE
			Conversation
			INTL( 8683, "The Soul of Artherk is truly the symbol of hope that brings compassion and wisdom required to face "
			"any perilous situations. Only a pious man with absolute devotion to our Lord can summon it in the "
			"presence of mortals. Unfortunately, I am not this person. I cannot help you further for it is part "
			"of your task to locate this righteous person and persuade him or her to assist you.")		
		ENDIF
	ENDIF
ELSE
	IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
		Conversation
		INTL( 8684, "Only a \"Lightbringer\" can obtain the Soul of Artherk.")
	ELSE
		Conversation
		INTL( 8586, "That is no concern of yours, spawn of darkness!")
	ENDIF
ENDIF 

Command(INTL( 7700, "STONECREST"))
INTL( 8685, "Stonecrest is located to the north.")

Command(INTL( 6251, "STONEHEIM"))
INTL( 8686, "Stoneheim is the name of this island.")

Command(INTL( 1243, "ARTHERK")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8687, "He is the god of peace and represents truth and compassion. Alas, his power has \"dwindled\" over "
	"the years.")
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 0) 
	Conversation
	INTL( 8688, "He is the god of peace and represents truth and compassion.")
ELSE
	Conversation
	INTL( 8586, "That is no concern of yours, spawn of darkness!")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS ")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	INTL( 8689, "There is no need for such hostility.")
ELSE
	Conversation
	INTL( 8690, "I would expect no more coming from you.")
ENDIF 
BREAK

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	INTL( 8691, "Return from the hole you crawled from, spawn of darkness!")
ELSE
	Conversation
	INTL( 8692, "May Artherk light your path and bring you strength.")
ENDIF
BREAK 	

Command(INTL( 3771, "?"))
INTL( 8693, "I have no answer for this.")

Default
""
IF (rnd.roll(dice(1,2) ) ) 
	Conversation
	INTL( 8694, "I have little time for this.")
ELSE
	Conversation
	INTL( 1791, "I don't know.")
ENDIF

EndTalk
}


// __QUEST_FLAG_WILL_OF_ARTHERK_QUEST 
// 0: -- 
// 1: Spoken with Beltigan. Beowulf is told to seek counsel of Aedenas Gravesoul.
// 2: Spoken with Aedenas. Beowulf is told to seek the White Crow to fetch the Fangs of True Resolve. 
// 3: Spoken with Mithanna Snowraven. She requires a Jade Ring of Sorcery + a dozen of Kraanian eyes.
//	4: Brought back the required components, Mithanna Snowraven tells Beowulf that he must seek Nissus Haloseeker.  
//	5: Spoken with Nissus and the Fangs are on their way. 
// 6: The last fang is created and the Night Retrievers are summoned. If they successfully steal a Fangs, this Flag
// is reduced to 5 and minus one fang. 
// 7: Spoken with King Aedenas 

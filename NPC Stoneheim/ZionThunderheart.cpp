#pragma hdrstop
#include "ZionThunderheart.h"

ZionThunderheart::ZionThunderheart()
{}

ZionThunderheart::~ZionThunderheart()
{}

extern NPCstructure::NPC ZionThunderheartNPC;

void ZionThunderheart::Create( ){
	npc = ZionThunderheartNPC;
	SET_NPC_NAME( "[10938]Zion Thunderheart");
	npc.InitialPos.X = 935;		   
	npc.InitialPos.Y = 1150;
	npc.InitialPos.world = 0;
}

void ZionThunderheart::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT WhoToldUserAboutSkull = 4;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_USER_HAS_SKULL_OF_EVIL) >= 1)
	IF(CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) >= 1)
		IF(CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) >= 2)
			IF(CheckFlag(__FLAG_USER_HAS_SKULL_OF_OGRIMAR) == 1)
				Conversation
				INTL( 9652, "I have already told you all that concerns you. Leave now unless you have some other business to take care of.")
			ELSEIF(CheckFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN) == 0 )
				GiveFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN, 1)
				PRIVATE_SYSTEM_MESSAGE(INTL( 10233, "You give the Skull of Evil, the Crown of Corruption and two arcane spellbooks to Zion."))
				TakeItem(__OBJ_SKULL_OF_EVIL)
				TakeItem(__OBJ_CROWN_OF_CORRUPTION)
				TakeItem(__OBJ_ARCANE_SPELLBOOK)
				TakeItem(__OBJ_ARCANE_SPELLBOOK)
				Conversation
				INTL( 9653, "Ahhh, I see you have gathered everything I require. Perhaps there is hope for you yet. Well then, as you have kept "
				"your part of the bargain, I will keep mine. The Skull of Ogrimar is hidden under the false bottom of a chest inside the chambers "
				"of Vargus. I must warn you, the dark bishop values his material possessions much too highly for one of his position, and if you "
				"attempt to talk to him before getting the skull, he will most definitely hide it before you can get it. Remember, get the chest "
				"before talking with the dark bishop Vargus.")
			ELSEIF(CheckFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN) == 1)
				Conversation
				INTL( 9654, "I have already told you what to do, now make haste if you wish to get the skull before Vargus decides to change its location.")
			ELSE
				GiveFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN, 1)
				Conversation
				INTL( 9655, "Did I not tell you not to talk to Vargus before you looked inside the chest? Bah! Why do I even bother? I knew a pathetic "
				"weakling could never complete a task meant for a centaur! Nevertheless, I will tell you this much to help you. Were you to "
				"travel back to the temple, Vargus might think the danger to be gone and you might have another chance at getting the skull.")
			ENDIF
		ELSE
			Conversation
			INTL( 9656, "I will not tell you anything until you bring me two \"arcane\" \"spellbooks\"!")
		ENDIF
	ELSE
		IF(CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) >= 2)
			Conversation
			INTL( 9657, "I will not tell you anything until you bring me the \"Crown\" \"of\" \"Corruption\"!")
		ELSE
			Conversation
			INTL( 9658, "Do not mock me. You have but the Skull of Evil. You have yet to find two \"arcane\" \"spellbooks\" and the \"Crown\" \"of\" \"Corruption\".")
		ENDIF
	ENDIF
ELSE
	IF(CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) >= 1)
		IF(CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) >= 2)
			Conversation
			INTL( 9659, "I will not tell you anything until you bring me the \"Skull\" \"of\" \"Evil\"!")
		ELSE
			Conversation
			INTL( 9660, "Do not mock me. You have but the Crown of Corruption. You have yet to find the \"Skull\" \"of\" \"Evil\" and two \"arcane\" \"spellbooks\".")
		ENDIF
	ELSE
		IF(CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) >= 2)
			Conversation
			INTL( 9661, "Do not mock me. You bring before me but two arcane spellbooks. You have yet to find the \"Skull\" \"of\" \"Evil\" and the \"Crown\" \"of\" \"Corruption\".")
		ELSE
			IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 9)
				Conversation
				FORMAT(INTL( 9662, "You have attempted to thwart me? You do not frighten me, %s. Know that I have my eye on you, and that when the "
				"king passes away - and he WILL - you will be next on my list of people to find."), USER_NAME) 
			ELSE
				Conversation
				INTL( 9663, "Speak hastily for I have no time to spend with you.")
			ENDIF
		ENDIF
	ENDIF
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9664, "I am Zion Thunderheart, King Gravesoul's cousin. Soon, I shall be king of all Centaurs.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 9665, "If I feel like you must know, you will. Otherwise, that is none of your business.")

Command(INTL( 9547, "SKULL OF OGRIMAR"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_SKULL_OF_OGRIMAR) == 1)
		Conversation
		INTL( 9666, "I see you have found the skull, congratulations.")
	ELSEIF(CheckFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN) == 1)
		Conversation
		INTL( 9667, "I have already told you where the skull is located. It is up to you to find it now.")
	ELSEIF(CheckFlag(__FLAG_USER_HAS_TOLD_ZION_ABOUT_MORDENTHAL) == 0)
		Conversation
		INTL( 9668, "Who told you about the skull?")
		;YesNo = WhoToldUserAboutSkull;
	ELSEIF(CheckFlag(__FLAG_USER_HAS_TOLD_ZION_ABOUT_MORDENTHAL) == 1)
		Conversation
		INTL( 9669, "Yes that's right, the skull. I know where it is being kept, but that information will \"cost\" you dearly.")
		GiveFlag(__FLAG_USER_HAS_TOLD_ZION_ABOUT_MORDENTHAL, 2)
	ELSE
		Conversation
		INTL( 9670, "I told you, if you want to know where the skull is being kept, you will have to pay the \"price\" I ask for.")
	ENDIF
ELSE
	Conversation
	INTL( 9671, "That does not concern a weakling like you!")
ENDIF

;} else if( ( msg.Find( INTL( 8610, "MORDENTHAL") ) != -1 ) && YesNo == WhoToldUserAboutSkull) {;YesNo = 0;
Conversation
INTL( 9672, "I see, then I will help you. This does not make us allies, mind you! I will sooner slit my own throat before I "
"will trust you! Now then, what is it you wanted to know again?")
GiveFlag(__FLAG_USER_HAS_TOLD_ZION_ABOUT_MORDENTHAL, 1)

;} else if( ( msg.Find( INTL( 519, "LEAVE") ) != -1 ) && YesNo == WhoToldUserAboutSkull) {;YesNo = 0;
Conversation
INTL( 9673, "Very well... we shall see how far you will go without my aid.")
BREAK

;} else if(YesNo == WhoToldUserAboutSkull) {;
Conversation
INTL( 9674, "I can't believe that to be the truth. Now either tell me who told you about the skull or \"leave\" this place immediately!")

Command2(INTL( 9394, "COST"), INTL( 3746, "PRICE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9675, "I require nothing less than one \"Skull\" \"of\" \"Evil\", one \"Crown\" \"of\" \"Corruption\" and two \"arcane\" \"spellbooks\". After I have received "
	"everything, I will tell you the location of the skull so that you may claim it for yourself.")
ELSE
	Conversation
	INTL( 9671, "That does not concern a weakling like you!")
ENDIF

Command(INTL( 8370, "SKULL OF EVIL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_SKULL_OF_EVIL) == 1)
		Conversation
		INTL( 9676, "I already told you how to get the Skull of Evil.")
	ELSE
		Conversation
		INTL( 9677, "You don't know where to get it? Oh very well, I guess I must help you. The sooner you get it, the sooner I will receive it I suppose. "
		"The Skull of Evil is a powerful relic much coveted by many an adventurer. There is a skraug of the Moon Tug tribe that possesses "
		"one I believe. Perhaps he would be inclined to let it go if you made it worth his while.")
	ENDIF
ELSE
	Conversation
	INTL( 9671, "That does not concern a weakling like you!")
ENDIF

Command(INTL( 9678, "CROWN OF CORRUPTION"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) == 1)
		Conversation
		INTL( 9679, "I already told you how to get the Crown of Corruption.")
	ELSE
		Conversation
		INTL( 9680, "I don't know much about the crown, but rumor has it that the one who brandishes it will become slightly harder to strike. The last "
		"I heard, this relic was seen in the possession of the thieves in Stonecrest.")
	ENDIF
ELSE
	Conversation
	INTL( 9671, "That does not concern a weakling like you!")
ENDIF

Command(INTL( 7929, "ARCANE SPELLBOOK"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) >= 1)
		Conversation
		INTL( 9681, "I already told you how to get an arcane spellbook.")
	ELSE
		Conversation
		INTL( 9682, "There are several ways to go about getting an arcane spellbook, but the easiest way would be to find a master sorcerer and ask him "
		"for one. Where can you find a master sorcerer you ask? Well, I don't have all the answers, but I will tell you this: one resides in "
		"a place called the Wizard's Vale, on the island of Raven's Dust.")
	ENDIF
ELSE
	Conversation
	INTL( 9671, "That does not concern a weakling like you!")
ENDIF

CmdAND(INTL( 6455, "WIZARD"), INTL( 9077, "VALE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9683, "Wizard's Vale is a valley that begins somewhere along the southwestern coast of Raven's Dust.")
ELSE
	Conversation
	INTL( 9671, "That does not concern a weakling like you!")
ENDIF

CmdAND(INTL( 10231, "BONES"), INTL( 8606, "OGRIMAR"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 1)
	Conversation
	INTL( 10234, "There is a human in that jumbled mass of buildings you call a town that has an interesting tale closely related "
	"to this subject. Perhaps you should go find and pester him for information instead of me.")
ELSE
	Conversation
	INTL( 9671, "That does not concern a weakling like you!")
ENDIF

Command2(INTL( 1072, "KING"),INTL( 7998, "GRAVESOUL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9684, "I'm going to be his successor, whether he likes it or not. The day he dies is the day "
	"I take over the Centaurs. I'm the best choice, and everyone knows it. So the sooner he "
	"dies, the sooner we can clean up Stoneheim of all the rabble that weakens it.")
ELSE
	Conversation
	INTL( 9685, "Like I would tell *you* anything about this.")
ENDIF

Command2(INTL( 8005, "KYATHOS"),INTL( 8006, "SHATTERSKULL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9686, "He's almost on top of my hit list, but not quite.")
ELSE
	Conversation
	INTL( 9687, "This is no concern of yours.")
ENDIF

Command2(INTL( 8009, "THOR"),INTL( 8010, "GLAREFIRE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9688, "He may be good at making weapons, but I'm certain Malachai Fatebringer is better. "
	"I can sense a challenge coming up, I really can. And challenge leads to conflict, which "
	"in turn leads to strength. It can only be good for our kind.")
ELSE
	Conversation
	INTL( 9689, "Walk away while you still can!")
ENDIF

Command2(INTL( 8013, "DIONYSUS"),INTL( 8014, "SILVERSTREAM"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9690, "What most people don't know is that he uses a musical instrument to maintain the peace "
	"among Centaurs. Can you imagine it? He's actually *mind controlling* us so we don't fight! "
	"This disgusts me! Why am I the only one to see how *wrong* this is?!?")
ELSE
	Conversation
	INTL( 9691, "I have nothing to tell you!")
ENDIF

Command2(INTL( 8046, "MALACHAI"),INTL( 8047, "FATEBRINGER"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9692, "Malachai is my best supporter and my most sincere ally. When I become king, I will "
	"make him my First Counselor.")
ELSE
	Conversation
	INTL( 9693, "A honorable fellow and visionary, you should give him all the respect he deserves.")
ENDIF

Command2(INTL( 8017, "GLADDIUS"),INTL( 8018, "WINDCHASER"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 9694, "He and Kyathos Shatterskull are a thorn at my side, but you just wait until I become their king. "
	"Then we'll see who's the real thorn.")
ELSE
	Conversation
	INTL( 9695, "Begone from my sight, weakling!")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 9696, "You will pay this insult in blood!")
FIGHT

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 9697, "Take your stench with you.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1) 
	Conversation
	INTL( 3921, "Please try to be more specific.")
ELSE
	Conversation
	INTL( 5250, "I don't think that concerns me.")
ENDIF

EndTalk
}



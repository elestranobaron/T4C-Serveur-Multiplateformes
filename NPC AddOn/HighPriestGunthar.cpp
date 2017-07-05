#pragma hdrstop
#include "HighPriestGunthar.h"

HighPriestGunthar::HighPriestGunthar()
{}

HighPriestGunthar::~HighPriestGunthar()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void HighPriestGunthar::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12744]High Priest Gunthar");
	npc.InitialPos.X = 910;		   
	npc.InitialPos.Y = 2765;
	npc.InitialPos.world = 1;
}

void HighPriestGunthar::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Stone = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 5)
	Conversation
	INTL( 12276, "I greet you in the name of our blessed lord Artherk, my child. Welcome to his humble church.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12277, "Welcome to our blessed lord Artherk's humble church, my child. I have heard that you recently "
	"met with the vile necromancer? I hope he didn't corrupt your reason with his foolish \"demands\".")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12278, "Please hurry! You must find the merchant! Go to the merchant's guild in Windhowl and ask them where "
	"to find him.") 
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 18)
	Conversation
	INTL( 12279, "I sense you have the stone but you must first seek the gypsy's counsel. Once "
	"you have done so, return here at once.") 	
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) <= 22)
	Conversation
	INTL( 12280, "Have you found the stone yet? Please hurry! You must find it and bring it back to me!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 23)
	Conversation
	INTL( 12281, "Hurry! You must bring the stone to Olin Haad before it's too late!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12282, "You've returned at last! Why the strange \"look\" upon your face?")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12283, "You should meet with Tarnian. He fights for Lighthaven and I'm sure he will be able to help you. Look for him "
	"in the outskirts of town, possibly near the cavern.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 38)
	Conversation
	INTL( 12284, "I have been very busy trying to figure out what to do about this Olin Haad matter... I'm afraid I "
	"can't offer any help to you right now.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12285, "Welcome back, my child. May the \"blessing\" \"of\" \"Artherk\" enlighten the path that you must "
	"take. I have received word from the king...")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 39)
	Conversation
	INTL( 12286, "You should go find Caledbolg if you want to have a chance at stopping Olin Haad. It is kept safe in "
	"a shrine in the southeast part of the desert on Raven's Dust.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 12287, "You have Caledbolg! I knew you could do it! Now you stand a very good chance of defeating Olin Haad. "
	"Go see Efnisien, he will tell you about the entrance to the temple.")
ELSE
	Conversation
	FORMAT(INTL( 12288, "May Artherk bless our wonderful lives. Ha! Ha! It's always a pleasure talking with you, %s!"), USER_NAME)
ENDIF

Command(INTL( 12289, "DEMAND"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12290, "Yes, ever since the day he came in our poor town, he started to demand things that we could not give "
	"to him. For the most part, we could not understand what it was he wanted, except maybe for this \"stone\"...")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12187, "HEARTSTONE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12292, "By Artherk! What have I done? Quickly, you must find the merchant! Can you help me get the stone back?")
	SetYesNo(Stone)
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 11845, "STONE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12293, "One day, I was cleaning the cellar of the church when I happened upon an old stone that looked somewhat out "
	"of place. I eventually sold it to a nice \"merchant\" for a fair price. Two days later, the \"necromancer\" "
	"came bearing a letter from the king that said he was entitled to the stone.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 1257, "MERCHANT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12294, "The merchant... he was a nice man. He came to our church to pay homage to our lord Artherk while he was "
	"in town. That is when he saw the stone... He offered me gold coins and a ruby rod of foreign design for it "
	"and... \"wait\"!")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12295, "WAIT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12296, "Now that I think about it... the merchant asked me something that I found odd at the time. He asked me if "
	"anyone had asked for the Heartstone before, but I told him no, and that he was the first. But when the "
	"\"necromancer\" came with his letter from the king, he also called it the Heartstone.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 693, "NECROMANCER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12297, "May Artherk shield me from the influence of that vile spawn of wickedness. Our king, for reasons known only "
	"to him, hired this creature of darkness to stop a group of cultists called the \"Corrupters\" \"of\" "
	"\"Gluriurl\". Supposedly, the king promised him the stone if he could manage to get rid of the cultists.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command2(INTL( 12298, "CORRUPTERS"), INTL( 12299, "GLURI"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12300, "The Corrupters are believed to be a fanatic cult that worships a forgotten god called Gluriurl. The king "
	"believes that they are the survivors of an ancient battle that occured a century ago... the \"Battle\" "
	"\"of\" \"Emanations\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

CmdAND(INTL( 10739, "BATTLE"), INTL( 11923, "EMANATION"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12301, "From what is written, the Battle of Emanations was the great battle between the Dragons and a powerful "
	"group of renegade Seraphs called the \"Harvesters\" \"of\" \"Life\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

CmdAND(INTL( 5333, "HARVESTER"), INTL( 1915, "LIFE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12302, "The Harvesters of Life thrived on absolute destruction. They were nearly unstoppable and when they tried "
	"to destroy the island of Stoneheim, the \"Dragons\" intervened.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12303, "The sole purpose of a Harvester is to bring the dead god Gluriurl back to life. They believe that "
	"once they achieve this, one of them will be chosen to rule over Althea. To dupe them into thinking "
	"this way, the dead god's heart gives them the \"illusion\" of power.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 1367, "DRAGON"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12304, "The Dragons, who were less in number than their enemies, lost nearly two thirds of their kin. Those Seraphs "
	"that were allied to the Dragons perished, and the Harvesters of Life were \"completely\" annihilated, or so "
	"it was thought.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 10708, "COMPLET"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12305, "It is only recently, after a series of gruesome events, that \"Theodore\" \"XIII\" discovered that not all of the "
	"Harvesters were destroyed in the battle. The survivors passed down their arcane knowledge to others and they "
	"eventually created the Cult of Gluriurl.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 754, "THEODORE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12306, "I do not know why the king would hire a necromancer to dispose of the cult, but I believe the answers are "
	"somehow linked to this \"Heartstone\"...")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

YES(Stone)
	Conversation
	INTL( 12307, "You will? Oh thank heavens! If the stone is... I don't want to think about it, I must get it back! Now then, "
	"what would be a good place for you to start \"looking\"?")
NO(Stone) // GAMEDESIGN: LOWER USER'S KARMA FOR SAYING NO
	Conversation
	INTL( 12308, "Oh please! The church will pay you for your services. Can you help me get the stone back?")
	SetYesNo(Stone)
YesNoELSE(Stone)
	Conversation
	INTL( 12309, "Will you get the stone back for me?")
	SetYesNo(Stone)

Command(INTL( 1303, "LOOK"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12310, "Yes that's it! You should start your search in Windhowl, far to the west. There you will find the merchant's "
	"guild. You can ask them where to find the \"Nomad\". Please hurry and get the stone back. Oh, and take this, "
	"you seem to need the gold more than I.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 6)
	GiveGold(1000)
	GiveXP(10000)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9912, "You receive 10000 experience points."))
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12311, "Ahh... I see. So Olin Haad told you about the Heartstone. I know I shouldn't have \"kept\" it from you but I wasn't "
	"sure if you would've helped me otherwise.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 11802, "NOMAD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12312, "That is what he calls himself. If you ask the merchant's guild about him, I am sure they will recognize the name.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12313, "KEPT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12314, "Alright then... the Heartstone is the heart of an ancient god named Lothar the Just. He was the god of Justice "
	"and the brother of our revered Artherk. It is written that millenia ago, a god named Gluriurl broke the Compact, "
	"which prompted a war between the \"gods\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 9502, "GODS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12315, "Gluriurl, who understood the potential of the ancient race, made contact with an elven king, Makrsh P'Tangh, to "
	"whom he promised untold riches and power in exchange for a \"service\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12097, "SERVICE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12316, "The elven king was to erect a monument to our dear Artherk and lure him into its center, where a powerful "
	"ritual was taking place. Thousands of Elves died in the ceremony. After the ritual was complete, Artherk's "
	"essence was bound into a \"physical\" \"body\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

CmdAND(INTL( 10712, "PHYSICAL"), INTL( 12317, "BODY"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12318, "In this state, the god was vulnerable and thus, could be killed. Gluriurl, in the body of Makrsh P'Tangh, "
	"attacked Artherk with all his might. Just before the evil god absorbed Artherk's essence into his own, "
	"Lothar intervened and defeated Gluriurl, \"sacrificing\" himself in the process.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12319, "SACRIFIC"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12320, "Not much else is known about the Celestial War. However, other records indicate that when Lothar sacrificed "
	"his own life, it created a force strong enough to \"bind\" the essence of Gluriurl into his own Heart.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12321, "BIND"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12322, "It is believed that in the Heartstone lie the last remnants of the dead god. If the seal was to be broken, "
	"Gluriurl would return to life again! Do you remember when I told you about the Battle of Emanations? That "
	"was the last battle that occured because of this \"seal\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12323, "SEAL"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12324, "Recently, the stone has started to throb with energy. I don't know what Olin Haad's \"true\" \"intentions\" are, "
	"but something must be done to prevent Gluriurl from coming back to life. If he were to live again, the world would "
	"suffer greatly from his thirst for vengeance.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

CmdAND(INTL( 9630, "TRUE"), INTL( 12325, "INTENTION"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 24)
	Conversation
	INTL( 12326, "That's why I want you to meet with someone, a strange fellow who is known as the Nameless Bard... I am prohibited "
	"from telling you more about it. You should talk to Tarnian. He is a good friend and he fights to free Lighthaven "
	"from Olin Haad's clutches. Look for him in the outskirts of town, possibly near the cavern.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 25)
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

CmdAND(INTL( 552, "BLESSING"), INTL( 1243, "ARTHERK"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12327, "So... you've heard about my wife. Yes, she died... Alenthia was... she was pregnant when th.. that "
	"vile necromancer killed her. He took her and my unborn child from me! What is worse, he didn't only "
	"take their bodies, but their \"souls\" as well.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12328, "SOULS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12329, "He bound their essence inside his necklace... He is trying to use this as leverage to force me into "
	"revealing the location of the burial grounds of Lothar. My poor Aly! As much as I want to save her, "
	"Artherk would never allow me to do such a thing. It would mean the end of everything! We must \"stop\" "
	"the dog at all costs!")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 7346, "STOP"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12330, "As I said before, I received a letter from the king that explained Olin Haad's deception. The "
	"necromancer never stopped the Corrupters of Gluriurl as he was hired to do... he's actually "
	"a \"part\" of them!")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 1998, "PART"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12331, "Do you remember when I told you that the Corrupters were a fanatic cult of Gluriurl and that the king "
	"thought they were the survivors from the Battle of Emanations? It has been confirmed that Olin Haad "
	"was a \"Harvester\" of Life in this battle.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 5333, "HARVESTER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12332, "The sole purpose of a Harvester is to bring the dead god Gluriurl back to life. They believe that "
	"once they achieve this, one of them will be chosen to rule over Althea. To dupe them into thinking "
	"this way, the dead god's heart gives them the \"illusion\" of power.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12333, "ILLUSION"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12334, "He gives them what they call the Gift of Corruption. It supposedly nourishes the desire to revive "
	"dead god, while giving them considerable power. I used to believe that it was impossible for a mere "
	"mortal to fight against a for like this until just \"recently\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12335, "RECENT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12336, "When I sent you to retrieve the Darkstone and the Skull of Gluriurl, I thought that the only way to "
	"stop the Harvesters was to gather the components for the ritual and hide them, but I was \"wrong\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12337, "WRONG"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12338, "In one of my books on the Battle of Emanations, I read that the alliance used a mighty blade called "
	"Caledbolg to defeat the Harvesters. I also found out that Artherk has blessed us by giving you the "
	"only thing that can give us access to where the sword lays... the \"Heart\" \"of\" \"Artherk\".")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

CmdAND(INTL( 12339, "HEART"), INTL( 1243, "ARTHERK"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12340, "What we had all along in our humble church was not the Heart of Gluriurl, but that of our humble lord, "
	"Artherk. To think that I actually sold it to a merchant! Finally, my dear friend \"Efnisien\" can begin "
	"to hope.")
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF

Command(INTL( 12088, "EFNISIEN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12341, "Efnisien is the guardian of the entrance to Lothar's temple, but the necromancer doesn't know that. "
	"You should go now and find that blade. Caledbolg is kept safe in a shrine in the southeast part of "
	"the desert on Raven's Dust.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 39)
ELSE
	Conversation
	INTL( 12291, "I'm afraid I cannot help you with that right now, my child.")
ENDIF


Command(INTL( 483, "NAME"))
INTL( 12342, "My name is Gunthar, but you may call me father Gunthar.")

Command(INTL( 11737, "GUNTHAR"))
INTL( 12343, "Yes, that is my name, although you may call me father Gunthar, child.")

CmdAND(INTL( 12344, "HIGH"), INTL( 2115, "PRIEST"))
INTL( 12345, "Yes, I am the high priest of Lighthaven.")

Command(INTL( 489, "WORK"))
INTL( 12346, "I am the High Priest of this town. My duties mostly involve teaching the priests, as well as an "
"occasional sermon or two.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12347, "Go with Artherk's blessing, my child.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 12348, "Perhaps the answer will come to you in your prayers.")
ELSE
	Conversation
	INTL( 12349, "I am old now, my child. My memory is not what it used to be.")
ENDIF

EndTalk
}
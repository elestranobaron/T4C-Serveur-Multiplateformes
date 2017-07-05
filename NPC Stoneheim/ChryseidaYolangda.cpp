#pragma hdrstop
#include "ChryseidaYolangda.h"

ChryseidaYolangda::ChryseidaYolangda()
{}

ChryseidaYolangda::~ChryseidaYolangda()
{}

extern NPCstructure::NPC ChryseidaYolangdaNPC;

void ChryseidaYolangda::Create( void )
{
   npc = ChryseidaYolangdaNPC;
	SET_NPC_NAME( "[10839]Chryseida Yolangda" );
   npc.InitialPos.X = 255;
   npc.InitialPos.Y = 740;
	npc.InitialPos.world = 0; 
	npc.boPrivateTalk = TRUE;
}
				 
void ChryseidaYolangda::OnTalk( UNIT_FUNC_PROTOTYPE )

{ 

CONSTANT nNumHints = 20; // If you add a hint in her ball reading, update this value! 
CONSTANT PayHint = 1;

InitTalk

Begin
INTL( 9376, "Well, well. I see that you are a wanderer, too.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9377, "I am known as Chryseida Yolangda, the wandering \"gypsy\".") 

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 9378, "I wander around the world in \"search\" of kindred spirits. I can also \"foretell\" "
"your future, but only once an hour.")

Command2(INTL( 9379, "GYPSY"),INTL( 9380, "GYPSIE"))
INTL( 9381, "This title bears a lot of incomfort to the townspeople but I can assure you "
"that I am no thief nor a charlatan.")

Command(INTL( 9382, "CRYSTAL BALL"))
INTL( 9383, "Let me look into it... I see nothing!")

CmdAND(INTL( 10765, "SYMBOL"),INTL( 10272, "HOPE")) 
INTL( 10766, "Why yes, I have some of those. I might also have a few items of interest to you. Feel "
"free to browse through them.") 
CreateItemList
	AddBuyItem( 12, __OBJ_TORCH )
	AddBuyItem( 50, __OBJ_LIGHT_HEALING_POTION )
	AddBuyItem( 125, __OBJ_HEALING_POTION )
	AddBuyItem( 300, __OBJ_SERIOUS_HEALING_POTION )
	AddBuyItem( 50, __OBJ_POTION_OF_MANA )	   
	AddBuyItem( 150, __OBJ_MANA_ELIXIR ) 
	AddBuyItem( 1000, __OBJ_POTION_OF_CURE_RABIES ) 
	AddBuyItem( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
	AddBuyItem( 10000, __OBJ_SCROLL_OF_WINDHOWL )
	AddBuyItem( 25000, __OBJ_SCROLL_OF_SILVERSKY )
	AddBuyItem( 50000, __OBJ_SCROLL_OF_STONECREST ) 
	AddBuyItem( 10000, __OBJ_SYMBOL_OF_HOPE)
	AddBuyItem( 2000, __OBJ_MANDRAKE )
SendBuyItemList

Command(INTL( 1304, "BUY"))
INTL( 9384, "I might have a few items of interest to you. Feel free to browse "
"through them.")
CreateItemList
	AddBuyItem( 12, __OBJ_TORCH )
	AddBuyItem( 50, __OBJ_LIGHT_HEALING_POTION )
	AddBuyItem( 125, __OBJ_HEALING_POTION )
	AddBuyItem( 300, __OBJ_SERIOUS_HEALING_POTION )
	AddBuyItem( 50, __OBJ_POTION_OF_MANA )	   
	AddBuyItem( 150, __OBJ_MANA_ELIXIR ) 
	AddBuyItem( 1000, __OBJ_POTION_OF_CURE_RABIES ) 
	AddBuyItem( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
	AddBuyItem( 10000, __OBJ_SCROLL_OF_WINDHOWL )
	AddBuyItem( 25000, __OBJ_SCROLL_OF_SILVERSKY )
	AddBuyItem( 50000, __OBJ_SCROLL_OF_STONECREST ) 
	AddBuyItem( 10000, __OBJ_SYMBOL_OF_HOPE)
	AddBuyItem( 2000, __OBJ_MANDRAKE )
SendBuyItemList

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 9385, "I can't help you find him, but I'm sure you don't need me to tell you where he is. "
	"Simply follow your heart and you should be able to find him.")
ELSE
	Conversation
	INTL( 9386, "The Oracle? Oh, he definitely exists, but only the very worthy or the very "
	"unworthy can see him.")
ENDIF

Command(INTL( 1306, "SELL"))
INTL( 9387, "Let's see what you have to sell then.")
CreateItemList
	AddSellItem( PAWNSHOP, 0, 100000 )
	AddSellItem( MAGIC, 0, 100000 )
	AddSellItem( POTION, 0, 100000 )
	AddSellItem( JEWEL, 0, 100000 )
SendSellItemList( INTL( 4250, "It seems there is nothing I want after all.") )

Command(INTL( 9388, "SEARCH"))
INTL( 9389, "Well, wandering the country like this, I have developed an uncanny ability to discover what is \"hidden\", be it "
"objects left by thieves, or animals trying to hide themselves from me. If you wish, I could \"teach\" you this "
"ability, for a price.")

Command2(INTL( 9390, "HIDDEN"), INTL( 9391, "HIDE"))
INTL( 9392, "Yes, there is one that I know who has a knack for hiding things. We used to play hide and go seek when we were but "
"little children, although he would never tell you that. It has been a long time since I have heard from him though, "
"and I doubt he would remember me. His name was Meltar. If you ever see him, ask him to teach you how to hide.")
IF (CheckFlag(__FLAG_CHRYSEIDA_TOLD_ABOUT_MELTAR) == 0)
	GiveFlag(__FLAG_CHRYSEIDA_TOLD_ABOUT_MELTAR,1) 
ENDIF 

Command(INTL( 3868, "ALTHEA"))
INTL( 3869, "Althea is the name of the world in which we live in.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 9393, "Raven's Dust is an island located south of \"Arakas\". I am sure that "
"you've already visited it.")

Command4(INTL( 554, "HELP"),INTL( 4275, "HINT"),INTL( 9396, "CLUE"),INTL( 9397, "FORETEL")) 
""
IF((CheckFlag(__QUEST_TIMER_CHRYSEIDA_HINTS) <= CurrentRound) || (CurrentRound < (CheckFlag(__QUEST_TIMER_CHRYSEIDA_HINTS)-72000)) )
	SWITCH(rnd.roll(dice (1,nNumHints)) ) 
		CASE(1)
			Conversation
			INTL( 9401, "There are six collectors on Stoneheim: Headhunter Wajpoothin, Khan Wulgworth, Grant Hornkeep, "
			"King Aedenas Gravesoul, Beltigan Whitesword and Mordenthal. If you ask them nicely, perhaps "
			"they'll send you on a quest to help them with their collections.")
		ENDCASE
		CASE(2)
			IF(CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) > 0)
				IF(rnd.roll(dice(1,2)) > 1)
					Conversation
					INTL( 9402, "In my crystal ball, I can see you... talking to a horse. It is a beautiful animal... "
					"and it talks. It appears you have befriended it, but it was a long process.")
				ELSE
					Conversation
					INTL( 9403, "In my crystal ball, I can see you... talking to a dark centaur... A sense of dread "
					"looms over him. I see clouds... treachery... but a fair exchange at the same time.")
				ENDIF
			ELSE
				Conversation
				INTL( 9404, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(3)
			IF(CheckItem(__OBJ_ASSASSIN_BLADE) > 0)
				Conversation
				INTL( 9405, "In my crystal ball, I can see you talking to a crook... light-footed, he is, unless "
				"that is his name. It's not clear. You say something, but I can't hear it all. I can "
				"make out the words 'assassin' and 'blade', but the rest is all whispers.")
			ELSE
				Conversation
				INTL( 9406, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(4)
			IF(CheckItem(__OBJ_GRIM_BLADE_OF_WAR) > 0)
				Conversation
				INTL( 9407, "In my crystal ball, I can see you talking to a very, very evil warrior. He takes a "
				"grim sword from your hands and gives you a black gem. No, wait! He takes another sword "
				"from you... then another... and another. His name is... oh dear! It's Mordenthal "
				"himself! What a dark path you walk!")
			ELSE
				Conversation
				INTL( 9408, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(5)
			IF(CheckItem(__OBJ_ROBE_OF_HELL) > 0)
				Conversation
				INTL( 9409, "In my crystal ball, I can see you talking to a sinister man... His name is J... "
				"Justin? Jules? It's not very clear, I'm afraid. He wants something from you, a "
				"robe... An infernal robe? You give it to him, with two others, and he exchanges "
				"them for a staff.")
			ELSE
				Conversation
				INTL( 9410, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(6)
			IF(CheckItem(__OBJ_BOW_OF_CENTAUR_SLAYING) > 0)
				Conversation
				INTL( 9411, "In my crystal ball, I can see you talking to a very, very beautiful female warrior. "
				"She confiscates some bows from you, but compensates you for your loss by giving you "
				"a cloak of some kind. Oh, I recognize her, now! It's Resha, from Stonecrest.")
			ELSE
				Conversation
				INTL( 9412, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(7)
			IF(CheckItem(__OBJ_BROKEN_ETHEREAL_KEY) > 0)
				Conversation
		 		INTL( 9413, "In my crystal ball, I can see you talking to a young man... He is the son of a very "
				"powerful creature... a Seraph! He takes the key from your hand, I can see it! "
				"He gestures over it, and restores it. His name... I can't sense it. He lives in the "
				"shadow of Beltigan, so perhaps that will help.")
			ELSE
				Conversation
				INTL( 9414, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(8)
			IF((CheckFlag(__FLAG_FACTION_WITH_THIEVES) > 600) AND (CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) == 0))
				Conversation
				INTL( 9415, "In my crystal ball, I can see you talking to a rogue... He... he is handing you "
				"a strange item. I think it's... a crown. It is corrupt, an evil item. What could you "
				"be doing that?")
			ELSE
				Conversation
				INTL( 9416, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(9)
			IF((CheckFlag(__FLAG_NUMBER_OF_SKULLS_TURNED_IN) < 100) AND (CheckItem(__OBJ_VILLAIN_SKULL) >= 10))
				Conversation
				INTL( 9417, "In my crystal ball, I can see you talking to Delnar Steelblade. I do not know where "
				"he is now, I fear... You give him skulls and he rewards you. I can't see what "
				"he gives you, but you said something about 'villains' and 'skulls'. That is all I see.")
			ELSE
				Conversation
				INTL( 9418, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(10)
			IF((CheckItem(__OBJ_SKULL_OF_OGRIMAR) > 0) AND (CheckItem(__OBJ_BLOOD_OF_OGRIMAR) > 0))
				Conversation
				INTL( 9419, "In my crystal ball, I can see you talking to a very, very evil warrior. You ask him "
				"for some bones several times, and he finally gives them to you. The bones don't "
				"really look like bones, but that's what they are called anyway. This bodes great ill, "
				"I tell you.")
			ELSE
				Conversation
				INTL( 9420, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(11)
			IF(((CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 14) || (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 15)) AND (CheckFlag(__FLAG_USER_GOT_ROEN_RING) == 0))
				Conversation
				INTL( 9421, "In my crystal ball, I can see you talking to a strange man of the woods. He is a hunter "
				"and a teacher... You talk to him and he says he has dreamt of you... And he gives you "
				"a ring, a beautiful, precious ring. He has little else to tell you and you leave.")
			ELSE
				Conversation
				INTL( 9422, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(12)
			IF(CheckFlag(__FLAG_USER_HAS_BLOOD_OF_OGRIMAR) == 0 && CheckItem(__OBJ_DEMONIC_BLOOD) >= 3 && CheckItem(__OBJ_FOUL_POTION) >= 2 && CheckItem(__OBJ_BLACK_WIDOW_VENOM) >= 5)
				Conversation
				INTL( 9423, "In my crystal ball, I can see you talking to a man named... It escapes me. He is a dark bishop "
				"and lives in a dark temple. You carry a number of foul items in your backpack, and you give "
				"them to him. He... rewards you with... the blood of an evil god, although that might just be "
				"a metaphor.")
			ELSE
				Conversation
				INTL( 9424, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(13)
			IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1 && CheckItem(__OBJ_VILLAIN_SKULL) >= 2 && CheckItem(__OBJ_SCROLL_OF_HATE) >= 2)
				Conversation
				INTL( 9425, "In my crystal ball, I can see you talking to a skraug. I think... Yes, it's a female "
				"skraug. Her name... She says her name is Oogla. She takes some of the things you carry and "
				"gives you a skull... an evil skull. My crystal ball shows nothing else, I'm sorry.")
			ELSE
				Conversation
				INTL( 9426, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(14)
			IF(CheckFlag(__FLAG_USER_HAS_SKULL_OF_EVIL) >= 1 && CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) >= 1 && CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) >= 2 && CheckFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN) == 0 )
				Conversation
				INTL( 9427, "In my crystal ball, I can see you talking to a centaur. He is both noble and evil, I'm sorry to "
				"say... He tells you about a chest with a fake bottom, about a dark bishop... and something "
				"called the Skull of Ogrimar. I'd rather not say any more about this, I apologize.")
			ELSE
				Conversation
				INTL( 9428, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(15)
			IF((CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 5) && (CheckFlag(__QUEST_TIMER_FANGS_OF_TRUE_RESOLVE) == 0))
				Conversation
				INTL( 9429, "In my crystal ball, I can see you talking to a priest of Artherk. You say something "
				"about some Fangs of True Resolve, and he sends you on a quest to earn them. he says "
				"to find Ruby Dragon Fangs and some kind of eternal candles... I can't quite hear "
				"the rest.")
			ELSE
				Conversation
				INTL( 9430, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(16)
			IF((CheckFlag(__QUEST_FLAG_ARTHERK_HEART) == 0) && CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1)
				Conversation
				INTL( 9431, "In my crystal ball, I can see you talking to a white sorceress... Oh, it's Mithanna! "
				"She tells you about the 'Heart of Artherk', and you leave on a quest to find it. There "
				"are still many trials ahead, I fear. I wish you good luck!")
			ELSE
				Conversation
				INTL( 9432, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(17)
			IF((CheckFlag(__QUEST_FLAG_ARTHERK_SOUL) == 0) && CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1)
				Conversation
				INTL( 9433, "In my crystal ball, I can see you talking to a priest of Artherk... Nissus, I believe. "
				"He tells you about the 'Soul of Artherk', and you leave on a quest to find it. There "
				"are still many trials ahead, I fear. I wish you good luck.")
			ELSE
				Conversation
				INTL( 9434, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(18)
			IF(CheckFlag(__QUEST_FLAG_ARTHERK_WILL) == 1)
				Conversation
				INTL( 9435, "In my crystal ball, I can see you talking to a white-winged woman. Her name is too "
				"long and complex for me to pronounce. I believe it happened in the past. Now, I see "
				"you")
			ELSE
				Conversation
				INTL( 9436, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDIF
		ENDCASE
		CASE(19)
			SWITCH(CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST))
				CASE(1)
					Conversation
					INTL( 9437, "In my crystal ball, I can see you talking to a proud king, a centaur. He "
					"says something about a White Crow... I wonder, could he be talking about "
					"a snow raven?")
				ENDCASE
				CASE(2)
					Conversation
					INTL( 9438, "In my crystal ball, I can see you talking to Mithanna Showraven. I can see her "
					"clearly. You mention the Will of Artherk, and she proposes a deal to you in "
					"exchange for her assistance.")
				ENDCASE
				CASE(3)
					Conversation
					INTL( 9439, "In my crystal ball, I can see you talking to Mithanna Snowraven. You are "
					"bringing her several items... A Jade Ring of Sorcery and six pairs of "
					"tarantula eyes. In exchange, she tells you something, but I can't hear it...")
				ENDCASE
				CASE(4)
					Conversation
					INTL( 9440, "In my crystal ball, I can see you talking to Nissus Haloseeker. You ask him "
					"about the Fangs of True Resolve... and he tells you what you need in order "
					"to fashion them for you. It has to do with ruby fangs and infinite candles, "
					"something like that.")
				ENDCASE
				CASE(5)
					Conversation
					INTL( 9441, "In my crystal ball, I can see you talking to King Gravesoul, ruler of the "
					"Centaur people. He asks you for help. There is a problem in the village of the "
					"Centaurs, and he needs you to free some of his people.")
				ENDCASE
				CASE(6)
					Conversation
					INTL( 9442, "In my crystal ball, I can see you talking to King Gravesoul, ruler of the "
					"Centaur people. He asks you for help. There is a problem in the village of the "
					"Centaurs, and he needs you to free some of his people.")
				ENDCASE
				CASE(7)
					Conversation
					INTL( 9443, "In my crystal ball, I can see you hitting red-eyed centaurs over the head with "
					"a special staff. It's a strange sight, really.")
				ENDCASE
				CASE(8)
					Conversation
					INTL( 9444, "In my crystal ball, I can see you hitting red-eyed centaurs over the head with "
					"a special staff. It's a strange sight, really.")
				ENDCASE
				CASE(9)
					Conversation
					INTL( 9445, "In my crystal ball, I can see you battling shadowing, almost invisible creatures. "
					"They surround you and a centaur smith... I believe his name is Starefire... It's "
					"not very clear.")
				ENDCASE
				CASE(10)
					Conversation
					INTL( 9446, "In my crystal ball, I can see you talking to a centaur, a smith. Thor Glarefire, "
					"I can hear his name, now. He tells you about the Hammer of Finality, whatever "
					"that is.")
				ENDCASE
				CASE(11)
					Conversation
					INTL( 9447, "In my crystal ball, I can see you talking to a centaur, a smith. Thor Glarefire, "
					"I can hear his name, now. He tells you about the Hammer of Finality, whatever "
					"that is.")
				ENDCASE
				CASE(12)
					Conversation
					INTL( 9448, "In my crystal ball, I can see you talking to a bare-chested man, someone I've "
					"never seen on Stonecrest. He's a smith. You've been told he could manufacture "
					"the item you seek.")
				ENDCASE
				CASE(13)
					Conversation
					INTL( 9449, "In my crystal ball, I can see you talking to a bare-chested man, someone I've "
					"never seen on Stonecrest. He's a smith. You've been told he could manufacture "
					"the item you seek.")
				ENDCASE
				CASE(14)
					Conversation
					INTL( 9450, "In my crystal ball, I can see you talking to a bare-chested man, someone I've "
					"never seen on Stonecrest. He's a smith. You've been told he could manufacture "
					"the item you seek.")
				ENDCASE
				CASE(15)
					Conversation
					INTL( 9451, "In my crystal ball, I see you standing at a crossroad. On one side, you are "
					"talking to a man named Greenleaf, on the other, you are talking to a man "
					"from the land of the Raven's Dust, someone named Brown Bart, I believe.")
				ENDCASE
				CASE(16)
					Conversation
					INTL( 9452, "In my crystal ball, I can see you talking to King Gravesoul one more time. "
					"You ask him about the Will of Artherk one last time, and he gives you a "
					"special key.")
				ENDCASE
				CASE(17)
					Conversation
					INTL( 9453, "In my crystal ball, I can see you talking to Beltigan Whitesword. After you ask "
					"him to assemble something for you, he performs a magical ritual and gives you "
					"the Key of Artherk.")
				ENDCASE
				OTHERWISE
					Conversation
					INTL( 9454, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
			ENDSWITCH
		ENDCASE
		OTHERWISE
			Conversation
			INTL( 9455, "I fear I see... nothing. Perhaps I can try again, if you *really* need a \"hint\"?")
	ENDSWITCH							 
	GiveFlag(__QUEST_TIMER_CHRYSEIDA_HINTS,CurrentRound + 72000)
	Conversation
	INTL( 11346, " Visit me again in an hour if you want more \"hints\".")
ELSE
	Conversation
	INTL( 11347, "It is too soon, now. Come back later and I will look into your future again.")
ENDIF

Command(INTL( 515, "ARAKAS"))
INTL( 9458, "Arakas is located somewhere to the north of \"Raven's\" \"Dust\".")

Command5(INTL( 697, "ASSHOLE"),INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 1919, "WHORE"),INTL( 698, " ASS "))
INTL( 9459, "Have you ever heard such a thing as a gypsy curse?")
BREAK

Command4(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"))
INTL( 1075, "Farewell.")
BREAK

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// SEARCH ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Command2(INTL( 495, "LEARN"), INTL( 496, "TEACH"))
""
;const int nLEVEL = 20;
const int nINT = 25;
IF( USER_LEVEL < nLEVEL )
	IF( USER_TRUE_INT < nINT )
		Conversation
		FORMAT( INTL( 9460, "You need %u more levels and %u more intelligence to learn search."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
	ELSE
		Conversation
		FORMAT( INTL( 9461, "You need %u more levels to learn search."), nLEVEL - USER_LEVEL )
	ENDIF
ELSE
	IF( USER_TRUE_INT < nINT )
		Conversation
		FORMAT( INTL( 9462, "You need %u more intelligence to learn search."), nINT - USER_TRUE_INT )
	ELSE
		Conversation
		INTL( 9463, "Splendid! Let us proceed then.")
		CreateSkillList
			AddTeachSkill( __SKILL_SEARCH, 1, 2000 )
		SendTeachSkillList
	ENDIF
ENDIF

Command(INTL( 502, "TRAIN"))
""
IF( UserSkill(__SKILL_SEARCH) == 0 )
	Conversation
	INTL( 814, "You must \"learn\" the skill before I can train you.")
ELSEIF( UserSkill(__SKILL_SEARCH) < 100 )
		Conversation
		INTL( 1481, "Very good, then let's begin your training.")
		CreateSkillList
			AddTrainSkill( __SKILL_SEARCH, 100, 50 )
		SendTrainSkillList	
ELSE
	Conversation
	INTL( 9464, "I have taught you all that I know. You are already a master of search!")
ENDIF

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 9465, "I am afraid that I do not know.")
ELSE
   Conversation
   INTL( 9466, "I am sorry but my crystal ball is broken on that one.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void ChryseidaYolangda::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Chryseida data function, handles her shop and skill
// 
//////////////////////////////////////////////////////////////////////////////////////////
{


NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_SEARCH, 1, 2000 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN		 
		TRAIN_SKILL( __SKILL_SEARCH, 100, 50 )
	CLOSE_NPC_DATA_TRAIN

	NPC_SHOP_DATA

      NPC_SELL( 12, __OBJ_TORCH )
		NPC_SELL( 50, __OBJ_LIGHT_HEALING_POTION )
		NPC_SELL( 50, __OBJ_POTION_OF_MANA )
		NPC_SELL( 125, __OBJ_HEALING_POTION )
		NPC_SELL( 300,   __OBJ_SERIOUS_HEALING_POTION ) 
		
		NPC_SELL( 150, __OBJ_MANA_ELIXIR) 
		NPC_SELL( 1000, __OBJ_POTION_OF_CURE_RABIES ) 
		NPC_SELL( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
		NPC_SELL( 10000, __OBJ_SCROLL_OF_WINDHOWL )
		NPC_SELL( 25000, __OBJ_SCROLL_OF_SILVERSKY )
		NPC_SELL( 50000, __OBJ_SCROLL_OF_STONECREST ) 
		NPC_SELL( 10000, __OBJ_SYMBOL_OF_HOPE )        
		NPC_SELL( 2000, __OBJ_MANDRAKE )
      NPC_BUY( PAWNSHOP, 0, 10000 )
      NPC_BUY( MAGIC, 0, 10000 )
      NPC_BUY( POTION, 0, 10000 )
      NPC_BUY( JEWEL, 0, 10000 )

      NPC_SOLD_ITEM(  INTL( 9467, "Thank you!") )
      NPC_FAILED_SELL( INTL( 9468, "You do not have enough gold coins."))
      NPC_BOUGHT_ITEM( INTL( 9469, "We have a deal.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
}


// Araknor.cpp: implementation of the Araknor class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Araknor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Araknor::Araknor()
{}

Araknor::~Araknor()
{}

extern NPCstructure::NPC AraknorNPC;

void Araknor::Create(){
	npc = AraknorNPC;
	SET_NPC_NAME( "[3029]Araknor" );
	npc.InitialPos.X = 2981;
	npc.InitialPos.Y = 1035;
	npc.InitialPos.world = 0;
	SET_RANGE(5,5,5,5);
}

void Araknor::OnTalk( UNIT_FUNC_PROTOTYPE ){

CONSTANT MAKESCROLL = 1;
CONSTANT BOOK = 2; 
CONSTANT CREATESCROLLS = 3;
CONSTANT NumberOfScrollsToBeMade = 4;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS) != 0)
	IF(CurrentRound < CheckFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS))
		IF(CurrentRound > 6000 * CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS))
			IF(Gold >= 10000 * CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS))								  					 
				FOR(0, CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS))
					TakeGold(10000)
					GiveItem(__OBJ_NECROMANTIC_SCROLL)
				ENDFOR				
				Conversation
				INTL( 10063, "I have finished the task set before me. Here is what you asked for.")
				IF(CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS) == 1)
					PRIVATE_SYSTEM_MESSAGE(INTL( 10064, "Araknor gives you a necromantic scroll."))
					PRIVATE_SYSTEM_MESSAGE(INTL( 10065, "Araknor takes 10000 gold."))
				ELSE
					PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 10066, "Araknor gives you %u necromantic scrolls."), CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS)))
					PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 10067, "Araknor takes %u gold."), 10000 * CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS)))
				ENDIF
				RemFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS) 
				RemFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS)
			ELSE
				Conversation
				FORMAT(INTL( 10068, "I suggest you return when you have at least %u gold to pay for the scrolls."), 10000 * CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS))
				BREAK
			ENDIF
		ELSE
			Conversation
			INTL( 10069, "I will need more time... come back again later.")
			BREAK
		ENDIF
	ELSEIF(CurrentRound >= CheckFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS) + 6000 * CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS))
		IF(Gold >= 10000 * CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS))
			FOR(0, CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS))
				TakeGold(10000)
				GiveItem(__OBJ_NECROMANTIC_SCROLL)
			ENDFOR			
			Conversation
			INTL( 10063, "I have finished the task set before me. Here is what you asked for.")
			IF(CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS) == 1)
				PRIVATE_SYSTEM_MESSAGE(INTL( 10064, "Araknor gives you a necromantic scroll."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 10065, "Araknor takes 10000 gold."))
			ELSE
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 10066, "Araknor gives you %u necromantic scrolls."), CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS)))
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 10067, "Araknor takes %u gold."), 10000 * CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS)))
			ENDIF
			RemFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS) 
			RemFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS)
		ELSE
			Conversation
			FORMAT(INTL( 10068, "I suggest you return when you have at least %u gold to pay for the scrolls."), 10000 * CheckFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS))
			BREAK
		ENDIF
	ELSE
		Conversation
		INTL( 10069, "I will need more time... come back again later.")
		BREAK
	ENDIF
ELSE 
	Conversation
	INTL( 1155, "... Yes? Be brief, I have \"important\" matters to attend to.")
ENDIF

Command(INTL( 10070, "NECROMANTIC SCROLL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 10071, "You need some necromantic scrolls? Hmm, I suppose I can sell some to you. I don't have any right now so you must give me "
	"time to make some. I must warn you that they will cost no less than 10000 gold each. Do you still want me to create some?")
	SetYesNo(CREATESCROLLS)
ELSE
	Conversation
	INTL( 624, "What are you talking about?")
ENDIF

YES(CREATESCROLLS)
	Conversation
	INTL( 10072, "Very well, I shall begin right away. Now tell me, how many scrolls will you require?")
	;YesNo = NumberOfScrollsToBeMade;
NO(CREATESCROLLS)
	Conversation
	INTL( 10603, "Very well. What do you want then?")
YesNoELSE(CREATESCROLLS)
	Conversation
	INTL( 10604, "Do you want me to create some necromantic scrolls or not?")
	SetYesNo(CREATESCROLLS)

;} else if( ( msg.Find( INTL( 10073, "NONE") ) != -1 ) && YesNo == NumberOfScrollsToBeMade) {;YesNo = 0;
Conversation
INTL( 10074, "If you don't want any, then why did you ask me in the first place?")

;} else if( ( msg.Find( INTL( 10075, "DON'T WANT") ) != -1 ) && YesNo == NumberOfScrollsToBeMade) {;YesNo = 0;
Conversation
INTL( 10074, "If you don't want any, then why did you ask me in the first place?")

;} else if( ( msg.Find( INTL( 10076, "DONT WANT") ) != -1 ) && YesNo == NumberOfScrollsToBeMade) {;YesNo = 0;
Conversation
INTL( 10074, "If you don't want any, then why did you ask me in the first place?")

;} else if( ( msg.Find( INTL( 519, "LEAVE") ) != -1 ) && YesNo == NumberOfScrollsToBeMade) {;YesNo = 0;
Conversation
INTL( 1211, "Remember, the dead will always walk the realm.")
BREAK

;} else if( ( ( msg.Find( INTL( 7311, " 1 ") ) != -1 ) || ( msg.Find( INTL( 10507, " ONE ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 1)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10508, "Good. I estimate this will take around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10509, " 2 ") ) != -1 ) || ( msg.Find( INTL( 10510, " TWO ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 2)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10511, " 3 ") ) != -1 ) || ( msg.Find( INTL( 10512, " THREE ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 3)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10513, " 4 ") ) != -1 ) || ( msg.Find( INTL( 10514, " FOUR ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 4)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10515, " 5 ") ) != -1 ) || ( msg.Find( INTL( 10516, " FIVE ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 5)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10517, " 6 ") ) != -1 ) || ( msg.Find( INTL( 10518, " SIX ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 6)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10519, " 7 ") ) != -1 ) || ( msg.Find( INTL( 10520, " SEVEN ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 7)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10521, " 8 ") ) != -1 ) || ( msg.Find( INTL( 10522, " EIGHT ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 8)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10523, " 9 ") ) != -1 ) || ( msg.Find( INTL( 10524, " NINE ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 9)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if( ( ( msg.Find( INTL( 10525, " 10 ") ) != -1 ) || ( msg.Find( INTL( 10526, " TEN ") ) != -1 ) ) && YesNo == NumberOfScrollsToBeMade) {;
GiveFlag(__FLAG_NUMBER_OF_NECROMANTIC_SCROLLS_USER_WANTS, 10)
GiveFlag(__FLAG_TIMER_ARAKNOR_STARTED_MAKING_SCROLLS, CurrentRound)
Conversation
INTL( 10081, "Good. I estimate each scroll will take me around 5 minutes to make.")
BREAK

;} else if(YesNo == NumberOfScrollsToBeMade) {;
Conversation
INTL( 10082, "Please choose a quantity between 1 and 10. How many scrolls do you want?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1156, "I go by the name of Araknor the \"dark\".")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1157, "I am the necromancer of this tower. I gather information about the dead. "
"The townsfolk resent my presence because of my profession.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command(INTL( 1161, "APPRENTICE"))
""
IF (CheckFlag(__FLAG_ARAKNOR_APPRENTICE) >= 1)
	Conversation
	INTL( 1162, "The path of the necromancer is not an easy one. As your first lesson, I can \"teach\" you how "
	"to cast the lesser drain spell.")
ELSE
	Conversation
	INTL( 1163, "The path of the necromancer is not an easy one. I sense you are not quite ready yet to become "
	"my apprentice.")
ENDIF

Command2(INTL( 495, "LEARN"), INTL( 496, "TEACH"))
INTL( 7509, "Let's begin the lesson then.")
CreateSkillList
	AddTeachSkill (__SPELL_LESSER_DRAIN, 13, 7152)
SendTeachSkillList

Command(INTL( 1175, "BLANK MAGIC SCROLL"))
INTL( 1176, "Are you here to ask me to make a blank magic scroll for you?")
SetYesNo(MAKESCROLL)

YES(MAKESCROLL)
   IF ((CheckItem(__OBJ_RUNIC_SCRIPTING_KIT) > 0) AND (CheckItem(__OBJ_PLAIN_BLANK_SCROLL) >0) AND (Gold >= 500))
      Conversation
      INTL( 1177, "Hmph. Looks like you've got everything. Let's get to work, then... Here we go. "
		"Your very own blank magic scroll...")
		TakeItem(__OBJ_PLAIN_BLANK_SCROLL)
		TakeGold(500)
		GiveItem(__OBJ_BLANK_MAGIC_SCROLL)
	ELSE
		Conversation
		INTL( 1178, "It's like I said: a runic scripting kit, a plain blank scroll and 500 gold pieces. "
		"Just come back when you have everything.")
	ENDIF

NO(MAKESCROLL)
Conversation
INTL( 1179, "Well, let me tell you, having blank magic scrolls is necessary if you're ever going to "
"own a \"scroll\" \"of\" \"enchantment\". All self-respecting magic-users always have a few handy.")

YesNoELSE(MAKESCROLL)
Conversation
INTL( 1180, "*sigh* As you wish.")

Command(INTL( 1181, "SCROLL OF ENCHANTMENT"))
INTL( 1182, "Scroll of enchantments are scrolls which some wizards use to improve some magical "
"items. They're not easy to make, but they're pretty handy. Don't look at me, I don't "
"sell these scrolls. Whatever I get, I keep for myself.")

Command(INTL( 1183, "DARK"))
INTL( 1184, "I follow the dark path of \"necromancy\".")

Command(INTL( 1185, "IMPORTANT"))
INTL( 1186, "I must contend with the dreaded necromancer known as \"Jarko\", also known as "
"the \"Decrepit\" One. I must have his \"spellbook\". I MUST!")

Command(INTL( 1187, "DECREPIT"))
INTL( 1188, "When you see Jarko, you will know what I mean by this.")

Command(INTL( 1189, "PAY"))
INTL( 1190, "The only reason the people of this town are letting me stay here is because "
"of the vast resources that I own. If it wasn't for that, I would have been "
"kicked out a long time ago. I have also heard a rumor that several \"brigands\" "
"have started harrassing the citizens and the merchants lately.")

Command(INTL( 565, "BRIGAND"))
INTL( 1191, "Brigands have regrouped recently to attack any merchant who crosses the "
"forest. It is a rather strange thing since they usually fight among "
"themselves. They must have chosen a leader. But in any case, I don't "
"care much about them or anything they might do. As long as they don't "
"cross my path, I won't have to kill them.. I despise wasting valuable power.")

Command2(INTL( 1192, "NECROMANCY"),INTL( 693, "NECROMANCER"))
INTL( 1193, "The art of necromancy is surely the greatest of all. It gives you control "
"over death and can bring forth people who were once themselves dead. It "
"is a path that few follow for that it is a dark one that will "
"surely darken your soul. But the loss of a soul is a very small "
"price to pay for such a power! The only one with powers equal to mine "
"on this island is \"Jarko\".")

Command(INTL( 475, "STONE OF LIFE"))
""
IF (CheckItem (__OBJ_STONE_OF_LIFE) > 0)
   GetItemHandle( __OBJ_STONE_OF_LIFE, StoneOfLife )
   IF (CheckUnitFlag (StoneOfLife, __ITEM_QUEST_STONE_OF_LIFE)  == (CheckGlobalFlag (__QUEST_STONE_OF_LIFE)) && (CheckGlobalFlag (__QUEST_STONE_OF_LIFE) > CurrentRound ) )
      Conversation
      INTL( 1194, "I can feel the power of the Stone of Life! I sense its energies, pulsating "
      "as if... it could not be.. but.. it is.. alive..? {Araknor} {swiftly} {takes} {the} "
      "{Stone} {of} {Life} Here, I will give you this strange weapon in exchange.. I think "
      "it's called Shadowblade... yes... that is it.")
      GiveItem( __OBJ_SHADOW_BLADE )
      TakeItemHandle (StoneOfLife) 	
		;int nNumStonesOfLife = CheckItem( __OBJ_STONE_OF_LIFE );
      FOR( 0,  nNumStonesOfLife)
         TakeItem(__OBJ_STONE_OF_LIFE) 
      ENDFOR
   ELSE
      Conversation
      INTL( 1195, "The Stone of Life you owned is worth nothing! Pah! Dust to dust, it "
      "shall return whence it came.")
      TakeItemHandle (StoneOfLife)
   ENDIF
ELSE
    Conversation
    INTL( 1196, "The Stone of Life? I do not know much about it.")
ENDIF

Command(INTL( 541, "JARKO"))
INTL( 1197, "Jarko the necromancer dwells in the mountains in the northern part of this "
"island. He has two main armies, the goblins and the undeads. I can deal "
"easily with both of them, however. His \"spellbook\" could be very useful to me.") 

Command(INTL( 759, "SPELLBOOK"))
""
IF ((CheckItem(__OBJ_JARKO_SPELLBOOK) >= 1) && (CheckFlag(__FLAG_KILLED_JARKO) >= 1))
   IF (CheckNPCFlag (__JARKO_SPELLBOOK_TO_ARAKNOR) > CurrentRound)
      Conversation      
      INTL( 1198, "I am currently studying Jarko's spellbook! Yours is probably a fake one!")
   ELSE
      Conversation
      INTL( 1199, "You have Jarko's spellbook? Great! Do you agree to exchange that "
      "precious spellbook for a special item?")
      SetYesNo (BOOK)
   ENDIF
ELSEIF (CheckItem(__OBJ_JARKO_SPELLBOOK) == 1)
   Conversation
   INTL( 1200, "You claim to have Jarko's spellbook yet did not get it yourself? "
   "It's probably a fake one. Worse yet, it is perhaps a magical trap "
   "to lure inexperienced apprentices such as yourself.")
      IF(CheckItem(__OBJ_JARKO_SPELLBOOK) >1)
         Conversation
         INTL( 1201, "{Araknor} {takes} {the} {spellbooks} {you} {have} {and} {they} {burst} {into} {flames.}")
      ELSE
         Conversation
         INTL( 1202, "{Araknor} {takes} {the} {spellbook} {you} {have} {and} {it} {bursts} {into} {flames.}")
      ENDIF
	;int nNumSpellbooks = CheckItem(__OBJ_JARKO_SPELLBOOK);
   FOR(0, nNumSpellbooks)
      TakeItem(__OBJ_JARKO_SPELLBOOK)
   ENDFOR
ELSE
   Conversation
   INTL( 1203, "The spellbook is the most precious object a mage has. Whenever I can "
   "put my hands on an ancient spellbook, I literally devour its pages "
   "to learn new spells. Of course, more spells means more power for me.")
ENDIF

YES (BOOK)
IF (CheckItem (__OBJ_JARKO_SPELLBOOK) >= 1)
   TakeItem(__OBJ_JARKO_SPELLBOOK)
   GiveNPCFlag(__JARKO_SPELLBOOK_TO_ARAKNOR, rnd.roll( dice( 1, 2 ) ) HOURS TDELAY)
	GiveFlag(__FLAG_ARAKNOR_APPRENTICE, 1)
   Conversation
   INTL( 1204, "You shall not regret this young one. As a token of my appreciation, I will allow you to study "
	"the dark art as my \"apprentice\". Also, ")
   IF (rnd.roll( dice( 1, 2 ) ) == 1)
      Conversation
      INTL( 1205, "I give you this ring of confidence.")
      GiveItem (__OBJ_RING_OF_CONFIDENCE)
   ELSE
      Conversation
      INTL( 1206, "I give you this small ring of darkness. I do not know its exact properties, "
      "but I sense the magic pulsing within.")
      GiveItem (__OBJ_RING_OF_DARKNESS)
   ENDIF
ELSE
   Conversation
   INTL( 1207, "But you do not have the spellbook!")
ENDIF

NO (BOOK)
Conversation
INTL( 1208, "You are missing out on a great offer! There is nothing that you could possibly "
"achieve with that spellbook by yourself.") 

YesNoELSE (BOOK)
Conversation
INTL( 1209, "I see you are not interested with my offer... So be it!")

Command(INTL( 1159, "SCROLL"))
INTL( 1160, "If you have a plain blank scroll, I can help you make a \"blank\" \"magic\" \"scroll\", "
"but it'll cost you. You also need a runic scripting kit, but that's not something "
"I can help you with. I charge 500 gold for this service, so come prepared... and wealthy.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1210, "That wasn't smart.")
TakeGold(Gold)
BREAK

Command5(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1211, "Remember, the dead will always walk the realm.") BREAK

Default
INTL( 1212, "Do not bother me with this.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Araknor::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_LESSER_DRAIN, 13, 7152)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE

#pragma hdrstop
#include "Yrian.H"

Yrian::Yrian()
{}

Yrian::~Yrian()
{}

extern NPCstructure::NPC YrianNPC;
 
void Yrian::Create( void )
{
	npc = ( YrianNPC );
	SET_NPC_NAME( "[2910]Yrian Earthsong" );
	npc.InitialPos.X = 2877;
	npc.InitialPos.Y = 169;
	npc.InitialPos.world = 0;
}

void Yrian::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT HEAL = 1;
CONSTANT Odour = 2;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 13)
	Conversation
	INTL( 1103, "You are welcome in our forest as long as you don't harm it.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 13)
	Conversation
	INTL( 11781, "*Cough* *cough*... May the tranquility of the whispering leaves fill your soul. Are you "
	"the \"Traveler\" sent by the Winds to help us get rid *cough*... of this foul odour?")
	SetYesNo(Odour)
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 14)
	Conversation
	INTL( 11782, "Did you get my staff back? *cough*... Remember, the enemy camp is southeast near the water. "
	"Please hurry *cough*... before it's too late.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 15)
	IF(CheckItem(__OBJ_SOLINAE_STAFF) > 0)
		Conversation
		INTL( 11783, "*Cough*... Your arrival is as warm as a summer day sunrise! I can feel Solinae's staff in your "
		"possession.")
		GiveXP(75000)
		PRIVATE_SYSTEM_MESSAGE(INTL( 11784, "You receive 75000 experience points."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11785, "Solinae's staff leaves your hands and magically floats into Yrian's."))
		TakeItem(__OBJ_SOLINAE_STAFF)
		Conversation
		INTL( 11786, "I must thank you for this great service. The druids of Arakas will forever be in your debt. Now, "
		"about this \"Nomad\"...")
	ELSE
		Conversation
		INTL( 11787, "Once again, I wish to thank you for your help in retrieving my staff. Now, about this \"Nomad\"...")
	ENDIF
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 16)
	Conversation
	INTL( 11788, "I must thank you once again for your help, Traveler sent by the Winds. Remember, the one you were seeking "
	"earlier probably went west, near the gypsy settlement. You should hurry if you wish to catch up to him.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11789, "I wish you luck in your travels friend. I know you have a long journey ahead of you.")
ELSE
	Conversation
	INTL( 11790, "You have healed the land my child. I knew you were the Traveller send by the Winds. I knew it.")
ENDIF

YES(Odour)
	Conversation
	INTL( 11791, "You truly are a blessing! *Cough* *cough*... forgive me, I mustn't get excited in my \"state\".")
NO(Odour)
	Conversation
	INTL( 11792, "There must be a mistake *cough* *cough*... I must keep hoping the \"Traveler\" will come to us soon...")
YesNoELSE(Odour)
	Conversation
	INTL( 11793, "*Cough*... Are you the Traveler sent by the Winds to help us or not?")
	SetYesNo(Odour)

Command2(INTL( 11794, "STATE"), INTL( 11795, "ODOUR"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 13)
	Conversation
	INTL( 11796, "*Cough* *cough*... *sigh* Don't you smell it? Our Great Father is diseased and there isn't much I can do, "
	"as I don't have much time myself. Like our tree, I've been poisoned so that I don't offer any \"resistance\".")
ELSE
	Conversation
	INTL( 11797, "*Cough* *cough*... Perhaps I should rest now.")
ENDIF

Command(INTL( 11338, "RESISTANCE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 13)
	Conversation
	INTL( 11798, "Please, I implore you, Traveler sent by the Winds, help us! *Cough* *cough*... This all happened because of "
	"a man who calls himself \"Nomad\"!")
ELSE
	Conversation
	INTL( 11797, "*Cough* *cough*... Perhaps I should rest now.")
ENDIF

Command(INTL( 1322, "TRAVELER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 13)
	Conversation
	INTL( 11799, "It is written in our Ogham that a Traveler from the Tears of the Past will be sent by the Winds to cleanse "
	"the Land of its \"Wounds\". To this Traveler, the power of Balance will be given.")
ELSE
	Conversation
	INTL( 11797, "*Cough* *cough*... Perhaps I should rest now.")
ENDIF

Command(INTL( 11800, "WOUNDS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 13)
	Conversation
	INTL( 11801, "The land is screaming, my friend... *cough* it is suffering from something related to this \"odour\".")
ELSE
	Conversation
	INTL( 11797, "*Cough* *cough*... Perhaps I should rest now.")
ENDIF

Command(INTL( 11802, "NOMAD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 13)
	Conversation
	INTL( 11803, "He came with his minions and he asked for the location of a crypt. *Cough*... we didn't know what he was "
	"talking about and so we couldn't answer his questions. As a reward, he cursed our Great Father with this "
	"plague. If only I had my \"staff\", *cough* I could reverse the harm that he's done...")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 15)
	Conversation
	INTL( 11804, "He said that he was from a cult of some kind. He cursed our Great Tree while praying to some god he called "
	"Gluriurl. This \"crypt\" he was looking for was supposedly a temple to this god... *cough* *cough*.")
ELSE
	Conversation
	INTL( 11797, "*Cough* *cough*... Perhaps I should rest now.")
ENDIF

Command(INTL( 7292, "CRYPT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 15)
	Conversation
	INTL( 11805, "Yes, now it's coming back to me. He said something about the way to the temple being near a small gypsy "
	"settlement somewhat far west from here. Perhaps that would be a good place for you to search *cough*! "
	"Take this... May it protect you as it has protected me. Now, please forgive me, but I must rest now...")
	PRIVATE_SYSTEM_MESSAGE(INTL( 11806, "Yrian gives you a Guardian Ring of Vitality."))
	PRIVATE_SYSTEM_MESSAGE(INTL( 11807, "Yrian gives you a Gem of Vitality."))
	GiveItem(__OBJ_GUARDIAN_RING_OF_VITALITY)
	GiveItem(__OBJ_GEM_OF_VITALITY)
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 16)
ELSE
	Conversation
	INTL( 11797, "*Cough* *cough*... Perhaps I should rest now.")
ENDIF

Command(INTL( 8891, "STAFF"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 13)
	Conversation
	INTL( 11808, "My staff is an ancient relic that was created by the Great Druid Solinae the Eternal Child. *Cough* *cough*... "
	"It was created from the heart of the great tree whose seeds gave birth to our Great Father, centuries ago. "
	"Unfortunately, this Nomad saw the potential and he ordered his \"commander\" to take it from me.")
ELSE
	Conversation
	INTL( 11797, "*Cough* *cough*... Perhaps I should rest now.")
ENDIF

Command(INTL( 11809, "COMMANDER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 13)
	Conversation
	INTL( 11810, "In my weakened state, *cough* *cough*... I couldn't stop him. They've set up a camp southeast from here, "
	"near the water. Please! You must return my staff to me! *Cough* *cough*...")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 14)
ELSE
	Conversation
	INTL( 11797, "*Cough* *cough*... Perhaps I should rest now.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1104, "I am Yrian Earthsong, elder of this small community and founder of "
"the \"Order\" \"of\" \"Nature\".")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1105, "My priority is to protect nature from the insanity of humans and "
"foul creatures such as \"goblins\". The burden of keeping the "
"\"Stone\" \"of\" \"Life\" out of the hands of evil lies upon my "
"shoulders. Finally, I also have to instruct the young ones such as "
"\"Lantalir\" \"Rainmist\" how to control their growing power. I can probably "
"even \"teach\" you a \"spell\", if you're patient enough, that is.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1106, "Oh, I don't know if she's dead or alive for sure, but she left us to find "
"her true love years ago... Some say she lives with a troll, now. Me? I "
"just think it's hogwash and she died.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1107, "Balork cursed you, you say? I'm sorry to hear that. If \"Annabelle\" the "
"Blessed One was still here, she might be able to help you. But she's long "
"gone, now. I hear a troll took her away to feast upon her.") 

Command3(INTL( 507, "ORKANIS"),INTL( 484, "MHORGWLOTH"),INTL( 535, "TROLL"))
INTL( 1108, "Mhorgwloth lives in the now ruined Castle Orkanis in the northwestern "
"part of the island. He is a troll, and even if you defeat him--which "
"is somewhat unlikely--he will regenerate and will eventually return.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 1109, "The island of Raven's Dust is southern of this island. Our brothers "
"have created there a sanctuary of peace dedicated to nature.")

Command2(INTL( 680, "ORDER OF NATURE"),INTL( 1110, "COMMUNITY"))
INTL( 1111, "I founded the Order of Nature for the sole purpose of protecting "
"nature around us. We are careful not to play God, however, and thus, "
"we shall not play with the elements unless it is truly necessary.")

Command(INTL( 539, "GOBLIN"))
INTL( 1112, "When they were brought here by the foul \"Jarko\", they were so "
"eager to eliminate the citizens of Windhowl and Lighthaven that "
"they were blindly destroying the forest. My elemental magic alone "
"was barely enough to stop the massacre, and thus I had to "
"take \"steps\"... It led to the creation of the \"Stone\" \"of\" \"Life\".")

Command(INTL( 1113, "STEPS"))
INTL( 1114, "With the aid of the \"Stone\" \"of\" \"Life\", which served as a catalyst, "
"my elemental spells became strong enough to repel the army back to the "
"western mountains.") 

Command(INTL( 836, "FOREST GUARDIAN"))
INTL( 1115, "The Forest Guardians are trees that can walk. You might "
"have seen some at the entrance of this forest. Do not harm them, for they "
"are our friends and they prevent the goblins from invading us.")

Command2(INTL( 685, "LANTALIR"),INTL( 686, "RAINMIST"))
INTL( 1116, "Lantalir Rainmist has an uncanny talent. He is a very good student "
"and he learns fast. Sometimes, I feel like he is the son I never had. "
"He will someday grow as a very proficient water elementalist, if he " 
"so wishes.")

Command2(INTL( 841, "DUNIKUS"),INTL( 842, "HORNWIND"))
INTL( 1117, "Dunikus Hornwind is proficient with controlling the winds, something "
"I'll never be able to do. Winds are so unpredictable.")

Command(INTL( 515, "ARAKAS"))
INTL( 1118, "Arakas is the island you are standing on.") 

Command2(INTL( 541, "JARKO"),INTL( 693, "NECROMANCER"))
INTL( 1119, "Jarko is a dark-souled necromancer, not that I've actually seen "
"many followers of the dark path notably good. In any case, he has "
"to be stopped. He causes the earth to rot, but it is a satisfying "
"thought that his skin is rotting too.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1120, "Lighthaven is a town located on the south eastern part of this "
"island. Its sister town is named \"Windhowl\" and is located "
"on the southwestern part.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1121, "The inhabitants of Windhowl do not share our concerns for "
"nature, they are much too busy doing business with Lighthaven "
"and fighting brigands.")

Command(INTL( 475, "STONE OF LIFE"))
""
IF (CheckGlobalFlag (__QUEST_STONE_OF_LIFE) == 0 )
	IF (CheckNPCFlag (__YRIAN_DELAY) > CurrentRound)
		Conversation
		INTL( 1122, "The Stone of Life is used merely as a defense to protect nature against "
		"harm. However, the Stone of Life must not fall in the wrong hands or "
		"terrible things could happen. If it gets stolen, we can create a new "
		"Stone of Life after a certain amount of time. The previous Stone of Life "
		"then becomes lifeless and is no longer filled with power.")
	ELSE
		IF (rnd.roll( dice( 1, 5 ) ) == 1 ) 
			Conversation
			INTL( 1123, "It is terrible my friend! The Stone of Life has been stolen! You must "
			"retrieve it for us or we will be defenseless against the goblins and "
			"the undeads. We have seen the thief, it appears to be the Renegade "
			"Orc Leader, general of Jarko's armies. If the stone happens to fall "
			"in the hands of Jarko....")
			GiveGlobalFlag(__QUEST_STONE_OF_LIFE, 2 HOURS TDELAY ) 
			GiveGlobalFlag(__WHO_HAS_THE_STONE_FLAG, rnd.roll( dice( 1, 2 ) ) )
			GiveGlobalFlag(__TROLL_STONE_OF_LIFE, 0 )
		ELSE
			Conversation
			INTL( 1124, "The Stone of Life is used merely as a defense to protect nature against "
			"harm. However, the Stone of Life must not fall in the wrong hands or "
			"terrible things could happen. If it gets stolen, we can create a new "
			"Stone of Life after a certain amount of time. The previous Stone of Life "
			"then becomes lifeless and is no longer filled with power.")
			GiveNPCFlag (__YRIAN_DELAY, rnd.roll( dice( 2, 5 ) ) MINUTES TDELAY)
		ENDIF
	ENDIF
ELSEIF (CheckGlobalFlag (__QUEST_STONE_OF_LIFE) > CurrentRound )
//////////////////////////////////
// STONE OF LIFE IS STILL VALID //
//////////////////////////////////
	IF (CheckItem (__OBJ_STONE_OF_LIFE) == 0)
		Conversation
		INTL( 1125, "It is terrible my friend! The Stone of Life has been stolen! You must "
		"retrieve it for us or we will be defenseless against the goblins and "
		"the undeads. We have seen the thief, it appears to be the Renegade "
		"Orc Leader, general of Jarko's armies. If the stone happens to fall "
		"in the hands of Jarko... *gasp*") 
	ELSE
		BOOL boDone = FALSE;
		while( !boDone ){
		GetItemHandle( __OBJ_STONE_OF_LIFE, StoneOfLife )
		IF ( StoneOfLife == NULL )
			boDone = TRUE
		ELSE
			IF (CheckUnitFlag (StoneOfLife, __ITEM_QUEST_STONE_OF_LIFE) == (CheckGlobalFlag (__QUEST_STONE_OF_LIFE)))
				TakeItemHandle( StoneOfLife )
				GiveItem(__OBJ_TWISTED_DAGGER)
				GiveGlobalFlag( __QUEST_STONE_OF_LIFE, 0 ) 
				;int nNumStones = CheckItem(__OBJ_STONE_OF_LIFE); 
				FOR( 0, nNumStones )
					TakeItem(__OBJ_STONE_OF_LIFE) 
				ENDFOR
				boDone = TRUE
				Conversation
				INTL( 1126, "You have retrieved the Stone of Life? Marvelous! We shall "
				"reward you for this good deed with this magnificent twisted "
				"dagger and the knowledge that you probably saved us from "
				"a potential disaster.")
			ELSE
				TakeItemHandle( StoneOfLife )
			ENDIF
		ENDIF
}
	ENDIF

ELSEIF (CheckGlobalFlag (__QUEST_STONE_OF_LIFE) < CurrentRound )
//////////////////////////////////
// STONE OF LIFE IS NOT VALID //
//////////////////////////////////
GiveGlobalFlag( __QUEST_STONE_OF_LIFE, 0 )
	IF (CheckItem (__OBJ_STONE_OF_LIFE) == 1)
		TakeItem(__OBJ_STONE_OF_LIFE)
		Conversation
		INTL( 1127, "I noticed you have retrieved the Stone of Life and we are grateful, but "
		"we have already created a new Stone of Life. The one you have is no "
		"longer useful and can no longer endanger lives. ")
	ELSEIF (CheckItem (__OBJ_STONE_OF_LIFE) > 1)
		;int nNumStones = CheckItem(__OBJ_STONE_OF_LIFE); 
		FOR( 0, nNumStones )						
			TakeItem(__OBJ_STONE_OF_LIFE) 
		ENDFOR
		Conversation
		INTL( 1128, "I noticed you have a few lifeless Stone of Life. They are useless "
		"since we have created a new Stone of Life.")
	ELSE
		Conversation
		INTL( 1129, "Our precious Stone of Life has been stolen, but it is no longer "
		"a threat to us. We took care of the matter quite rapidly.")
	ENDIF
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 698, " ASS "),INTL( 697, "ASSHOLE"))
INTL( 1130, "Such filthiness, begone!") BREAK

Command3(INTL( 700, "SPELL"),INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 7565, "I see you're interested. This is the spell I can teach you.")
CreateSkillList
	AddTeachSkill (__SPELL_HEAL_CRITICAL, 21, 29457)
SendTeachSkillList

Command2(INTL( 569, "HEAL"),INTL( 1143, " MEND "))
""
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1144, "I could \"teach\" you the spell of heal critical myself, but I can also "
	"mend your wounds if you would like that.")
ELSE
	IF (USER_LEVEL < 6)
		Conversation
		INTL( 1145, "Since you are not strong enough to acquire gold pieces on your own, "
		"I shall heal your wounds. You are now healed, my friend.")
		HealPlayer(USER_MAXHP)
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
	ELSE
		Conversation
		FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"), ( (USER_MAXHP-USER_HP) / 2) )
		SetYesNo(HEAL)
	ENDIF
ENDIF

YES(HEAL)
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (Gold < ((USER_MAXHP-USER_HP)/2))
		IF (Gold > 0) 
			Conversation
			INTL( 1148, "You did not have enough gold pieces but I have healed a few of your wounds "
			"nonetheless for what you could spare.")		
			CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7566, "You give %u gold to Yrian Earthsong."), Gold) ) 
			PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 			
			HealPlayer(Gold*2) 
			TakeGold(Gold)  
		ELSE
			Conversation
			INTL( 1149, "You do not have enough gold pieces to be healed. You will have to find "
			"have to find the gold first. I heard that the \"goblins\" have "
			"stolen a fair amount of gold pieces...")
		ENDIF
	ELSE
		Conversation
		INTL( 1150, "Your wounds are now healed. Please feel free to come back if you "
		"need more healing.")
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7566, "You give %u gold to Yrian Earthsong."), ((USER_MAXHP-USER_HP) / 2)) )
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)		
		TakeGold( ( (USER_MAXHP-USER_HP) / 2) )	
		HealPlayer(USER_MAXHP)
	ENDIF
ENDIF

NO(HEAL)
	Conversation
	INTL( 1151, "As you wish. Feel free to come again if you change your mind.")

YesNoELSE(HEAL)
	Conversation
	INTL( 1152, "I guess you don't need healing if you can't answer yes or no.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1153, "Remember that nature must be protected or we will all die.") BREAK

Default
INTL( 1154, "I wish I knew but alas, I do not.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Yrian::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL(__SPELL_HEAL_CRITICAL, 21, 29457)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE

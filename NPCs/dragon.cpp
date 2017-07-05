//////////////////////////////////////////////////////////////////////
// Dragon.cpp: implementation of Dragon the Dragon
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Dragon.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Dragon::Dragon()
{}

Dragon::~Dragon()
{}

extern NPCstructure::NPC DragonNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void Dragon::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
//

{
   npc = DragonNPC;
   npc.appearance = 20028;
   SET_NPC_NAME( "[3033]DarkFang" );
   npc.InitialPos.X = 2835;
   npc.InitialPos.Y = 1113;
   npc.InitialPos.world = 0;
   npc.boPrivateTalk = TRUE;
}

void Dragon::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}


void Dragon::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Dragon::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//

{
CONSTANT GOLD = 1;
CString sUserName = USER_NAME;
sUserName.MakeUpper();

InitTalk

Begin
""
IF (CheckFlag(__DRAGON_IS_SILENT) == 1)
	Conversation
	INTL( 1864, "...")
	BREAK
ELSE
   IF (USER_LEVEL>=30)
		Conversation
		INTL( 1865, "Hrrm... I see you have grown. Very well, you are once "
		"more worthy of addressing me.")
      RemFlag(__DRAGON_IS_SILENT) 
	ELSE
		Conversation
		INTL( 1866, "*growl* Whoever you are, you had better have "
		"a good reason for disturbing \"Darkfang\"!")
	ENDIF
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1867, "Only other dragons know my ancient name, for I am the greatest dragon of "
"Firesky. You mortals may call me \"Darkfang\".")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1868, "How ignorant you can be sometimes, little one. I am a \"dragon\", I do not have "
"to work as you do. I am my own person.. erm.. dragon! If I am ever hungry, I "
"could always eat you anyway! Fortunately for you, the citizens of this "
"\"town\" are bringing me enough food to satisfy my appetite.")

Command2(INTL( 513, "LIGHTHAVEN"),INTL( 1869, "TOWN"))
INTL( 1870, "This is a small human town. It is nothing compared to the Dragon "
"Kingdom, I tell you. This town's name is Lighthaven--how ridiculous! "
"There's even a filthy cemetery with a \"crypt\" where the dead still walk.")

Command(INTL( 1243, "ARTHERK"))
INTL( 1871, "Artherk is not my god. He is but a human god, which simply shows how "
"much of a weakling he is.")

Command(INTL( 1872, "FEEL"))
INTL( 1873, "I ate a red monster yesterday whose name was \"Diabobolo\". I had indigestion "
"for hours and had to rest here. The people of this \"town\" took advantage of "
"my weakness to surround me with this meaningless fence. Of course, they "
"have not yet figured out that I could simply fly over it. *growl*")

Command(INTL( 1874, "DIABOBOLO"))
INTL( 1875, "It tasted rather bitter, gave me heartburns and left me with a heck of a bad "
"breath!")

Command2(INTL( 7292, "CRYPT" ),INTL( 7293, "TOMB RAIDER"))   // Quest level 5-10 
""
IF(CheckFlag(__QUEST_DRAGON_QUEST_COMPLETED) == 2)
	Conversation
	INTL( 1876, "Thank you for taking care of the tomb raider who was hiding in the Crypt.")
ELSE
   IF ((CheckFlag(__QUEST_DRAGON_QUEST_COMPLETED) == 1) && (CheckFlag(__FLAG_KILLED_TOMB_RAIDER) > 0))
      Conversation
      INTL( 1877, "Good. You have accomplished the small task successfully. I am "
      "pleased with you. {You} {have} {been} {awarded} {5000} "
      "{experience} {points.}") 
      GiveXP(5000)
      RemFlag(__FLAG_KILLED_TOMB_RAIDER)
      GiveFlag(__QUEST_DRAGON_QUEST_COMPLETED, 2)
   ELSE
		Conversation
		INTL( 1878, "One of your kind has greatly offended me. He is the tomb raider lurking in the Crypt. "
		"Deal with him swiftly and I shall reward you greatly.")
      RemFlag(__FLAG_KILLED_TOMB_RAIDER)     // Erase any previous Tomb Raider flag
      GiveFlag(__QUEST_DRAGON_QUEST_COMPLETED, 1)
   ENDIF
ENDIF

Command(INTL( 1879, "DRAGON'S TOOTH"))
INTL( 1880, "You have GOT to be kidding!! You think I'm going to give you one of my sharp, "
"precious teeth? Do you REALLY want to see them from this close? I guess I could "
"chew on you for a while, if that's what you truly desire... No? Didn't think so. "
"Don't bother me with these idiocies.")

Command(INTL( 515, "ARAKAS"))
INTL( 1881, "Arakas is the island you are currently standing on. Did you not know that already?")

Command2(INTL( 1882, "FOURTH COMING"),INTL( 1883, "4TH"))
INTL( 1884, "The Fourth Coming approaches and it will be thee who shalt be judged this time. "
"The question is... Are you ready for it?")

Command2(INTL( 1886, "KARMA"),INTL( 1024, "WORTH"))
""
IF(CheckFlag(__KNOWS_ABOUT_SERAPHS) == 0)
	Conversation
	INTL( 1887, "The measure of a person isn't gold but karma, or worth in your language. The "
	"more good deeds you do, the more you attract positive magic. The reverse is also "
	"true: a black heart attracts negative magic. Some people will not want to help "
	"you if you are too far in one path or another.")
ELSE
	IF (USER_KARMA>=400)
		Conversation
		INTL( 1888, "I have seldom seen someone as worthy as you among mortals, young friend. "
		"Certainly, the Light Seraph who sleeps within you rejoices at your greatness and "
		"your achievements. In my eyes, you are certainly a sight to behold! Well done!")
	ELSEIF (USER_KARMA>=300)
		Conversation
		INTL( 1889, "You are on the path to true worthiness, the kind that this world has not seen "
		"in aeons. Perhaps if you remain on this path, you will discover the true power "
		"that lies within your soul. I will say no more for now.")
	ELSEIF (USER_KARMA>=200)
		Conversation
		INTL( 1890, "You are very worthy, my young friend, but there is still room for improvement. "
		"If you would hear my advice, try a little harder and you shall reach a higher "
		"level of consciousness.")
	ELSEIF (USER_KARMA>=100)
		Conversation
		INTL( 1891, "Hmm... I seem to detect a trace of worthiness within you. This is a good omen. "
		"Perhaps you should nurture that worthiness, so that it may grow and make you "
		"a better individual.")
	ELSEIF (USER_KARMA>-100)
		Conversation
		INTL( 1892, "Bah! Do not speak to me of worthiness. After all you have done, you still have "
		"not committed to one side or the other? This is hardly good news...")
	ELSEIF( USER_KARMA <= -400 )
		Conversation
		INTL( 1893, "Well well! If this isn't my small friend! How unworthy you have become! Your "
		"aura is dark and threatening. You must not have many friends, but at least you "
		"are soon to emerge as a Dark Seraph. Perhaps that will be enough for you.")
	ELSEIF (USER_KARMA<=-300)
		Conversation
		INTL( 1894, "You travel a dark road, young one, and while I may not approve of that choice, "
		"at least you have gained strength in that direction. There are still some who "
		"are further along than you are, but you are still remarkable.")
   ELSEIF (USER_KARMA<=-200)
		Conversation
		INTL( 1895, "This is interesting. You have chosen with some resolve to become unworthy, "
		"despite the risks that come with that choice. It is certainly a valid "
		"option, but until you reach true unworthiness, you will remain vulnerable.")
	ELSEIF (USER_KARMA<=-100)
		Conversation
		INTL( 1896, "Ahh... I see you have chosen a darker path than most. Interesting choice. "
		"Well, perhaps it is for the best, since the world needs balance.")
   ELSE
		Conversation
		INTL( 1897, "Ahh... I see you have chosen a darker path than most. Interesting choice. "
		"Well, perhaps it is for the best, since the world needs balance.")      
   ENDIF
ENDIF

Command(INTL( 1898, "SERAPH"))
""
IF (USER_LEVEL <= 5)
   Conversation
   INTL( 1899, "Do not EVER speak that word again to me until you are ready.")
ELSEIF (USER_LEVEL < 30)
	Conversation
	INTL( 1900, "*ROAR* I said NOT to speak that word before me ever again! Not before you are fit "
	"to speak it.")
//	GiveFlag(__DRAGON_IS_SILENT,1)
	BREAK
ELSE
	Conversation
	INTL( 1901, "Ah, at last someone of some value with whom I can discuss this matter... "
	"Seraphs were impressive, as lesser creatures go, but they are long gone, now. "
	"*sigh* It is funny that I should miss them now, they who turned upon us in the "
	"end, we dragons who taught them all they knew... But they were good pupils, "
	"and their equals never walked the lands of Althea after their passing.")
	GiveFlag(__KNOWS_ABOUT_SERAPHS,1)
ENDIF

Command(INTL( 884, "WORLD"))
INTL( 1902, "The world of Althea of course!")

Command(INTL( 1903, "DARKFANG"))
INTL( 1904, "Ahh, another mortal come to annoy me with feeble requests. Tell me, what is "
"it you \"want\"?")

Command2(INTL( 1905, "WANT"),INTL( 554, "HELP"))
INTL( 1906, "Want help? Most people come to me requesting many things. I can only offer "
"a few \"gold\" pieces or perhaps \"heal\" your wounds if you wish me to.")

Command(INTL( 10297, "RUBY DRAGON FANG")) 
""
IF (CheckFlag(__FLAG_DARKFANG_SOUVENIRS) == 0)
	Conversation
	INTL( 10298, "What let you think that I have a ruby dragon fang?")
ELSE 
	IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
		SWITCH(CheckFlag(__FLAG_DARKFANG_GAVE_RUBY_FANG) ) 
			CASE(0)
				IF (CheckFlag(__QUEST_DRAGON_QUEST_COMPLETED) == 2) 	 
					Conversation
					INTL( 10299, "So, you need a ruby dragon fang, eh? Let me see... you helped me a while back by defeating "
					"that annoying tomb raider in the crypt. It is just fair that I assist you in this time of need "
					"as well. I will give you one ruby dragon fang. Keep it safely as I have a rather limited amount "
					"of those. Heh! Heh!")
					GiveFlag(__FLAG_DARKFANG_GAVE_RUBY_FANG, 1)
					GiveItem(__OBJ_RUBY_DRAGON_FANG)
					PRIVATE_SYSTEM_MESSAGE(INTL( 10300, "Darkfang gives you a ruby dragon fang."))
				ELSE
					Conversation
					INTL( 10301, "I am well-aware that you desperately need a ruby dragon fang but I do not "
					"want to depart myself of one for nothing. Let's see what you can do for me... "
					"Hmmm. One of your kind has greatly offended me. He is lurking in the \"crypt\" "
					"where I cannot reach him.")					
					GiveFlag(__QUEST_DRAGON_QUEST_COMPLETED, 1)
				ENDIF
			ENDCASE		
			CASE(1) 
				IF (CheckItem(__OBJ_RUBY_DRAGON_FANG) >=1) 
					Conversation
					INTL( 10302, "You already have the fang I gave you. I do not see why I would give you another "
					"one right now.")
				ELSE
					Conversation
					INTL( 10303, "So, you've used up the fang I gave you? Very well, I'll give you another one. "
					"Use it wisely.")
					GiveItem(__OBJ_RUBY_DRAGON_FANG)
					PRIVATE_SYSTEM_MESSAGE(INTL( 10300, "Darkfang gives you a ruby dragon fang."))
				ENDIF 
			ENDCASE
			OTHERWISE
		ENDSWITCH
	ELSE
		Conversation
		INTL( 10304, "I fail to see what would be the purpose of you owning a ruby dragon fang.")
	ENDIF
ENDIF 

Command(INTL( 10305, "SOUVENIRS")) 
INTL( 10306, "I kept some of Scarlet's \"ruby\" \"dragon\" \"fangs\" as souvenirs of this duel.")
IF (CheckFlag(__FLAG_DARKFANG_SOUVENIRS) == 0)
	GiveFlag(__FLAG_DARKFANG_SOUVENIRS, 1) 
ENDIF 

Command(INTL( 10307, "RUBY DRAGON"))
INTL( 10308, "Ruby dragons are very fond of battle, and that is usually their downfall. Even though they "
"are powerful spell casters, they prefer to dive blindlessly, breathing flames, and ripping foes "
"apart with their talons. I once fought a ruby dragon who was foolish enough to dare challenge me "
"to the death, guess who won?")

Command(INTL( 10309, "SCARLET"))
INTL( 10310, "Scarlet is the \"ruby\" \"dragon\" that I fought a long time ago. Let's say that I kept a few "
"\"souvenirs\" of that fight.")

Command(INTL( 1907, " EAT "))
INTL( 1908, "Eat? I do not require food right now.")

Command(INTL( 1909, "GOLD"))
INTL( 1910, "Gold? You want me to lend some to you, small one?")
SetYesNo(GOLD)

YES(GOLD)
	IF (CheckFlag (__FLAG_DRAGON) != 1 )
		Conversation
		INTL( 1911, "Here are 200 gold pieces! I hope it will serve you well.")
		GiveGold(200)
		GiveFlag (__FLAG_DRAGON, 1)     
	ELSE
		Conversation
		INTL( 1912, "I have already helped you, weakling! By the nostrils of the great storm dragon, "
		"it is no wonder you mortals are inferior! Slay a few monsters in the dungeons "
		"and leave me be!")
	ENDIF

NO(GOLD)
	Conversation
	INTL( 1913, "I agree, it would not be a good idea to be indebted to me.")

YesNoELSE(GOLD)
	Conversation
	INTL( 1914, "May I take it as a yes?")
	SetYesNo(GOLD)

Command2(INTL( 569, "HEAL"),INTL( 1915, "LIFE"))
""
IF (USER_LEVEL > 5)
    Conversation
    INTL( 1916, "I have healed weaklings such as you for days. It's time to grow. "
    "Seek your own kind at the temple to heal your frail body.")
ELSE 
	IF (USER_MAXHP == USER_HP)
		Conversation
		INTL( 1147, "You do not need healing, you have no wounds.")
   ELSE
		Conversation
		INTL( 1917, "I will help you until you can take care of yourself alone, small one.")
		// CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		HealPlayer(USER_MAXHP)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
	ENDIF 
ENDIF

Command(INTL( 1367, "DRAGON"))
INTL( 1885, "Indeed I am, and probably the oldest of all dragons. Most of us dwelt on this "
"\"world\" long before the human race appeared. Don't get on the bad side "
"of my brothers, for we love the sweet taste of hum... erm... nevermind that.")

Command(INTL( 1918, "GETITEMGLOOMBLADE"))
""
TakeItem(__OBJ_GLOOMBLADE)

Command5(INTL( 697, "ASSHOLE"),INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 1919, "WHORE"),INTL( 698, " ASS "))
INTL( 1920, "You are unworthy to speak with I. Now begone, puny mortal, before I eat you!")
BREAK

Command5(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1921, "Farewell...")
BREAK

Default
INTL( 7173, "I am sorry, but I do not understand what you're saying!")

EndTalk

}


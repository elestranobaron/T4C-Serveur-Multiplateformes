#pragma hdrstop
#include "Annabelle.H"


Annabelle::Annabelle()
{}

Annabelle::~Annabelle()
{}

extern NPCstructure::NPC Priestess_Annabelle;

void Annabelle::Create( void )
{
	npc = ( Priestess_Annabelle );
	SET_NPC_NAME( "[2893]Annabelle" );
	npc.InitialPos.X = 1551; 
	npc.InitialPos.Y = 205;
	npc.InitialPos.world = 0;
}


void Annabelle::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT FIRST_QUESTION = 1
 
InitTalk

Begin
INTL( 529, "Oh! You startled me! *smile* Is there something I can do for you?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 530, "I'm Annabelle. Nice to make your acquaintance. What are you doing in these parts?")

Command(INTL( 523, "ANNABELLE"))
INTL( 531, "Yes, that's my \"name\".")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 532, "Oh, I do a little of this, a little of that. I'm just tidying things up until "
"my \"William\" returns to me. He is a little late though.")

Command(INTL( 533, "WILLIAM"))
INTL( 534, "It seems like ages ago since he left for war. Still, he promised to meet "
"me here, so I wait for him. Perhaps you've seen him? He's tall, dark and "
"handsome...")

Command(INTL( 535, "TROLL"))
INTL( 536, "Yes, he walks around here, but he is not dangerous, not if you do not attack him. "
"In fact, he is very friendly and always protects me from those \"goblins\".") 

Command2(INTL( 537, "CASTLE"),INTL( 507, "ORKANIS"))
INTL( 538, "This is the Orkanis Castle, although it isn't as beautiful as it was before the "
"\"troll\" established himself here.") 

Command(INTL( 539, "GOBLIN"))
INTL( 540, "I do not like goblins, they are mean creatures.")

Command(INTL( 541, "JARKO"))
INTL( 542, "I heard that Jarko is a mad man. I hope somebody will be able to stop him.")

Command("CRAPO")
""
IF (CheckFlag( __FLAG_CHOICE) == 1)
   Conversation
   "You make two ! GOOD !"
   GiveFlag(__FLAG_CHOICE,2)
ELSE
   GiveFlag(__FLAG_CHOICE,0)
ENDIF

Command(INTL( 543, "CURSE"))
INTL( 544, "There are a few beings in this world that bestow curses upon innocents "
"like you. They are truly evil beings.")

Command(INTL( 509, "BALORK"))
INTL( 545, "I shiver just to think of this monster! Does he still roam the dungeon below "
"the temple of \"Lighthaven\", cursing people with his \"Brand\"?")
SetYesNo(FIRST_QUESTION) 

	YES(FIRST_QUESTION)
	Conversation
	INTL( 546, "*sigh* I pity the souls who are cursed by this malevolent demon.")
	
	NO(FIRST_QUESTION)
	Conversation
	INTL( 547, "Peculiar, since I had a visitor recently who had been \"cursed\" by that foul creature.")
	
	YesNoELSE(FIRST_QUESTION)
	Conversation
	INTL( 548, "I guess you do not know.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 549, "Lighthaven is a small yet beautiful town located on the other side of the island.")

Command(INTL( 514, "WINDHOWL"))
INTL( 550, "Windhowl is \"Lighthaven\"'s sister town located south. It's a bit far, but "
"I heard the merchants have great merchandise up there. That reminds me, "
"perhaps \"William\" will bring me back a gift when he comes "
"back. I wonder what it could be... A silk dress, maybe? Yes, that would be nice.")

Command(INTL( 515, "ARAKAS"))
INTL( 551, "That's the island you are currently standing on. I hope you knew that or "
"you are somewhat lost, methinks.") 

Command(INTL( 552, "BLESSING"))
INTL( 553, "I was a priestess, once... I am not ignorant in the matters of removing "
"\"curses\" and \"healing\" the wounded.")

Command(INTL( 554, "HELP"))
INTL( 555, "I can do little for you myself, but perhaps you could visit the \"Old\" \"Hermit\" "
"and ask for his guidance. He has little power himself, but knows many "
"powerful priests and has acquired great wisdom during his \"exile\".") 

Command(INTL( 556, "OLD HERMIT"))
INTL( 557, "His real name is Theorn Lemnearan. He lives in the mountains and shuns "
"people. Do not be surprised if he receives you coldly, but remember that "
"he has a good heart. ")
GiveFlag(__FLAG_ANNABELLE,1)

Command("GREGRE")
""
IF (CheckFlag( __FLAG_CHOICE) == 0)
   Conversation
   "You make one ! GOOD !"
   GiveFlag(__FLAG_CHOICE,1)
ELSE
   GiveFlag(__FLAG_CHOICE,0)
ENDIF

Command(INTL( 558, "EXILE"))
INTL( 559, "He left everything behind him to study his books and to finally have peace.")

Command(INTL( 560, "THEORN LEMNEARAN"))
INTL( 561, "That's the \"Old\" \"Hermit\"'s real name.")

Command(INTL( 502, "TRAIN"))
INTL( 562, "Train you with what? I do not think I could help you.")

Command(INTL( 496, "TEACH"))
INTL( 563, "I have little to teach, alas, except perhaps the ways to a kinder, gentler "
"lifestyle. *sigh* There are few students for that, nowadays.")

Command(INTL( 484, "MHORGWLOTH"))
INTL( 564, "Mhorgwloth is the name of the \"troll\" who dwells around here.") 

Command(INTL( 565, "BRIGAND"))
INTL( 566, "The brigands are brutes, but \"Mhorgwloth\" protects me from their "
"dirty hands.")

Command(INTL( 510, "BRAND"))
""
IF (CheckFlag( __BALORK_BRAND) == 1)
	Conversation
	INTL( 567, "Hmmmm... I see that \"Balork\" has put his evil mark upon your brow... "
	"Great sorrow it will bring you, I fear, but great achievements as well. "
	"Years ago, I could have removed it from you, but the demon's curse has "
	"grown in strength while the years have weakened my faith. Alas, I cannot "
	"\"help\" you.")
ELSE
	Conversation
	INTL( 568, "\"Balork\" used to mark people, to curse them before dying. Upon their "
	"own deaths, he would own their souls and torment them in his dungeon. "
	"Perhaps he still does it, I do not know.")
ENDIF

Command(INTL( 569, "HEAL"))
""
IF( USER_HP < (USER_MAXHP / 2) )
	target->SetHP( USER_MAXHP / 2, true )
	Conversation
	INTL( 570, "I have healed some of your wounds, but I cannot heal you more.")
	CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 
ELSE
	Conversation
	INTL( 571, "I am sorry but I cannot heal your wounds. My healing abilities have greatly "
	"weakened over the years.") 
ENDIF
	
Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 572, "Farewell. If you see my \"William\", tell him to meet me here at once.")
BREAK

Default
INTL( 573, "I do not know about that, sorry my friend.") 

EndTalk
}

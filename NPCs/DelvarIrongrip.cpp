#pragma hdrstop
#include "DelvarIrongrip.H"

DelvarIrongrip::DelvarIrongrip()
{}

DelvarIrongrip::~DelvarIrongrip()
{}

extern NPCstructure::NPC DelvarIrongripNPC;

void DelvarIrongrip::Create( void )
{
        npc = ( DelvarIrongripNPC );
        SET_NPC_NAME( "[3032]Delvar Irongrip" );
        npc.InitialPos.X = 2407; 
        npc.InitialPos.Y = 807;
        npc.InitialPos.world = 0;
}

void DelvarIrongrip::OnAttack( UNIT_FUNC_PROTOTYPE ){
    switch(rnd(0, 4)){
    case 0: SHOUT(INTL( 2029, "Die!")); break;
    case 1: SHOUT(INTL( 2030, "You're bleeding? Come to me and bleed some more!")); break;
    case 2:break;
    case 3:break;
    case 4:break;
	}
	NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void DelvarIrongrip::OnAttacked( UNIT_FUNC_PROTOTYPE ){
    switch(rnd(0, 4)){
    case 0: SHOUT(INTL( 2031, "Ouch! You'll pay for this with your life!")); break;
    case 1: SHOUT(INTL( 2032, "Ow!")); break;
    case 2:break;
    case 3:break;
    case 4:break;
	}
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void DelvarIrongrip::OnTalk( UNIT_FUNC_PROTOTYPE )

{
const int LPOTION = 1;

InitTalk

Begin
INTL( 2033, "Be careful, this forest is filled with vile \"creatures\".")
IF ((CheckNPCFlag (__FLAG_DELAY_DELVAR) > CurrentRound) || (CheckGlobalFlag(__GLOBAL_FLAG_GOBLIN_QUEST) == 1)) // This means the delay is not over yet               
// Do nothing since the Quest is already running.
ELSE   
   IF (rnd.roll(dice(1, 20) ) == 1)
                SUMMON( "DORKENROTSMELL", 2690, 905 )                                 
                SUMMON( "NPCGOBLINSCOUT", 2691, 905 )
                SUMMON( "NPCGOBLINSCOUT", 2692, 905 )
                SUMMON( "NPCGOBLINSCOUT", 2687, 911 )
                SUMMON( "NPCGOBLINSCOUT", 2697, 913 )
                SUMMON( "NPCGOBLINSCOUT", 2761, 919 )
                SUMMON( "NPCGOBLINSCOUT", 2751, 908 )
                SUMMON( "NPCGOBLINWARRIOR", 2745, 931 )
                SUMMON( "NPCGOBLINWARRIOR", 2739, 940 )
                SUMMON( "NPCGOBLINWARRIOR", 2702, 901 )
                SUMMON( "NPCGOBLINWARRIOR", 2685, 895 )
                GiveGlobalFlag(__GLOBAL_FLAG_GOBLIN_QUEST, 1) 
	ELSE
      GiveNPCFlag (__FLAG_DELAY_DELVAR, rnd.roll(dice(3, 4 ) ) MINUTES TDELAY )
	ENDIF
ENDIF	

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 2036, "Be careful, this forest is filled with vile \"creatures\".")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2037, "The name's Delvar Irongrip, the strongest warrior on this island, with "
"the possible exception of \"Murmuntag\". I am a \"survivor\", I cannot be "
"beaten even in this hostile forest.")

Command(INTL( 2038, "CREATURE"))
INTL( 2039, "Indeed, hideous creatures such as \"goblins\" roam in the forest. You might "
"even see \"brigands\" cowardly hidden in the shadows, waiting for the "
"opportunity to strike a lethal blow in your back and steal your gold.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2040, "I am a mercenary and I have been employed by a few inhabitants of "
"\"Lighthaven\" to purify this forest of \"brigands\" and \"goblins\".")

Command2(INTL( 791, "GLOOMBLADE"),INTL( 1353, "GLUM SWORD"))
INTL( 2041, "Some people call it a glum sword, but it's actually a Gloomblade, and it's not "
"very easy to find. I guess you'd have to ask someone who knows more about making "
"swords than I do. I just use them.")

Command(INTL( 523, "ANNABELLE"))
INTL( 2042, "Aye, I knew her well, that Annabelle. Lovelier than an Elf -- not that I know "
"what Elves look like, they left this world a long, long time ago. But aye, "
"you'd love to meet her...")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2043, "Curse that Balork and his Brand! There are many like you who walk the land "
"and bear his mark. I tell you, friend, you have to seek Annabelle, blessed "
"her eyes! She'll know what to do.")

Command(INTL( 1037, "MURMUNTAG"))
INTL( 2044, "He is skilled, but he is also an orc. I do not have hatred toward his "
"race despite their dark origins, I simply do not trust him.")

Command(INTL( 565, "BRIGAND"))
""
IF (CheckFlag(__FLAG_BRIGAND_TRUST) != 0 )
    Conversation
    INTL( 2045, "I have heard that you have been doing business with them. I must warn "
    "you my friend, you are walking a dangerous path.")
ELSE
    Conversation
    INTL( 2046, "Brigands are not very skilled fighters, but beware of the assassins "
    "that lurk in the forest north of Windhowl.")
ENDIF

Command(INTL( 539, "GOBLIN"))
INTL( 2047, "I always slay a few after breakfast, it helps my digestion.")

Command(INTL( 746, "DRUID"))
INTL( 2048, "The Druids are sworn to protect nature no matter what.")

Command(INTL( 554, "HELP"))
INTL( 2049, "Help? Perhaps I could part with one of my healing \"potions\".")

Command(INTL( 666, "POTION"))
""
IF (CheckFlag(__FLAG_DELVAR_POTION) == 1)
    Conversation
    INTL( 2050, "I've already helped you, remember? I gave you a potion. Now, if you are "
    "not able to dwell in the forest by yourself, you should return to "
    "\"Lighthaven\".")
ELSE
    Conversation
    INTL( 2051, "Are you in pain, my friend? I could give you one of my potions, if "
    "you think it can help you. Do you want one?")
    SetYesNo(LPOTION)
ENDIF

YES (LPOTION)
GiveItem(__OBJ_HEALING_POTION) 
GiveFlag(__FLAG_DELVAR_POTION, 1)
Conversation
INTL( 2052, "Take this potion and drink it wisely, for it will be the only one I give to you.")

NO (LPOTION)
Conversation
INTL( 2053, "It is your decision my friend.")

YesNoELSE (LPOTION)
Conversation
INTL( 2054, "I guess you could not answer that simple question.")

Command(INTL( 2055, "SURVIVOR"))
INTL( 2056, "The key to survive is to keep yourself healthy. You can bring \"potions\" "
"or learn techniques to \"heal\" yourself.")

Command(INTL( 569, "HEAL"))
""
IF( USER_HP < (USER_MAXHP / 2) )
	target->SetHP( USER_MAXHP / 2, true )
	Conversation
    INTL( 2057, "I can treat your minor wounds. I am sorry but I cannot teach you how "
    "to mend yourself because I don't have the time. Someday, you'll find "
    "somebody who'll be able to.")
ELSE
	Conversation
    INTL( 2058, "I am sorry, but my first aid abilities cannot heal your wounds anymore.")
ENDIF



Command(INTL( 1243, "ARTHERK"))
INTL( 2059, "Artherk? If he is the God his worshippers claim he is, why does he "
"hide in the celestial realm while we need him right here? It is not "
"him who prevents the \"goblins\" from gaining dominion over the island, it "
"is my sword and I.")

Command(INTL( 541, "JARKO"))
INTL( 2060, "If only I could find where he is hiding...")

Command2(INTL( 2061, "CAVERN"),INTL( 881, "CAVE"))
INTL( 2062, "There are many caverns on this island. Keep an eye for \"Jarko\"'s caverns "
"because they are filled with undeads and \"goblins\".")

Command(INTL( 753, "GOLDMOON"))
INTL( 2063, "The kingdom of Goldmoon is currently ruled by King Theodore the XIIIth. It "
"encompasses the islands of \"Arakas\" and \"Raven's\" \"Dust\".")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 2064, "Raven's Dust is a small island located southwest of this island. It can only "
"be reached by ship. The castle of King \"Theodore\" and the town of "
"\"Silversky\" are also located on that island.")

Command(INTL( 754, "THEODORE"))
INTL( 2065, "King Theodore is not worthy of being our king. He doesn't do anything "
"for his kingdom, nor does he seem to care.")

Command(INTL( 998, "SILVERSKY"))
INTL( 2066, "I have never gone to Silversky myself, I could not tell you what it's like.")

Command(INTL( 515, "ARAKAS"))
INTL( 2067, "Arakas is the name of this island.")

Command(INTL( 514, "WINDHOWL"))
INTL( 2068, "Windhowl is on this island, southwest from here.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 2069, "I was born and raised in this small town. On the opposite side of "
"the island stands its sister town, \"Windhowl\".")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 2070, "I could easily break you in half if I wanted to, little one.")
FIGHT

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2071, "It is time to depart, my friend.") BREAK

Default
INTL( 2072, "Really? I did not really think it was important.")

EndTalk
}

//////////////////////////////////////////////////////////////////////
// KirlorDhul.cpp: implementation of the KirlorDhul class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "KirlorDhul.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KirlorDhul::KirlorDhul()
{}

KirlorDhul::~KirlorDhul()
{}

void KirlorDhul::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

extern NPCstructure::NPC Lord_Kirlor;

void KirlorDhul::Create(){
    npc = Lord_Kirlor;
	SET_NPC_NAME( "[3046]Kirlor Dhul" );
    npc.InitialPos.X = 2967;
    npc.InitialPos.Y = 1111;
	npc.InitialPos.world = 0;
}


void KirlorDhul::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT REGISTER = 1

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11766, "There was some commotion on the street just outside earlier... I wonder what it was? Perhaps "
	"someone saw what happened.")
ELSE
	Conversation
	INTL( 11767, "Welcome friend. I trust the guards aren't giving you to much of a rough time? Please, share your "
	"thoughts.")
	IF ((CheckNPCFlag (__FLAG_DELAY_KIRLOR) > CurrentRound) || (CheckGlobalFlag(__GLOBAL_FLAG_GOBLIN_QUEST) == 1)) // This means the delay is not over yet
	ELSE   // This means the delay is over
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
			GiveNPCFlag (__FLAG_DELAY_KIRLOR, rnd.roll(dice(3, 5 ) ) MINUTES TDELAY )
		ENDIF
	ENDIF	
ENDIF

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 1629, "My name is Kirlor Dhul, Lord of Lighthaven. I \"work\" to help my citizens "
"live a better life!")

Command4(INTL( 489, "WORK"),INTL( 1435, "LORD"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1630, "My occupation is to collect taxes, serve our great \"King\" and protect the "
"villagers of our humble town, although, we have had some \"problems\" with "
"that lately.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1631, "I heard that she has Elven blood running in her veins. Methinks it is untrue "
"because we all know that Elves have been wiped out a long time ago. Or "
"were they?") 

Command3(INTL( 510, "BRAND"),INTL( 509, "BALORK"),INTL( 582, "BALORK'S CURSE"))
INTL( 1503, "That's a fairy tale.")

Command(INTL( 1072, "KING"))
INTL( 1632, "Yes, our great King Theodore the \"XIII\"th.")

Command(INTL( 1633, "XIII"))
INTL( 1634, "His story is a rather short one, and not too inspiring. When \"Theopold\" "
"died, his 12 other sons all had to compete in a deadly \"tournament\".  The "
"survivor would then inherit the kingdom. Surprisingly, Theodore was the only "
"one to survive this lethal match. Rumor has it that the reason he survived "
"was because he was sleeping when the tournament actually took place, although "
"I have not been able to confirm this.")

Command(INTL( 1460, "THEOPOLD"))
INTL( 1635, "Ahh! A great king indeed. He united all the villages of \"Goldmoon\" to fight "
"against the ever-growing hordes of goblins. His leadership led to a legendary "
"victory and kept peace throughout the land. Now that his son is on the throne, "
"the situation is deteriorating at an alarming rate. Our forces are wearing "
"thin and the last time I asked him what his plans were for the region, he "
"told me that he would sleep on it!")

Command(INTL( 753, "GOLDMOON"))
INTL( 1636, "Goldmoon is the kingdom regrouping all the villages on the island of "
"\"Arakas\" and \"Raven's\" \"Dust\".")

Command(INTL( 1284, "RAVEN"))
INTL( 1637, "That is the island on which the castle of Theodore is located. Head south "
"of \"Arakas\" if you wish to find it.")

Command(INTL( 515, "ARAKAS"))
INTL( 1440, "That is the name of the island you are currently on.")

Command(INTL( 1638, "TOURNAMENT"))
INTL( 1639, "I heard it was a very bloody fight.")

Command2(INTL( 1648, "REGISTER"),INTL( 1640, "PROBLEM"))
INTL( 2786, "Brigands have been banding together to attack our merchant carriers. "
"Since I don't have many guards, I can't spare any of them to protect the "
"merchants. I must keep them to \"protect\" the town against a sudden goblin "
"invasion. Lord Sunrock is offering rewards for anyone who will help a merchant "
"to deliver his report across the forest to our sister town, \"Windhowl\". "
"Would you like to register?")
SetYesNo (REGISTER)

YES (REGISTER)
 IF (CheckFlag(__QUEST_MERCHANT) == 1)
     IF (CheckItem (__OBJ_MERCHANT_LETTER) > 0) 
        Conversation
        INTL( 1642, "I remember giving you a letter not long ago. Go see a merchant, now.")
    ELSE
        Conversation
        INTL( 1643, "You've lost the letter? Already? Oh well, I'll give you another "
        "one, but be careful please.")
        GiveItem(__OBJ_MERCHANT_LETTER)
    ENDIF
 ELSE
    IF (USER_LEVEL > 4)
        GiveItem(__OBJ_MERCHANT_LETTER)
        GiveFlag(__QUEST_MERCHANT, 1 )
        Conversation
        INTL( 1644, "Splendid! Here is a \"letter\", now go present it to a \"merchant\" and be "
        "on your way to Windhowl. I wish you the best of luck.")                                   
    ELSE
        Conversation
        INTL( 7178, "I highly doubt you would be able to make it to Windhowl at your level.")
    ENDIF
 ENDIF

NO(REGISTER)
Conversation
INTL( 2787, "As you wish, I surely cannot force you into doing this!")

YesNoELSE(REGISTER)
Conversation
INTL( 1647, "Make up your mind.")

 Command(INTL( 514, "WINDHOWL"))
INTL( 1650, "The path to Windhowl is home to many brigands and strange creatures, so be "
"careful not to get ambushed.")

Command(INTL( 1257, "MERCHANT"))
INTL( 1651, "Many of them cannot afford to get plundered by roving bandits and will be grateful "
"for the assistance. See \"Rolph\" or \"Sigfried\" if you want to help them with the report.")

Command(INTL( 2518, "SIGFRIED"))
INTL( 2781, "Sigfried is the town's weaponsmith.")

Command(INTL( 2345, "ROLPH"))
INTL( 7163, "Rolph is the town's armorer.")

Command(INTL( 1301, "LETTER"))
INTL( 1652, "Just ask any merchant about it and he will give you more details.")

Command(INTL( 1653, "PROTECT"))
INTL( 1654, "Those guards are the best at their job. There isn't a monster who gets "
"within bow-shot that doesn't get chased back to the mountains.")

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1655, "Feel free to come back anytime.") BREAK

Default
INTL( 1656, "Ask around, maybe they could tell you something.")

EndTalk

}

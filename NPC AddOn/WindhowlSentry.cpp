#pragma hdrstop
#include "WindhowlSentry.h"

WindhowlSentry::WindhowlSentry()
{}

WindhowlSentry::~WindhowlSentry()
{}

extern NPCstructure::NPC WindhowlSentryNPC;

void WindhowlSentry::Create( ){
	npc = WindhowlSentryNPC;
	SET_NPC_NAME( "[12785]Windhowl sentry");
	npc.InitialPos.X = 1816;
	npc.InitialPos.Y = 1297;
	npc.InitialPos.world = 0;
}

void WindhowlSentry::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void WindhowlSentry::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void WindhowlSentry::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Accept = 1;

InitTalk

Begin
""
IF(USER_LEVEL < 50)
	Conversation
	INTL( 12699, "Hmm, you look like you're a bit too weak to help in the fight against Hel...")
	BREAK
ELSE
	IF(CheckFlag(__FLAG_ADDON_USER_HAS_KILLED_CARMAN) == 1)
		IF(CheckFlag(__FLAG_ADDON_USER_REWARDED_FOR_KILLING_CARMAN) == 0)
			IF(CheckFlag(__FLAG_ADDON_USER_SPAWNED_CARMAN) == 1)
				Conversation
				INTL( 12700, "I must admit, I wasn't sure if you would be able to pull it off. Well done! Now, to show the "
				"town's gratitude, I have a special \"reward\" for you.")
			ELSE
				Conversation
				INTL( 12701, "So, you also participated in the battle against Hel, did you? Very well, I have a \"reward\" "
				"for you as well.")
			ENDIF
		ELSE
			Conversation
			INTL( 12702, "I thank you for helping us get rid of that menace once again. I just hope it's for good "
			"this time.")
		ENDIF
	ELSE
		Conversation
		INTL( 12703, "You look like you can handle yourself in a fight... I really could use some \"help\" from someone like you...")
	ENDIF
ENDIF

Command(INTL( 554, "HELP"))
""
IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_CARMAN_PRESENT) == 0)
	Conversation
	INTL( 12704, "A Seraph called Hel has been plaguing this town for awhile now, abducting people when they wander "
	"outside the gates and performing all kinds of twisted forms of torture for the sheer pleasure of it. "
	"Unfortunately, I can't leave my post here because I have to make sure no one else wanders outside. "
	"That's why I need you to \"take\" \"care\" of her for me.")
ELSE
	Conversation
	INTL( 12705, "I already sent someone to confront her but knowing her, it's going to take a lot more to defeat her. "
	"If you're up for a tough fight, she's just north of town.")
	GiveFlag(__FLAG_ADDON_USER_SPAWNED_CARMAN, 1)
ENDIF

CmdAND(INTL( 12706, "TAKE"), INTL( 12707, "CARE"))
""
IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_CARMAN_PRESENT) == 0)
	Conversation
	INTL( 12708, "You must confront her and make her stop this madness, no matter what the cost. What do you say? Will "
	"you do this for the townspeople of Windhowl?")
	SetYesNo(Accept)
ELSE
	Conversation
	INTL( 12709, "I really should stop talking and return to my watch...")
ENDIF

YES(Accept)
	Conversation
	INTL( 12710, "Great! I should warn you that you'll probably need to bring several friends to deal with her if things "
	"get ugly. Hell, if you have access to an army, bring it along. Don't try fighting her alone...")
	SUMMON("CARMANSPAWNER", 1663, 1040)
	GiveFlag(__FLAG_ADDON_USER_SPAWNED_CARMAN, 1)
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_CARMAN_PRESENT, 1)
NO(Accept)
	Conversation
	INTL( 12711, "That's too bad... I would've thought you the type to help those in need. I guess I was wrong.")
YesNoELSE(Accept)
	Conversation
	INTL( 12712, "Will you confront Hel for the townspeople of Windhowl or not?")
	SetYesNo(Accept)

Command(INTL( 617, "REWARD"))
""
IF(CheckFlag(__FLAG_ADDON_USER_HAS_KILLED_CARMAN) == 1)
	IF(CheckFlag(__FLAG_ADDON_USER_REWARDED_FOR_KILLING_CARMAN) == 0)
		IF(CheckFlag(__FLAG_ADDON_USER_SPAWNED_CARMAN) == 1)
			Conversation
			INTL( 12713, "It is with great honor that I present this reward to you. All the townspeople pitched in, so I "
			"hope it's enough.")
			GiveGold(USER_LEVEL*500)
			GiveXP((USER_LEVEL^2)*100)
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 12714, "You receive %u experience points."), (USER_LEVEL^2)*100))
			GiveFlag(__FLAG_ADDON_USER_REWARDED_FOR_KILLING_CARMAN, 1)
		ELSE
			Conversation
			INTL( 12715, "It is with great honor that I present this reward to you. All the townspeople pitched in, so I "
			"hope it's enough.")
			GiveGold(USER_LEVEL*500)
			GiveXP((USER_LEVEL^2)*100)
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 12714, "You receive %u experience points."), (USER_LEVEL^2)*100))
			GiveFlag(__FLAG_ADDON_USER_REWARDED_FOR_KILLING_CARMAN, 1)
		ENDIF
	ELSE
		Conversation
		INTL( 12716, "You've already been rewarded for your efforts and the townspeople have nothing left to give.")
	ENDIF
	GiveFlag(__FLAG_ADDON_USER_HAS_KILLED_CARMAN, 0)
	GiveFlag(__FLAG_ADDON_USER_SPAWNED_CARMAN, 0)
ELSE
	Conversation
	INTL( 12717, "What reward? I can't reward you until you have gotten rid of Hel.")
ENDIF

Command(INTL( 489, "WORK"))
INTL( 12718, "I'm here to make sure that no one wanders outside the gates.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12719, "Good luck.")
BREAK

Default
INTL( 12709, "I really should stop talking and return to my watch...")

EndTalk
}
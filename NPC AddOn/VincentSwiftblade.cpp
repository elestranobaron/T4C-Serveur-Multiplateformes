#pragma hdrstop
#include "VincentSwiftblade.h"

VincentSwiftblade::VincentSwiftblade()
{}

VincentSwiftblade::~VincentSwiftblade()
{}

extern NPCstructure::NPC VincentSwiftbladeNPC;

void VincentSwiftblade::Create( ){
	npc = VincentSwiftbladeNPC;
	SET_NPC_NAME( "[12784]Vincent Swiftblade");
	npc.InitialPos.X = 2830; 
	npc.InitialPos.Y = 1150;
	npc.InitialPos.world = 0;
}

void VincentSwiftblade::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT AcceptMission = 1; 


InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_MERCENARY_LEADER_DEFEAT)==1) 
	Conversation
	FORMAT(INTL( 12680, "%s, I've heard you were part of the group who defeated the mercenary's leader. Very well done! I have the promised \"reward\" right here."), USER_NAME) 
ELSEIF ((USER_LEVEL>=8)&&(CheckFlag(__FLAG_ADDON_CAMP_ASSAULT)==0))
	Conversation
	INTL( 12681, "Halt adventurer! Our leader \"Tarnian\" \"Wolfmane\" needs a group of heroes to make a coordinated assault "
	"on three different camps of \"Olin\" \"Haad\"'s men at once. If you're interested, there is a very generous "
	"bounty for whoever participates in the downfall of the men's leader. Would you be interested in undertaking "
	"this mission?")
	SetYesNo(AcceptMission)
ELSEIF(CheckFlag(__FLAG_ADDON_CAMP_ASSAULT)==1)
	Conversation
	INTL( 12682, "I can fill you on the \"details\" whenever you feel ready to strike the mercenary camps.") 
ELSE
	Conversation
	INTL( 12683, "Well met.")
ENDIF 

YES(AcceptMission)
Conversation
INTL( 12684, "Very well, I will fill you in the \"details\" whenever you are ready.") 

NO(AcceptMission)
Conversation
INTL( 12685, "A pity, but I understand. I doubt you would have succeeded anyways.")  

YesNoELSE(AcceptMission) 
Conversation
INTL( 12686, "Well, do you think you have what it takes to do this?")
SetYesNo(AcceptMission) 

Command(INTL( 12687, "DETAILS")) 
INTL( 12688, "The foul \"Olin\" \"Haad\" has enlisted the mercenaries' aid and they've taken the town under siege ever since. "
"The task which lies ahead is no easy one. You will need to conduct a coordinated attack on the three camps "
"located near Lighthaven's northern. Hopefully, this will eventually attracts the mercenary "
"lieutenants' attention. You will then need to deal with them swiftly. This should force the leader out of his "
"hideout located further north. Be wary that he is a very skillful axeman who fears no one. If you defeat the "
"leader, it should destabilize the mercenaries enough for us to pierce through their defenses. You and all "
"the brave soldiers who participate in his demise can then return here and collect a \"reward\".")
IF(CheckFlag(__FLAG_ADDON_CAMP_ASSAULT) == 1) 
	GiveFlag(__FLAG_ADDON_CAMP_ASSAULT, 2) 
ENDIF 

Command(INTL( 617, "REWARD")) 
""
IF(CheckFlag(__FLAG_ADDON_MERCENARY_LEADER_DEFEAT) == 1) 
	Conversation
	INTL( 12689, "I've heard of your participation in the mercenary leader's demise. Well done! Here's your reward as "
	"promised.") 
	GiveGoldNoEcho(500) 
	;int nExpReward = USER_LEVEL*750;
	PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward)) 
	GiveXP(nExpReward)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12690, "Vincent Swiftblade gives you a pouch of gold.")) 
	GiveFlag(__FLAG_ADDON_MERCENARY_LEADER_DEFEAT, 0) 
ELSE
	Conversation
	INTL( 12691, "I fail to see why you deserve any reward from me.") 
ENDIF

Command2(INTL( 12692, "TARNIAN"),INTL( 12693, "WOLFMANE")) 
INTL( 12694, "Tarnian Wolfman is the only man capable of stopping \"Olin\" \"Haad\" from overthrowing us all. That is the "
"reason why I chose to follow him.") 

Command(INTL( 513, "LIGHTHAVEN")) 
INTL( 12695, "I do my best so that Lighthaven does not fall entirely under \"Olin\" \"Haad\"'s control.") 

Command2(INTL( 11925, "OLIN"),INTL( 11926, "HAAD")) 
INTL( 12696, "Olin Haad is a shrewd and merciless necromancer who has visions of conquest and power. \"Tarnian\" \"Wolfmane\" "
"has sworn his life to fight until Olin's demise. So did I.") 

Command(INTL( 483, "NAME"))
INTL( 12697, "The name is Vincent Swiftblade to you. As the name implies, I am one of the finest blades around here.")

Command2(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"))
INTL( 12698, "I fight for the freedom of Lighthaven.") 

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 1623, "I cannot help you with this.")
ELSE
	Conversation
	INTL( 11825, "I don't understand what you mean.")
ENDIF

EndTalk
}
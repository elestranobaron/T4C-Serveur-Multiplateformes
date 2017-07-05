#pragma hdrstop
#include "GMassistant.h"

GMassistant::GMassistant()
{}

GMassistant::~GMassistant()
{}

extern NPCstructure::NPC GMassistantNPC;

void GMassistant::Create( ){
	npc = GMassistantNPC;
	SET_NPC_NAME( "[7397]GM Assistant" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}
void GMassistant::OnAttacked( UNIT_FUNC_PROTOTYPE ){	   
	CastSpellSelf(__SPELL_NPC_CANTRIP_FREEZE)
	SELF_DESTRUCT; 
	// FIGHT; // Notes: SELF_DESTRUCT does not work if server < 1.10 
}

void GMassistant::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void GMassistant::OnTalk( UNIT_FUNC_PROTOTYPE )
{

UseC
static int iMonsterAmount[4];
static CString csMonsterID[4];
static CString csLastUserID;  
												  
InitTalk

Begin						   
""
IF(lpUser->GetGodFlags() & GOD_CAN_SUMMON_MONSTERS)
	IF (USER_NAME == csLastUserID)
		Conversation
		FORMAT(INTL( 7299, "GM Assistant v0.2 revision 11... internal systems check... OK. Welcome back, %s. Input command:"), USER_NAME)
	ELSE
		Conversation
		INTL( 7300, "GM Assistant v0.2 revision 11... internal systems check... OK. Input command:")
		;csLastUserID = USER_NAME;
	ENDIF
ELSE
	Conversation
	INTL( 7301, "Unauthorized user entry... communication terminated.")
	BREAK
ENDIF

Command(INTL( 7302, "LAST USER"))
""
IF (USER_NAME == csLastUserID) 
	Conversation
	INTL( 7303, "The last session user was you.")
ELSE
	Conversation
	FORMAT(INTL( 7304, "The last session user was %s."), csLastUserID) 
ENDIF

ParamCmd(INTL( 7305, "SHOUT $"))
""
;if ((strstr( PARAM(0), INTL( 7306, "!")) == 0) && (strstr( PARAM(0), INTL( 3771, "?")) == 0))
{
	CHATTER_SHOUT(FORMAT(INTL( 7307, "%s."), PARAM(0)));
}else{
	CHATTER_SHOUT( PARAM(0) )
};

/*
CmdAND("HELP", "TOPICS")
"The complete documentation regarding the dynamic portals and all of the "
"GM Assistant's features can be found in Section 12.4 of the server "
"documentation."  

CmdAND("HELP", "TOPICS")
"Accessing help files... Help is available on the following topics: \"Battlegrounds\", \"Invasions\", "
"\"Quests\" and \"Dynamic\" \"portals\"."

CmdAND("HELP", "BATTLEGROUND")
"Accessing help files... The battleground feature is not currently implemented."

CmdAND("HELP", "INVASION")
"Accessing help files... The invasion feature is not currently implemented."

CmdAND("HELP", "QUEST")
"Accessing help files... The quest feature is currently very limited. The \"Island\" \"Madness\" "
"maze is active and offers users a complex set of islands in which several different "
"quests may take place. The settings can be changed with the \"ISLAND\" \"MADNESS\" "
"command. Further help is available in the \"ISLAND\" \"MADNESS\" help sub-topic."

CmdAND3("HELP", "HEALING", "WELL")
"Accessing help files...  The healing well can be manually summoned using the monster ID \"HEALINGWELL\". "
"You can enable or disable the healing of the well by entering the commands \"enable\" \"well\" \"healing\" "
"or \"disable\" \"well\" \"healing\" at the GM assistant. Note: If you enable this option, ALL the healing wells "
"will provide healing. The default setting is {enabled}."

Command("HELP")
"Accessing help files... The GM assistant is an NPC designed for use with various GM "
"oriented features. It is basically a tool that you can summon whenever it is needed, "
"whether for a GM-specific quest or battleground. The help files are divided into topics "
", all accessible by typing \"help\" followed by the topic. For example, if you needed help "
"on how to start an invasion, you would type \"help\" \"invasion\". A list of the topics is "
"available by typing \"help\" \"topics\". Note: the GM assistant will only respond to GMs "
"with the GOD_CAN_SUMMON_MONSTERS gameop flag. If the GM assistant is attacked, it will "
"immediately self-destruct. You can also input the \"delete\" command to destroy it manually."
*/

Command(INTL( 554, "HELP"))
INTL( 7308, "All the commands and features included in the GM Assistant are documented in section 12.4 of the server documentation.")

CmdAND3(INTL( 7309, "ISLAND MADNESS"), INTL( 7310, "PRESET"), INTL( 7311, " 1 "))
INTL( 7312, "Processing... Island Madness teleporter configuration 1 selected.")
GiveGlobalFlag(__GLOBAL_FLAG_ISLAND_MAZE_PRESET, 1)

CmdAND(INTL( 7309, "ISLAND MADNESS"), INTL( 7313, " END "))
INTL( 7314, "Processing... Island Madness teleporters are now disabled.")
GiveGlobalFlag(__GLOBAL_FLAG_ISLAND_MAZE_PRESET, 0)

CmdAND(INTL( 7315, "ISOLATED ISLAND"), INTL( 7316, "START"))
INTL( 7317, "Processing... Isolated Island portal is enabled.")
GiveGlobalFlag(__GLOBAL_FLAG_ISOLATED_PRESET, 1) 

CmdAND(INTL( 7315, "ISOLATED ISLAND"), INTL( 7313, " END "))
INTL( 7318, "Processing... Isolated Island portal is now disabled.")
GiveGlobalFlag(__GLOBAL_FLAG_ISOLATED_PRESET, 0) 

CmdAND(INTL( 7319, "SCATTERED BONES"), INTL( 7316, "START"))
INTL( 7320, "Processing... Scattered Bones dungeon is enabled.")
GiveGlobalFlag(__GLOBAL_FLAG_SCATTERED_BONES_PRESET, 1)

CmdAND(INTL( 7319, "SCATTERED BONES"), INTL( 7313, " END "))
INTL( 7321, "Processing... Scattered Bones dungeon is now disabled.")
GiveGlobalFlag(__GLOBAL_FLAG_SCATTERED_BONES_PRESET, 0)

ParamCmd(INTL( 7322, "SET MONSTER $ TO $ $"))
""
;int iMonsterNumber = NUM_PARAM(0) - 1;
if(iMonsterNumber >= 0 && iMonsterNumber < 4){
	iMonsterAmount[iMonsterNumber] = NUM_PARAM(1);
	csMonsterID[iMonsterNumber] = PARAM(2);
	Conversation
	FORMAT(INTL( 7323, "Processing... Command executed successfully. Monster parameter %u is set to summon %u %s(s)."), iMonsterNumber + 1, iMonsterAmount[iMonsterNumber], csMonsterID[iMonsterNumber]);
}else{
	Conversation
	INTL( 7324, "Processing... Error executing command. Can only summon 4 different types of monsters at the same time. Input command:");
};

Command(INTL( 7325, "RESET MONSTERS"))
INTL( 7326, "Processing... Command executed successfully. All monster parameters reset. Input command:");
{
	int nCount;
	for( nCount = 0; nCount <= 3; nCount++){
		iMonsterAmount[nCount] = 0;
	};
}
		
Command(INTL( 7327, "LIST MONSTERS"))
INTL( 7328, "Accessing... ");
{
	int nCount;
	for( nCount = 0; nCount <= 3; nCount++){
		if(iMonsterAmount[nCount] > 0){
			Conversation
			FORMAT(INTL( 7329, "Monster parameter %u is set to summon %u %s(s). "), nCount + 1, iMonsterAmount[nCount], csMonsterID[nCount]);
		};
	};																					  
}

/*
Command(INTL( 7478, "MASS SUMMON2")) 
INTL( 7479, "Processing... This command is temporarily disabled.")
*/

ParamCmd(INTL( 7687, "MASS SUMMON2 $ $ $ $")) 
"";
int x1 = NUM_PARAM(0);
int y1 =	NUM_PARAM(1);
int x3 = NUM_PARAM(2);
int y3 =	NUM_PARAM(3);
int b1 = x1 + y1;
int b3 = -x3 + y3;
int x2 = (b1 - b3) / 2;
int y2 = -x2 + b1;
b1 = -x1 + y1;
b3 = x3 + y3;
int x4 = (b3 - b1) / 2;
int y4 = x4 + b1;
if(x1 < x2 && x1 < x3 && x1 < x4){
	int m1 = (x2 - x1) / (y2 - y1);
	b1 = -m1 * x1 + y1;
	int m2 = (x3 - x2) / (y3 - y2);
	int b2 = -m2 * x2 + y2;
	int m3 = (x4 - x3) / (y4 - y3);
	b3 = -m3 * x3 + y3;
	int m4 = (x1 - x4) / (y1 - y4);
	int b4 = -m4 * x4 + y4;
	int NumberOfMonstersSummoned;
	if(x1 >= 0 && x1 <= 3071 && x2 >= 0 && x2 <= 3071 && x3 >= 0 && x3 <= 3071 && x4 >= 0 && x4 <= 3071 && y1 >= 0 && y1 <= 3071 && y2 >= 0 && y2 <= 3071 && y3 >= 0 && y3 <= 3071 && y4 >= 0 && y4 <= 3071){
		int nCount;
		for( nCount = 0; nCount < 3; nCount++){
			if(iMonsterAmount[nCount] > 0){
				for(NumberOfMonstersSummoned = 0; NumberOfMonstersSummoned <= iMonsterAmount[nCount];){
					int x = (rnd.roll(dice(1, x3 - x1 + 1)) + x1 - 1);
					int y = (rnd.roll(dice(1, y4 - y2 + 1)) + y2 - 1);
					if((y >= m1 * x + b1) && (y >= m2 * x + b2) && (y <= m3 * x + b3) && (y <= m4 * x + b4)){
						NumberOfMonstersSummoned++;
						SUMMON( csMonsterID[nCount], x, y)
					};
				};
			};
		};
		Conversation
		FORMAT(INTL( 7481, "Processing... Command executed successfully. A total of %u monsters were summoned at target location."), iMonsterAmount[0] + iMonsterAmount[1] + iMonsterAmount[2] + iMonsterAmount[3]);
	}else{
		Conversation
		INTL( 7482, "Processing... Error executing command. Invalid coordinates. Input command:");
	};
}else{
	Conversation
	INTL( 7482, "Processing... Error executing command. Invalid coordinates. Input command:");
};

ParamCmd(INTL( 7480, "MASS SUMMON $ $ $ $")) 	
""
;if(NUM_PARAM(0) <= NUM_PARAM(2)){
	;if(NUM_PARAM(1) <= NUM_PARAM(3)){
		;if(NUM_PARAM(0) >= 0 && NUM_PARAM(0) <= 3071 && NUM_PARAM(1) >= 0 && NUM_PARAM(1) <= 3071 && NUM_PARAM(2) >= 0 && NUM_PARAM(2) <= 3071 && NUM_PARAM(3) >= 0 && NUM_PARAM(3) <= 3071){
			{
				int nCount;
				for( nCount = 0; nCount <= 3; nCount++){
					if(iMonsterAmount[nCount] > 0){
						if(iMonsterAmount[nCount] > 50){
							iMonsterAmount[nCount] = 50;
						};
						{
							int iNumberOfMonstersSummoned;
							for(iNumberOfMonstersSummoned = 1; iNumberOfMonstersSummoned <= iMonsterAmount[nCount]; iNumberOfMonstersSummoned++){
								SUMMON( csMonsterID[nCount], rnd.roll(dice(1, NUM_PARAM(2) - NUM_PARAM(0) + 1, NUM_PARAM(0) - 1)), rnd.roll(dice(1, NUM_PARAM(3) - NUM_PARAM(1) + 1, NUM_PARAM(1) - 1)))
							};
						};
					};
				};
			};
			Conversation
			FORMAT(INTL( 7481, "Processing... Command executed successfully. A total of %u monsters were summoned at target location."), iMonsterAmount[0] + iMonsterAmount[1] + iMonsterAmount[2] + iMonsterAmount[3]);
		}else{
			Conversation
			INTL( 7482, "Processing... Error executing command. Invalid coordinates. Input command:");
		}
	}else{
		Conversation
		INTL( 7483, "Processing... Error executing command. First Y coordinate must be inferior or equal to second Y coordinate. Input command:");
	}
}else{
	;if(NUM_PARAM(1) <= NUM_PARAM(3)){
		Conversation
		INTL( 7484, "Processing... Error executing command. First X and Y coordinates must be inferior or equal to second X and Y coordinates. Input command:");
	}else{
		Conversation
		INTL( 7485, "Processing... Error executing command. First X coordinate must be inferior or equal to second X coordinate. Input command:");
	}
} 
			  
ParamCmd(INTL( 7330, "SET PORTAL $ REWARD XP TO $"))
"";
CString csPortalID = PARAM(0);
int nXP = NUM_PARAM( 1 );
csPortalID.MakeUpper();
BYTE bPortalIndex = csPortalID[0] - 'A';			  
if(bPortalIndex >= 0 && bPortalIndex <= 25){
	if (( nXP <= 100000 ) && (nXP >= 1)){			
		dfGlobalFlags.SetFlag( 30320 + bPortalIndex, NUM_PARAM(1) )
		Conversation
		FORMAT(INTL( 7331, "Processing... Command successfully executed. Dynamic portal %c will now reward %u experience points."), bPortalIndex + 'A', nXP);
	}else{
		Conversation
		INTL( 7332, "Error executing command. Can only set XP reward between 1 and 100000 experience points. Input command:");
	};
}else{
	Conversation
	FORMAT(INTL( 7333, "Error executing command. %s is not a valid dynamic portal ID. Input command:"), PARAM(0) );
};

ParamCmd(INTL( 7334, "SET PORTAL $ REWARD GP TO $"))
"";
CString csPortalID = PARAM(0);
int nGP = NUM_PARAM( 1 );
csPortalID.MakeUpper();
BYTE bPortalIndex = csPortalID[0] - 'A';
if(bPortalIndex >= 0 && bPortalIndex <= 25){
	if ((nGP <= 100000) && (nGP >= 1)){			
		dfGlobalFlags.SetFlag( 30294 + bPortalIndex, nGP )
		Conversation
		FORMAT(INTL( 7486, "Processing... Command successfully executed. Dynamic portal %c will now reward %u gold."), bPortalIndex + 'A', nGP);
	}else{
		Conversation
		INTL( 7335, "Error executing command. Can only set GP reward between 1 and 100000 gold Input command:");
	};
}else{
	Conversation
	FORMAT(INTL( 7333, "Error executing command. %s is not a valid dynamic portal ID. Input command:"), PARAM(0) );
};
 
ParamCmd(INTL( 7336, "SET PORTAL $ TO $ $ $"))
"";
CString csPortalID = PARAM(0);
csPortalID.MakeUpper();
BYTE bPortalIndex = csPortalID[0] - 'A';
if(bPortalIndex >= 0 && bPortalIndex <= 25){
	WORD wPositionX = NUM_PARAM(1);
	WORD wPositionY = NUM_PARAM(2);
	BYTE bPositionWORLD = NUM_PARAM(3);
	if((wPositionX <= 3071 && wPositionX >= 0) && (wPositionY <= 3071 && wPositionY >= 0) && (bPositionWORLD <= 4 && bPositionWORLD >= 0)){
		dfGlobalFlags.SetFlag( 30257 + bPortalIndex, ( ( (DWORD)( (WORD)wPositionX ) << 20 ) + ( (DWORD)( (WORD)wPositionY ) << 8 ) + (DWORD)( (BYTE)bPositionWORLD ) ) )
		Conversation
		FORMAT(INTL( 7337, "Processing... Command successfully executed. Dynamic portal %c will now teleport to %u, %u, %u."), bPortalIndex + 'A', wPositionX, wPositionY, bPositionWORLD);
	}else{
		Conversation
		FORMAT(INTL( 7338, "Error executing command. %u, %u, %u is not a valid coordinate. Input command:"), wPositionX, wPositionY, bPositionWORLD);
	};
}else{
	Conversation
	FORMAT(INTL( 7333, "Error executing command. %s is not a valid dynamic portal ID. Input command:"), PARAM(0) );
};

ParamCmd(INTL( 7905, "CONVERT $ $ $ TO SANCTUARY"))
""
IF ((NUM_PARAM(0) > 3071) || (NUM_PARAM(0) < 0))
	Conversation
	INTL( 11717, "Error executing command. The X coordinate entered is incorrect.") 
ELSEIF ((NUM_PARAM(1) > 3071) || (NUM_PARAM(1) < 0))
	Conversation
	INTL( 11718, "Error executing command. The Y coordinate entered is incorrect.") 
ELSEIF ((NUM_PARAM(2) > 4) || (NUM_PARAM(2) < 0)) 
	Conversation
	INTL( 11719, "Error executing command. The world ID entered is incorrect.")
ELSE
	DWORD nFlag;	
	IF (NUM_PARAM(0) >= 2048) 
		;nFlag= (NUM_PARAM(0) * 1048576) + (NUM_PARAM(1) * 256) + (NUM_PARAM(2) - 4294967296); 
	ELSE
		;nFlag = (NUM_PARAM(0) * 1048576) + (NUM_PARAM(1) * 256) + (NUM_PARAM(2)); 
	ENDIF 
	Conversation
	FORMAT(INTL( 7906, "Processing... Coordinates %u, %u, %u converted to %u."), NUM_PARAM(0), NUM_PARAM(1), NUM_PARAM(2), nFlag)
ENDIF 

CmdAND3(INTL( 7339, "ENABLE"), INTL( 10737, "COLOSSEUM"), INTL( 1856, "MONSTER")) 
INTL( 11720, "Processing... The monster summoning of the Colosseum is now enabled.")
GiveGlobalFlag(__COLOSSEUM_MONSTER_DISABLE,0)

CmdAND3(INTL( 7342, "DISABLE"),INTL( 10737, "COLOSSEUM"), INTL( 1856, "MONSTER")) 
INTL( 11721, "Processing... The monster summoning of the Colosseum is now disabled.") 
GiveGlobalFlag(__COLOSSEUM_MONSTER_DISABLE, 1) 

CmdAND3(INTL( 11722, "STATUS"),INTL( 10737, "COLOSSEUM"),INTL( 1856, "MONSTER")) 
""
IF (CheckGlobalFlag(__COLOSSEUM_MONSTER_DISABLE) == 0) 
	Conversation
	INTL( 11723, "Processing... It is currently possible for players to summon monsters inside "
	"the colosseum.") 
ELSE
	Conversation
	INTL( 11724, "Processing... The Colosseum monster summoning feature is disabled.") 	
ENDIF 

CmdAND3(INTL( 20000, "ENABLE"), INTL( 20001, "BATTLE"), INTL(20002 , "MODE")) 
INTL( 11720, "Processing... The Battle Mode is now enabled.")
GiveGlobalFlag(__BATTLE_MODE_ENABLE,1)

CmdAND3(INTL( 20004, "DISABLE"),INTL( 20001, "BATTLE"), INTL(20002 , "MODE")) 
INTL( 11721, "Processing... The Battle Mode is now disabled.") 
GiveGlobalFlag(__BATTLE_MODE_ENABLE, 0) 

CmdAND3(INTL( 20005, "STATUS"),INTL( 20001, "BATTLE"),INTL( 20002, "MODE")) 
""
IF (CheckGlobalFlag(__BATTLE_MODE_ENABLE) == 1) 
	Conversation
	INTL( 20006, "Processing... the Battle Mode is now enabled. Players can fight,"
	"bringing gold and experience gains.") 
ELSE
	Conversation
	INTL(20007 , "Processing... The Battle Mode feature is disabled.") 	
ENDIF

CmdAND3(INTL( 7339, "ENABLE"),INTL( 7340, "WELL"),INTL( 2691, "HEALING"))
INTL( 7341, "Processing... The healing well is enabled.")
GiveGlobalFlag(__GLOBAL_FLAG_HEALING_WELL_ENABLED, 0) 
// __GLOBAL_FLAG_HEALING_WELL_ENABLED
// 0: The well heals. 
// 1:	The well does not heal.

CmdAND3(INTL( 7342, "DISABLE"),INTL( 7340, "WELL"),INTL( 2691, "HEALING"))
INTL( 7343, "Processing... The healing well is disabled.")
GiveGlobalFlag(__GLOBAL_FLAG_HEALING_WELL_ENABLED, 1) 

Command(INTL( 7688, "DISPEL ME"))
INTL( 7689, "Processing... Command successfully executed. Target completely dispelled of all effects. Input command:")
CastSpellTarget(__SPELL_MOB_COMPLETE_DISPEL_SPELL)

Command2(INTL( 7344, "DELETE"), INTL( 7345, "SELF-DESTRUCT"))
""
CastSpellSelf(__SPELL_NPC_CANTRIP_FREEZE)
SELF_DESTRUCT;

Command5(INTL( 518, "BYE"), INTL( 7346, "STOP"), INTL( 521, "EXIT"), INTL( 519, "LEAVE"), INTL( 520, "QUIT"))
INTL( 7347, "Communication terminated.")
BREAK

Default
INTL( 7348, "Unrecognized command. Read help files for more information. Input command:")

EndTalk

}
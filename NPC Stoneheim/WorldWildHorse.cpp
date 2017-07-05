///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "WorldWildHorse.h"

WorldWildHorse::WorldWildHorse()
{}

WorldWildHorse::~WorldWildHorse()
{}

extern NPCstructure::NPC WorldWildHorseNPC;

void WorldWildHorse::Create( void )
{
      npc = ( WorldWildHorseNPC );
      SET_NPC_NAME( "[10937]A mysterious wild horse" );  
      npc.InitialPos.X = 0; 
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0;
 npc.boPrivateTalk = TRUE;
}
 
void WorldWildHorse::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}
	
}
 

void WorldWildHorse::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////
 
{
InitTalk

Begin
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) < 10)
	BREAK
ELSE
	Conversation
	INTL( 9150, "You seem friendly enough... Since the Centaurs have given you so many Scrolls of Horse Friendship, "
	"I must assume you're a good fellow.")
ENDIF

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 9151, "I am a horse. Don't mind my talking, that's just the way I am. Some call me the World Wild Horse. "
"Personally, I think it's a stupid name.")

Command3(INTL( 488, "WHAT DO YOU"),INTL( 489, "WORK"),INTL( 487, "OCCUPATION"))
INTL( 9152, "I travel around the world. As long as you have Scrolls of Horse Friendship, I can teleport you to one of many "
"\"teleport\" \"locations\" around the world, but it will cost you a scroll every time.")

CmdAND(INTL( 1046, "TELEPORT"),INTL( 9153, "LOCATION"))
INTL( 9154, "Here are the places where I can take you: \"Lighthaven\" \"Bridge\", \"Arakas's\" \"Stonehenge\", \"Annabelle's\" "
"\"House\", \"Arakas's\" \"Brigands\", \"Windhowl's\" \"Entrance\", \"Blackblood's\" \"Castle\", \"Silversky\" "
"\"Castle\", \"Raven's\" \"Dust\" \"Stonehenge\", \"Raven's\" \"Dust\" \"Desert\", "
"and \"Stonecrest\" \"Plaza\".")

CmdAND(INTL( 7700, "STONECREST"),INTL( 9155, "PLAZA"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(286, 730, 0) 
	SUMMON2( "WORLDWILDHORSE",291, 731, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10287, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 


CmdAND3(INTL( 1284, "RAVEN"),INTL( 9158, "DUST"),INTL( 1492, "DESERT"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(280, 2520, 0)
	SUMMON2( "WORLDWILDHORSE",281, 2521, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10288, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 


CmdAND3(INTL( 1284, "RAVEN"),INTL( 9158, "DUST"),INTL( 9159, "STONEHENGE"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation	
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(1695, 2165, 0)
	SUMMON2( "WORLDWILDHORSE",1696, 2166, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10289, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 


CmdAND(INTL( 998, "SILVERSKY"),INTL( 537, "CASTLE"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation	
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(1495, 2465, 0)
	SUMMON2( "WORLDWILDHORSE",1496, 2466, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10290, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 

CmdAND(INTL( 3863, "BLACKBLOOD"),INTL( 537, "CASTLE"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation	
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(410, 1725 ,0)
	SUMMON2( "WORLDWILDHORSE",411, 1726, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10291, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 

CmdAND(INTL( 514, "WINDHOWL"),INTL( 8946, "ENTRANCE"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation	
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(1825, 1300 ,0)
	SUMMON2( "WORLDWILDHORSE",1826, 1301, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10292, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 

CmdAND(INTL( 513, "LIGHTHAVEN"),INTL( 9160, "BRIDGE"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(2775,1015,0)
	SUMMON2( "WORLDWILDHORSE",2776,1016, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10293, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 

CmdAND(INTL( 515, "ARAKAS"),INTL( 9159, "STONEHENGE"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(2790, 175,0)
	SUMMON2( "WORLDWILDHORSE",2791,176, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10294, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 

CmdAND(INTL( 523, "ANNABELLE"),INTL( 9161, "HOUSE"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(1580, 210,0)
	SUMMON2( "WORLDWILDHORSE",1581, 211, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10295, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 

CmdAND(INTL( 515, "ARAKAS"),INTL( 9162, "BRIGANDS"))
""
IF (CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) >= 1) 
	Conversation
	INTL( 9156, "Here we go.")
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	TELEPORT(2180, 1245 ,0)
	SUMMON2( "WORLDWILDHORSE",2181, 1246, 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9157, "The World Wild Horse carries you on his back to your destination."))
	SELF_DESTRUCT;
ELSE
	Conversation
	INTL( 10296, "A horse I may be, a fool I am not. I can clearly see that you no longer "
	"have the Scrolls of Horse Friendship.")
	BREAK
ENDIF 

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 9163, "Well, so long and thanks for all the scrolls")

;int nNumScrolls = CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP);
FOR(0, nNumScrolls) 
	TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
ENDFOR
BREAK 

Command4(INTL( 520, "QUIT"),INTL( 521, "EXIT"),INTL( 519, "LEAVE"),INTL( 518, "BYE"))
INTL( 973, "Goodbye.")

Default
INTL( 1864, "...")

EndTalk
}

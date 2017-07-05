#pragma hdrstop
#include "Well.h"

Well::Well()
{}

Well::~Well()
{}

extern NPCstructure::NPC WellNPC;

void Well::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}
	
}

void Well::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}
void Well::Create( void )
{
    npc = WellNPC;
    SET_NPC_NAME( "[2991]A magical well" );
    npc.InitialPos.X = 812;
    npc.InitialPos.Y = 630;
    npc.InitialPos.world = 2;
	 npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Well::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
{
InitTalk

Begin
INTL( 6393, "{You} {hear} {some} {faint} {sounds} {of} {dripping} {water.}")

Command(INTL( 6394, "MAKE MINE THY MIGHT"))  
""
IF (CheckFlag(__QUEST_ROYAL_KEY6) <= 4) 
	Conversation
	INTL( 6395, "{You} {hear} {the} {words} {you've} {spoken} {echoing} {back} {to} {you} {from} {the} {depths} {of} {the} {well.}")
ELSE
	IF (USER_KARMA >= 150)
		IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)	// User is a Champion of Order?
			IF (CheckItem(__OBJ_SWORD_OF_MIGHT) == 0)	// User doesn't already have a Sword of Might:
				Conversation		
				INTL( 6396, "{The} {Sword} {of} {Might} {magically} {floats} {out} {of} {the} {well} {into} "
				"{your} {hands!}  {You} {receive} {12,000} {experience} {points} {as} {a} {reward.}")
				GiveFlag(__QUEST_SWORD_OF_MIGHT, (CurrentRound+rnd.roll(dice(1,500))))
				GiveItem(__OBJ_SWORD_OF_MIGHT)
				GetItemHandle(__OBJ_SWORD_OF_MIGHT, Sword_Of_Might)
				GiveUnitFlag(Sword_Of_Might, __ITEM_FLAG_SWORD_OF_MIGHT, CheckFlag(__QUEST_SWORD_OF_MIGHT))
				GiveXP(12000)
			ELSE	// User already has Sword of Might:										
				Conversation
				INTL( 6397, "{You} {hear} {the} {words} {you've} {spoken} {echoing} {back} {to} {you} {from} {the} {depth} {of} {the} {well.}")
			ENDIF
		ELSE
			Conversation
			INTL( 6397, "{You} {hear} {the} {words} {you've} {spoken} {echoing} {back} {to} {you} {from} {the} {depth} {of} {the} {well.}")
		ENDIF
	ELSE						
		Conversation
		INTL( 6397, "{You} {hear} {the} {words} {you've} {spoken} {echoing} {back} {to} {you} {from} {the} {depth} {of} {the} {well.}")
	ENDIF
ENDIF

Command(INTL( 7296, "ENTER") )
INTL( 6398, "{The} {inside} {of} {the} {well} {is} {too} {slippery!}")

Default
INTL( 6395, "{You} {hear} {the} {words} {you've} {spoken} {echoing} {back} {to} {you} {from} {the} {depths} {of} {the} {well.}")
BREAK

EndTalk
}


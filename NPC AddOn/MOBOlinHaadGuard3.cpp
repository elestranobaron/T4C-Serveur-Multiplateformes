#pragma hdrstop
#include "MOBOlinHaadGuard3.h"

MOBOlinHaadGuard3::MOBOlinHaadGuard3()
{}

MOBOlinHaadGuard3::~MOBOlinHaadGuard3()
{}

extern NPCstructure::NPC MOBOlinHaadGuard3NPC;

void MOBOlinHaadGuard3::Create(){
   npc = MOBOlinHaadGuard3NPC;
   SET_NPC_NAME( "[12753]Olin Haad guard" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}

void MOBOlinHaadGuard3::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
	IF (rnd.roll(dice(1,30)) == 1) 
		IF (rnd.roll(dice(1,2)) == 1) 
			SHOUT(INTL( 12413, "You're no match for me!")) 
		ELSE 
			SHOUT(INTL( 12422, "Ow! You'll pay for that in blood!"))
		ENDIF 
	ENDIF    
   }
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBOlinHaadGuard3::OnDeath( UNIT_FUNC_PROTOTYPE )
{

NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void MOBOlinHaadGuard3::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
SWITCH (rnd.roll(dice(1,3)))
CASE(1)
	Conversation
	INTL( 12423, "Stay put and I might not hurt you.")
ENDCASE
CASE(2)
	Conversation
	INTL( 12424, "Olin Haad is your new master. Obey him and you will be spared.")
ENDCASE
CASE(3)
	Conversation
	INTL( 12425, "Don't resist Olin Haad. Nothing can stop us now.") 
ENDCASE
ENDSWITCH
BREAK

Default
""
BREAK

EndTalk
}



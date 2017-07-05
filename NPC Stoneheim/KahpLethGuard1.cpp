#pragma hdrstop
#include "KahpLethGuard1.H"

KahpLethGuard1::KahpLethGuard1()
{}

KahpLethGuard1::~KahpLethGuard1()
{}

extern NPCstructure::NPC KahpLethSkraugBattlefieldGuardNPC;

void KahpLethGuard1::Create( void )
{
      npc = ( KahpLethSkraugBattlefieldGuardNPC ) ;
      SET_NPC_NAME( "[10863]A skraug guard" );
      npc.InitialPos.X = 0;
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0; 
		npc.boPrivateTalk = TRUE;
}

void KahpLethGuard1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk
    
Begin
INTL( 9314, "You bedder go back to surface... Me smell bad skraungs near.")

Command4(INTL( 518, "BYE"), INTL( 519, "LEAVE"), INTL( 520, "QUIT"), INTL( 521, "EXIT"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 9315, "The skraung guard glares at you and you quickly wish you were somewhere else."))
BREAK

Default
""
PRIVATE_SYSTEM_MESSAGE(INTL( 9316, "The skraung guard stares blankly at you as you ask your question."))

EndTalk
}
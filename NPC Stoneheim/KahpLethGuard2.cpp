#pragma hdrstop
#include "KahpLethGuard2.H"

KahpLethGuard2::KahpLethGuard2()
{}

KahpLethGuard2::~KahpLethGuard2()
{}

extern NPCstructure::NPC KahpLethSkraugBattlefieldGuardNPC;

void KahpLethGuard2::Create( void )
{
      npc = ( KahpLethSkraugBattlefieldGuardNPC ) ;
      SET_NPC_NAME( "[10864]A skraug guard" );
      npc.InitialPos.X = 0;
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0; 
		npc.boPrivateTalk = TRUE;
}

void KahpLethGuard2::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk
 
Begin
INTL( 9335, "Watch yur back. No more guards after dis point. You in battlezone now.")

Command4(INTL( 518, "BYE"), INTL( 519, "LEAVE"), INTL( 520, "QUIT"), INTL( 521, "EXIT"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 9336, "The skraug guard glares at you and you quickly wish you were somewhere else."))
BREAK

Default
""
PRIVATE_SYSTEM_MESSAGE(INTL( 9337, "The skraug guard stares blankly at you as you ask your question."))

EndTalk

}
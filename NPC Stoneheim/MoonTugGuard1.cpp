#pragma hdrstop
#include "MoonTugGuard1.H"

MoonTugGuard1::MoonTugGuard1()
{}

MoonTugGuard1::~MoonTugGuard1()
{}

extern NPCstructure::NPC MoonTugSkraugBattlefieldGuardNPC;

void MoonTugGuard1::Create( void )
{
      npc = ( MoonTugSkraugBattlefieldGuardNPC ) ;
      SET_NPC_NAME( "[10897]A skraug sentry" );
      npc.InitialPos.X = 0;
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0; 
			npc.boPrivateTalk = TRUE;
}
 
void MoonTugGuard1::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk
Begin
INTL( 9338, "Dis is no place fer leetle hummies like you. Big skraugs fight over dere.")

Command4(INTL( 518, "BYE"), INTL( 519, "LEAVE"), INTL( 520, "QUIT"), INTL( 521, "EXIT"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 9339, "The skraug sentry growls ominously when you wave your hand... you quickly stop and look away."))
BREAK

Default
""
IF (rnd.roll(dice(1, 2) ) == 1)
   Conversation
   INTL( 9340, "Hummie bedder go back home before you get hert.")
ELSE
   Conversation
   INTL( 9341, "No time for leetle hummie questions.")
ENDIF

EndTalk
}
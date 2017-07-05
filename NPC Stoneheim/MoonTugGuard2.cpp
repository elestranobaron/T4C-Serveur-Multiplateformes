#pragma hdrstop
#include "MoonTugGuard2.H"

MoonTugGuard2::MoonTugGuard2()
{}

MoonTugGuard2::~MoonTugGuard2()
{}

extern NPCstructure::NPC MoonTugSkraugBattlefieldGuardNPC;

void MoonTugGuard2::Create( void )
{
      npc = ( MoonTugSkraugBattlefieldGuardNPC ) ;
      SET_NPC_NAME( "[10898]A sentry" );
      npc.InitialPos.X = 0;
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0; 
			npc.boPrivateTalk = TRUE;
}
  

void MoonTugGuard2::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk
Begin
INTL( 9342, "Dis be border between Moon Tug and battleground. Dere be no more protection over dere.")

Command4(INTL( 518, "BYE"), INTL( 519, "LEAVE"), INTL( 520, "QUIT"), INTL( 521, "EXIT"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 9339, "The skraug sentry growls ominously when you wave your hand... you quickly stop and look away."))
BREAK

Default
""
IF (rnd.roll(dice(1, 10) ) == 1)
   Conversation
   INTL( 9343, "Grrr, arrg.")
ELSE
   Conversation
   INTL( 9341, "No time for leetle hummie questions.")
ENDIF

EndTalk
}
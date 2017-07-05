#pragma hdrstop
#include "Doppelganger.H"

Doppelganger::Doppelganger()
{}

Doppelganger::~Doppelganger()
{}

extern SimpleMonster::NPC DoppelgangerNPC;

void Doppelganger::Create( void )
{
        npc = ( DoppelgangerNPC );
        SET_NPC_NAME( "[12730]Doppelganger" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void Doppelganger::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	TFormat FORMAT;
	if( target != NULL )
	{
		IF(NPC_HP>2500)
			IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 1)
				CastSpellSelf(__SPELL_DOPPELGANGER_SELF_DAMAGE_1_SPELL)
			ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 2)
				CastSpellSelf(__SPELL_DOPPELGANGER_SELF_DAMAGE_2_SPELL)
			ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) > 2)
				CastSpellSelf(__SPELL_DOPPELGANGER_SELF_DAMAGE_3_SPELL)
			ELSE
				PRIVATE_SYSTEM_MESSAGE(INTL( 12001, "You can't seem to be able to affect the doppelganger..."))
			ENDIF
		ELSE
/* V2 fix for the Doppel portal abuse of logging within a portal and re-killing the same doppelganger - Aedus (15Mar06) */
			SWITCH(CheckFlag(__FLAG_ADDON_DOPPELGANGER_PORTAL_USED_TO_ENTER))
				CASE(1)
					GiveFlag(__FLAG_ADDON_PORTAL_1_CLEARED, 1)
				ENDCASE
				CASE(2)
					GiveFlag(__FLAG_ADDON_PORTAL_2_CLEARED, 1)
				ENDCASE
				CASE(3)
					GiveFlag(__FLAG_ADDON_PORTAL_3_CLEARED, 1)
				ENDCASE
				CASE(4)
					GiveFlag(__FLAG_ADDON_PORTAL_4_CLEARED, 1)
				ENDCASE
				CASE(5)
					GiveFlag(__FLAG_ADDON_PORTAL_5_CLEARED, 1)
				ENDCASE
				CASE(6)
					GiveFlag(__FLAG_ADDON_PORTAL_6_CLEARED, 1)
				ENDCASE
				CASE(7)
					GiveFlag(__FLAG_ADDON_PORTAL_7_CLEARED, 1)
				ENDCASE
				CASE(8)
					GiveFlag(__FLAG_ADDON_PORTAL_8_CLEARED, 1)
				ENDCASE
			ENDSWITCH
/* V2 Fix (Aug 07, 2007) - Allow a player to reenter the same dopple fight until they kill him */
			GiveFlag(__FLAG_V2_DOPPLE_PORTAL_FIX, 0)
			CONSTANT Portals = (CheckFlag(__FLAG_ADDON_PORTAL_1_CLEARED) + CheckFlag(__FLAG_ADDON_PORTAL_2_CLEARED) +
					CheckFlag(__FLAG_ADDON_PORTAL_3_CLEARED) + CheckFlag(__FLAG_ADDON_PORTAL_4_CLEARED) +
					CheckFlag(__FLAG_ADDON_PORTAL_5_CLEARED) + CheckFlag(__FLAG_ADDON_PORTAL_6_CLEARED) +
					CheckFlag(__FLAG_ADDON_PORTAL_7_CLEARED) + CheckFlag(__FLAG_ADDON_PORTAL_8_CLEARED));
			IF(Portals == 8 )
				PRIVATE_SYSTEM_MESSAGE(INTL( 12002, "Your body quivers with power as you absorb the doppelganger's remaining essence."))
				SHOUT(INTL( 12003, "H...how can this be possible? NOOOOOOO!"))
			ELSE
				PRIVATE_SYSTEM_MESSAGE(INTL( 12004, "You absorb part of the doppelganger's essence into your own."))
				SHOUT(FORMAT(INTL( 12005, "I don't believe it! I'll get you next time, %s!"), USER_NAME))
			ENDIF
			GiveFlag(__FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER, Portals + 1)
			SELF_DESTRUCT;
		ENDIF
	}
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

/*
void Doppelganger::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		
	}
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}
*/

void Doppelganger::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
/* V2 fix for the Doppel portal abuse of logging within a portal and re-killing the same doppelganger - Aedus (15Mar06) */
		SWITCH(CheckFlag(__FLAG_ADDON_DOPPELGANGER_PORTAL_USED_TO_ENTER))
			CASE(1)
				GiveFlag(__FLAG_ADDON_PORTAL_1_CLEARED, 1)
			ENDCASE
			CASE(2)
				GiveFlag(__FLAG_ADDON_PORTAL_2_CLEARED, 1)
			ENDCASE
			CASE(3)
				GiveFlag(__FLAG_ADDON_PORTAL_3_CLEARED, 1)
			ENDCASE
			CASE(4)
				GiveFlag(__FLAG_ADDON_PORTAL_4_CLEARED, 1)
			ENDCASE
			CASE(5)
				GiveFlag(__FLAG_ADDON_PORTAL_5_CLEARED, 1)
			ENDCASE
			CASE(6)
				GiveFlag(__FLAG_ADDON_PORTAL_6_CLEARED, 1)
			ENDCASE
			CASE(7)
				GiveFlag(__FLAG_ADDON_PORTAL_7_CLEARED, 1)
			ENDCASE
			CASE(8)
				GiveFlag(__FLAG_ADDON_PORTAL_8_CLEARED, 1)
			ENDCASE
		ENDSWITCH
/* V2 Fix (Aug 07, 2007) - Allow a player to reenter the same dopple fight until they kill him */
		GiveFlag(__FLAG_V2_DOPPLE_PORTAL_FIX, 0)
		CONSTANT Portals = 	(CheckFlag(__FLAG_ADDON_PORTAL_1_CLEARED) + CheckFlag(__FLAG_ADDON_PORTAL_2_CLEARED) +
				CheckFlag(__FLAG_ADDON_PORTAL_3_CLEARED) + CheckFlag(__FLAG_ADDON_PORTAL_4_CLEARED) +
				CheckFlag(__FLAG_ADDON_PORTAL_5_CLEARED) + CheckFlag(__FLAG_ADDON_PORTAL_6_CLEARED) +
				CheckFlag(__FLAG_ADDON_PORTAL_7_CLEARED) + CheckFlag(__FLAG_ADDON_PORTAL_8_CLEARED));
		IF(Portals == 8 )
			PRIVATE_SYSTEM_MESSAGE(INTL( 12002, "Your body quivers with power as you absorb the doppelganger's remaining essence."))
			SHOUT(INTL( 12003, "H...how can this be possible? NOOOOOOO!"))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 12004, "You absorb part of the doppelganger's essence into your own."))
			SHOUT(FORMAT(INTL( 12005, "I don't believe it! I'll get you next time, %s!"), USER_NAME))
		ENDIF
		GiveFlag(__FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER, Portals + 1)
		SELF_DESTRUCT;
	}

    CLOSE_HANDLER
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}
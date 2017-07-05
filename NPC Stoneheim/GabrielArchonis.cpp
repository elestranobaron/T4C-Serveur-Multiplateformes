#pragma hdrstop
#include "GabrielArchonis.h"

GabrielArchonis::GabrielArchonis()
{}

GabrielArchonis::~GabrielArchonis()
{}

extern NPCstructure::NPC OracleAssistantNPC;

void GabrielArchonis::Create( ){
   npc = OracleAssistantNPC;
	SET_NPC_NAME(   "[10852]Gabriel Archonis" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void GabrielArchonis::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 

	TFormat FORMAT;
	if( target != NULL ){

		IF(CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT) == 0) // If noone has hit Gabriel yet
			GiveNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT, CurrentRound) // Gabriel can now be hit
			GiveFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT, CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT)) // and this character is the one that can hurt him
		ELSEIF(CurrentRound - CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT) >= 6000) // However, if the chosen character has not hit Gabriel for over 5 minutes
			GiveNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT, CurrentRound) // Gabriel can now be hit by anyone else
			GiveFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT, CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT)) // this character being the one that can now hurt him
		ENDIF
		IF(CheckFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT) == CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT)) // If user is the 'one'
			GiveNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT, CurrentRound) // This line and the next one renew the flag to ensure the user can hit Gabriel for another 5 minutes
			GiveFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT, CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT))
			IF(USER_HP<50) // If user is low hp enough that he can harm the assistant
//			IF(USER_HP<5/100*USER_MAXHP) // If user is low hp enough that he can harm the assistant
				IF(NPC_HP>750000) // If assistant is strong enough to survive one more hit
					CastSpellSelf(__SPELL_MOB_ORACLE_ASSISTANT_SELF_DAMAGE_SPELL)
//					self->SetHP(NPC_HP-500000, true) // assistant suffers one hit
				ELSE
					GiveFlag(__FLAG_USER_HAS_DEFEATED_ASSISTANT, 1) // the assistant is defeated and the user is sent back to the Oracle
					PRIVATE_SYSTEM_MESSAGE(INTL( 8231, "You have defeated Gabriel Archonis!"))
					CastSpellTarget(__SPELL_MOB_ORACLE_ASSISTANT_TELEPORT_SPELL)
					SELF_DESTRUCT;
				ENDIF
			ELSE
				IF(NPC_HP<=9900000)
					CastSpellSelf(__SPELL_MOB_ORACLE_ASSISTANT_SELF_HEAL_SPELL)
//					self->SetHP(NPC_HP+100000, true)
	 //			ELSE
	 //			PRIVATE_SYSTEM_MESSAGE(INTL( 11329, "HP<9.9m This message is for debugging purposes only. Please ignore"))
				ENDIF
			ENDIF
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 10531, "Something seems to prevent you from hurting Gabriel."))
		ENDIF

	}

NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void GabrielArchonis::OnHit( UNIT_FUNC_PROTOTYPE )
{ 

	TFormat FORMAT;
	if( target != NULL ){

		IF(CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT) == 0) // If noone has hit Gabriel yet
			GiveNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT, CurrentRound) // Gabriel can now be hit
			GiveFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT, CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT)) // and this character is the one that can hurt him
		ELSEIF(CurrentRound - CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT) >= 6000) // However, if the chosen character has not hit Gabriel for over 5 minutes
			GiveNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT, CurrentRound) // Gabriel can now be hit by anyone else
			GiveFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT, CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT)) // this character being the one that can now hurt him
		ENDIF
		IF(CheckFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT) == CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT)) // If user is the 'one'
			GiveNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT, CurrentRound) // This line and the next one renew the flag to ensure the user can hit Gabriel for another 5 minutes
			GiveFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT, CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT))
			IF(USER_HP<50) // If user is low hp enough that he can harm the assistant
				IF(NPC_HP>750000) // If assistant is strong enough to survive one more hit
					CastSpellSelf(__SPELL_MOB_ORACLE_ASSISTANT_SELF_DAMAGE_SPELL)
				ELSE
					GiveFlag(__FLAG_USER_HAS_DEFEATED_ASSISTANT, 1) // the assistant is defeated and the user is sent back to the Oracle
					PRIVATE_SYSTEM_MESSAGE(INTL( 8231, "You have defeated Gabriel Archonis!"))
					CastSpellTarget(__SPELL_MOB_ORACLE_ASSISTANT_TELEPORT_SPELL)
					SELF_DESTRUCT;
				ENDIF
			ELSE
				IF(NPC_HP<=9900000)
					CastSpellSelf(__SPELL_MOB_ORACLE_ASSISTANT_SELF_HEAL_SPELL)
	//	 		ELSE
	//				PRIVATE_SYSTEM_MESSAGE(INTL( 11329, "HP<9.9m This message is for debugging purposes only. Please ignore"))
				ENDIF
			ENDIF
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 10531, "Something seems to prevent you from hurting Gabriel."))
		ENDIF

	}

SimpleMonster::OnHit( UNIT_FUNC_PARAM );
}

void GabrielArchonis::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 8232, "In the name of all that is good and pure, I salute you! Prepare to taste my steel!")
GiveNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT, CurrentRound)
GiveFlag(__FLAG_CHARACTER_CAN_HIT_ASSISTANT, CheckNPCFlag(__FLAG_GABRIEL_CAN_BE_HIT))
FIGHT

Default
""

EndTalk
}

#pragma hdrstop
#include "ShadeenMaskedAssassin.H"

ShadeenMaskedAssassin::ShadeenMaskedAssassin()
{}

ShadeenMaskedAssassin::~ShadeenMaskedAssassin()
{}

extern NPCstructure::NPC ShadeenMaskedAssassinNPC;

void ShadeenMaskedAssassin::Create( void )
{
        npc = ( ShadeenMaskedAssassinNPC );
        SET_NPC_NAME( "[2982]Shadeen's masked assassin" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void ShadeenMaskedAssassin::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		SHOUT(INTL( 6316, "Arrrgh..."))
	}
   SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void ShadeenMaskedAssassin::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{		
		SWITCH(rnd.roll(dice(1,9)))
			CASE (1)
				SHOUT(INTL( 6317, "Your fate is sealed!"))
			ENDCASE			
			CASE(2)
				SHOUT(INTL( 6318, "Shadeen put her faith in us! We shall not fail!"))
			ENDCASE
         CASE(3)
         	SHOUT(INTL( 6319, "I enjoy seeing you bleeding to death."))
         ENDCASE
         OTHERWISE
         ENDCASE
		ENDSWITCH
	}
   SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}




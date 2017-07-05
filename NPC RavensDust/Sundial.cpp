//////////////////////////////////////////////////////////////////////
// Sundial.cpp: implementation of the Sundial class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Sundial.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Sundial::Sundial()
{}

Sundial::~Sundial()
{}

extern NPCstructure::NPC SundialNPC;

void Sundial::Create( ){
	npc = SundialNPC;
	SET_NPC_NAME( "[2983]A sundial" );
	npc.InitialPos.X = 0; 
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void Sundial::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}
	
}

void Sundial::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Sundial::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
SWITCH(TFCTime::Hour())
	CASE(0)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7558, "The sun is not up yet."))
	ENDCASE
	CASE(1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7558, "The sun is not up yet."))
	ENDCASE
	CASE(2)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7558, "The sun is not up yet."))
	ENDCASE
	CASE(3)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7558, "The sun is not up yet."))
	ENDCASE
	CASE(4)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3644, "According to the sundial, it is 4 hours past highmoon."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3646, "According to the sundial, it is 5 hours past highmoon."))
		ENDIF
	ENDCASE
	CASE(5)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3646, "According to the sundial, it is 5 hours past highmoon."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3649, "According to the sundial, it is 6 hours past highmoon."))
		ENDIF
	ENDCASE
	CASE(6)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3649, "According to the sundial, it is 6 hours past highmoon."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3652, "According to the sundial, it is 5 hours before highsun."))
		ENDIF
	ENDCASE
	CASE(7)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3652, "According to the sundial, it is 5 hours before highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3655, "According to the sundial, it is 4 hours before highsun."))
		ENDIF
	ENDCASE
	CASE(8)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3655, "According to the sundial, it is 4 hours before highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3658, "According to the sundial, it is 3 hours before highsun."))
		ENDIF
	ENDCASE
	CASE(9)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3658, "According to the sundial, it is 3 hours before highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3661, "According to the sundial, it is 2 hours before highsun."))
		ENDIF
	ENDCASE
	CASE(10)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3661, "According to the sundial, it is 2 hours before highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3664, "According to the sundial, it is almost highsun."))
		ENDIF
	ENDCASE
	CASE(11)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3664, "According to the sundial, it is almost highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3667, "According to the sundial, it is highsun."))
		ENDIF
	ENDCASE
	CASE(12)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3667, "According to the sundial, it is highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3670, "According to the sundial, it is a bit past highsun."))
		ENDIF
	ENDCASE
	CASE(13)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3670, "According to the sundial, it is a bit past highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3673, "According to the sundial, it is 2 hours past highsun."))
		ENDIF
	ENDCASE
	CASE(14)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3673, "According to the sundial, it is 2 hours past highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3676, "According to the sundial, it is 3 hours past highsun."))
		ENDIF
	ENDCASE
	CASE(15)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3676, "According to the sundial, it is 3 hours past highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3645, "According to the sundial, it is 4 hours past highsun."))
		ENDIF
	ENDCASE
	CASE(16)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3645, "According to the sundial, it is 4 hours past highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3648, "According to the sundial, it is 5 hours past highsun."))
		ENDIF
	ENDCASE
	CASE(17)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3648, "According to the sundial, it is 5 hours past highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3651, "According to the sundial, it is 6 hours past highsun."))
		ENDIF
	ENDCASE
	CASE(18)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3651, "According to the sundial, it is 6 hours past highsun."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3654, "According to the sundial, it is 5 hours before highmoon."))
		ENDIF
	ENDCASE
	CASE(19)
		IF((TFCTime::Minute()) <= 30)
			PRIVATE_SYSTEM_MESSAGE(INTL( 3654, "According to the sundial, it is 5 hours before highmoon."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 3657, "According to the sundial, it is 4 hours before highmoon."))
		ENDIF
	ENDCASE
	CASE(20)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7559, "The sun is no longer visible."))
	ENDCASE
	CASE(21)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7559, "The sun is no longer visible."))
	ENDCASE
	CASE(22)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7559, "The sun is no longer visible."))
	ENDCASE
	CASE(23)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7559, "The sun is no longer visible."))
	ENDCASE
ENDSWITCH
BREAK

Default
""

EndTalk

}
	
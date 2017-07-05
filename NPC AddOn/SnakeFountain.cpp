#pragma hdrstop
#include "SnakeFountain.h"

SnakeFountain::SnakeFountain()
{}

SnakeFountain::~SnakeFountain()
{}

extern NPCstructure::NPC WellNPC;

void SnakeFountain::Create( ){
  npc = WellNPC;
	SET_NPC_NAME( "[12773]A well filled with snakes" );
  npc.InitialPos.X = 826;
  npc.InitialPos.Y = 1907;
  npc.InitialPos.world = 1;
}
void SnakeFountain::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void SnakeFountain::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void SnakeFountain::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF ((CheckItem(__OBJ_FLASK_OF_GLURIURL_BLOOD)>=1)||(CheckItem(__OBJ_HEART_OF_GLURIURL)>=1)) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 12580, "You discern an inscription on the well which reads:")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 12581, "  ~Herein lies the blood of Gluriurl~"))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12582, "The well is filled with snakes submerged in greenish waters.")) 		
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12580, "You discern an inscription on the well which reads:")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 12581, "  ~Herein lies the blood of Gluriurl~"))
	    PRIVATE_SYSTEM_MESSAGE(INTL( 12583, "The well is filled with snakes submerged in greenish waters but you manage to gather some of the liquid into a flask.")) 
		GiveItem(__OBJ_FLASK_OF_GLURIURL_BLOOD) 
	ENDIF
ELSEIF(IsInRange(8)) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 12584, "You hear some hissing noises but you're too far away from the well to inspect it.")) 
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12585, "You must step closer to the well to inspect it.")) 
ENDIF
BREAK

Default
""
BREAK

EndTalk

}

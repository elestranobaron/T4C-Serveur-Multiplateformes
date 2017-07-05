#pragma hdrstop
#include "Gluriurl.h"

Gluriurl::Gluriurl()
{}

Gluriurl::~Gluriurl()
{}

extern NPCstructure::NPC GluriurlNPC;

void Gluriurl::Create( ){
  npc = GluriurlNPC;
  SET_NPC_NAME( "[12739]Gluriurl {God of Corruption}");
  npc.InitialPos.X = 0; 
  npc.InitialPos.Y = 0;
  npc.InitialPos.world = 0;
}

void Gluriurl::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		switch(rnd(0, 5))
			{
			case 0: CastSpellSelf(__SPELL_MOB_FAST_REGEN); break;
			default: break;
			}
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Gluriurl::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 

	GLOBAL_SYSTEM_MESSAGE(INTL( 12161, "The sky darkens suddenly...")); 
	CastSpellSelf(__SPELL_EFFECT_FIRECIRCLE);
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_GLURIURL_PRESENT, 1);

NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void Gluriurl::OnDeath( UNIT_FUNC_PROTOTYPE )
{

	if( target != NULL )
	{
		IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 41)
			GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 42)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12162, "The Gypsy's voice enters your head:"))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12163, "You have defeated the God of Corruption! Please, come visit me when you have the chance,"))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12164, "as I must thank you personally for all you have done."))
		ENDIF
		GLOBAL_SYSTEM_MESSAGE(INTL( 12165, "The ground shakes violently for a few seconds."))
	}
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_GLURIURL_PRESENT, 0);

NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}


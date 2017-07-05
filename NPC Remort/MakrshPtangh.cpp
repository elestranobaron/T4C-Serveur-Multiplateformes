#pragma hdrstop
#include "MakrshPtangh.h"

MakrshPtangh::MakrshPtangh()
{}

MakrshPtangh::~MakrshPtangh()
{}

extern NPCstructure::NPC MakrshPtanghNPC;

void MakrshPtangh::Create( ){
	npc = MakrshPtanghNPC;
	SET_NPC_NAME( "[11524]Makrsh P'Tangh" );
	npc.InitialPos.X = 2265;
	npc.InitialPos.Y = 295;
	npc.InitialPos.world = 1;
}

void MakrshPtangh::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MakrshPtangh::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 11376, "Ahh finally! I have waited long for one such as yourself. I am surprised you made it "
"this far. Come now, I will show you the true meaning of pain!")
SUMMON2("MAKRSHPTANGH2", 2265, 145, 1)
//GLOBAL_SYSTEM_MESSAGE( "A deadly fog is suddently springing from the depths..." );
GiveGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_IS_FIGHTING, 0)
CastSpellSelf(__SPELL_NPC_CANTRIP_FLAK)
SELF_DESTRUCT
BREAK

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
""

Command2(INTL( 11377, "MakrshPtangh"), INTL( 8955, "UNSEEN"))
""

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
""

Default
""

EndTalk
}
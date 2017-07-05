#pragma hdrstop
#include "HighPriestGunthar2.h"

HighPriestGunthar2::HighPriestGunthar2()
{}

HighPriestGunthar2::~HighPriestGunthar2()
{}

extern NPCstructure::NPC HighPriestGunthar2NPC;

void HighPriestGunthar2::Create( ){
	npc = HighPriestGunthar2NPC;
	SET_NPC_NAME( "[12744]High Priest Gunthar");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void HighPriestGunthar2::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}

void HighPriestGunthar2::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void HighPriestGunthar2::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	
	CastSpellSelf(__SPELL_SELF_DESTRUCT_2_MINUTES);
SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}

void HighPriestGunthar2::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Stone = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 22)
	Conversation
	FORMAT(INTL( 12350, "By our divine Artherk, that was close! You saved my life, %s! Now then, were you successful in "
	"retrieving the stone?"), USER_NAME)
	SetYesNo(Stone)
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 23)
	Conversation
	INTL( 12281, "Hurry! You must bring the stone to Olin Haad before it's too late!")
	BREAK
ELSE
	Conversation
	INTL( 12351, "Oh dear, I must return to the temple before anything else happens to me!")
	BREAK
ENDIF

YES(Stone)
	Conversation
	INTL( 12352, "Artherk be praised! You must hurry and bring it to Olin Haad then. I will return to the temple and wait "
	"for you there.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 12353, "You receive 200000 experience points."))
	GiveXP(200000)
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 23)
NO(Stone)
	Conversation
	INTL( 12354, "Well what are you doing here then? Please! You must retrieve the stone before all is lost!")
	BREAK
YesNoELSE(Stone)
	Conversation
	INTL( 12355, "Well? Were you successful in retrieving the stone or not?")
	SetYesNo(Stone)

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12281, "Hurry! You must bring the stone to Olin Haad before it's too late!")
BREAK

Default
INTL( 12356, "There's no time for this. Bring the stone to Olin Haad before it's too late!")

EndTalk
}



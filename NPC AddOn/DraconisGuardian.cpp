#pragma hdrstop
#include "DraconisGuardian.h"

DraconisGuardian::DraconisGuardian()
{}

DraconisGuardian::~DraconisGuardian()
{}

extern NPCstructure::NPC DraconisGuardianNPC;

void DraconisGuardian::Create( ){
	npc = DraconisGuardianNPC;
	SET_NPC_NAME( "[12732]Draconis guardian");
	npc.InitialPos.X = 1910; 
	npc.InitialPos.Y = 2170;
	npc.InitialPos.world = 1;
} 

void DraconisGuardian::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	
	CastSpellSelf(__SPELL_MOB_GUARDIAN_SELF_DAMAGE)
NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void DraconisGuardian::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
	   	CastSpellSelf(__SPELL_MOB_GUARDIAN_SELF_DAMAGE)
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void DraconisGuardian::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DraconisGuardian::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT EfnisienSent = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 41)
	Conversation
	INTL( 1864, "...")
	BREAK
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 41)
	Conversation
	INTL( 12057, "Argh... it hurts everywhere. Who... are you? Why... are you... here? Did Efnisien send you?")
	SetYesNo(EfnisienSent)
ELSE
	Conversation
	INTL( 1864, "...")
	BREAK
ENDIF

YES(EfnisienSent)
	Conversation
	INTL( 12058, "Olin Haad didn't get... him them. I'm glad for that at least. I don't know how that insane... "
	"necromancer knew that he was a \"draconis\", but he did. Only a dragon... can sense such a thing.")
NO(EfnisienSent)
	Conversation
	INTL( 12059, "Olin Haad did get him then... I'm sorry, but I must rest and wait until the traveler from the "
	"prophecy comes. If only... Efnisien was still alive...")
YesNoELSE(EfnisienSent)
	Conversation
	INTL( 12060, "Did Efnisien... send you or not?")
	SetYesNo(EfnisienSent)

Command(INTL( 12061, "DRACONIS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 41)
	Conversation
	INTL( 12062, "We half-dragons... were to protect this temple. He somehow knew that... and came prepared with some "
	"magic that... that was alien to us. He corrupted my kin and... defeated me. Please, I implore you... "
	"I can feel Caledbolg on you... which can only mean that you are... you are the one from the \"prophecy\".")
ELSE
	Conversation
	INTL( 12063, "I must rest now...")
ENDIF

Command(INTL( 12064, "PROPHECY"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 41)
	Conversation
	INTL( 12065, "'A Traveler who comes from the tears of the past will be sent by the Winds to cleanse the Land of "
	"its Wounds. To him the power of Balance will be given...' You are that traveler... the only one that "
	"can restore Justice to Althea. You are the one that can stop Olin Haad from bringing corruption "
	"to the entire world. You must \"stop\" him...")
ELSE
	Conversation
	INTL( 12063, "I must rest now...")
ENDIF

Command(INTL( 7346, "STOP"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 41)
	Conversation
	FORMAT(INTL( 12066, "Urgh... you must hasten %s for Olin Haad has already made is way inside the "
	"\"burial\" \"chamber\"... it is only a matter of time before the unthinkable happens... "),USER_NAME) 
ELSE
	Conversation
	INTL( 12063, "I must rest now...")
ENDIF

CmdAND(INTL( 12067, "BURIAL"),INTL( 12068, "CHAMBER"))
"" 
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 41)
	Conversation
	INTL( 12069, "The portal behind me is the only mean of entering the burial chamber... Please hurry "
	"before all is lost... I must rest now...")
ELSE
	Conversation
	INTL( 12063, "I must rest now...")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 12070, "It doesn't matter now...") 

Command(INTL( 489, "WORK"))
INTL( 12071, "I am the guardian of Lothar's tomb but alas I failed...") 

Default
INTL( 12072, "Urgh... it hurts...")
BREAK

EndTalk
} 
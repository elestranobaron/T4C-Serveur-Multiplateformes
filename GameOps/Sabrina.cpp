/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Sabrina.H"

Sabrina::Sabrina()
{}

Sabrina::~Sabrina()
{}

extern NPCstructure::NPC NPCSabrina;

void Sabrina::Create( void )
{
      npc = ( NPCSabrina );
      SET_NPC_NAME( "[7401]Sabrina" );		
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
//      npc.InitialPos.X = 1819; 
//      npc.InitialPos.Y = 1653;
      npc.InitialPos.world = 0;
}

void Sabrina::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	CastSpellSelf(__SPELL_MOB_INVISIBILITY_SPELL);
}

void Sabrina::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{  
	CHATTER_SHOUT(""); 
	}
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Sabrina::OnAttacked( UNIT_FUNC_PROTOTYPE ){    	
	if(rnd(0,10) == 1) 
	{
	switch(rnd(0, 2))
		{
		case 0: CHATTER_SHOUT(INTL( 7371, "Help! I am being attacked by giant rats!!!")); break;
		case 1: CHATTER_SHOUT(INTL( 7372, "Somebody help me! There's too many of them!")); break;
		case 2: CHATTER_SHOUT(INTL( 7373, "AAAAAAHH! I HATE RATS!")); break;		 
		}
	}    
self->Do(flee);
self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Sabrina::OnTalk( UNIT_FUNC_PROTOTYPE ){

InitTalk

Begin
""
IF(CheckFlag(__RATS_KILLED) == 25)
	Conversation
	FORMAT(INTL( 7374, "Oh! You killed all of them? I can't thank you enough, %s!"), USER_NAME)
ELSEIF(CheckFlag(__RATS_KILLED) >= 20)
	Conversation
	FORMAT(INTL( 7375, "Oh, thank you so much for your help, %s. I am very grateful. Don't worry about me, I can take care of the rest."), USER_NAME)
ELSE
	Conversation
	INTL( 7376, "Don't just stand there! Help me!")
	BREAK
ENDIF

Command(INTL( 569, "HEAL"))
INTL( 7690, "You are in need of healing? Say no more, I will restore you immediately.")
CastSpellTarget(__SPELL_MOB_COMPLETE_HEAL_TARGET_SPELL)

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 7377, "Sabrina, at your service.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"), INTL( 488, "WHAT DO YOU"))
INTL( 7378, "I teach art to the children of Lighthaven.")

Command3(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"))
FORMAT(INTL( 7379, "Farewell, %s, and be safe on your journey."), USER_NAME)
BREAK

Default
INTL( 7380, "I am sorry, but I really have no idea what you are talking about.")

EndTalk

}


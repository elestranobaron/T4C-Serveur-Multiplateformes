#pragma hdrstop
#include "RemortNPC1.h"

RemortNPC1::RemortNPC1()
{}

RemortNPC1::~RemortNPC1()
{}

extern NPCstructure::NPC RemortNPC;

void RemortNPC1::Create( ){
	npc = RemortNPC;
	SET_NPC_NAME(  "[10908]Alphan" );
	npc.InitialPos.X = 1285;
	npc.InitialPos.Y = 890;
	npc.InitialPos.world = 1;
}
void RemortNPC1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void RemortNPC1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void RemortNPC1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin 
""
IF(CheckFlag(__FLAG_REMORT_PROCESS) == 0)
	Conversation
	INTL( 10313, "Welcome, young one. I am here to \"assist\" you in preparing for your new life.")
ELSEIF(CheckFlag(__FLAG_REMORT_PROCESS) == 1)
	IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
		Conversation
		INTL( 10314, "I cannot help you until you have spent all your energy. Come back and see me when you have done that.")
		BREAK
	ELSE
		GiveFlag(__FLAG_REMORT_PROCESS, 2)
		Conversation
		INTL( 10315, "It seems you are now ready for the final stage of your transformation. If there is nothing further, we will "
		"\"begin\" immediately.")
	ENDIF
ELSEIF(CheckFlag(__FLAG_REMORT_PROCESS) == 2)
	Conversation
	INTL( 10316, "When you are \"ready\", we may \"begin\" the final stage of your transformation.")
ENDIF

Command2(INTL( 483, "NAME"), INTL( 485, "WHO ARE YOU"))
INTL( 10317, "I am the one called Alphan.")

Command3(INTL( 489, "WORK"), INTL( 3696, "WHAT DO YOU DO"), INTL( 487, "OCCUPATION"))
INTL( 10318, "I have been waiting for your arrival. I am here to \"help\" you prepare to start your new life.")

Command2(INTL( 10319, "ASSIST"), INTL( 554, "HELP"))
""
IF(CheckFlag(__FLAG_REMORT_PROCESS) == 0)
	GiveFlag(__FLAG_REMORT_PROCESS, 1)
	Conversation
	FORMAT(INTL( 10320, "You have been granted a certain amount of energy that must be spent before you can move on to the next "
	"stage of evolution. Right now, you have a total of %u points of energy. Each of my associates will briefly "
	"explain to you how these may be spent to increase your abilities. Talk to each one and once you have spent "
	"all this energy, come back to talk to me and I shall arrange for your departure back into the world."), CheckFlag(__FLAG_REMORT_POINTS))
ELSEIF(CheckFlag(__FLAG_REMORT_PROCESS) == 1)
	Conversation
	INTL( 10321, "Go talk to my associates. They will help you understand what exactly you can do with this extra energy.")
ELSE
	Conversation
	INTL( 10322, "We will begin the final stage of your transformation when you are \"ready\".")
ENDIF

Command2(INTL( 7390, "READY"), INTL( 10323, "BEGIN"))
""
IF(CheckFlag(__FLAG_REMORT_PROCESS) == 2)
	Conversation
	INTL( 10324, "The preparations are complete. Within a few seconds, you will be transported to Lighthaven to begin your life "
	"anew. I wish you good luck on your journey. May we one day meet again!")
	CastSpellTarget(__SPELL_REMORT_TELEPORT_SPELL)
	BREAK
ELSE
	Conversation
	INTL( 10325, "There are many things in life that we know and understand. This is not one of them.")
ENDIF

Command4(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"))
""
IF(CheckFlag(__FLAG_REMORT_PROCESS) == 0)
	Conversation
	INTL( 10326, "Very well, return when you are ready to hear what I have to say.")
ELSEIF(CheckFlag(__FLAG_REMORT_PROCESS) == 1)
	Conversation
	INTL( 10327, "Remember, return here once you have spent all your extra energy.")
ELSE
	Conversation
	INTL( 10328, "Return once you are ready for the final stage of transformation.")
ENDIF
BREAK

Default
INTL( 10325, "There are many things in life that we know and understand. This is not one of them.")

EndTalk

}
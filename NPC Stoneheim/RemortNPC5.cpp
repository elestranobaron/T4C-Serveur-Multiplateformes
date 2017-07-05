#pragma hdrstop
#include "RemortNPC5.h"

RemortNPC5::RemortNPC5()
{}

RemortNPC5::~RemortNPC5()
{}

extern NPCstructure::NPC RemortNPC;

void RemortNPC5::Create( ){
	npc = RemortNPC;
	SET_NPC_NAME( "[10912]Epilan" );
	npc.InitialPos.X = 1325;
	npc.InitialPos.Y = 850;
	npc.InitialPos.world = 1;
}
void RemortNPC5::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void RemortNPC5::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void RemortNPC5::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT IncreaseHealth = 1;
CONSTANT IncreaseMana = 2;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_REMORT_PROCESS) == 0)
	Conversation
	INTL( 10329, "I cannot help you until you have spoken to Alphan. Go talk to him and then come see me.")
	BREAK
ELSE
	IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
		Conversation
		FORMAT(INTL( 10417, "Welcome, %s. I am here to help you increase your maximum \"health\" and \"mana\" by focusing your energy."), USER_NAME) 
	ELSE
		Conversation
		INTL( 10331, "You have spent all your extra energy. You should now talk to Alphan again.")
		BREAK
	ENDIF
ENDIF

Command2(INTL( 483, "NAME"), INTL( 485, "WHO ARE YOU"))
INTL( 10418, "I am the one called Epilan.")

Command3(INTL( 489, "WORK"), INTL( 3696, "WHAT DO YOU DO"), INTL( 487, "OCCUPATION"))
INTL( 10419, "I am here to help you increase your maximum \"health\" and \"mana\" by focusing your energy.")

Command(INTL( 10420, "HEALTH"))
INTL( 10421, "To increase your maximum health by 10, you will need to spend 1 point of energy. Is this acceptable?")
SetYesNo(IncreaseHealth)

Command(INTL( 902, "MANA"))
INTL( 10422, "To increase your maximum mana by 5, you will need to spend 1 point of energy. Is this acceptable?")
SetYesNo(IncreaseMana)

YES(IncreaseHealth)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= 1)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 1)
		;target->SetMaxHP(USER_TRUE_MAXHP + 10);
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10423, "It is done. You have 1 point of energy remaining. What else would you like to increase?")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10602, "It is done. You have %u points of energy remaining. What else would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		INTL( 10425, "You do not have enough energy to increase your maximum health. You should now go talk to Alphan.")
	ENDIF
NO(IncreaseHealth)
	Conversation
	INTL( 10426, "Very well. What would you like to increase then?")
YesNoELSE(IncreaseHealth)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseHealth)

YES(IncreaseMana)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= 1)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 1)
		;target->SetMaxMana(target->GetMaxMana() + 5);
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10423, "It is done. You have 1 point of energy remaining. What else would you like to increase?")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10424, "It is done. You have %u points of energy remaining. What else would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		INTL( 10427, "You do not have enough energy to increase your maximum mana. You should now go talk to Alphan.")
	ENDIF
NO(IncreaseMana)
	Conversation
	INTL( 10426, "Very well. What would you like to increase then?")
YesNoELSE(IncreaseMana)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseMana)

Command4(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"))
""
IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
	Conversation
	INTL( 10428, "If you wish to increase your maximum health or mana again later, come back and see me.")
ELSE
	Conversation
	INTL( 10376, "Now that all your extra energy has been spent, you should go talk to Alphan.")
ENDIF
BREAK

Default
INTL( 10325, "There are many things in life that we know and understand. This is not one of them.")

EndTalk

}
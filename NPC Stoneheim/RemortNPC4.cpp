#pragma hdrstop
#include "RemortNPC4.h"

RemortNPC4::RemortNPC4()
{}

RemortNPC4::~RemortNPC4()
{}

extern NPCstructure::NPC RemortNPC;

void RemortNPC4::Create( ){
	npc = RemortNPC;
	SET_NPC_NAME( "[10911]Delaan" );
	npc.InitialPos.X = 1285;
	npc.InitialPos.Y = 850;
	npc.InitialPos.world = 1;
}
void RemortNPC4::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void RemortNPC4::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void RemortNPC4::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT IncreaseFireResistance = 1;
CONSTANT IncreaseWaterResistance = 2;
CONSTANT IncreaseAirResistance = 3;
CONSTANT IncreaseEarthResistance = 4;
CONSTANT IncreaseDarkResistance = 6;

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
		FORMAT(INTL( 10400, "Welcome, %s. I am here to help you increase your elemental \"resistances\" by focusing your energy."), USER_NAME) 
	ELSE
		Conversation
		INTL( 10331, "You have spent all your extra energy. You should now talk to Alphan again.")
		BREAK
	ENDIF
ENDIF

Command2(INTL( 483, "NAME"), INTL( 485, "WHO ARE YOU"))
INTL( 10442, "I am the one called Delaan.")

Command3(INTL( 489, "WORK"), INTL( 3696, "WHAT DO YOU DO"), INTL( 487, "OCCUPATION"))
INTL( 10401, "I am here to help you increase your elemental \"resistances\" by focusing your energy.")

Command(INTL( 11338, "RESISTANCE"))
""
IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
	Conversation
	INTL( 10402, "By focusing your new energies, I can help you increase any or all of your elemental resistances. These directly "
	"reflect your defensive abilities against each of the elements. The elemental resistances you can increase are \"fire\", "
	"\"water\", \"air\", \"earth\" and \"dark\". Each and every increase in your elemental resistances costs the same "
	"amount of energy. Now, which resistance would you like to increase?")
ELSE
	Conversation
	INTL( 10335, "You have spent all your extra energy. You should now go talk to Alphan.")
	BREAK
ENDIF

Command(INTL( 10381, "FIRE"))
INTL( 10403, "To increase your fire resistance by 10, you will need to spend 2 points of energy. Is this acceptable?")
SetYesNo(IncreaseFireResistance)

Command(INTL( 2590, "WATER"))
INTL( 10404, "To increase your water resistance by 10, you will need to spend 2 points of energy. Is this acceptable?")
SetYesNo(IncreaseWaterResistance)

Command(INTL( 1692, "AIR"))
INTL( 10405, "To increase your air resistance by 10, you will need to spend 2 points of energy. Is this acceptable?")
SetYesNo(IncreaseAirResistance)

Command(INTL( 10388, "EARTH"))
INTL( 10406, "To increase your earth resistance by 10, you will need to spend 2 points of energy. Is this acceptable?")
SetYesNo(IncreaseEarthResistance)

Command(INTL( 1183, "DARK"))
INTL( 10407, "To increase your dark resistance by 10, you will need to spend 2 points of energy. Is this acceptable?")
SetYesNo(IncreaseDarkResistance)

YES(IncreaseFireResistance)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
		SET_FIRE_RESIST(USER_TRUE_FIRE_RESIST + 10)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10408, "It is done. You have 1 point of energy remaining. Perhaps you should talk to one of my associates to see what you can "
			"do with it.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10594, "It is done. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10595, "You do not have enough energy to increase this elemental resistance. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseFireResistance)
	Conversation
	INTL( 10411, "Very well. Which elemental resistance would you like to increase then?")
YesNoELSE(IncreaseFireResistance)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseFireResistance)

YES(IncreaseWaterResistance)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
		SET_WATER_RESIST(USER_TRUE_WATER_RESIST + 10)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10412, "It is done. You have 1 point of energy remaining. Perhaps you should talk to one of my associates to see what you can "
			"do with it.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10596, "It is done. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10597, "You do not have enough energy to increase this elemental resistance. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseWaterResistance)
	Conversation
	INTL( 10411, "Very well. Which elemental resistance would you like to increase then?")
YesNoELSE(IncreaseWaterResistance)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseWaterResistance)

YES(IncreaseAirResistance)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
		SET_AIR_RESIST(USER_TRUE_AIR_RESIST + 10)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10413, "It is done. You have 1 point of energy remaining. Perhaps you should talk to one of my associates to see what you can "
			"do with it.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10598, "It is done. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10599, "You do not have enough energy to increase this elemental resistance. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseAirResistance)
	Conversation
	INTL( 10411, "Very well. Which elemental resistance would you like to increase then?")
YesNoELSE(IncreaseAirResistance)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseAirResistance)

YES(IncreaseEarthResistance)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
		SET_EARTH_RESIST(USER_TRUE_EARTH_RESIST + 10)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10414, "It is done. You have 1 point of energy remaining. Perhaps you should talk to one of my associates to see what you can "
			"do with it.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10600, "It is done. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10601, "You do not have enough energy to increase this elemental resistance. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseEarthResistance)
	Conversation
	INTL( 10411, "Very well. Which elemental resistance would you like to increase then?")
YesNoELSE(IncreaseEarthResistance)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseEarthResistance)

YES(IncreaseDarkResistance)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
		SET_DARK_RESIST(USER_TRUE_DARK_RESIST + 10)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10415, "It is done. You have 1 point of energy remaining. Perhaps you should talk to one of my associates to see what you can "
			"do with it.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10409, "It is done. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10410, "You do not have enough energy to increase this elemental resistance. You have %u points of energy remaining. Which elemental resistance would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseDarkResistance)
	Conversation
	INTL( 10411, "Very well. Which elemental resistance would you like to increase then?")
YesNoELSE(IncreaseDarkResistance)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseDarkResistance)

Command4(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"))
""
IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
	Conversation
	INTL( 10416, "If you wish to increase your elemental resistances again later, come back and see me.")
ELSE
	Conversation
	INTL( 10376, "Now that all your extra energy has been spent, you should go talk to Alphan.")
ENDIF
BREAK

Default
INTL( 10325, "There are many things in life that we know and understand. This is not one of them.")

EndTalk

}
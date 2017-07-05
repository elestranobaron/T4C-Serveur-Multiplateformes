#pragma hdrstop
#include "RemortNPC3.h"

RemortNPC3::RemortNPC3()
{}

RemortNPC3::~RemortNPC3()
{}

extern NPCstructure::NPC RemortNPC;

void RemortNPC3::Create( ){
	npc = RemortNPC;
	SET_NPC_NAME( "[10910]Caplan" );
	npc.InitialPos.X = 1245;
	npc.InitialPos.Y = 890;
	npc.InitialPos.world = 1;
}
void RemortNPC3::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void RemortNPC3::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void RemortNPC3::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT IncreaseFirePower = 1;
CONSTANT IncreaseWaterPower = 2;
CONSTANT IncreaseAirPower = 3;
CONSTANT IncreaseEarthPower = 4;
CONSTANT IncreaseLightPower = 5;
CONSTANT IncreaseDarkPower = 6;

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
		FORMAT(INTL( 10377, "Welcome, %s. I am here to help you increase your elemental \"powers\" by focusing your energy."), USER_NAME) 
	ELSE
		Conversation
		INTL( 10331, "You have spent all your extra energy. You should now talk to Alphan again.")
		BREAK
	ENDIF
ENDIF

Command2(INTL( 483, "NAME"), INTL( 485, "WHO ARE YOU"))
INTL( 11326, "I am the one called Caplan.") 
// Delaan, Epilan

Command3(INTL( 489, "WORK"), INTL( 3696, "WHAT DO YOU DO"), INTL( 487, "OCCUPATION"))
INTL( 10378, "I am here to help you increase your elemental \"powers\" by focusing your energy.")

Command(INTL( 10379, "POWER"))
""
IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
	Conversation
	INTL( 10380, "By focusing your new energies, I can help you increase any or all of your elemental powers. These directly "
	"reflect your spellcasting ability in each of the elements. The elemental powers you can increase are \"fire\", "
	"\"water\", \"air\", \"earth\", \"light\" and \"dark\". Note that the higher you decide to push an elemental "
	"power, the more costly in energy the process will be. For example, raising all your elemental powers by 5 "
	"costs much less energy than raising one elemental power by 30. Such is the price of specialization. Now, which "
	"power would you like to increase?")
ELSE
	Conversation
	INTL( 10335, "You have spent all your extra energy. You should now go talk to Alphan.")
	BREAK
ENDIF

Command(INTL( 10381, "FIRE"))
""
IF(USER_TRUE_FIRE_POWER - 100 == 0)
	Conversation
	INTL( 10382, "To increase your fire power by 5, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseFirePower)
ELSE
	Conversation
	FORMAT(INTL( 10383, "To increase your fire power by 5 points, you will need to spend %u points of energy. Is this acceptable?"), (USER_TRUE_FIRE_POWER - 95) / 5)
	SetYesNo(IncreaseFirePower)
ENDIF

Command(INTL( 2590, "WATER"))
""
IF(USER_TRUE_WATER_POWER - 100 == 0)
	Conversation
	INTL( 10384, "To increase your water power by 5, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseWaterPower)
ELSE
	Conversation
	FORMAT(INTL( 10385, "To increase your water power by 5 points, you will need to spend %u points of energy. Is this acceptable?"), (USER_TRUE_WATER_POWER - 95) / 5)
	SetYesNo(IncreaseWaterPower)
ENDIF

Command(INTL( 1692, "AIR"))
""
IF(USER_TRUE_AIR_POWER - 100 == 0)
	Conversation
	INTL( 10386, "To increase your air power by 5, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseAirPower)
ELSE
	Conversation
	FORMAT(INTL( 10387, "To increase your air power by 5 points, you will need to spend %u points of energy. Is this acceptable?"), (USER_TRUE_AIR_POWER - 95) / 5)
	SetYesNo(IncreaseAirPower)
ENDIF

Command(INTL( 10388, "EARTH"))
""
IF(USER_TRUE_EARTH_POWER - 100 == 0)
	Conversation
	INTL( 10389, "To increase your earth power by 5, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseEarthPower)
ELSE
	Conversation
	FORMAT(INTL( 10390, "To increase your earth power by 5 points, you will need to spend %u points of energy. Is this acceptable?"), (USER_TRUE_EARTH_POWER - 95) / 5)
	SetYesNo(IncreaseEarthPower)
ENDIF

Command(INTL( 4574, "LIGHT"))
""
IF(USER_TRUE_LIGHT_POWER - 100 == 0)
	Conversation
	INTL( 10391, "To increase your light power by 5, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseLightPower)
ELSE
	Conversation
	FORMAT(INTL( 10392, "To increase your light power by 5 points, you will need to spend %u points of energy. Is this acceptable?"), (USER_TRUE_LIGHT_POWER - 95) / 5)
	SetYesNo(IncreaseLightPower)
ENDIF

Command(INTL( 1183, "DARK"))
""
IF(USER_TRUE_DARK_POWER - 100 == 0)
	Conversation
	INTL( 10393, "To increase your dark power by 5, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseDarkPower)
ELSE
	Conversation
	FORMAT(INTL( 10394, "To increase your dark power by 5 points, you will need to spend %u points of energy. Is this acceptable?"), (USER_TRUE_DARK_POWER - 95) / 5)
	SetYesNo(IncreaseDarkPower)
ENDIF

YES(IncreaseFirePower)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= (USER_TRUE_FIRE_POWER - 95) / 5)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - ((USER_TRUE_FIRE_POWER - 95) / 5))
		SET_FIRE_POWER(USER_TRUE_FIRE_POWER + 5)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10395, "It is done. You have 1 point of energy remaining. Which elemental power would you like to increase?")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10584, "It is done. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10585, "You do not have enough energy to increase this elemental power. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseFirePower)
	Conversation
	INTL( 10398, "Very well. Which elemental power would you like to increase then?")
YesNoELSE(IncreaseFirePower)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseFirePower)

YES(IncreaseWaterPower)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= (USER_TRUE_WATER_POWER - 95) / 5)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - ((USER_TRUE_WATER_POWER - 95) / 5))
		SET_WATER_POWER(USER_TRUE_WATER_POWER + 5)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10395, "It is done. You have 1 point of energy remaining. Which elemental power would you like to increase?")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10586, "It is done. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10587, "You do not have enough energy to increase this elemental power. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseWaterPower)
	Conversation
	INTL( 10398, "Very well. Which elemental power would you like to increase then?")
YesNoELSE(IncreaseWaterPower)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseWaterPower)

YES(IncreaseAirPower)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= (USER_TRUE_AIR_POWER - 95) / 5)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - ((USER_TRUE_AIR_POWER - 95) / 5))
		SET_AIR_POWER(USER_TRUE_AIR_POWER + 5)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10395, "It is done. You have 1 point of energy remaining. Which elemental power would you like to increase?")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10588, "It is done. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10589, "You do not have enough energy to increase this elemental power. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseAirPower)
	Conversation
	INTL( 10398, "Very well. Which elemental power would you like to increase then?")
YesNoELSE(IncreaseAirPower)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseAirPower)

YES(IncreaseEarthPower)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= (USER_TRUE_EARTH_POWER - 95) / 5)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - ((USER_TRUE_EARTH_POWER - 95) / 5))
		SET_EARTH_POWER(USER_TRUE_EARTH_POWER + 5)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10395, "It is done. You have 1 point of energy remaining. Which elemental power would you like to increase?")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10590, "It is done. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10591, "You do not have enough energy to increase this elemental power. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseEarthPower)
	Conversation
	INTL( 10398, "Very well. Which elemental power would you like to increase then?")
YesNoELSE(IncreaseEarthPower)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseEarthPower)

YES(IncreaseLightPower)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= (USER_TRUE_LIGHT_POWER - 95) / 5)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - ((USER_TRUE_LIGHT_POWER - 95) / 5))
		SET_LIGHT_POWER(USER_TRUE_LIGHT_POWER + 5)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10395, "It is done. You have 1 point of energy remaining. Which elemental power would you like to increase?")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10592, "It is done. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10593, "You do not have enough energy to increase this elemental power. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseLightPower)
	Conversation
	INTL( 10398, "Very well. Which elemental power would you like to increase then?")
YesNoELSE(IncreaseLightPower)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseLightPower)

YES(IncreaseDarkPower)
	IF(CheckFlag(__FLAG_REMORT_POINTS) >= (USER_TRUE_DARK_POWER - 95) / 5)
		GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - ((USER_TRUE_DARK_POWER - 95) / 5))
		SET_DARK_POWER(USER_TRUE_DARK_POWER + 5)
		IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
			Conversation
			INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
			Conversation
			INTL( 10395, "It is done. You have 1 point of energy remaining. Which elemental power would you like to increase?")
		ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
			Conversation
			FORMAT(INTL( 10396, "It is done. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSE
		Conversation
		FORMAT(INTL( 10397, "You do not have enough energy to increase this elemental power. You have %u points of energy remaining. Which elemental power would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
	ENDIF
NO(IncreaseDarkPower)
	Conversation
	INTL( 10398, "Very well. Which elemental power would you like to increase then?")
YesNoELSE(IncreaseDarkPower)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseDarkPower)

Command4(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"))
""
IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
	Conversation
	INTL( 10399, "If you wish to increase your elemental powers again later, come back and see me.")
ELSE
	Conversation
	INTL( 10376, "Now that all your extra energy has been spent, you should go talk to Alphan.")
ENDIF
BREAK

Default
INTL( 10325, "There are many things in life that we know and understand. This is not one of them.")

EndTalk

}
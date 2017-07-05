#pragma hdrstop
#include "RemortNPC2.h"

RemortNPC2::RemortNPC2()
{}

RemortNPC2::~RemortNPC2()
{}

extern NPCstructure::NPC RemortNPC;

void RemortNPC2::Create( ){
	npc = RemortNPC;
	SET_NPC_NAME(  "[10909]Betran" );
	npc.InitialPos.X = 1245;
	npc.InitialPos.Y = 930;
	npc.InitialPos.world = 1;
}
void RemortNPC2::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void RemortNPC2::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void RemortNPC2::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT IncreaseStrength = 1;
CONSTANT IncreaseAgility = 2;
CONSTANT IncreaseEndurance = 3;
CONSTANT IncreaseIntelligence = 4;
CONSTANT IncreaseWisdom = 5;

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
		FORMAT( INTL( 10330, "Welcome, %s. I am here to help you increase your main \"attributes\" by focusing your energy."),USER_NAME) 
	ELSE
		Conversation
		INTL( 10331, "You have spent all your extra energy. You should now talk to Alphan again.")
		BREAK
	ENDIF
ENDIF

Command2(INTL( 483, "NAME"), INTL( 485, "WHO ARE YOU"))
INTL( 11325, "I am the one called Betran.")  

// Caplan, Delaan, Epilan

Command3(INTL( 489, "WORK"), INTL( 3696, "WHAT DO YOU DO"), INTL( 487, "OCCUPATION"))
INTL( 10332, "I am here to help you increase your main \"attributes\" by focusing your energy.")

Command2(INTL( 10333, "ATTRIBUTE"), INTL( 910, "STAT"))
""
IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
	Conversation
	INTL( 10334, "By focusing your new energies, I can help you increase any or all of your main attributes. The attributes "
	"you can increase are \"strength\", \"endurance\", \"agility\", \"intelligence\" and \"wisdom\". Note that the "
	"higher you decide to push an attribute, the more costly in energy the process will be. For example, raising "
	"all your attributes by 1 costs much less energy than raising one attribute by 5. Such is the price of "
	"specialization. Now, which attribute would you like to increase?")
ELSE
	Conversation
	INTL( 10335, "You have spent all your extra energy. You should now go talk to Alphan.")
	BREAK
ENDIF

Command(INTL( 8126, "STRENGTH"))
""
IF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
	Conversation
	INTL( 10336, "To increase your strength attribute by 1, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseStrength)
ELSEIF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
	Conversation
	INTL( 10337, "To increase your strength attribute by 1, you will need to spend 2 points of energy. Is this acceptable?")
	SetYesNo(IncreaseStrength)
ELSEIF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
	Conversation
	INTL( 10338, "To increase your strength attribute by 1, you will need to spend 3 points of energy. Is this acceptable?")
	SetYesNo(IncreaseStrength)
ELSEIF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
	Conversation
	INTL( 10339, "To increase your strength attribute by 1, you will need to spend 4 points of energy. Is this acceptable?")
	SetYesNo(IncreaseStrength)
ELSEIF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
	Conversation
	INTL( 10340, "To increase your strength attribute by 1, you will need to spend 5 points of energy. Is this acceptable?")
	SetYesNo(IncreaseStrength)
ELSE
	Conversation
	INTL( 10341, "You may not increase your strength attribute any further. There is only so much we can do through training.")
ENDIF

Command(INTL( 10342, "AGILITY"))
""
IF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
	Conversation
	INTL( 10343, "To increase your agility attribute by 1, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseAgility)
ELSEIF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
	Conversation
	INTL( 10344, "To increase your agility attribute by 1, you will need to spend 2 points of energy. Is this acceptable?")
	SetYesNo(IncreaseAgility)
ELSEIF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
	Conversation
	INTL( 10345, "To increase your agility attribute by 1, you will need to spend 3 points of energy. Is this acceptable?")
	SetYesNo(IncreaseAgility)
ELSEIF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
	Conversation
	INTL( 10346, "To increase your agility attribute by 1, you will need to spend 4 points of energy. Is this acceptable?")
	SetYesNo(IncreaseAgility)
ELSEIF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
	Conversation
	INTL( 10347, "To increase your agility attribute by 1, you will need to spend 5 points of energy. Is this acceptable?")
	SetYesNo(IncreaseAgility)
ELSE
	Conversation
	INTL( 10348, "You may not increase your agility attribute any further. There is only so much we can do through training.")
ENDIF

Command(INTL( 10349, "ENDURANCE"))
""
IF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
	Conversation
	INTL( 10350, "To increase your endurance attribute by 1, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseEndurance)
ELSEIF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
	Conversation
	INTL( 10351, "To increase your endurance attribute by 1, you will need to spend 2 points of energy. Is this acceptable?")
	SetYesNo(IncreaseEndurance)
ELSEIF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
	Conversation
	INTL( 10352, "To increase your endurance attribute by 1, you will need to spend 3 points of energy. Is this acceptable?")
	SetYesNo(IncreaseEndurance)
ELSEIF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
	Conversation
	INTL( 10353, "To increase your endurance attribute by 1, you will need to spend 4 points of energy. Is this acceptable?")
	SetYesNo(IncreaseEndurance)
ELSEIF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
	Conversation
	INTL( 10354, "To increase your endurance attribute by 1, you will need to spend 5 points of energy. Is this acceptable?")
	SetYesNo(IncreaseEndurance)
ELSE
	Conversation
	INTL( 10355, "You may not increase your endurance attribute any further. There is only so much we can do through training.")
ENDIF

Command(INTL( 10356, "INTELLIGENCE"))
""
IF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
	Conversation
	INTL( 10357, "To increase your intelligence attribute by 1, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseIntelligence)
ELSEIF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
	Conversation
	INTL( 10358, "To increase your intelligence attribute by 1, you will need to spend 2 points of energy. Is this acceptable?")
	SetYesNo(IncreaseIntelligence)
ELSEIF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
	Conversation
	INTL( 10359, "To increase your intelligence attribute by 1, you will need to spend 3 points of energy. Is this acceptable?")
	SetYesNo(IncreaseIntelligence)
ELSEIF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
	Conversation
	INTL( 10360, "To increase your intelligence attribute by 1, you will need to spend 4 points of energy. Is this acceptable?")
	SetYesNo(IncreaseIntelligence)
ELSEIF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
	Conversation
	INTL( 10361, "To increase your intelligence attribute by 1, you will need to spend 5 points of energy. Is this acceptable?")
	SetYesNo(IncreaseIntelligence)
ELSE
	Conversation
	INTL( 10362, "You may not increase your intelligence attribute any further. There is only so much we can do through training.")
ENDIF

Command(INTL( 7712, "WISDOM"))
""
IF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
	Conversation
	INTL( 10363, "To increase your wisdom attribute by 1, you will need to spend 1 point of energy. Is this acceptable?")
	SetYesNo(IncreaseWisdom)
ELSEIF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
	Conversation
	INTL( 10364, "To increase your wisdom attribute by 1, you will need to spend 2 points of energy. Is this acceptable?")
	SetYesNo(IncreaseWisdom)
ELSEIF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
	Conversation
	INTL( 10365, "To increase your wisdom attribute by 1, you will need to spend 3 points of energy. Is this acceptable?")
	SetYesNo(IncreaseWisdom)
ELSEIF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
	Conversation
	INTL( 10366, "To increase your wisdom attribute by 1, you will need to spend 4 points of energy. Is this acceptable?")
	SetYesNo(IncreaseWisdom)
ELSEIF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
	Conversation
	INTL( 10367, "To increase your wisdom attribute by 1, you will need to spend 5 points of energy. Is this acceptable?")
	SetYesNo(IncreaseWisdom)
ELSE
	Conversation
	INTL( 10368, "You may not increase your wisdom attribute any further. There is only so much we can do through training.")
ENDIF

YES(IncreaseStrength)
	IF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 1)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 1)
			SET_STR(USER_TRUE_STR + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10536, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10537, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
			SET_STR(USER_TRUE_STR + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10538, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10539, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 3)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 3)
			SET_STR(USER_TRUE_STR + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10540, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10541, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 4)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 4)
			SET_STR(USER_TRUE_STR + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10542, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10543, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_STR - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 5)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 5)
			SET_STR(USER_TRUE_STR + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10544, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10545, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ENDIF
NO(IncreaseStrength)
	Conversation
	INTL( 10373, "Very well. Which attribute would you like to increase then?")
YesNoELSE(IncreaseStrength)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseStrength)

YES(IncreaseAgility)
	IF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 1)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 1)
			SET_AGI(USER_TRUE_AGI + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10546, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10547, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
			SET_AGI(USER_TRUE_AGI + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10548, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10549, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 3)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 3)
			SET_AGI(USER_TRUE_AGI + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10550, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10551, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 4)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 4)
			SET_AGI(USER_TRUE_AGI + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10552, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10553, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_AGI - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 5)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 5)
			SET_AGI(USER_TRUE_AGI + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10554, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10555, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ENDIF
NO(IncreaseAgility)
	Conversation
	INTL( 10373, "Very well. Which attribute would you like to increase then?")
YesNoELSE(IncreaseAgility)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseAgility)

YES(IncreaseEndurance)
	IF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 1)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 1)
			SET_END(USER_TRUE_END + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10556, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10557, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
			SET_END(USER_TRUE_END + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10558, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10559, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 3)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 3)
			SET_END(USER_TRUE_END + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10560, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10561, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 4)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 4)
			SET_END(USER_TRUE_END + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10562, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10563, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_END - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 5)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 5)
			SET_END(USER_TRUE_END + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10564, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10565, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ENDIF
NO(IncreaseEndurance)
	Conversation
	INTL( 10373, "Very well. Which attribute would you like to increase then?")
YesNoELSE(IncreaseEndurance)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseEndurance)

YES(IncreaseIntelligence)
	IF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 1)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 1)
			SET_INT(USER_TRUE_INT + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10566, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10567, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
			SET_INT(USER_TRUE_INT + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10568, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10569, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 3)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 3)
			SET_INT(USER_TRUE_INT + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10570, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10571, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 4)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 4)
			SET_INT(USER_TRUE_INT + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10572, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10573, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_INT - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 5)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 5)
			SET_INT(USER_TRUE_INT + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10574, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10575, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ENDIF
NO(IncreaseIntelligence)
	Conversation
	INTL( 10373, "Very well. Which attribute would you like to increase then?")
YesNoELSE(IncreaseIntelligence)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseIntelligence)

YES(IncreaseWisdom)
	IF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 0)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 1)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 1)
			SET_WIS(USER_TRUE_WIS + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10576, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10577, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 3)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 2)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 2)
			SET_WIS(USER_TRUE_WIS + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10578, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10579, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 6)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 3)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 3)
			SET_WIS(USER_TRUE_WIS + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10580, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10581, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) == 7)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 4)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 4)
			SET_WIS(USER_TRUE_WIS + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10582, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10583, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ELSEIF(USER_TRUE_WIS - (20 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5) <= 9)
		IF(CheckFlag(__FLAG_REMORT_POINTS) >= 5)
			GiveFlag(__FLAG_REMORT_POINTS, CheckFlag(__FLAG_REMORT_POINTS) - 5)
			SET_WIS(USER_TRUE_WIS + 1)
			IF(CheckFlag(__FLAG_REMORT_POINTS) == 0)
				Conversation
				INTL( 10369, "It is done. You have spent all your extra energy. You should now go talk to Alphan.")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) == 1)
				Conversation
				INTL( 10370, "It is done. You have 1 point of energy remaining. Which attribute would you like to increase?")
			ELSEIF(CheckFlag(__FLAG_REMORT_POINTS) > 1)
				Conversation
				FORMAT(INTL( 10371, "It is done. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
			ENDIF
		ELSE
			Conversation
			FORMAT(INTL( 10372, "You do not have enough energy to increase this attribute. You have %u points of energy remaining. Which attribute would you like to increase?"), CheckFlag(__FLAG_REMORT_POINTS))
		ENDIF
	ENDIF
NO(IncreaseWisdom)
	Conversation
	INTL( 10373, "Very well. Which attribute would you like to increase then?")
YesNoELSE(IncreaseWisdom)
	Conversation
	INTL( 10374, "Well, is it acceptable or not?")
	SetYesNo(IncreaseWisdom)

Command4(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"))
""
IF(CheckFlag(__FLAG_REMORT_POINTS) > 0)
	Conversation
	INTL( 10375, "If you wish to increase your main attributes more later, come back and see me.")
ELSE
	Conversation
	INTL( 10376, "Now that all your extra energy has been spent, you should go talk to Alphan.")
ENDIF
BREAK

Default
INTL( 10325, "There are many things in life that we know and understand. This is not one of them.")

EndTalk

}
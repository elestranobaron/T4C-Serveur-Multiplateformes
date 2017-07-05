#include "Stdafx.h"
#include "ForestWanderer.h"

ForestWanderer::ForestWanderer()
{}

ForestWanderer::~ForestWanderer()
{}

extern NPCstructure::NPC ForestWandererNPC;

void ForestWanderer::Create( ){
    npc = ForestWandererNPC;
    SET_NPC_NAME(  "[10973]A shadow in the woods" );
    npc.InitialPos.X = 2620;
    npc.InitialPos.Y = 2065;
    npc.InitialPos.world = 0;
}

void ForestWanderer::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void ForestWanderer::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void ForestWanderer::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT GOHOME = 1;

InitTalk

Begin
""
IF (IsInRange(4))
	PRIVATE_SYSTEM_MESSAGE(INTL( 10619, "A voice says: ''Hello, traveller. I see that you are \"lost\".''"))
ELSE
	Conversation
	INTL( 11327, "I can't hear you. Come closer.")
	BREAK
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10620, "A voice says: ''I'm just a wanderer, don't mind me.''"))

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10621, "A voice says: ''I just walk around these woods, helping lost souls find their way home.''"))

Command2(INTL( 3999, "LOST"),INTL( 5193, "HOME"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10622, "A voice says: ''Do you wish to be sent home?''"))
SetYesNo(GOHOME)

YES(GOHOME)
	PRIVATE_SYSTEM_MESSAGE(INTL( 10623, "A voice says: ''And here's a little gift to thank you for your visit.''"))
	SWITCH(rnd.roll(dice(1,6))) 
		CASE(1)
			SUMMON("FORESTWANDERER", 2568, 1945)
		ENDCASE
		CASE(2)
			SUMMON("FORESTWANDERER", 2638, 1901)
		ENDCASE
		CASE(3)
			SUMMON("FORESTWANDERER", 2897, 1915)
		ENDCASE
		CASE(4)
			SUMMON("FORESTWANDERER", 2970, 1950)
		ENDCASE
		CASE(5)
			SUMMON("FORESTWANDERER", 2881, 2130)
		ENDCASE
		CASE(6)
			SUMMON("FORESTWANDERER", 2620, 2065)
		ENDCASE
	ENDSWITCH

	IF(CheckFlag(__QUEST_FOREST_WANDERER_GIFTS) <6)
		GiveFlag(__QUEST_FOREST_WANDERER_GIFTS, CheckFlag(__QUEST_FOREST_WANDERER_GIFTS)+1)
	ENDIF	
	SWITCH(rnd.roll(dice(1,CheckFlag(__QUEST_FOREST_WANDERER_GIFTS))))
		CASE(1)
			GiveItem(__OBJ_DRACHENSWORD) // Fighter 1
		ENDCASE
		CASE(2)
			GiveItem(__OBJ_DRACHENSTAFF) // Mage 1
		ENDCASE
		CASE(3)
			GiveItem(__OBJ_DRACHENHELM) // Mage 2
		ENDCASE
		CASE(4)
			GiveItem(__OBJ_DRACHENSHIELD) // Fighter 2
		ENDCASE
		CASE(5)
			GiveItem(__OBJ_DRACHENROBE) // Mage 3
		ENDCASE
		CASE(6)
			GiveItem(__OBJ_DRACHENPLATE) // Fighter 3
		ENDCASE
	ENDSWITCH	
	PRIVATE_SYSTEM_MESSAGE(INTL( 10624, "You sense someone playing with your inventory."))	
	PRIVATE_SYSTEM_MESSAGE(INTL( 10625, "You feel lightheaded after being teleported back on Raven's Dust.")) 
	TELEPORT(715, 1295, 0)    // Send the user home, at the north of Raven's Dust. 
	SELF_DESTRUCT
	BREAK

NO(GOHOME)
	PRIVATE_SYSTEM_MESSAGE(INTL( 10626, "A voice says: ''I take it you like it here, then...''"))

YesNoELSE(GOHOME)
	PRIVATE_SYSTEM_MESSAGE(INTL( 10627, "A voice says: ''Say again?''"))
	SetYesNo(GOHOME)

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10628, "A voice says: ''Goodbye, then.''"))
TELEPORT(2778, 2006, 0) // Send the user back in the center of the island. (ouch!) 
BREAK

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10629, "A voice says: ''Are you \"lost\"?''"))

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10628, "A voice says: ''Goodbye, then.''"))

Command2(INTL( 988, "ELF"),INTL( 987, "ELVES"))
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10630, "A voice says: ''If there were Elves here, I certainly wouldn't tell you.''"))

Default
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10631, "A voice says: ''I can't hear you well. Could you speak louder?''"))
 
EndTalk

}

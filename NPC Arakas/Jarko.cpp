//////////////////////////////////////////////////////////////////////
// Jarko.cpp: implementation of Jarko
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Jarko.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Jarko::Jarko()
{}

Jarko::~Jarko()
{}

extern NPCstructure::NPC _Jarko;

void Jarko::OnAttack( UNIT_FUNC_PROTOTYPE )
{
if( target != NULL )
	{ 
    ;int nRandomNumber = rnd.roll(dice(1,3));
	SWITCH (rnd.roll(dice(1,20)))
		CASE (1)
		FOR( 0, nRandomNumber ) 
		    SUMMON( INTL( 729, "Skeleton Warrior"), FROM_NPC(rnd.roll(dice(1, 2))-4,X), FROM_NPC(rnd.roll(dice(1, 2))-4,Y))
		ENDFOR
		ENDCASE
		OTHERWISE
	ENDSWITCH
	}
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void Jarko::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
    if( target != NULL ){
        ;int nRandomNumber = rnd.roll(dice(1,3)); 
        SWITCH (rnd.roll(dice(1,20))) 
        CASE (1)
		    
		    FOR( 0, nRandomNumber )  
                SUMMON( INTL( 729, "Skeleton Warrior"), FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
            ENDFOR
        ENDCASE
        OTHERWISE
        ENDSWITCH
    }
    
    NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Jarko::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		GiveFlag(__FLAG_KILLED_JARKO, 1);
		// Jarko is a very bad guy...
		IF (USER_KARMA <= (100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
			GiveKarma(2*(500-USER_KARMA)/500)
		ENDIF
 }

	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}


//////////////////////////////////////////////////////////////////////////////////////////
void Jarko::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Jarko
//
{
 npc = _Jarko;
 SET_NPC_NAME( "[2897]Jarko the necromancer" );
 npc.InitialPos.X = 0;
 npc.InitialPos.Y = 0;
 npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Jarko::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Jarko
// 
//
{
CONSTANT SPELLBOOK = 1;
CONSTANT STONE = 2;

InitTalk

Begin
INTL( 730, "I hope for your sake that you are not here to thwart my \"plans\".")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 731, "The name is the Great Jarko to you and it will be the last you will ever "
"hear if you attempt to thwart my \"plans\" of conquest. With this \"spellbook\" "
"in my hand, nothing shall stand in my way, not even \"Makrsh\" \"P'Tangh\" and "
"especially not you.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 7174, "Devilish monster? Cursed from beyond? Marked from eternity? Yeah, right!")

Command(INTL( 523, "ANNABELLE"))
INTL( 733, "Who is she? Bah! I have no time for such nonsense!")

Command(INTL( 734, "ARAKNOR"))
INTL( 735, "Araknor might practice the same dark art as I do, but he really is no "
"match for my powerful magic. In fact, he can barely fight one of my "
"goblins. Some day, he is bound to make a mistake that will cost him his "
"life, and then I shall enslave him as one of my undead minions.")

Command3(INTL( 484, "MHORGWLOTH"),INTL( 535, "TROLL"),INTL( 507, "ORKANIS"))
INTL( 736, "Mhorgwloth the troll lives in the ruined Castle of Orkanis north of these "
"mountains. He usually does not bother my \"goblins\" much, unless "
"they attempt to enter his domain.")

Command3(INTL( 737, "LICH"),INTL( 738, "MAKRSH"),INTL( 739, "P'TANGH"))
INTL( 740, "The Lich Makrsh P'Tangh is said to have been cursed--or blessed--during "
"one of the \"comings\", I do not quite remember which one nor do I really care. "
"It is said that he was once an Elven prince who now rules as the Prince "
"of Darkness. Pah! I am sure he is no match for my magic!") 

Command2(INTL( 741, "4TH COMING"),INTL( 742, "COMING"))
INTL( 743, "The Oracle claims it has seen a vision and that the Fourth Coming is finally "
"at hand and humans will be judged for their misdeeds. It does not cause me "
"much concern because I intend to be powerful enough to be *THE* judge.")

Command(INTL( 744, "ORC"))
INTL( 745, "It was a good move to recruit the Orc Leader. He is able to lead my armies "
"to great victories even though the \"goblins\" despise him.")

Command(INTL( 746, "DRUID"))
INTL( 747, "The druids are located on the northeastern part of the island. Their "
"magical powers are the only threat to my \"plans\". I would be "
"highly interested in studying the \"source\" of their power.") 

Command(INTL( 748, "SOURCE"))
INTL( 749, "According to the reports I have received from my goblin spy, the druids "
"apparently worship a \"stone\" \"of\" \"life\", which is an ordinary stone in which "
"they have poured life, hence its name.")

Command4(INTL( 489, "WORK"),INTL( 750, "PLANS"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 751, "It is not of your business to know what I do. But you shall know in time.")

Command2(INTL( 539, "GOBLIN"),INTL( 691, "UNDEAD"))
INTL( 752, "The goblins and the undead minions are nothing but my war toys. They can "
"be easily replaced if they are defeated. By my grandfather's rotting leg, "
"if one goblin dies, I can even channel a small portion of my magical energy and "
"animate his lifeless body. Nothing can stop me! Ha ha ha!!")

Command4(INTL( 753, "GOLDMOON"),INTL( 515, "ARAKAS"),INTL( 754, "THEODORE"),INTL( 755, "ISLAND"))
INTL( 756, "The island of Arakas is part of the kingdom of Goldmoon and it is ruled by "
"King Theodore. They say he is weak, but I say he is intelligent enough not "
"to cross my path by sending his armies against mine. Only the \"druids\" " 
"dare to challenge me.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 757, "Lighthaven is able to repel my goblins but still, it has problems with "
"the minor undeads that are raising from their own cemetary.")

Command(INTL( 514, "WINDHOWL"))
INTL( 758, "I can assure you that this town will fall into my hands in no time.") 

Command(INTL( 759, "SPELLBOOK"))
INTL( 760, "\"Araknor\" once tried to wrest the spellbook of necromancy from me, but "
"failed miserably. Would you like to have it and all the powers that are "
"kept within these pages?")
SetYesNo(SPELLBOOK)

YES (SPELLBOOK)
	Conversation
	INTL( 761, "Ahahaha! Wrong choice! Prepare to meet your doom!")
	FIGHT 

NO (SPELLBOOK)
	Conversation
	INTL( 762, "Wise choice young one, for what lies within these pages could mean your death.")

YesNoELSE (SPELLBOOK)
	Conversation
	INTL( 763, "Oh, I see, you do not want to answer me.")

Command(INTL( 475, "STONE OF LIFE"))
""
IF (CheckGlobalFlag (__QUEST_STONE_OF_LIFE) > CurrentRound )
//////////////////////////////////
// STONE OF LIFE IS STILL VALID //
//////////////////////////////////
	IF (CheckItem (__OBJ_STONE_OF_LIFE) == 0)
		Conversation
		INTL( 764, "My sources tell me that the Stone of Life has been stolen from the "
		"druids. By the rotten leg of my grandfather, I must have it! I MUST! "
		"Find it and bring it back to me in time, and I shall reward you greatly!")
	ELSE
		BOOL boDone = FALSE;
		while( !boDone ){
		GetItemHandle( __OBJ_STONE_OF_LIFE, StoneOfLife )
		IF ( StoneOfLife == NULL )
			boDone = TRUE
		ELSE
			IF (CheckUnitFlag (StoneOfLife, __ITEM_QUEST_STONE_OF_LIFE) == (CheckGlobalFlag (__QUEST_STONE_OF_LIFE)))
				Conversation
				INTL( 765, "You have the Stone of Life? I can sense its incredible power, the energy "
				"instilled by the \"druids\" is still trapped within. Will you give it to me so I can "
				"study it?")
				SetYesNo(STONE);
				boDone = true;
			ELSE
				TakeItemHandle( StoneOfLife )
			ENDIF
		ENDIF
		}
	ENDIF
ELSE
//////////////////////////////////
// STONE OF LIFE IS NOT VALID //
//////////////////////////////////
IF (CheckItem (__OBJ_STONE_OF_LIFE) == 1)
	TakeItem(__OBJ_STONE_OF_LIFE)
	Conversation
	INTL( 766, "You had one Stone of Life stored deep within your backpack, but since it "
	"has been drained of its power, I have taken the liberty of destroying it.")
ELSEIF (CheckItem (__OBJ_STONE_OF_LIFE) > 1 )
	;int nNumStones = CheckItem(__OBJ_STONE_OF_LIFE); 
	FOR( 0, nNumStones )
		TakeItem(__OBJ_STONE_OF_LIFE) 
	ENDFOR
	Conversation
	INTL( 767, "You had a few Stones of Life stored in your backpack, but they are all drained "
	"of their magical lifeforce. I have thus made them vanish into oblivion with "
	"a single word of magic.")
ELSE
	Conversation
	INTL( 768, "The Stone of Life? Yes, I would like to own one in order for me to study "
	"its properties. The druids instill life into one, I wonder if I could "
	"create something similar--but much more powerful--by imbuing it "
	"with death.")
	ENDIF
ENDIF

YES(STONE) 
	TakeItem( __OBJ_STONE_OF_LIFE )
	Conversation
	INTL( 769, "You have chosen wisely. Now, prepare yourself for your next assignment... "
	"DEATH!!!")
	FIGHT

NO(STONE)
	Conversation
	INTL( 770, "What? You dare to defy me? Very well then! Meet your DOOM!!")
	FIGHT

YesNoELSE(STONE)
	Conversation
	INTL( 771, "You seem quite hesitant young one. Don't worry, I won't leave you the "
	"choice anyhow. Ahahahaha!")
	FIGHT

Command5(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 772, "If you get killed on your way back, do not worry, I have a job for you. Ha ha ha!")
BREAK

Default
INTL( 773, "Do not bother me about it, I simply do not care.")

EndTalk
}



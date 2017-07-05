#pragma hdrstop
#include "DwarthonStoneface.H"

DwarthonStoneface::DwarthonStoneface()
{}

DwarthonStoneface::~DwarthonStoneface()
{}

extern NPCstructure::NPC DwarthonStonefaceNPC;

void DwarthonStoneface::Create( void )
{
        npc = ( DwarthonStonefaceNPC );
        SET_NPC_NAME( "[2945]Dwarthon Stoneface" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}
		  
void DwarthonStoneface::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
   SHOUT(INTL( 4899, "AAaaaaaargh!"))
	}

NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void DwarthonStoneface::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
   IF (rnd.roll(dice(1,30)) == 1)
      SHOUT(INTL( 4900, "Do not worry, this will be a clean blow!"))
   ENDIF
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void DwarthonStoneface::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
      SWITCH (rnd.roll(dice(1,30)))
         CASE (1)
            SHOUT(INTL( 4901, "Ah! You merely did a scar!"))
         ENDCASE
         CASE (2){     
            SHOUT(INTL( 4902, "Nightblades!"))
				;int nSummons = rnd.roll(dice(1,3)); 
            FOR( 0, nSummons)
               SUMMON( "Nightblade", FROM_NPC(-5,X), FROM_NPC(-5,Y))
            ENDFOR
         }ENDCASE
         OTHERWISE
         ENDCASE
      ENDSWITCH
   }
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void DwarthonStoneface::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT HEAD = 1;

InitTalk

Begin
""
IF (CheckFlag(__FLAG_BLACKBLOOD_WANTS_YOU) >= 1)
   Conversation
   INTL( 4903, "\"Bane\" \"Blackblood\" has decided that your life is of no use to him.")
   GiveFlag(__FLAG_BLACKBLOOD_WANTS_YOU, (CheckFlag(__FLAG_BLACKBLOOD_WANTS_YOU) - 1) )
   FIGHT
ELSE
   Conversation
   FORMAT(INTL( 4904, "I have heard of the %s name, but am not familiar with it."), USER_NAME)
ENDIF

Command4(INTL( 3696, "WHAT DO YOU DO"),INTL( 4905, "WHAT ARE YOU"),INTL( 487, "OCCUPATION"),INTL( 489, "WORK"))
INTL( 4906, "You could say that I am a barber with very bad aim.") 

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 4907, "Stand aside. I do not have time for this.")

Command2(INTL( 4188, "DWARTHON"),INTL( 4189, "STONEFACE"))
INTL( 4908, "Yes. Dwarthon Stoneface is the name.")

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4909, "The name is \"Dwarthon\" \"Stoneface\" to you. I am \"Bane\"'s most "
"favored servant and thus, earned the title of \"executioner\".")

Command(INTL( 4910, "EXECUTION")) 
INTL( 4911, "Why am I an executioner? Hmmm! Let's see... ah yes... I love to kill!")

Command(INTL( 1686, "TOWER"))
INTL( 4912, "The tower? Ah yes, that's where that insane \"old\" \"man\" lives!")

Command2(INTL( 3848, "ZHAKAR"),INTL( 4913, "OLD MAN"))
INTL( 4914, "Zhakar is only a fool but do not underestimate his arcane skills.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 4915, "You are new around here, aren't you? Yes, even this small island is part of "
"Raven's Dust. ")

Command(INTL( 537, "CASTLE"))
INTL( 4916, "This is Lord \"Bane\"'s castle.") 

Command(INTL( 3846, "ROGUE MAGE"))
INTL( 4917, "The rogue mages are great scouts and their magical skills are of great use to us.") 

Command(INTL( 3845, "BLACKGUARD"))
INTL( 4918, "They still have much to learn in this field of work but they are extremely well-trained.") 

Command(INTL( 3844, "NIGHTBLADE"))
INTL( 4919, "They have been chosen for their loyalty to Lord \"Bane\" and their assassination "
"skills. They are everywhere. Some are even under \"King\" \"Theodore\"'s service. "
"They are waiting for the right \"moment\"...")

Command(INTL( 4920, "MOMENT"))
INTL( 4921, "You shall see in due time...")

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 4922, "One day, he will kneel before me and beg for mercy. But I will not listen "
"to that weakling. No, I will not! I will deliver a clean and swift blow to "
"his neck and present his head on a silver plate to Lord \"Bane\".")

Command(INTL( 509, "BALORK"))
INTL( 4923, "Ding-a-ling! I don't know everybody you numbskull!")

Command(INTL( 541, "JARKO"))
INTL( 4924, "Doesn't ring a bell!")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
""
IF (CheckFlag(__QUEST_DWARTHON_STONEFACE) == 5) 
   Conversation
   INTL( 4925, "Bane is probably the most dangerous man you'll ever see. This is why "
   "I serve him... because I know that he simply cannot lose.")
ELSEIF (CheckFlag(__QUEST_DWARTHON_STONEFACE) == 1)
   Conversation
   INTL( 4926, "Still haven't slew \"Delwobble\"? You're slow.")
ELSEIF (CheckFlag(__QUEST_DWARTHON_STONEFACE) == 2)
   Conversation
   INTL( 4927, "Good. You've proven yourself worthy and possibly useful to "
   "our cause. You may now talk with Lord Bane but be careful "
   "with the words you are using. He may or may not be merciful "
   "if you displease him and if you do displease him, then it "
   "shall be my duty to see you properly punished.")
   GiveFlag(__QUEST_DWARTHON_STONEFACE, 5)
ELSE
   Conversation
   INTL( 4928, "You cannot blame Lord Bane from not allowing himself to talk "
   "to strangers he can't trust. I shall test your abilities. "
   "You simply have to go into the dungeon under the castle "
   "and seek the mad summoner named Delwobble and SLAY him!") 
   GiveFlag(__QUEST_DWARTHON_STONEFACE, 1) 
ENDIF   

Command(INTL( 4929, "DELWOBBLE"))
INTL( 4930, "Delwobble is a mad summoner who dwells under the castle.")

Command2(INTL( 1492, "DESERT"),INTL( 3865, "VULTURE'S DEN"))
INTL( 4931, "I never went in the desert nor do I ever want to.")

Command5(INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "),INTL( 4932, "COCK"),INTL( 4933, "DICK"))
INTL( 4934, "Have you lost your head? Or better yet, do you want to lose it?")
SetYesNo( HEAD )

YES(HEAD)
Conversation
INTL( 4935, "No problem.")
FIGHT

NO( HEAD )
Conversation
INTL( 4936, "I thought so. Then again, I do not like your filthy face!")
FIGHT

YesNoELSE( HEAD )
Conversation
INTL( 4937, "Today, you will learn some good manners.")
FIGHT

Command4(INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 4938, "Now, let me do my work.")
BREAK

Default
""
IF (rnd.roll(dice(1, 2) ))
   Conversation
   INTL( 4939, "You've much to learn about this world.")
ELSE
   Conversation
   INTL( 4940, "Tell it to someone who cares.")
ENDIF

EndTalk
}

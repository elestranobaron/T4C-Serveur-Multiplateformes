/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "AaronBrownbark.H"

AaronBrownbark::AaronBrownbark()
{}

AaronBrownbark::~AaronBrownbark()
{}

extern NPCstructure::NPC BrownbarkNPC;

void AaronBrownbark::Create( void )
{
      npc = ( BrownbarkNPC );
      SET_NPC_NAME( "[2911]A walking tree" );  
      npc.InitialPos.X = 0; 
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0;
}

void AaronBrownbark::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
InitTalk

Begin
""
IF (CheckItem(__OBJ_GREEN_GEMSTONE) == 0) 
	Conversation
	INTL( 1864, "...")
	BREAK
ELSE
	IF (CheckFlag(__FLAG_HAVE_MET_BROWNBARK) == 0)
		Conversation
		INTL( 3840, "What is it that you want?")
		GiveFlag(__FLAG_HAVE_MET_BROWNBARK,1) 
	ELSE
		Conversation // Areuh. :)
		FORMAT(INTL( 3841, "You have come back, %s. What is it that I can do for you?"), USER_NAME ) 
	ENDIF
ENDIF
	
Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 3842, "I am Brownbark. If you seek answers, I can honestly tell you that I am not the one "
"you should ask.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 3843, "I have left my \"brethren\" a long time ago in search of solitude.") 

Command3(INTL( 3844, "NIGHTBLADE"),INTL( 3845, "BLACKGUARD"),INTL( 3846, "ROGUE MAGE"))
INTL( 3847, "They have been hired by \"Bane\" \"Blackblood\" himself to cause mischiefs.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 3849, "He is a befuddled wizard but do not judge him hastily. He is quite powerful in the Art.")

Command(INTL( 746, "DRUID"))
INTL( 3850, "If you see them, they are located to the south-west of \"Silversky\".")

Command(INTL( 836, "FOREST GUARDIAN"))
INTL( 3851, "The Forest Guardian are the protectors of Light. They are allied with the \"Druids\".")

Command(INTL( 3852, "DAEMON TREE"))
INTL( 3853, "The Daemon Trees are the evil counterpart of the \"Forest\" \"Guardians\". They do not "
"see the Light, they only see darkness and hatred.")

Command(INTL( 3854, "RAVENWOOD"))
INTL( 3855, "Ravenwood is the name of the cursed forest.")

Command(INTL( 3856, "MIRROR LAKE"))
INTL( 3857, "This is a beautiful place, isn't it? There is no hatred here. Only peace.")

Command(INTL( 3858, "BRETHREN"))
INTL( 3859, "I used to be allied with \"GreyLeaf\" but I have learned the mistakes of my ways. The "
"\"Forest\" \"Guardians\" showed me the light. I've decided to reside in this peaceful "
"place known as \"mirror\" \"lake\".")

Command(INTL( 3860, "GREYLEAF"))
INTL( 3861, "GreyLeaf is the powerful \"Daemon\" \"Tree\" that roams in \"Ravenwood\".")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 3864, "Bane is the mad man who attempts to control the island.")

Command2(INTL( 1492, "DESERT"),INTL( 3865, "VULTURE'S DEN"))
INTL( 3866, "Beware of the monsters that roam in the desert of Vulture's Den.")

Command(INTL( 998, "SILVERSKY"))
INTL( 3867, "Silversky is the only town on \"Raven's\" \"Dust\".")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 3768, "Raven's Dust is the name of this island.")

Command(INTL( 3868, "ALTHEA"))
INTL( 3869, "Althea is the name of the world in which we live in.")

Command(INTL( 1243, "ARTHERK"))
INTL( 3870, "Artherk is the human's God of Healing and Mending.")

Command2(INTL( 3871, "WORMLORD"),INTL( 3872, "WORM LORD"))
INTL( 3873, "I have never seen it myself.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 3874, "I cannot taste the softness of flesh.")
BREAK

Command(INTL( 3771, "?"))
INTL( 3875, "I am not the Oracle. I do not have answers for everything.")
Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
FORMAT(INTL( 3876, "It is time for you to depart, %s."), USER_NAME)
BREAK

Default
INTL( 3877, "I am sorry but you will have to seek your answer elsewhere.")

EndTalk
}


/*

Anrak Brownbark always had a natural talent for manipulating axes. In his
younger days, he amazed his friends by juggling several axes at a time. He
also became a gifted axe-thrower, seldom missing his mark (or seldom hitting
it, if his goal was to miss). Once, soon after he became a man, he had a
dream that a lovely maiden lost in the woods was being attacked by dark
living trees. He woke up with a start and, his heart still beating fast,
heard the chilling scream of terror of the maiden echo outside. He quickly
grabbed his custom-made Twin-Blade Axe and rushed into the woods, calling
out for the lost maiden. Following her cries and the sounds of the pursuit,
he managed to catch up with the evil creatures and slew them mercilessly,
his axe cutting them in half with every swing. He ordered her to run while
he finished them off, and she obeyed.

The trees were no ordinary trees, however. Rather, they were necromantic
corruptions based on the gentle Forest Guardians. While their evil shells
were destroyed, the necromancer who controlled them was not. Hidden in his
remote tower, he observed the young Anrak's deeds with detached annoyance.
He sensed his destiny was to become a hero. This was a man who could prove
troublesome later, so he should be handled quickly (although for a
long-lived necromancer, quickly can still mean decades). He set upon
creating a spell that would curse the budding hero and prevent him from
reaching his destiny...

Meanwhile, Anrak found the maiden he had saved and fell in love with her.
There was something unusual about her, however. Perhaps it was her wide,
slightly slanted eyes, or the fairness of her skin, or the litheness of her
figure, but whatever it was, there was a fairy-like quality about her that
he could not resist. She returned his love and they were married before
winter. They had one son, whom they named Aaron. While his son grew, Anrak
stayed home and cared for his family, but dreams of a greater destiny
returned to haunt him, urging him to leave and do great deeds. He resisted
for a while, but eventually decided to leave, promising his wife that he
would return soon. She did not say anything, as if she knew what was fated
to happen.

Anrak left the next morning. Days stretched into weeks, weeks into months,
months into seasons, and seasons into years. Anrak would occasionally send
word to his family and promise a quick return, but one adventure led to
another, and his bed remained half cold, with only his wife to warm it up.
She grew sad and lonely, caring for nothing but her son Aaron, who had
become the center of her life. Finally, word reached her that her husband
had arrived to Silversky and was on his way home. He would be there the
following week. He was rich, he was famous, and, more importantly, he was
back!

Unfortunately, Necromancer Zhakar was still at work. His spell had been
ready for years. All he needed now was for Anrak to return to Raven's Dust.
As soon as he did, dark agents notified the necromancer, who feared that
Anrak would come to slay him. He sent some Demon Trees to attack him on the
way. Those were special Demon Trees, however: a single scratch from any one
of them would infect him with a transformation disease--he too would become
a Demon Tree. Upon meeting the evil trees, Anrak fought valiantly, but could
not avoid getting hurt in the process. He slew them all, but he was sick
from his wounds. He hobbled his way home, but by the time he reached it, he
had become a living tree. Fortunately, the goodness of his soul prevailed,
and he did not become evil. He lost his ability to speak and interact with
humans, however, and has since moved away from most of them.

His wife died quietly a few months after his return. Aaron learned fairly
early how to fend for himself, but never knew too much about the cause of
his father's curse.

*/
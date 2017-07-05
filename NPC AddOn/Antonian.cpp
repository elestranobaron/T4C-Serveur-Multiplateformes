#pragma hdrstop
#include "Antonian.h"

Antonian::Antonian()
{}

Antonian::~Antonian()
{}

extern NPCstructure::NPC GuildLeaderEthanNPC;

void Antonian::Create( ){
	npc = GuildLeaderEthanNPC;
	SET_NPC_NAME( "[12722]Hermit Antonian");
	npc.InitialPos.X = 2372;
	npc.InitialPos.Y = 733;
	npc.InitialPos.world = 0;
}

void Antonian::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT TarnianGiveTablet = 1;
CONSTANT Directions = 2;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 26)
	Conversation
	INTL( 11827, "Hello young one. What brings you to see an old hermit such as myself?")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 11828, "Hello young one. What brings you to see an old hermit such as myself? Oh! You have a Runed Stone Tablet! "
	"Tell me, did Tarnian Wolfmane give this to you?")
	SetYesNo(TarnianGiveTablet)
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 27)
	Conversation
	INTL( 11829, "Oh, it's you again. Are you here for some directions to a nexus stone?")
	SetYesNo(Directions)
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 28)
	Conversation
	INTL( 11830, "Have you talked to Aquinos yet? Use the tablet to travel to Raven's Dust and then travel to the temple in "
	"Silversky to find him. He will be able to tell you more on this Nameless Bard.")
ELSEIF((CheckFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED)>5)&&(CheckFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED)<15))
	Conversation
	INTL( 11831, "Ah, so you've been able to locate more nexus stones in Raven's Dust... interesting to say the least. " 
	"Alas, I may not be of assistance to you since I haven't explored this island nor do I "
	"intend to. Still, if you think you've located all the nexus stones there as well, come back " 
	"and I'll help you activate its remaining power.") 
ELSEIF((CheckFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED)>=15)&&(CheckFlag(__FLAG_ADDON_NEXUS_STONEHEIM_ACTIVATED)==0))
	Conversation
	INTL( 11832, "Ah, you've finally located every nexus stones on Raven's Dust. This is great news indeed. "
	"Now, about \"unlocking\" its power...") 
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11833, "I have done everything I can to help you... the rest is up to you.")
ELSE
	Conversation
	INTL( 11834, "Did you come to brag about the little adventure you had in Lighthaven? I hope not. Cause at your age, "
	"that was considered a daily chore for me... heh heh.")
ENDIF

YES(TarnianGiveTablet)
	Conversation
	INTL( 11835, "Ahh, that trusting fool, so he gave you the \"Runed\" \"Stone\" \"Tablet\" and sent you to me. Sometimes "
	"I wonder if there's anything at all in that little head of his.")
NO(TarnianGiveTablet)
	Conversation
	INTL( 11836, "Ahh... well then what is it you wanted?")
YesNoELSE(TarnianGiveTablet)
	Conversation
	INTL( 11837, "Did Tarnian Wolfmane give you that stone tablet or not?")

Command(INTL( 11838, "UNLOCK")) 
""
IF((CheckFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED)<15)||(CheckFlag(__FLAG_ADDON_NEXUS_STONEHEIM_ACTIVATED)==1))
	IF (rnd.roll( dice(1,2) ) == 1)
		Conversation
		INTL( 8482, "I don't know anything about that.")
	ELSE
		Conversation
		INTL( 11839, "I don't quite understand what you mean.")
	ENDIF
ELSE
	IF(CheckFlag(__QUEST_ISLAND_ACCESS) < 2) 
		Conversation
		INTL( 11840, "Ah yes, I believe I can unlock the full potential of the tablet but... I'm not sure "
		"you've done all there is to do on Raven's Dust just yet. Come back once you're " 
		"truly ready to travel to Stoneheim.") 		
	ELSE
		Conversation
		INTL( 11841, "Let's see the tablet... There, it's done! Using it, you can now go to Stoneheim whenever "
		"you desire it.") 
		PRIVATE_SYSTEM_MESSAGE(INTL( 11842, "You give the runed stone tablet to Antonian...")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 11843, "He passes his fingers over the runes and they start to glow! He then hands it back to you.")) 
		GiveFlag(__FLAG_ADDON_NEXUS_STONEHEIM_ACTIVATED, 1)
	ENDIF
ENDIF

CmdAND3(INTL( 11844, "RUNE"), INTL( 11845, "STONE"), INTL( 11846, "TABLET"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 11847, "Oh it's quite remarkable! My latest project, it's a device that can be used to travel long distances "
	"in the \"blink\" of an eye!")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 11849, "BLINK"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 11850, "That fast yes! Very exciting isn't it? You see, the high priest of Lighthaven recently asked me to look "
	"into matters concerning magical transportation. It seems this tablet is the answer to the high "
	"priest's \"prayers\".")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 11851, "PRAYER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 11852, "Well, the stone's magic is so \"ancient\" that it predates even the oldest of races, making it impossible "
	"for any other magic, including Olin Haad's, to detect its use.")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 10782, "ANCIENT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 11853, "From what I can tell by the engravings, the tablet acts as a kind of focus. When the bearer of the tablet "
	"places it on a \"nexus\" \"index\", the tablet's rune that matches that of the nexus stone beside it "
	"will start to glow. I believe that if you activate enough of these runes, you will be able to "
	"travel to Raven's Dust.")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

CmdAND(INTL( 11854, "NEXUS"), INTL( 11855, "INDEX"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 11856, "Beside each nexus stone is an index on which you must place the tablet. There are many of these stones "
	"scattered throughout the islands. Fortunately for you, I have already discovered the \"location\" of "
	"several of them here on Arakas. Seeing as you need it more than I do, I will let you keep the tablet "
	"for yourself.")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 9153, "LOCATION"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 11857, "I had originally sent Tarnian to activate the nexus stones, but I guess he got caught up in that crusade "
	"of his. I can give you \"directions\" to the stones to help you out. Oh I almost forgot, you can use the "
	"tablet at any time to come back here. When I discovered that, I had this cottage built so I could better "
	"study the tablet's behavior. You can use this knowledge to your advantage when activating the nexus stones.")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 11858, "DIRECTION"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 11859, "Now where did I put those charts? Please excuse me a moment, I seem to have misplaced them...")
	PRIVATE_SYSTEM_MESSAGE(INTL( 11860, "Antonian becomes so engrossed in his search that he completely forgets about your presence."))
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 27)
	BREAK
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

YES(Directions)
	IF(CheckFlag(__FLAG_ADDON_NEXUS_1_ACTIVATED) == 0)
		Conversation
		INTL( 11861, "Travel north and search the river until you find a bridge across, onto a small island. There is "
		"a nexus stone on that island.")
	ELSEIF(CheckFlag(__FLAG_ADDON_NEXUS_2_ACTIVATED) == 0)
		Conversation
		INTL( 11862, "Take the road south and head southwest at the first fork. Shortly after the road turns west, you "
		"will come to another fork. Go north and then northwest across the bridge after that. As soon as "
		"you cross the bridge, head straight north and you will come upon another nexus stone.")
	ELSEIF(CheckFlag(__FLAG_ADDON_NEXUS_3_ACTIVATED) == 0)
		Conversation
		INTL( 11863, "Take the road south and head southwest at the first fork. Shortly after the road turns west, you "
		"will come to another fork. Take the southwest road until you cross a bridge, then head straight "
		"south into the valley to find another nexus stone.")
	ELSEIF(CheckFlag(__FLAG_ADDON_NEXUS_4_ACTIVATED) == 0)
		Conversation
		INTL( 11864, "Take the road south and head southwest at the first fork. Shortly after the road turns west, you "
		"will come to another fork. Go north and then northwest across the bridge after that. As soon as "
		"you cross the bridge, follow the river west until its end where it meets the ocean. You should "
		"find a nexus stone beside the shore there.")
	ELSEIF(CheckFlag(__FLAG_ADDON_NEXUS_5_ACTIVATED) == 0)
		Conversation
		INTL( 11865, "I don't have any specific directions for this nexus stone, but I will tell you that it is located "
		"on the southernmost point on this island. With that, you should be able to find it on your own.")
	ELSE
		IF(CheckFlag(__QUEST_ISLAND_ACCESS) == 0) 
			Conversation
			INTL( 11866, "It looks like you've found all the nexus stones that I know of. Alas, you "
			"cannot use its power right now to travel to Raven's Dust because you still " 
			"have important things to accomplish on Arakas before leaving.") 			
		ELSE
			Conversation
			INTL( 11867, "It looks like you've found all the nexus stones that I know of. If you use the Runed Stone Tablet now, "
			"you should be able to travel to Raven's Dust without any complications. Once you get there, you should "
			"head to Silversky. Aquinos, a friend of mine, is a \"scholar\" at the temple there. He knows where to "
			"find the \"one\" you're looking for.")
			PRIVATE_SYSTEM_MESSAGE(INTL( 11868, "You receive 250000 experience points."))
			GiveXP(250000)
			GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 28)
		ENDIF 
	ENDIF
NO(Directions)
	Conversation
	INTL( 11869, "Well then what did you want?")
YesNoELSE(Directions)
	Conversation
	INTL( 11870, "Did you come here for directions to a nexus stone or not?")
	SetYesNo(Directions)

Command(INTL( 11871, "ONE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 28)
	Conversation
	INTL( 11872, "While you were away looking for nexus stones, I received a message from the High Priest saying you were "
	"looking for the Nameless Bard. Unfortunately, I have no way of knowing where you will end up once you get "
	"to Raven's Dust. However, I can tell you that Silversky is on the southeastern part of the island. Maybe "
	"that will be enough for you to find it.")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 11873, "SCHOLAR"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 28)
	Conversation
	INTL( 11874, "He's a zoologist that studies creatures that manifest some degree of intelligence. One day, he heard about "
	"this creature that could speak and he sought it out. He is now one of a few people who know where to find "
	"the Nameless Bard.")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 11875, "I am Antonian.")

Command(INTL( 489, "WORK"))
INTL( 11876, "Oh, I am just an old hermit...")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 4316, "Safe travels.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 8482, "I don't know anything about that.")
ELSE
	Conversation
	INTL( 11839, "I don't quite understand what you mean.")
ENDIF


EndTalk
}
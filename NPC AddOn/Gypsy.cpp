#pragma hdrstop
#include "Gypsy.h"

Gypsy::Gypsy()
{}

Gypsy::~Gypsy()
{}

extern NPCstructure::NPC GypsyNPC;

void Gypsy::Create( ){
	npc = GypsyNPC;
	SET_NPC_NAME( "[12742]Gypsy");
	npc.InitialPos.X = 2370;
	npc.InitialPos.Y = 360;
	npc.InitialPos.world = 0;
}

void Gypsy::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT FirstQuestion = 1;
CONSTANT SecondQuestion = 2;
CONSTANT ThirdQuestion = 3;
CONSTANT ItemChoice = 4;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 16)
	Conversation
	INTL( 12222, "Welcome... if you have come to have your fortune told, you must come back some other time. "
	"Great events will happen soon and I must prepare for them.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 16)
	Conversation
	INTL( 12223, "Well met, \"Traveler\" sent by the winds!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 17)
	Conversation
	INTL( 12224, "To reach the temple, you must go through the cave that lies north of here. In that temple will you "
	"find the one you seek.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 18)
	Conversation
	INTL( 12225, "I see that you have found the temple... I can feel the presence of a \"Darkheart\" on you.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 19)
	Conversation
	INTL( 12226, "You must hurry! Bring the stone to the temple in Lighthaven before anything happens to it!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	FORMAT(INTL( 12227, "You have a long road ahead of you, %s."), USER_NAME)
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 42)
	Conversation
	INTL( 12228, "Well-met Traveller sent by the Winds! It's a pleasure to see you again. First, I must thank you in "
	"the name of the Council of the Eight for your help in releasing Althea from its destiny of the \"Fourth\" "
	"\"Coming\".")
ELSE
	Conversation
	FORMAT(INTL( 12229, "Good day to you, %s. I trust you are not letting all this success get to your head? Hee hee."), USER_NAME)
ENDIF

CmdAND(INTL( 12230, "FOURTH"), INTL( 742, "COMING"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 42)
	Conversation
	INTL( 12231, "If Olin Haad had brought Gluriurl back to life, the god of Death would have been force to come. "
	"The last time the gods were at war, they destroyed much of the known land, except for these three "
	"islands. Now that the remains of the god have returned to their \"respectful\" \"guardians\", we "
	"can begin to hope again.")
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

CmdAND(INTL( 12233, "RESPECT"), INTL( 4313, "GUARDIAN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 42)
	Conversation
	INTL( 12234, "The skull and heart of Gluriurl were returned to the Council of the Eight. His torso was returned "
	"to the Nameless Bard and the heart of Lothar and Artherk to the humans. Before I let you go on "
	"with your adventuring days, I would like to present these gifts to you, as a token of our "
	"appreciation. Sadly, I must take my leave of you, but remember child that this is only the beginning "
	"of your legacy.")
	GiveItem(__OBJ_QUIVER_OF_STABILITY)
	GiveItem(__OBJ_AMULET_OF_REJUVENATION)
	GiveItem(__OBJ_AMULET_OF_REPLENISHMENT)
	GiveItem(__OBJ_GEM_OF_REJUVENATION)
	GiveItem(__OBJ_GEM_OF_REPLENISHMENT)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12235, "The gypsy gives you a Quiver of Stability, an Amulet of Rejuvenation, a Gem of "
	"Rejuvenation, an Amulet of Replenishment and a Gem of Replenishment."))
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 43)
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

Command(INTL( 1322, "TRAVELER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 16)
	Conversation
	INTL( 12236, "You seem surprised that I know about that... the answer is simple. I am a \"seer\".")
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF
	
Command(INTL( 12237, "SEER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 16)
	Conversation
	INTL( 12238, "I can see images in my dreams that are beyond understanding. For instance, I had a vision yesterday, "
	"and you were in it. You were searching for someone named... \"Nomad\" I believe.")
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF
	
Command(INTL( 11802, "NOMAD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 16)
	Conversation
	INTL( 12239, "I can help you find him, but first I must attune myself with your aura. Let's see now... did the one "
	"called Olin Haad tell you about the New Breed, yes or no?")
	SetYesNo(FirstQuestion)
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

YES(FirstQuestion)
	Conversation
	INTL( 12240, "I see... and did you believe him when he said that you were a Harvester of Life?")
	SetYesNo(SecondQuestion)
NO(FirstQuestion)
	Conversation
	INTL( 12241, "You lie, but that is of no consequence to me. Did you believe him when he said that you were a Harvester "
	"of Life?")
	SetYesNo(SecondQuestion)
YesNoELSE(FirstQuestion)
	Conversation
	INTL( 12242, "Answer the question please... did Olin Haad tell you about the New Breed, yes or no?")
	SetYesNo(FirstQuestion)

YES(SecondQuestion)
	Conversation
	INTL( 12243, "I see... There is a legend that says, 'From the ashes of the noble races, a new race of beings shall "
	"arise. To them, the power of Balance shall be given.' Are you a \"Harvester\" \"of\" \"Life\" or a "
	"\"Giver\" \"of\" \"Life\", New Breed?")
	SetYesNo(ThirdQuestion)
NO(SecondQuestion)
	Conversation
	INTL( 12244, "I see... there might be hope for you after all. There is a legend that says, 'From the ashes of the "
	"noble races, a new race of beings shall arise. To them, the power of Balance shall be given.' Are you "
	"a \"Harvester\" \"of\" \"Life\" or a \"Giver\" \"of\" \"Life\", New Breed?")
	SetYesNo(ThirdQuestion)
YesNoELSE(SecondQuestion)
	Conversation
	INTL( 12245, "Answer the question please... did you believe Olin Haad when he said that you were a Harvester of Life?")
	SetYesNo(SecondQuestion)

;} else if( ( msg.Find(INTL( 5333, "HARVESTER")) != -1 ) && YesNo == ThirdQuestion) {;YesNo = 0;
	Conversation
	INTL( 12246, "I see... I have found the one you are searching for. He is in the ancient temple of a dead god called Gluriurl. "
	"The temple is located on an island that was separated from the mainland by a large body of water during "
	"the god's downfall. To reach this island, you must travel through a cave that lies north of here.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 17)

;} else if( ( msg.Find(INTL( 12247, "GIVER")) != -1 ) && YesNo == ThirdQuestion) {;YesNo = 0;
	Conversation
	INTL( 12248, "I see... I have found the one you are searching for. He is in the ancient temple of a dead god called Gluriurl. "
	"The temple is located on an island that was separated from the mainland by a large body of water during "
	"the god's downfall. To reach this island, you must travel through a cave that lies north of here.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 17)

;} else if(YesNo == ThirdQuestion) {;
	Conversation
	INTL( 12249, "Answer the question please... are you a \"Harvester\" \"of\" \"Life\" or a \"Giver\" \"of\" \"Life\", New Breed?")

Command(INTL( 12250, "DARKHEART"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 18)
	Conversation
	INTL( 12251, "I can understand your confusion. A Darkheart is a very powerful relic that is known in many legends "
	"throughout countless ages. These stones are usually associated with curses and maledictions. I first "
	"learned about it in one of my \"dreams\".")
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

Command(INTL( 12252, "DREAM"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 18)
	Conversation
	INTL( 12253, "The dream is always the same... a \"decaying\" \"corpse\" stands in front of me, talking about this "
	"stone, and no matter how hard I try, I cannot understand it. I believe the dream is trying to tell me "
	"that the Darkheart is somehow related to a greater \"plan\".")
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

Command2(INTL( 12254, "DECAY"), INTL( 12255, "CORPSE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 18)
	Conversation
	INTL( 12256, "I can never see it very well, but from what I remember when I wake from the dream, the corpse reminds me "
	"of the god of Death, the Harbinger. But why would the god of Death speak to me? No, I do not believe it "
	"is him.")
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

Command(INTL( 4202, "PLAN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 18)
	Conversation
	INTL( 12257, "In the dream, I saw hundreds of Darkheart stones falling from the sky like rain, entering the soil like "
	"seeds and blossoming into great heroes of ancient times. At the end of the dream, the decaying corpse "
	"says that for each seed that blossoms, a thousand lives will be \"sacrificed\".")
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

Command(INTL( 12258, "SACRIFICE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 18)
	Conversation
	INTL( 12259, "I am having trouble understanding it all. One thing is certain though, you must bring this stone to the "
	"temple of Artherk in Lighthaven. That is one of the few places I know where you can leave the stone "
	"for safekeeping. Before you leave however, I have \"something\" I would like to give you...")
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

Command(INTL( 4082, "SOMETHING"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 18)
	Conversation
	INTL( 12260, "I have three magical objects which might be of interest to you, but you may only take one. I have an "
	"\"Amulet\" \"of\" \"Regeneration\" which increases your health over time, an \"Amulet\" \"of\" "
	"\"Renewal\" which increases your mana over time and \"Trueshot's\" \"Quiver\" which increases accuracy "
	"with the bow. Which will you choose?")
	SetYesNo(ItemChoice)
ELSE
	Conversation
	INTL( 12232, "I see... you and I having this conversation, but not on this day.")
ENDIF

;} else if( ( msg.Find(INTL( 6621, "REGENERATION")) != -1 ) && YesNo == ItemChoice) {;YesNo = 0;
	Conversation
	INTL( 12261, "A wise choice. The other two objects will go to other adventurers in need, rest assured. Now, you "
	"should hurry and go to the Lighthaven temple before anything happens to you and you lose the stone.")
	GiveItem(__OBJ_AMULET_OF_REGENERATION)
	GiveItem(__OBJ_GEM_OF_REGENERATION)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12262, "The gypsy gives you an Amulet of Regeneration and a Gem of Regeneration."))
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 19)

;} else if( ( msg.Find(INTL( 12263, "RENEWAL")) != -1 ) && YesNo == ItemChoice) {;YesNo = 0;
	Conversation
	INTL( 12264, "A wise choice. The other two objects will go to other adventurers in need, rest assured. Now, you "
	"should hurry and go to the Lighthaven temple before anything happens to you and you lose the stone.")
	GiveItem(__OBJ_AMULET_OF_RENEWAL)
	GiveItem(__OBJ_GEM_OF_RENEWAL)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12265, "The gypsy gives you an Amulet of Renewal and a Gem of Renewal."))
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 19)

;} else if( ( msg.Find(INTL( 12266, "QUIVER")) != -1 ) && YesNo == ItemChoice) {;YesNo = 0;
	Conversation
	INTL( 12267, "A wise choice. The other two objects will go to other adventurers in need, rest assured. Now, you "
	"should hurry and go to the Lighthaven temple before anything happens to you and you lose the stone.")
	GiveItem(__OBJ_TRUESHOT_QUIVER)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12268, "The gypsy gives you Trueshot's Quiver."))
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 19)

;} else if(YesNo == ItemChoice) {;
	Conversation
	INTL( 12269, "You may only choose one. I have an \"Amulet\" \"of\" \"Regeneration\", an \"Amulet\" \"of\" \"Renewal\" "
	"and \"Trueshot's\" \"Quiver\". Which would you like to have?")

Command(INTL( 483, "NAME"))
INTL( 12270, "I cannot tell you my name... you will understand why someday.")

Command(INTL( 489, "WORK"))
INTL( 12271, "I try to ease the lives of those whose paths I cross.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 12272, "I have no answer for that.")
ELSE
	Conversation
	INTL( 12273, "If I ever see the answer, I will let you know.")
ENDIF


EndTalk
}
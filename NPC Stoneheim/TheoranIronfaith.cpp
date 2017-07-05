#pragma hdrstop
#include "TheoranIronfaith.h"

TheoranIronfaith::TheoranIronfaith()
{}

TheoranIronfaith::~TheoranIronfaith()
{}

extern NPCstructure::NPC TheoranIronfaithNPC;

void TheoranIronfaith::Create( void )
{
        npc = TheoranIronfaithNPC;
        SET_NPC_NAME( "[10929]Theoran Ironfaith" );
        npc.InitialPos.X = 565;
        npc.InitialPos.Y = 925;
        npc.InitialPos.world = 0;
}
 
void TheoranIronfaith::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT RingOfPureFaith = 1;
CONSTANT Healing = 2; 
CONSTANT BlessWater = 3; 

InitTalk

Begin
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
   INTL( 10253, "Prepare to defend yourself, spawn of darkness.")	
	PRIVATE_SYSTEM_MESSAGE(INTL( 10254, "Theoran eyes you grimly."))
   FIGHT
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation   
	INTL( 10255, "I have no desire to speak with individuals of your ilk.")
	BREAK
ELSE 
   Conversation
   INTL( 10256, "Greetings, friend.")	
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU")) 
INTL( 10257, "I am Theoran Ironfaith.")

Command(INTL( 10258, "THEORAN"))
INTL( 10259, "How can I be of assistance to you, my friend?")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 10260, "I am a cleric and have dedicated my entire life to Him. I wear this \"ring\" \"of\" \"pure\" \"faith\" as "
"a symbol of my devotion to Artherk, the god of Light.") 

CmdAND3(INTL( 8039, "RING"),INTL( 10261, "PURE"),INTL( 10262, "FAITH"))
INTL( 9725, "You seek to obtain a ring of pure faith? That is feasible through a small ritual that involves prayers and some "
"specific components. If you can gather a \"ring\" \"of\" \"faith\", a \"grail\" \"of\" \"purity\" and two \"flasks\" \"of\" \"holy\" \"water\", I'll "
"perform the holy ritual.") 
IF ((CheckItem(__OBJ_RING_OF_FAITH) >= 1) && (CheckItem(__OBJ_GRAIL_OF_PURITY) >= 1) && CheckItem(__OBJ_FLASK_OF_HOLY_WATER) >= 2) 
	Conversation
	INTL( 10799, " Ah, I see that you have gathered all the required components. Well done! Do you want me "
	"to perform the ritual right away?") 
	SetYesNo(RingOfPureFaith) 
ENDIF 

YES(RingOfPureFaith)
	IF ((CheckItem(__OBJ_RING_OF_FAITH) >= 1) && (CheckItem(__OBJ_GRAIL_OF_PURITY) >= 1) && CheckItem(__OBJ_FLASK_OF_HOLY_WATER) >= 2) 
		Conversation
		INTL( 9726, "Then, let's proceed. In the name of Artherk, I bless this ring and infuse it "
		"with my faith.... Here, I give you this ring of pure faith. May Artherk light thy path. ")
		PRIVATE_SYSTEM_MESSAGE(INTL( 9727, "Theoran carefully pours the holy water into the grail and immerses the ring."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9728, "Theoran gives you a ring of pure faith."))
		FOR(0,2) 
			TakeItem(__OBJ_FLASK_OF_HOLY_WATER) 
		ENDFOR
		TakeItem(__OBJ_RING_OF_FAITH) 
		TakeItem(__OBJ_GRAIL_OF_PURITY) 
		GiveItem(__OBJ_RING_OF_PURE_FAITH) 
	ELSE
		Conversation
		INTL( 9729, "You're missing some components, I'm afraid. The creation of a ring of pure faith requires a \"ring\" \"of\" \"pure\" \"faith\", "
		"a \"grail\" \"of\" \"purity\" and at least two \"flasks\" \"of\" \"holy\" \"water\". Please come back again once you've gathered all the "
		"necessary components.")
	ENDIF

NO(RingOfPureFaith)
	Conversation
	INTL( 9730, "Come back when you have the required components.")

YesNoELSE(RingOfPureFaith)
	Conversation
	INTL( 9731, "Well, do you want a ring of pure faith?")
	YesNoELSE(RingOfPureFaith) 

Command(INTL( 10800, "GRAIL OF PURITY")) 
INTL( 10801, "The \"centaur\" \"avengers\" stole all the grails of purity I had left. I doubt they'll be willing "
"to give them back to you without a fight.") 

Command2(INTL( 7995, "CENTAUR"),INTL( 10802, "AVENGER"))
INTL( 10803, "Even though the centaurs despise us, you have to remember that they are not evil. However, I "
"cannot say the same about the centaur avengers. For all that I know, they might be even working "
"for the vile Zion Thunderheart.") 

CmdAND(INTL( 8039, "RING"),INTL( 10262, "FAITH"))
INTL( 10804, "A friend of mine, \"Brother\" \"Thorkas\" of Silversky, has a great supply of these rings.") 

CmdAND(INTL( 10805, "HOLY"),INTL( 2590, "WATER"))
INTL( 10806, "The holy water is absolutely necessary for the holy ritual. \"Brother\" \"Thorkas\" of "
"Silversky is probably the best of our order for blessing water. However, if you bring "
"me a flask of crystal water, I'd be glad to do it for you.") 
IF (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 1) 
	Conversation
	INTL( 10807, " Ah, I see that you have a flask of crystal water. Do you want me to bless it?")
	SetYesNo(BlessWater) 
ENDIF 

YES(BlessWater)
IF (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 1) 
	Conversation
	INTL( 10808, "Very well. Here, your flask has been blessed.") 
	PRIVATE_SYSTEM_MESSAGE(INTL( 10809, "Theoran makes a gesture and whispers a prayer to Artherk.")) 
	TakeItem(__OBJ_FLASK_OF_CRYSTAL_WATER) 
	GiveItem(__OBJ_FLASK_OF_HOLY_WATER) 
	IF (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 1) 
		Conversation
		INTL( 10810, " Hmm. I see that you have another flask of crystal water. Do you want me to bless this "
		"one as well?") 
		SetYesNo(BlessWater) 
	ENDIF 
ELSE
	Conversation
	INTL( 10811, "Hey, it seems that you don't have a flask of crystal water afterall.")
ENDIF

NO(BlessWater)
Conversation
INTL( 10812, "Fine, I understand.")

YesNoELSE(BlessWater) 
Conversation
INTL( 10813, "Well, do you want me to bless your flask of crystal water?")
SetYesNo(BlessWater) 

Command(INTL( 10814, "THORKAS"))
INTL( 10815, "Brother Thorkas resides in the temple dedicated to Artherk in Silversky. Seek him out if you "
"need his assistance.") 

Command(INTL( 7710, "LIGHTBRINGER")) 
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 10263, "I wish you good luck on your journey, Lightbringer.")
ELSE
	Conversation
	INTL( 10264, "Should you wish to become a Lightbringer, you must first seek out the paladin, Sir \"Beltigan\".")
ENDIF 

Command2(INTL( 738, "MAKRSH"),INTL( 739, "P'TANGH")) 
INTL( 10265, "The cursed lich has to be stopped while it is still weak. A mere mortal stands no chance against "
"him but a \"Lightbringer\" might have a chance of vanquishing him...")

Command(INTL( 8606, "OGRIMAR")) 
INTL( 10266, "Ogrimar is the nemesis of our god, \"Artherk\". He is the god of the night and represents "
"everything that I stand against.") 

Command(INTL( 1243, "ARTHERK"))
INTL( 10267, "Artherk is the god of Light. It is He who you should turn for counsel when all odds "
"seem to be against you.")

Command(INTL( 8610, "MORDENTHAL"))
INTL( 10268, "Mordenthal is a dark knight who worships the god of the night, \"Ogrimar\". He resides "
"in a fortified keep surrounded by mountains located north of \"Stonecrest\". This man is " 
"very powerful and must not be trusted.")

Command(INTL( 9705, "BELTIGAN"))
INTL( 10269, "Beltigan is a paladin of Artherk who resides in his castle located south of \"Stonecrest\". It "
"is him who you should seek if you wish to become a \"Lightbringer\".")

Command2(INTL( 8013, "DIONYSUS"),INTL( 8014, "SILVERSTREAM"))
INTL( 10270, "Dionysus is the proud centaur who acts as a cleric in the small \"centaur\" \"town\".")

Command2(INTL( 9962, "NISSUS"),INTL( 9963, "HALOSEEKER"))
INTL( 10271, "Nissus Haloseeker is a priest who resides in \"Stonecrest\".")

CmdAND(INTL( 8891, "STAFF"),INTL( 10272, "HOPE"))
INTL( 10273, "The staves of hope can only be made by \"Dionysus\" \"Silverstream\", the centaur.") 

Command(INTL( 8125, "SKRAUG")) 
INTL( 10274, "The skraugs should not be trusted for they follow the dark path set by \"Ogrimar\".")

Command(INTL( 7995, "CENTAUR"))
INTL( 10275, "The centaurs resides in a small town on the southern part of the island.")

Command(INTL( 7700, "STONECREST"))
INTL( 10276, "Stonecrest is a town located to the western part of the island.")

Command2(INTL( 6251, "STONEHEIM"),INTL( 755, "ISLAND"))
INTL( 8686, "Stoneheim is the name of this island.") 

Command(INTL( 1613, "SANCTUARY"))
INTL( 10277, "I do not possess the power to bind your spirit here.")

Command(INTL( 569, "HEAL")) 
""
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	Conversation
	FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"), ((USER_MAXHP-USER_HP)))
	SetYesNo(Healing)
ENDIF

YES(Healing)
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (Gold < ((USER_MAXHP-USER_HP)))
		IF (Gold > 0) 
			Conversation
			INTL( 10278, "You did not have enough gold pieces but I have healed a few of your wounds "
			"nonetheless for what you could spare.")
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 10279, "You give %u gold to Theoran."), Gold))
			PRIVATE_SYSTEM_MESSAGE(INTL( 8225, "Your wounds have been partially healed!"))
			CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
			HealPlayer(Gold) 
			TakeGold(Gold)
		ELSE
			Conversation
			INTL( 10280, "You do not have enough gold pieces to be healed. You will have to find "
			"have to find the gold first.")
		ENDIF
	ELSE		
		Conversation
		INTL( 10281, "Thank you for this generous donation. Your wounds are now healed.  "
		"Please feel free to come back if you need more healing.")
		TakeGold(((USER_MAXHP-USER_HP)))
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 10279, "You give %u gold to Theoran."), USER_MAXHP-USER_HP))  
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		HealPlayer(USER_MAXHP)      
	ENDIF
ENDIF

NO(Healing)
Conversation
INTL( 10282, "Ask me again if you ever change your mind.")

YesNoELSE(Healing)
Conversation
INTL( 2211, "So be it, my friend.")

Command5(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 1919, "WHORE"),INTL( 698, " ASS "))
INTL( 10283, "I have no time for such nonsense.")
PRIVATE_SYSTEM_MESSAGE(INTL( 10284, "Theoran looks quite angry at you.")) 
BREAK

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL")) 
INTL( 10285, "Farewell. May Artherk light thy path.")
PRIVATE_SYSTEM_MESSAGE(INTL( 10286, "Theoran casts a protective spell on you.")) 
CastSpellTarget(__SPELL_NPC_THEORAN_BOOST) 
BREAK 

Default
""
IF (rnd.roll(dice(1,2) ) == 1)
   Conversation
   INTL( 8230, "Hmm, yes that's very interesting.")
ELSE
   Conversation
   INTL( 5758, "I have no interest in that matter.")
ENDIF

EndTalk
}

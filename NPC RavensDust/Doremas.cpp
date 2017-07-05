//////////////////////////////////////////////////////////////////////
// Doremas.cpp: implementation of the Doremas class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Doremas.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Doremas::Doremas()
{}

Doremas::~Doremas()
{}

extern NPCstructure::NPC DoremasNPC;
 
void Doremas::Create( ){
    npc = DoremasNPC;
	SET_NPC_NAME( "[2943]Doremas" );
    npc.InitialPos.X = 1448; 
    npc.InitialPos.Y = 2503;
	npc.InitialPos.world = 0;
}

void Doremas::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT DECISION = 1;

InitTalk

Begin
""
IF (CheckItem(__OBJ_SCROLL_OF_EVIL_DEED) > 1) 
	Conversation
	INTL( 4676, "You have more than one scroll of evil deed? You must discard all but one if you wish "
	"to receive your instructions.")
ELSEIF (CheckItem(__OBJ_SCROLL_OF_EVIL_DEED) == 1)
	GetItemHandle(__OBJ_SCROLL_OF_EVIL_DEED, EvilDeedScroll)		
	IF (CheckUnitFlag( EvilDeedScroll, __ITEM_FLAG_SCROLL_OF_EVIL_DEED ) == CheckFlag(__FLAG_SHADEEN_PLAYER_A))
		Conversation
		INTL( 4677, "You must give the scroll that Shadeen gave you to an accomplice in whom you trust. He or she "
		"will have to create a diversion by robbing the bank's safe.  ")
	ELSEIF ((CheckFlag(__FLAG_SHADEEN_PLAYER_B) != 0) && (CheckFlag(__FLAG_USER_HAS_ROBBED_THE_SAFE_BEFORE) == 0)) 
		Conversation
		INTL( 4678, "You've already been assigned with the mission previously. If you wish to \"abort\" it, just "
		"say so.")
	ELSE
		Conversation
		INTL( 4679, "You have a scroll of evil deed that bears the crest of Shadeen? Lemme read it for a "	
		"a moment.. Humm... nice.. Listen up carefully. You *must* create a diversion to allow "
		"your associate to get past Menark's guards lest you want him to have his skull smashed "
		"by the guards. You have to find the \"combination\" for the bank's safe. This ain't gonna "
		"be that easy. I know this... Rondy has the 1st number, Geram has the 2nd one and.. "
		"only Talon Irongaze knows the 3rd one. *grin* I wish you good luck! Your friend is "
		"counting on you... If you wish not to undertake this task, you can tell me the secret "
		"keyword '\"abort\"' and you'll be able to return to the hole you crawled from. Heh! Heh! "
		"Once you've successfully robbed the bank, you must tell your friend to rush to Menark "
		"for he will have only a few moments before the guards come back.")
		RemFlag(__FLAG_USER_HAS_ROBBED_THE_SAFE_BEFORE) 
		GiveFlag( __FLAG_SHADEEN_PLAYER_B, (CheckUnitFlag ( EvilDeedScroll, __ITEM_FLAG_SCROLL_OF_EVIL_DEED)))					
		TakeItemHandle( EvilDeedScroll )           
		GiveFlag(__QUEST_VAULT_CODE_ONE, rnd.roll(dice(1,49,1))) 
		GiveFlag(__QUEST_VAULT_CODE_TWO, rnd.roll(dice(1,49,1)))
		GiveFlag(__QUEST_VAULT_CODE_THREE, rnd.roll(dice(1,49,1)))
	ENDIF
ELSE
	Conversation
	INTL( 4680, "Heh...")
ENDIF	

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4681, "I don't see how that concerns you.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 7552, "Don't tell me you're here for some \"training\"...")

Command(INTL( 3918, "VISITOR"))
INTL( 4683, "I don't know what you're talking about. Only strange person I've seen is you!")

Command(INTL( 4117, "DOREMAS"))
INTL( 4684, "You would do best to forget that name...")

Command(INTL( 3848, "ZHAKAR"))
INTL( 4685, "Zhakar? I swear I never heard that name before! It's not me! I wasn't the "
"one who murde.. erm... Oh! You just want to know if I heard about him? Uh. "
"No, sorry I cannot help you.") 

Command(INTL( 4686, "SCUM"))
INTL( 4687, "He is my... associate but don't you tell this to anybody. If you do jolthead, I'll cut "
"your sticky tongue with this rusted butter knife!")

Command(INTL( 4115, "GRIMISH"))
""
IF(CheckFlag(__QUEST_KILL_THE_PIGS_COMPLETED) == 2)
	IF (CheckFlag(__QUEST_BALDRIC_SILVERKNIFE) == 0)
		SWITCH(CheckFlag(__FLAG_HAVE_MET_GRIMISH))
			CASE(0)
				Conversation
				INTL( 4688, "That brain-squashed goblin \"scum\"! I clearly told him that he was to meet me here! He has "
				"the nerve of making me wait here like a dim-witted bastard! AH! Wait until I get my hands on "
				"him and I'll show who is the boss around here.") 
			ENDCASE
			CASE(1)		
				Conversation
				INTL( 4689, "You've met Grimish? Where was that pox-marked ratsbane of a goblin is hiding? In a sewers "
				"perhaps? WHAT?! That brainless fool got caught by Ghundarg Rumblefoot? Damnit! I cannot "
				"do anything for him this time, that's for sure!")
				GiveFlag(__FLAG_HAVE_MET_GRIMISH, 2)
			ENDCASE
			CASE(2)
				Conversation			
				INTL( 4690, "What are you doing you miscreant? Seek that tickle-brained pest again "
				"and use force if necessary to get the information I require out of that "
				"useless slime.")
			ENDCASE
			CASE(3)
				Conversation	
				INTL( 4691, "He wants to play a game? He said what? Someone uglier than me? Everybody. I'm "
				"the best looking man you'll ever see. Get back to that boar-face weasel.")				 
			ENDCASE
			CASE(4)
				Conversation
				INTL( 4692, "You must report the password to \"Baldric\" \"Silverknife\" and do whatever he "
				"bids you to to do.")
			GiveFlag(__QUEST_BALDRIC_SILVERKNIFE, 1) 
			ENDCASE
		ENDSWITCH
	ELSEIF (CheckFlag(__QUEST_BALDRIC_SILVERKNIFE) == 1)
		Conversation
		INTL( 4693, "Dog-face? You're still here? What are you waiting for? Go see \"Baldric\" \"Silverknife!\". "
		"Remember the password is the Alliance is Renewed.")
	ELSE
		Conversation
		INTL( 4694, "I don't want to hear anything about him.")
	ENDIF
ELSE
	Conversation
	INTL( 4695, "What we're doing is none of your business.")
ENDIF

Command(INTL( 4696, "COMBINATION"))
""
IF (CheckFlag(__FLAG_SHADEEN_PLAYER_B) != 0)
	Conversation
	INTL( 4697, "Do I look like I know the safe's combination? I've already told you all this before!! Weren't "
	"you listening or what?! Rondy, Geram and Talon Irongaze are the ones you must seek.")	
ELSE	
	Conversation
	INTL( 4698, "Go bore somebody else.")
ENDIF

Command(INTL( 4699, "GERAM"))
INTL( 4700, "If you want to meet him, you'll probably find him crawling on the tavern's floor.")
 
Command(INTL( 4701, "RONDY"))
INTL( 4702, "Do not bother me about this pathetic pig-loving farmer.")

Command2(INTL( 4703, "TALON"),INTL( 4704, "IRONGAZE"))
INTL( 4705, "Don't mess around him too much or you'll get thrown in jail. I tell ya, it ain't the kind of "
"place you want to hang around!") 

Command(INTL( 4706, "ABORT"))
""
IF (CheckFlag(__FLAG_SHADEEN_PLAYER_B) != 0)
	Conversation
	INTL( 4707, "You were supposed to rob the bank to create a diversion, numbskull! Do you really wish to "
	"abort the plan we so carefully elaborated?")
	SetYesNo(DECISION)	
ELSE
	Conversation
	INTL( 4708, "Abort what?")
ENDIF

YES(DECISION)
Conversation
INTL( 11403, "Sure thing, you incompetent fool!")
RemFlag(__FLAG_SHADEEN_PLAYER_B)		  // Doremas removes all flags regarding the Quest of the Bank Diversion. 
RemFlag(__QUEST_VAULT_CODE_ONE)
RemFlag(__QUEST_VAULT_CODE_TWO)
RemFlag(__QUEST_VAULT_CODE_THREE)
///GiveFlag(__QUEST_VAULT_CODE_ONE, rnd.roll(dice(1,50))) 
//GiveFlag(__QUEST_VAULT_CODE_TWO, rnd.roll(dice(1,50)))
//GiveFlag(__QUEST_VAULT_CODE_THREE, rnd.roll(dice(1,50)))

NO(DECISION)
Conversation
INTL( 4709, "Bleah. You are really a coward, you know.")

YesNoELSE(DECISION)
Conversation
INTL( 4710, "Erm. Yeah, whatever you reeky dismal-dreaming scum.")

Command(INTL( 4711, "INSULT ME"))
INTL( 4712, "Sure thing, skipper! You are only a ")

SWITCH(rnd.roll(dice(1,51)))
CASE (1) Conversation INTL( 4713, "artless") ENDCASE
CASE (2) Conversation INTL( 4714, "bawdy") ENDCASE
CASE (3) Conversation INTL( 4715, "beslubbering") ENDCASE
CASE (4) Conversation INTL( 4716, "bootless") ENDCASE
CASE (5) Conversation INTL( 4717, "churlish") ENDCASE
CASE (6) Conversation INTL( 4718, "cockered") ENDCASE
CASE (7) Conversation INTL( 4719, "clouted") ENDCASE
CASE (8) Conversation INTL( 4720, "craven") ENDCASE
CASE (9) Conversation INTL( 4721, "currish") ENDCASE
CASE (10) Conversation INTL( 4722, "dankish") ENDCASE
CASE (11) Conversation INTL( 4723, "dissembling") ENDCASE
CASE (12) Conversation INTL( 4724, "droning") ENDCASE
CASE (13) Conversation INTL( 4725, "errant") ENDCASE
CASE (14) Conversation INTL( 4726, "fawning") ENDCASE
CASE (15) Conversation INTL( 4727, "fobbing") ENDCASE
CASE (16) Conversation INTL( 4728, "froward") ENDCASE
CASE (17) Conversation INTL( 4729, "frothy") ENDCASE
CASE (18) Conversation INTL( 4730, "gleeking") ENDCASE
CASE (19) Conversation INTL( 4731, "goatish") ENDCASE
CASE (20) Conversation INTL( 4732, "gorbellied") ENDCASE
CASE (21) Conversation INTL( 4733, "impertinent") ENDCASE
CASE (22) Conversation INTL( 4734, "infectious") ENDCASE
CASE (23) Conversation INTL( 4735, "jarring") ENDCASE
CASE (24) Conversation INTL( 4736, "loggerheaded") ENDCASE
CASE (25) Conversation INTL( 4737, "lumpish") ENDCASE
CASE (26) Conversation INTL( 4738, "mammering") ENDCASE
CASE (27) Conversation INTL( 4739, "mangled") ENDCASE
CASE (28) Conversation INTL( 4740, "mewling") ENDCASE
CASE (29) Conversation INTL( 4741, "paunchy") ENDCASE
CASE (30) Conversation INTL( 4742, "pribbling") ENDCASE
CASE (31) Conversation INTL( 4743, "puking") ENDCASE
CASE (32) Conversation INTL( 4744, "puny") ENDCASE
CASE (33) Conversation INTL( 4745, "quailing") ENDCASE
CASE (34) Conversation INTL( 4746, "rank") ENDCASE
CASE (35) Conversation INTL( 4747, "reeky") ENDCASE
CASE (36) Conversation INTL( 4748, "roguish") ENDCASE
CASE (37) Conversation INTL( 4749, "ruttish") ENDCASE
CASE (38) Conversation INTL( 4750, "saucy") ENDCASE
CASE (39) Conversation INTL( 4751, "smelly") ENDCASE
CASE (40) Conversation INTL( 4752, "spleeny") ENDCASE
CASE (41) Conversation INTL( 4753, "spongy") ENDCASE
CASE (42) Conversation INTL( 4754, "surly") ENDCASE
CASE (43) Conversation INTL( 4755, "totteting") ENDCASE
CASE (44) Conversation INTL( 4756, "umuzzled") ENDCASE
CASE (45) Conversation INTL( 4757, "vain") ENDCASE
CASE (46) Conversation INTL( 4758, "venomed") ENDCASE
CASE (47) Conversation INTL( 4759, "villainous") ENDCASE
CASE (48) Conversation INTL( 4760, "warped") ENDCASE
CASE (49) Conversation INTL( 4761, "wayward") ENDCASE
CASE (50) Conversation INTL( 4762, "weedy") ENDCASE
CASE (51) Conversation INTL( 4763, "yeasty") ENDCASE
ENDSWITCH
Conversation
INTL( 4764, " ")
SWITCH(rnd.roll(dice(1,50)))
CASE (1) Conversation INTL( 4765, "base-court") ENDCASE
CASE (2) Conversation INTL( 4766, "bat-fowling") ENDCASE
CASE (3) Conversation INTL( 4767, "beef-witted") ENDCASE
CASE (4) Conversation INTL( 4768, "beetle-headed") ENDCASE
CASE (5) Conversation INTL( 4769, "boil-brained") ENDCASE
CASE (6) Conversation INTL( 4770, "clapper-clawed") ENDCASE
CASE (7) Conversation INTL( 4771, "clay-brained") ENDCASE
CASE (8) Conversation INTL( 4772, "common-kissing") ENDCASE
CASE (9) Conversation INTL( 4773, "crook-pated") ENDCASE
CASE (10) Conversation INTL( 4774, "dismal-dreaming") ENDCASE
CASE (11) Conversation INTL( 4775, "dizzy-eyed") ENDCASE
CASE (12) Conversation INTL( 4776, "doghearted") ENDCASE
CASE (13) Conversation INTL( 4777, "dread-bolted") ENDCASE
CASE (14) Conversation INTL( 4778, "earth-vexing") ENDCASE
CASE (15) Conversation INTL( 4779, "elf-skinned") ENDCASE
CASE (16) Conversation INTL( 4780, "fat-kidneyed") ENDCASE
CASE (17) Conversation INTL( 4781, "fen-sucked") ENDCASE
CASE (18) Conversation INTL( 4782, "flap-mouthed") ENDCASE
CASE (19) Conversation INTL( 4783, "fly-bitten") ENDCASE
CASE (20) Conversation INTL( 4784, "folly-fallen") ENDCASE
CASE (21) Conversation INTL( 4785, "fool-born") ENDCASE
CASE (22) Conversation INTL( 4786, "full-gorged") ENDCASE
CASE (23) Conversation INTL( 4787, "guts-griping") ENDCASE
CASE (24) Conversation INTL( 4788, "half-faced") ENDCASE
CASE (25) Conversation INTL( 4789, "hasty-witted") ENDCASE
CASE (26) Conversation INTL( 4790, "hedge-born") ENDCASE
CASE (27) Conversation INTL( 4791, "hell-hated") ENDCASE
CASE (28) Conversation INTL( 4792, "idle-headed") ENDCASE
CASE (29) Conversation INTL( 4793, "ill-breeding") ENDCASE
CASE (30) Conversation INTL( 4794, "ill-nurtured") ENDCASE
CASE (31) Conversation INTL( 4795, "knotty-pated") ENDCASE
CASE (32) Conversation INTL( 4796, "milk-livered") ENDCASE
CASE (33) Conversation INTL( 4797, "motley-minded") ENDCASE
CASE (34) Conversation INTL( 4798, "onion-eyed") ENDCASE
CASE (35) Conversation INTL( 4799, "plume-plucked") ENDCASE
CASE (36) Conversation INTL( 4800, "pottle-deep") ENDCASE
CASE (37) Conversation INTL( 4801, "pox-marked") ENDCASE
CASE (38) Conversation INTL( 4802, "reeling-ripe") ENDCASE
CASE (39) Conversation INTL( 4803, "rough-hewn") ENDCASE
CASE (40) Conversation INTL( 4804, "rude-growing") ENDCASE
CASE (41) Conversation INTL( 4805, "rump-fed") ENDCASE
CASE (42) Conversation INTL( 4806, "shard-borne") ENDCASE
CASE (43) Conversation INTL( 4807, "sheep-biting") ENDCASE
CASE (44) Conversation INTL( 4808, "spur-galled") ENDCASE
CASE (45) Conversation INTL( 4809, "swag-bellied") ENDCASE
CASE (46) Conversation INTL( 4810, "tardy-gaited") ENDCASE
CASE (47) Conversation INTL( 4811, "tickle-brained") ENDCASE
CASE (48) Conversation INTL( 4812, "toad-spotted") ENDCASE
CASE (49) Conversation INTL( 4813, "urchin-snouted") ENDCASE
CASE (50) Conversation INTL( 4814, "weather-bitten") ENDCASE
ENDSWITCH
Conversation
INTL( 4764, " ")
SWITCH(rnd.roll(dice(1,51)))
CASE (1) Conversation INTL( 4815, "apple-john") ENDCASE
CASE (2) Conversation INTL( 4816, "baggage") ENDCASE
CASE (3) Conversation INTL( 4817, "barnacle") ENDCASE
CASE (4) Conversation INTL( 4818, "bladder") ENDCASE
CASE (5) Conversation INTL( 4819, "boar-pig") ENDCASE
CASE (6) Conversation INTL( 4820, "bugbear") ENDCASE
CASE (7) Conversation INTL( 4821, "bum-bailey") ENDCASE
CASE (8) Conversation INTL( 4822, "canker-blossom") ENDCASE
CASE (9) Conversation INTL( 4823, "clack-dish") ENDCASE
CASE (10) Conversation INTL( 4824, "clotpole") ENDCASE
CASE (11) Conversation INTL( 4825, "coxcomb") ENDCASE
CASE (12) Conversation INTL( 4826, "codpiece") ENDCASE
CASE (13) Conversation INTL( 4827, "death-token") ENDCASE
CASE (14) Conversation INTL( 4828, "dewberry") ENDCASE
CASE (15) Conversation INTL( 4829, "flap-dragon") ENDCASE
CASE (16) Conversation INTL( 4830, "flax-wench") ENDCASE
CASE (17) Conversation INTL( 4831, "flirt-gill") ENDCASE
CASE (18) Conversation INTL( 4832, "foot-licker") ENDCASE
CASE (19) Conversation INTL( 4833, "fustilarian") ENDCASE
CASE (20) Conversation INTL( 4834, "giglet") ENDCASE
CASE (21) Conversation INTL( 4835, "gudgeon") ENDCASE
CASE (22) Conversation INTL( 4836, "haggard") ENDCASE
CASE (23) Conversation INTL( 4837, "harpy") ENDCASE
CASE (24) Conversation INTL( 4838, "hedge-pig") ENDCASE
CASE (25) Conversation INTL( 4839, "horn-beast") ENDCASE
CASE (26) Conversation INTL( 4840, "hugger-mugger") ENDCASE
CASE (27) Conversation INTL( 4841, "jolthead") ENDCASE
CASE (28) Conversation INTL( 4842, "lewdster") ENDCASE
CASE (29) Conversation INTL( 4843, "lout") ENDCASE
CASE (30) Conversation INTL( 4844, "maggot-pie") ENDCASE
CASE (31) Conversation INTL( 4845, "malt-worm") ENDCASE
CASE (32) Conversation INTL( 4846, "mammet") ENDCASE
CASE (33) Conversation INTL( 4847, "measle") ENDCASE
CASE (34) Conversation INTL( 4848, "minnow") ENDCASE
CASE (35) Conversation INTL( 4849, "miscreant") ENDCASE
CASE (36) Conversation INTL( 4850, "moldwarp") ENDCASE
CASE (37) Conversation INTL( 4851, "mumble-news") ENDCASE
CASE (38) Conversation INTL( 4852, "nut-hook") ENDCASE
CASE (39) Conversation INTL( 4853, "pigeon-egg") ENDCASE
CASE (40) Conversation INTL( 4854, "pignut") ENDCASE
CASE (41) Conversation INTL( 4855, "puttock") ENDCASE
CASE (42) Conversation INTL( 4856, "pumpion") ENDCASE
CASE (43) Conversation INTL( 4857, "ratsbane") ENDCASE
CASE (44) Conversation INTL( 4858, "scut") ENDCASE
CASE (45) Conversation INTL( 4859, "skainsmate") ENDCASE
CASE (46) Conversation INTL( 4860, "strumpet") ENDCASE
CASE (47) Conversation INTL( 4861, "varlet") ENDCASE
CASE (48) Conversation INTL( 4862, "vassal") ENDCASE
CASE (49) Conversation INTL( 4863, "whey-face") ENDCASE
CASE (50) Conversation INTL( 4864, "wagtail") ENDCASE
CASE (51) Conversation INTL( 4865, "scum") ENDCASE
ENDSWITCH

/*
Command("INSULT ME")
"Sure thing, skipper! You are only a "
SWITCH(rnd.roll(dice(1,10)))
	CASE (1)
		Conversation
		"roguish "
	ENDCASE
	CASE (2)
		Conversation
		"puny "
	ENDCASE
	CASE (3)
		Conversation
		"mangled "
	ENDCASE
	CASE (4)
		Conversation
		"loggerheaded "
	ENDCASE
	CASE (5)
		Conversation
		"lumpish "
	ENDCASE
	CASE (6)
		Conversation
		"frothy "
	ENDCASE
	CASE (7)
		Conversation
		"puking "
	ENDCASE
	CASE (8)
		Conversation
		"smelly "
	ENDCASE
	CASE (9)
		Conversation
		"wayward "
	ENDCASE
	CASE (10)
		Conversation
		"goatish "
	ENDCASE
ENDSWITCH


SWITCH(rnd.roll(dice(1,10)))
	CASE (1)
		Conversation
		"beef-witted "
	ENDCASE
	CASE (2)
		Conversation
		"pox-marked "
	ENDCASE
	CASE (3)
		Conversation
		"fly-bitten "
	ENDCASE
	CASE (4)
		Conversation
		"dog-face "
	ENDCASE
	CASE (5)
		Conversation
		"ill-breeding "
	ENDCASE
	CASE (6)
		Conversation
		"sheep-biting "
	ENDCASE
	CASE (7)
		Conversation
		"bat-fowling "
	ENDCASE
	CASE (8)
		Conversation
		"boil-brained "
	ENDCASE
	CASE (9)
		Conversation
		"beetle-headed "
	ENDCASE
	CASE (10)
		Conversation
		"doghearted "
	ENDCASE
ENDSWITCH


SWITCH(rnd.roll(dice(1,10)))
	CASE (1)
		Conversation
		"boar-pig"
	ENDCASE
	CASE (2)
		Conversation
		"bugbear"
	ENDCASE
	CASE (3)
		Conversation
		"maggot-pie"
	ENDCASE
	CASE (4)
		Conversation
		"wagtail"
	ENDCASE
	CASE (5)
		Conversation
		"jolthead"
	ENDCASE
	CASE (6)
		Conversation
		"haggard"
	ENDCASE
	CASE (7)
		Conversation
		"hugger-mugger"
	ENDCASE
	CASE (8)
		Conversation
		"malt-worm"
	ENDCASE
	CASE (9)
		Conversation
		"clotpole"
	ENDCASE
	CASE (10)
		Conversation
		"ratsbane"
	ENDCASE
ENDSWITCH

*/
Conversation
INTL( 4866, "! Now, out of my face before I kick your hairy lil' bottom.")

Command(INTL( 502, "TRAIN"))
INTL( 7553, "Whatever, just be quick about it!")
CreateSkillList
	AddTrainSkill( __SKILL_ATTACK, 5000, 10 )
	AddTrainSkill( __SKILL_PARRY, 100, 75 )
	AddTrainSkill( __SKILL_DODGE, 5000, 10 )
SendTrainSkillList

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4868, "Hey, look over there!")
IF (Gold > 100)
	TakeGold(Gold / 5) 
ENDIF

Command4(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"))
INTL( 4869, "I'm closing my eyes now, and when I open them you'd better be gone!") BREAK

Default
INTL( 4870, "I've had enough of you.") BREAK

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Doremas::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ATTACK, 5000, 10 )
		TRAIN_SKILL( __SKILL_DODGE, 5000, 10 )
		TRAIN_SKILL( __SKILL_PARRY, 100, 75 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE

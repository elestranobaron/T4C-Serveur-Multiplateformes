#pragma hdrstop
#include "Glaenshenmilandira.h"

Glaenshenmilandira::Glaenshenmilandira()
{}

Glaenshenmilandira::~Glaenshenmilandira()
{}

extern NPCstructure::NPC GlaenshenmilandiraNPC;

void Glaenshenmilandira::Create( void )
{
	npc = GlaenshenmilandiraNPC;
	SET_NPC_NAME( "[10855]Glaenshenmilandira" );
	npc.InitialPos.X = 1965;
	npc.InitialPos.Y = 2815;
	npc.InitialPos.world = 0;
}

void Glaenshenmilandira::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT WILL = 1; 
CONSTANT RechargeHarp = 2;

InitTalk

Begin
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 16)
	IF (CheckFlag( __FLAG_COUNTER_PURIFIER_KILLED) > CheckFlag(__FLAG_COUNTER_NEOFLARE_KILLED) ) 
		Conversation
		INTL( 9173, "I am well aware that you are in dire need of my assistance to create the "
		"Will of Artherk. However, it has come to my attention that you have killed several of "
		"my Purifier friends. This is not an acceptable behavior for a Lightbringer. I will ask "
		"that you kill ") 		
		IF ((CheckFlag(__FLAG_COUNTER_PURIFIER_KILLED) - CheckFlag(__FLAG_COUNTER_NEOFLARE_KILLED)) > 1) 
			Conversation
			FORMAT(INTL( 9174, "%u Neoflares to atone for this deed. Only then will I accept to help you."), (CheckFlag(__FLAG_COUNTER_PURIFIER_KILLED) - CheckFlag(__FLAG_COUNTER_NEOFLARE_KILLED)))	                     	   
		ELSE
			Conversation
			INTL( 9175, "1 Neoflare to atone for this deed. Only then will I accept to help you.")			
		ENDIF 				
	ELSE
		Conversation
		INTL( 9178, "You are here in the Nether Isles because you need me to create the Will of Artherk for "
		"you, aren't you? I do not believe you know what this is all about, or what you are going "
		"to lose if you stay on this path, but there are great rewards for he who persists. Steel "
		"your will and you shall prevail. Now, will you give me those items so that I create this "
		"jewel you need?")
		SetYesNo(WILL) 
	ENDIF 
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 17)
	Conversation
	INTL( 9179, "You already have obtained the Will of Artherk. You can now \"return\" "
	"to Stonecrest and complete your quest.")
ELSE
	Conversation
	INTL( 9180, "I have nothing to say to you.")		
ENDIF 
	
YES(WILL)
   //;int nNumKeys = CheckItem( __OBJ_ETHEREAL_KEY); 
	//FOR(0, nNumKeys)
	//	TakeItem(__OBJ_ETHEREAL_KEY) 
	//ENDFOR
	;int nNumFangs = CheckItem(__OBJ_FANG_OF_TRUE_RESOLVE); 
	FOR(0, nNumFangs )
		TakeItem(__OBJ_FANG_OF_TRUE_RESOLVE)
	ENDFOR
	;int nNumHammers = CheckItem(__OBJ_HAMMER_OF_FINALITY);
	FOR(0, nNumHammers )
		TakeItem(__OBJ_HAMMER_OF_FINALITY)
	ENDFOR
	;int nNumDrums = CheckItem(__OBJ_DRUM_OF_FATE);
	FOR(0,  nNumDrums )
		TakeItem(__OBJ_DRUM_OF_FATE)
	ENDFOR
   GiveFlag(__QUEST_FLAG_ARTHERK_WILL, 1) 
	GiveItem(__OBJ_WILL_OF_ARTHERK)
	GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 17) 
	Conversation
	INTL( 9181, "Artherk has granted me the ability to merge these items into the holy "
	"\"Will\" \"of\" \"Artherk\". Here, it is now yours. You can now \"return\" "
	"to Stonecrest and complete your quest.")	
	CastSpellTarget(__SPELL_NPC_CANTRIP_BLUE_WIPE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9182, "You give the Hammers of Finality, the Drums of Fate and the Fangs of True Resolve to Glaenshenmilandira."))	
	PRIVATE_SYSTEM_MESSAGE(INTL( 9183, "Glaenshenmilandira gives you the Will of Artherk."))
	;int nExpReward = 250000; 	
	PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) )
	GiveXP(nExpReward)
	//PRIVATE_SYSTEM_MESSAGE(INTL( 9184, "Your ethereal key crumbles to dust!"))
NO(WILL)
	Conversation
	INTL( 8220, "Come back if you ever change your mind.")	 

YesNoELSE(WILL)
	Conversation
	INTL( 9185, "Do you need the Will of Artherk or not?")
	SetYesNo(WILL) 

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9186, "I am Glaenshenmilandira, a seraph of Artherk.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 9187, "I am a Seraph of Artherk. I do not usually have to interact with mortals and I "
"do not need to do mundane chores as you do.") 

Command(INTL( 9188, "PURIFIER")) 
INTL( 9189, "The purifiers are holy souls that have for purpose to maintain an acceptable amount of "
"nether monsters around here. Bear them malice, and you'll feel sorry.")

Command(INTL( 9190, "NEOFLARE"))
INTL( 9191, "The neoflares are powerful nether creatures that roam these isles. Even my \"purifiers\" " 
"are not strong enough to eradicate these vile monsters.")

CmdAND(INTL( 9205, "LUTE"),INTL( 8182, "PEACE"))
""
SWITCH(CheckFlag(__QUEST_DIONYSUS_RECHARGE_HARP))
	CASE(1)
		Conversation
		INTL( 9192, "Indeed, you have come to the right person to have the Lute of Peace recharged. "
		"Unfortunately, my power alone will not suffice, so I would ask that you bring me "
		"as many \"Magical\" \"Lutes\" as you can--bring at *least* six. The more you bring, "
		"the better the odds that I'll succeed at recharging the Lute of Peace.")
		GiveFlag(__QUEST_DIONYSUS_RECHARGE_HARP, 2)
	ENDCASE
	CASE(2)
		IF(CheckItem(__OBJ_MAGICAL_LUTE) >= 6)
			Conversation
			INTL( 9193, "I see you've got enough Magical Lutes for me to attempt to recharge the "
			"Lute of Peace. Shall we try this now?")
			SetYesNo(RechargeHarp)
		ELSE
			Conversation
			INTL( 9194, "I will need many \"Magical\" \"Lutes\" in order to recharge the lute. I need "
			"at least six, but my odds of success increase if you bring me more than that.")
			//Design note: odds of success = 30% + 5% per Magical Lute, min. 6 Lutes req'd.
		ENDIF
	ENDCASE
	CASE(3)
		Conversation
		INTL( 9195, "I already recharged the Lute, now please take it back to your friend Dionysos.")
	ENDCASE
	OTHERWISE
		IF (rnd.roll(dice(1,2) ) == 1)
		   Conversation
		   INTL( 9196, "This does not concern me.")
		ELSE
		   Conversation
		   INTL( 9197, "What can I say?")
		ENDIF
	ENDCASE
ENDSWITCH

YES(RechargeHarp)
	IF(CheckItem(__OBJ_MAGICAL_LUTE) >= 6)
		;int nNumLutes = CheckItem(__OBJ_MAGICAL_LUTE);
		FOR(0,nNumLutes) 
			TakeItem(__OBJ_MAGICAL_LUTE)
		ENDFOR
		PRIVATE_SYSTEM_MESSAGE(INTL( 9198, "You give the Seraph all your Magical Lutes."))
		Conversation
		FORMAT(INTL( 9199, "Thank you. You gave me %u Magical Lutes, so my odds of "
		"success are %u percent. Let me try this, now... "), nNumLutes, 30 + (nNumLutes * 5))
		IF(rnd.roll(dice(1,100)) <= (30 + (nNumLutes * 5)))
			Conversation
			INTL( 9200, "Yes!! It worked! Here's your Lute of Peace.")
			GiveFlag(__QUEST_DIONYSUS_RECHARGE_HARP, 3)
			;int nExpReward = USER_LEVEL*2000;
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
			GiveXP(nExpReward)
		ELSE
			Conversation
			INTL( 9201, "I'm sorry, the magical energies were too volatile and I failed. You must "
			"get me new Magical Lutes, I'm afraid.")
		ENDIF
	ELSE
		Conversation
		INTL( 9202, "Only ask me to do this if you *really* have six or more Magical Lutes.")
		BREAK
	ENDIF

NO(RechargeHarp)
	Conversation
	INTL( 9203, "Fine with me.")

YesNoELSE(RechargeHarp)
	Conversation
	INTL( 9204, "Ask again when you've made up your mind.")
	BREAK

CmdAND(INTL( 1096, "MAGIC"),INTL( 9205, "LUTE"))
INTL( 9206, "Magical Lutes are often the instrument of choice of the Death Jester. I doubt he "
"will part with it without a fight, however.")

Command(INTL( 6167, "RETURN"))
INTL( 8497, "See you around.")
CastSpellTarget(__SPELL_NPC_CANTRIP_BLUE_WIPE)
TELEPORT(205,671,0)
PRIVATE_SYSTEM_MESSAGE(INTL( 9177, "You feel somewhat dizzy after being translocated somewhere on Stoneheim."))
BREAK

Command(INTL( 9207, "WILL OF ARTHERK"))
INTL( 9208, "The Will of Artherk represents the drive and passion one must have to "
"truly change the world and the way people think.")

Command5(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 1919, "WHORE"),INTL( 698, " ASS "))
INTL( 9209, "If you'd had wings, I'd clip 'em right now!")
BREAK 

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll(dice(1,2) ) == 1)
   Conversation
   INTL( 9196, "This does not concern me.")
ELSE
   Conversation
   INTL( 9197, "What can I say?")
ENDIF

EndTalk
}

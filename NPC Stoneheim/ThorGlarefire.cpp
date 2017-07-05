#pragma hdrstop
#include "ThorGlarefire.h"
 
ThorGlarefire::ThorGlarefire()
{}

ThorGlarefire::~ThorGlarefire()
{}

extern NPCstructure::NPC ThorGlarefireNPC;

void ThorGlarefire::Create( ){
	npc = ThorGlarefireNPC;
	SET_NPC_NAME( "[10930]A busy blacksmith" );
	npc.InitialPos.X = 900; 
	npc.InitialPos.Y = 1070;
	npc.InitialPos.world = 0;
}

void ThorGlarefire::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT BROWSE = 1;
CONSTANT SWORDOFMAJESTY = 2; 
	
InitTalk

Begin					  
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 9)
	Conversation
	INTL( 10012, "You're bringing a friend along? Get him out of my shop and we'll talk!")
	SUMMON("MOBSHADOWSTALKER", FROM_USER(1, X), FROM_USER(1, Y) ) 	
	PRIVATE_SYSTEM_MESSAGE(INTL( 9750, "You sense some evil lurking nearby, sending shivers up your spine."))
	GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 10) 
	BREAK
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 10) 
	Conversation
	INTL( 10013, "I have to say that you have some peculiar friends. Hopefully, they won't come back for a while but you should "
	"watch your back. \"Mordenthal\" is obviously trying to prevent you from completing your quest.")
	GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 11) 
ELSE
	Conversation
	INTL( 10014, "A good day to you, friend. How may I be of service?")
	GiveNPCFlag( __FLAG_PC_HAS_SPENT, Gold)
ENDIF 

CmdAND(INTL( 5672, "HAMMER"), INTL( 8050, "FINALITY"))
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 11) 
	Conversation
	INTL( 10015, "Alas, even I cannot forge a hammer of finality. Fortunately, I know one of your kin that has the ability to "
	"create one. The man who can do them for you is \"Lance\" \"Silversmith\", a former pupil of mine  who now lives in "
	"Arakas. Bring him this letter from me and he will tell you what you need to make them.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 10016, "Thor gives you a tightly-wrapped parchment.")) 
	GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 12) 
	GiveItem(__OBJ_SILVERSMITH_LETTER) 
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 12) 
	Conversation
	INTL( 10794, "I've already told you what you need to know. Now, you should depart to Arakas where "
	"you are to meet with an old apprentice of mine, \"Lance\" \"Silversmith\".")
ELSE
	Conversation
	INTL( 10017, "You wouldn't know what to do with a hammer of finality.")
ENDIF

// __QUEST_FLAG_WILL_OF_ARTHERK_QUEST 
// 0: -- 
// 1: Spoken with Beltigan. Beowulf is told to seek counsel of Aedenas Gravesoul.
// 2: Spoken with Aedenas. Beowulf is told to seek the White Crow to fetch the Fangs of True Resolve. 
// 3: Spoken with Mithanna Snowraven. She requires a Jade Ring of Sorcery + a dozen of Kraanian eyes.
// 4: Brought back the required components, Mithanna Snowraver tells Beowulf that he must seek Nissus Haloseeker.  
// 5: Spoken with Nissus and the Fangs are on their way. 
// 6: The last fang is created and the Night Retrievers are summoned. If they successfully steal a Fangs, this Flag
// is reduced to 5 and minus one fang. 
// 7: Spoken with King Aedenas, told about Zion Thunderheart's betrayal 
// 8: Gotten the staff of submission from King Aedenas and sent on the quest to get mind control talisman 
// 9: Gotten all 12 talismans and brought them back to the centaur king. 

Command(INTL( 10018, "SILVERSMITH"))
INTL( 10019, "Lance Silversmith is a former pupil of mine who now lives somewhere in Arakas.")

Command(INTL( 8610, "MORDENTHAL"))
INTL( 10020, "Mordenthal is one of your kin who has chosen the path of dark.") 

Command2(INTL( 483, "NAME"), INTL( 485, "WHO ARE YOU"))
INTL( 10021, "Amongst my people, I am known as Thor of the iron arm, but you may call me Thor Glarefire.")

Command(INTL( 10022, "THOR GLAREFIRE"))
INTL( 10023, "Yes, that is my name. What may I do for you?")

Command2(INTL( 1072, "KING"),INTL( 7998, "GRAVESOUL"))
INTL( 10024, "He's our lord and liege, and we owe him loyalty and obedience. If you've got a problem "
"with that, get out of my shop.")

Command2(INTL( 8001, "ZION"),INTL( 8002, "THUNDERHEART"))
INTL( 10025, "Scum like him shouldn't be allowed to stay among us. We all know he is a traitor, but our king "
"refuses to break the law just to have him executed. But we will wait patiently for the day "
"he makes a mistake, and *then* we will have him judged for his crimes.")

Command2(INTL( 8005, "KYATHOS"),INTL( 8006, "SHATTERSKULL"))
INTL( 10026, "He's my best customer! If there were more people like him, I wouldn't be a pauper! Heh heh... I'm "
"kidding, Kyathos has made me a fairly well-to-do fellow, really. I can't complain.")

Command2(INTL( 8013, "DIONYSUS"),INTL( 8014, "SILVERSTREAM"))
INTL( 10027, "He's a little weepy for my taste, but I can't find much fault with him. We're grateful to have him "
"when trouble starts brewing.")

Command2(INTL( 8046, "MALACHAI"),INTL( 8047, "FATEBRINGER"))
INTL( 10028, "There isn't much to talk about. Actually, that's all there is to TALK about. That's all he "
"does, talk, *talk*, TALK! He's a big talker, but I've yet to see him in action. So yes, I think "
"he's all smoke and no fire.")

Command2(INTL( 8017, "GLADDIUS"),INTL( 8018, "WINDCHASER"))
INTL( 10029, "It's just a matter of time before he becomes a regular customer of mine, just like Kyathos. "
"Gladdius professes his belief in skill over equipment, but I know with Kyathos bragging about "
"how good he is, Gladdius will eventually cave in and start buying my equipment.")

Command3(INTL( 489, "WORK"), INTL( 3696, "WHAT DO YOU DO"), INTL( 487, "OCCUPATION"))
INTL( 10030, "Seeing as how I am very busy, I would appreciate it if you would make up your mind on what "
"you wish to buy. My wares are of the finest quality, you know.")

CmdAND(INTL( 10795, "HERO"),INTL( 7985, "BLADE"))
INTL( 10796, "You are quite capable of finding these on your own.") 

CmdAND(INTL( 8090, "RED"),INTL( 759, "SPELLBOOK")) 
INTL( 10797, "The red spellbooks are used by some spell casters on Stoneheim. Particularly, the skraugs are " 
"very fond of the primitive magic they contain.") 

CmdAND(INTL( 4880, "SWORD"),INTL( 3990, "MAJESTY"))
INTL( 10032, "Crafting a sword of majesty is one of my specialty. However, I cannot forge one unless I have "
"five \"red\" \"spellbooks\" and three \"hero's\" \"blades\".")
IF ((CheckItem(__OBJ_RED_SPELLBOOK) >= 5) && (CheckItem(__OBJ_BLADE_OF_HEROISM) >= 3))
	Conversation
	INTL( 10033, " Hmm. I see that you have everything that is required. Shall I begin the forging of "
	"the sword in question?")
	SetYesNo(SWORDOFMAJESTY) 
ELSE
	Conversation
	INTL( 10034, " If you can get these, then I'll gladly craft a sword of majesty for you.")
ENDIF

YES(SWORDOFMAJESTY) 
	IF ((CheckItem(__OBJ_RED_SPELLBOOK) < 5) || (CheckItem(__OBJ_BLADE_OF_HEROISM) < 3))
		Conversation	
		INTL( 10035, "I shall repeat my instructions, for it seems that you were not paying much attention. To make the sword you "
		"require, I will need five \"red\" \"spellbooks\" and three \"hero's\" \"blades\".") 		
	ELSE
		Conversation				  
		INTL( 10036, "Here you are then. The sword of majesty is of such power than no one -- not even you -- can "
		"truly wield it. Now off with you so that I may return to my work.")
		PRIVATE_SYSTEM_MESSAGE(INTL( 10037, "Thor gives you a sword of majesty.")) 
		FOR(0,5) 
			TakeItem(__OBJ_RED_SPELLBOOK)
		ENDFOR	
		FOR(0,3) 
			TakeItem(__OBJ_BLADE_OF_HEROISM)	
		ENDFOR
		GiveItem(__OBJ_SWORD_OF_MAJESTY)
	ENDIF

NO(SWORDOFMAJESTY)
	Conversation
	INTL( 10038, "So be it then. I was too busy to do it today anyway.")

YesNoELSE(SWORDOFMAJESTY)
	Conversation
	INTL( 10039, "Have you everything that is required?")
	SetYesNo(SWORDOFMAJESTY)

Command2(INTL( 1304, "BUY"), INTL( 7195, "PURCHASE"))
INTL( 10040, "A customer eh? Very well, but make it brief. I did not make all these wonderful weapons by watching customers you know."
"Well then, will you take a look at what I have to sell?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 292803,  __OBJ_HIGH_METAL_LONG_SWORD_1 )
		AddBuyItem( 339489,  __OBJ_HIGH_METAL_BROADSWORD_1 )
		AddBuyItem( 389622,  __OBJ_HIGH_METAL_SCIMITAR_1 )
		AddBuyItem( 443211,  __OBJ_HIGH_METAL_BASTARD_SWORD_1 )
      AddBuyItem( 443211,  __OBJ_HIGH_METAL_BASTARD_SWORD1_DUAL )
		AddBuyItem( 443211,  __OBJ_HIGH_METAL_HAND_AXE_1 )
		AddBuyItem( 560739,  __OBJ_HIGH_METAL_BATTLE_AXE_1 )
		AddBuyItem( 173463,  __OBJ_MITHRIL_DAGGER_1 )
		AddBuyItem( 249573,  __OBJ_MITHRIL_BLADE_1 )
      AddBuyItem( 249573,  __OBJ_MITHRIL_BLADE1_DUAL )
		AddBuyItem( 443211,  __OBJ_MITHRIL_FLAIL_1 )
		AddBuyItem( 976010,  __OBJ_HIGH_METAL_LONG_SWORD_2 )
		AddBuyItem( 1131630, __OBJ_HIGH_METAL_BROADSWORD_2 )
		AddBuyItem( 1298740, __OBJ_HIGH_METAL_SCIMITAR_2 )
		AddBuyItem( 1477370, __OBJ_HIGH_METAL_BASTARD_SWORD_2 )
      AddBuyItem( 1477370, __OBJ_HIGH_METAL_BASTARD_SWORD2_DUAL )
		AddBuyItem( 1477370, __OBJ_HIGH_METAL_HAND_AXE_2 )
		AddBuyItem( 1869130, __OBJ_HIGH_METAL_BATTLE_AXE_2 )
		AddBuyItem( 578210,  __OBJ_MITHRIL_DAGGER_2 )
		AddBuyItem( 831910,  __OBJ_MITHRIL_BLADE_2 )
      AddBuyItem( 831910,  __OBJ_MITHRIL_BLADE2_DUAL )
		AddBuyItem( 1477370, __OBJ_MITHRIL_FLAIL_2 )
		AddBuyItem( 339489, __OBJ_OAK_FLATBOW_1 )
		AddBuyItem( 389622, __OBJ_OAK_LONGBOW_1 )
		AddBuyItem( 443211, __OBJ_OAK_REFLEX_BOW_1 )
		AddBuyItem( 500247, __OBJ_OAK_RECURVE_BOW_1 )
		AddBuyItem( 560739, __OBJ_OAK_COMPOUND_BOW_1 )
		AddBuyItem( 624678, __OBJ_OAK_COMPOSITE_BOW_1 )
		AddBuyItem( 1131630, __OBJ_OAK_FLATBOW_2 )
		AddBuyItem( 1298740, __OBJ_OAK_LONGBOW_2 )
		AddBuyItem( 1477370, __OBJ_OAK_REFLEX_BOW_2 )
		AddBuyItem( 1667490, __OBJ_OAK_RECURVE_BOW_2 )
		AddBuyItem( 1869130, __OBJ_OAK_COMPOUND_BOW_2 )
		AddBuyItem( 2082260, __OBJ_OAK_COMPOSITE_BOW_2 )
	SendBuyItemList
NO(BROWSE)
	Conversation
	INTL( 10041, "Well, I believe you have no business here then.")
YesNoELSE(BROWSE)
	Conversation
	INTL( 10042, "Will you look at what I have for sale or not?")
	SetYesNo(BROWSE)

Command(INTL( 1306, "SELL"))
INTL( 10043, "You are keeping me from my work, you know. This had better be good.")
CreateItemList
	AddSellItem( WEAPON, 0, 100000 )
	AddSellItem( JEWEL | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList( INTL( 10044, "I really don't see anything I would want in there. You are wasting my time.") )

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 10045, "Leave this place now before you disgrace yourself any further!")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
""
IF(Gold < CheckNPCFlag( __FLAG_PC_HAS_SPENT ))
	Conversation
	INTL( 10046, "At least you were not a total waste of my time. Don't come back unless you want to buy "
	"something else!") BREAK
ELSEIF(Gold == CheckNPCFlag( __FLAG_PC_HAS_SPENT ))
	Conversation
	INTL( 10047, "Watching you leave this place will be the high point of my day.") BREAK
ELSE
	Conversation
	INTL( 10048, "Alright, you have sold me what you wanted to sell, now off with you!") BREAK
ENDIF

Default
INTL( 10049, "I have no time for this! If you have nothing intelligent to say then leave me be!")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void ThorGlarefire::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
{
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

		NPC_SELL( 292803,  __OBJ_HIGH_METAL_LONG_SWORD_1 )
		NPC_SELL( 339489,  __OBJ_HIGH_METAL_BROADSWORD_1 )
		NPC_SELL( 389622,  __OBJ_HIGH_METAL_SCIMITAR_1 )
		NPC_SELL( 443211,  __OBJ_HIGH_METAL_BASTARD_SWORD_1 )
      NPC_SELL( 443211,  __OBJ_HIGH_METAL_BASTARD_SWORD1_DUAL )
		NPC_SELL( 443211,  __OBJ_HIGH_METAL_HAND_AXE_1 )
		NPC_SELL( 560739,  __OBJ_HIGH_METAL_BATTLE_AXE_1 )
		NPC_SELL( 173463,  __OBJ_MITHRIL_DAGGER_1 )
		NPC_SELL( 249573,  __OBJ_MITHRIL_BLADE_1 )
      NPC_SELL( 249573,  __OBJ_MITHRIL_BLADE1_DUAL )
		NPC_SELL( 443211,  __OBJ_MITHRIL_FLAIL_1 )
		NPC_SELL( 976010,  __OBJ_HIGH_METAL_LONG_SWORD_2 )
		NPC_SELL( 1131630, __OBJ_HIGH_METAL_BROADSWORD_2 )
		NPC_SELL( 1298740, __OBJ_HIGH_METAL_SCIMITAR_2 )
		NPC_SELL( 1477370, __OBJ_HIGH_METAL_BASTARD_SWORD_2 )
      NPC_SELL( 1477370, __OBJ_HIGH_METAL_BASTARD_SWORD2_DUAL )
		NPC_SELL( 1477370, __OBJ_HIGH_METAL_HAND_AXE_2 )
		NPC_SELL( 1869130, __OBJ_HIGH_METAL_BATTLE_AXE_2 )
		NPC_SELL( 578210,  __OBJ_MITHRIL_DAGGER_2 )
		NPC_SELL( 831910,  __OBJ_MITHRIL_BLADE_2 )
      NPC_SELL( 831910,  __OBJ_MITHRIL_BLADE2_DUAL )
		NPC_SELL( 1477370, __OBJ_MITHRIL_FLAIL_2 )
		NPC_SELL( 339489, __OBJ_OAK_FLATBOW_1 )
		NPC_SELL( 389622, __OBJ_OAK_LONGBOW_1 )
		NPC_SELL( 443211, __OBJ_OAK_REFLEX_BOW_1 )
		NPC_SELL( 500247, __OBJ_OAK_RECURVE_BOW_1 )
		NPC_SELL( 560739, __OBJ_OAK_COMPOUND_BOW_1 )
		NPC_SELL( 624678, __OBJ_OAK_COMPOSITE_BOW_1 )
		NPC_SELL( 1131630, __OBJ_OAK_FLATBOW_2 )
		NPC_SELL( 1298740, __OBJ_OAK_LONGBOW_2 )
		NPC_SELL( 1477370, __OBJ_OAK_REFLEX_BOW_2 )
		NPC_SELL( 1667490, __OBJ_OAK_RECURVE_BOW_2 )
		NPC_SELL( 1869130, __OBJ_OAK_COMPOUND_BOW_2 )
		NPC_SELL( 2082260, __OBJ_OAK_COMPOSITE_BOW_2 )

		NPC_BUY( WEAPON, 0, 100000 )
		NPC_BUY( JEWEL | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 10050, "Well, here is the weapon you wanted, now off with you!") )
		NPC_FAILED_SELL( INTL( 10051, "Argh! What a waste of my time! You don't even have enough gold!") )
		NPC_BOUGHT_ITEM( INTL( 10052, "Yes yes, here is your money... now off you go!") )

	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
}
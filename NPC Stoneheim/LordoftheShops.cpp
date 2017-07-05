#pragma hdrstop
#include "LordoftheShops.h"

LordoftheShops::LordoftheShops()
{}

LordoftheShops::~LordoftheShops()
{}

extern NPCstructure::NPC LordoftheShopsNPC;

void LordoftheShops::Create( void )
{
	npc = LordoftheShopsNPC;
	SET_NPC_NAME( "[11523]Lord of the Shops" );
	npc.InitialPos.X = 715;
	npc.InitialPos.Y = 865;
	npc.InitialPos.world = 0;
}

void LordoftheShops::OnPopup( UNIT_FUNC_PROTOTYPE ){
		
	CastSpellSelf(__SPELL_MOB_LORD_OF_THE_SHOPS_TELEPORT_SPELL)

NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}
				 
void LordoftheShops::OnTalk( UNIT_FUNC_PROTOTYPE )

// TO DO LIST:
//
// * Make sure the user is aware that he's got 60 seconds to finish his transaction.
// * Implement that 60 seconds limit
// * Give the NPC about a dozen coordinates to randomly teleport to after the transaction.
// * Make sure the NPC stays "private."
// * Make the NPC disappear if "BYE" or curse words are used during the conversation.
// Invisible priest = 21044 (for monsterstatsetup)
{

InitTalk

Begin
""
IF(CheckNPCFlag(__NPC_FLAG_LORD_OF_THE_SHOPS_TIMER) == 0)
	GiveNPCFlag(__NPC_FLAG_LORD_OF_THE_SHOPS_TIMER, 1)
	CastSpellSelf(__SPELL_MOB_LORD_OF_THE_SHOPS_TELEPORT_SPELL)
	Conversation
	INTL( 11382, "Let's make this short, I'm a very busy man!")
ELSE
	Conversation
	INTL( 11383, "Hurry up, I don't have much time.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 11384, "I am... the LORD OF THE SHOPS!")
PRIVATE_SYSTEM_MESSAGE(INTL( 11385, "You hear the sound of thunder in the background."))

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 11386, "I sell \"unique\" \"items\" you can't find anywhere else in the world.")

CmdAND(INTL( 11387, "UNIQUE"),INTL( 923, "ITEM"))
INTL( 11388, "I have a \"wide\" \"selection\" of very special items. Other vendors won't even buy them from you. "
"Once you have them, they remain yours.")

CmdAND(INTL( 11389, "WIDE"),INTL( 11390, "SELECTION"))
INTL( 11391, "You can choose between \"bows\", \"melee\" \"weapons\", \"shields\" and \"armors\". "
"Once you've decided to buy from a selection, just say \"buy\" and your selection. "
"For instance, if you want to buy melee weapons, just say \"buy\" \"melee\" \"weapons\".")

CmdAND(INTL( 1304, "BUY"),INTL( 7994, "BOW"))
INTL( 11392, "We have just the bow for you!")
CreateItemList
	AddBuyItem( 762915/**0.75*/, __OBJ_CEDAR_LONGBOW_1 )
	AddBuyItem( 2543050/**0.75*/, __OBJ_CEDAR_LONGBOW_2 )
	AddBuyItem( 279071/**0.75*/, __OBJ_CEDAR_REFLEX_BOW )
	AddBuyItem( 837213/**0.75*/, __OBJ_CEDAR_REFLEX_BOW_1 )
	AddBuyItem( 2790710/**0.75*/, __OBJ_CEDAR_REFLEX_BOW_2 )
	AddBuyItem( 304986/**0.75*/, __OBJ_CEDAR_RECURVE_BOW )
	AddBuyItem( 914958/**0.75*/, __OBJ_CEDAR_RECURVE_BOW_1 )
	AddBuyItem( 3049860/**0.75*/, __OBJ_CEDAR_RECURVE_BOW_2 )
	AddBuyItem( 332053/**0.75*/, __OBJ_CEDAR_COMPOUND_BOW )
	AddBuyItem( 996159/**0.75*/, __OBJ_CEDAR_COMPOUND_BOW_1 )
	AddBuyItem( 3320530/**0.75*/, __OBJ_CEDAR_COMPOUND_BOW_2 )
	AddBuyItem( 360269/**0.75*/, __OBJ_CEDAR_COMPOSITE_BOW )
	AddBuyItem( 1080807/**0.75*/, __OBJ_CEDAR_COMPOSITE_BOW_1 )
	AddBuyItem( 3602690/**0.75*/, __OBJ_CEDAR_COMPOSITE_BOW_2 )
	AddBuyItem( 14410760/**0.75*/, __OBJ_CEDAR_COMPOSITE_BOW_3 )
	AddBuyItem( 420154/**0.75*/, __OBJ_LANCEWOOD_REFLEX_BOW )
	AddBuyItem( 1260462/**0.75*/, __OBJ_LANCEWOOD_REFLEX_BOW_1 )
	AddBuyItem( 4201540/**0.75*/, __OBJ_LANCEWOOD_REFLEX_BOW_2 )
	AddBuyItem( 451823/**0.75*/, __OBJ_LANCEWOOD_RECURVE_BOW )
	AddBuyItem( 1355469/**0.75*/, __OBJ_LANCEWOOD_RECURVE_BOW_1 )
	AddBuyItem( 4518230/**0.75*/, __OBJ_LANCEWOOD_RECURVE_BOW_2 )
	AddBuyItem( 484641/**0.75*/, __OBJ_LANCEWOOD_COMPOUND_BOW )
	AddBuyItem( 1453923/**0.75*/, __OBJ_LANCEWOOD_COMPOUND_BOW_1 )
	AddBuyItem( 4846410/**0.75*/, __OBJ_LANCEWOOD_COMPOUND_BOW_2 )
	AddBuyItem( 518611/**0.75*/, __OBJ_LANCEWOOD_COMPOSITE_BOW )
	AddBuyItem( 1555833/**0.75*/, __OBJ_LANCEWOOD_COMPOSITE_BOW_1 )
	AddBuyItem( 5186110/**0.75*/, __OBJ_LANCEWOOD_COMPOSITE_BOW_2 )
	AddBuyItem( 20744440/**0.75*/, __OBJ_LANCEWOOD_COMPOSITE_BOW_3 )
	AddBuyItem( 665993/**0.75*/, __OBJ_BLACK_LOCUST_RECURVE_BOW )
	AddBuyItem( 1997979/**0.75*/, __OBJ_BLACK_LOCUST_RECURVE_BOW_1 )
	AddBuyItem( 6659930/**0.75*/, __OBJ_BLACK_LOCUST_RECURVE_BOW_2 )
	AddBuyItem( 788609/**0.75*/, __OBJ_BLACK_LOCUST_COMPOUND_BOW )
	AddBuyItem( 2365827/**0.75*/, __OBJ_BLACK_LOCUST_COMPOUND_BOW_1 )
	AddBuyItem( 7886090/**0.75*/, __OBJ_BLACK_LOCUST_COMPOUND_BOW_2 )
	AddBuyItem( 921581/**0.75*/, __OBJ_BLACK_LOCUST_COMPOSITE_BOW )
	AddBuyItem( 2764743/**0.75*/, __OBJ_BLACK_LOCUST_COMPOSITE_BOW_1 )
	AddBuyItem( 9215810/**0.75*/, __OBJ_BLACK_LOCUST_COMPOSITE_BOW_2 )
SendBuyItemList

CmdAND3(INTL( 1304, "BUY"),INTL( 11393, "MELEE"),INTL( 914, "WEAPON"))
INTL( 11394, "We have just the weapon for you!")
CreateItemList
	AddBuyItem( 692073/**0.75*/, __OBJ_MITHRIL_MORNINGSTAR_1 )
	AddBuyItem( 2306910/**0.75*/, __OBJ_MITHRIL_MORNINGSTAR_2 )
	AddBuyItem( 9227640/**0.75*/, __OBJ_MITHRIL_MORNINGSTAR_3 )
	AddBuyItem( 360269/**0.75*/, __OBJ_ANCIENT_MORNINGSTAR )
	AddBuyItem( 1080807/**0.75*/, __OBJ_ANCIENT_MORNINGSTAR_1 )
	AddBuyItem( 3602690/**0.75*/, __OBJ_ANCIENT_MORNINGSTAR_2 )
	AddBuyItem( 230691/**0.75*/, __OBJ_HIGH_METAL_BROAD_AXE )
	AddBuyItem( 692073/**0.75*/, __OBJ_HIGH_METAL_BROAD_AXE_1 )
	AddBuyItem( 2306910/**0.75*/, __OBJ_HIGH_METAL_BROAD_AXE_2 )
	AddBuyItem( 9227640/**0.75*/, __OBJ_HIGH_METAL_BROAD_AXE_3 )
	AddBuyItem( 332053/**0.75*/, __OBJ_MITHRIL_BATTLE_AXE )
	AddBuyItem( 996159/**0.75*/, __OBJ_MITHRIL_BATTLE_AXE_1 )
	AddBuyItem( 3320530/**0.75*/, __OBJ_MITHRIL_BATTLE_AXE_2 )
	AddBuyItem( 451823/**0.75*/, __OBJ_MITHRIL_BROAD_AXE )
	AddBuyItem( 1355469/**0.75*/, __OBJ_MITHRIL_BROAD_AXE_1 )
	AddBuyItem( 4518230/**0.75*/, __OBJ_MITHRIL_BROAD_AXE_2 )
	AddBuyItem( 18072920/**0.75*/, __OBJ_MITHRIL_BROAD_AXE_3 )
	AddBuyItem( 921581/**0.75*/, __OBJ_ANCIENT_BROAD_AXE )
	AddBuyItem( 2764743/**0.75*/, __OBJ_ANCIENT_BROAD_AXE_1 )
	AddBuyItem( 9215810/**0.75*/, __OBJ_ANCIENT_BROAD_AXE_2 )
	AddBuyItem( 186913/**0.75*/, __OBJ_MITHRIL_LONG_SWORD )
	AddBuyItem( 560739/**0.75*/, __OBJ_MITHRIL_LONG_SWORD_1 )
	AddBuyItem( 1869130/**0.75*/, __OBJ_MITHRIL_LONG_SWORD_2 )
	AddBuyItem( 208226/**0.75*/, __OBJ_MITHRIL_BROADSWORD )
	AddBuyItem( 624678/**0.75*/, __OBJ_MITHRIL_BROADSWORD_1 )
	AddBuyItem( 2082260/**0.75*/, __OBJ_MITHRIL_BROADSWORD_2 )
	AddBuyItem( 230691/**0.75*/, __OBJ_MITHRIL_SCIMITAR )
	AddBuyItem( 692073/**0.75*/, __OBJ_MITHRIL_SCIMITAR_1 )
	AddBuyItem( 2306910/**0.75*/, __OBJ_MITHRIL_SCIMITAR_2 )
	AddBuyItem( 254305/**0.75*/, __OBJ_MITHRIL_BASTARD_SWORD )
	AddBuyItem( 762915/**0.75*/, __OBJ_MITHRIL_BASTARD_SWORD_1 )
	AddBuyItem( 2543050/**0.75*/, __OBJ_MITHRIL_BASTARD_SWORD_2 )
	AddBuyItem( 279071/**0.75*/, __OBJ_MITHRIL_TWO_HANDED_SWORD )
	AddBuyItem( 837213/**0.75*/, __OBJ_MITHRIL_TWO_HANDED_SWORD_1 )
	AddBuyItem( 2790710/**0.75*/, __OBJ_MITHRIL_TWO_HANDED_SWORD_2 )
	AddBuyItem( 11162840/**0.75*/, __OBJ_MITHRIL_TWO_HANDED_SWORD_3 )
	AddBuyItem( 332053/**0.75*/, __OBJ_ADAMANTITE_BROADSWORD )
	AddBuyItem( 996159/**0.75*/, __OBJ_ADAMANTITE_BROADSWORD_1 )
	AddBuyItem( 3320530/**0.75*/, __OBJ_ADAMANTITE_BROADSWORD_2 )
	AddBuyItem( 360269/**0.75*/, __OBJ_ADAMANTITE_SCIMITAR )
	AddBuyItem( 1080807/**0.75*/, __OBJ_ADAMANTITE_SCIMITAR_1 )
	AddBuyItem( 3602690/**0.75*/, __OBJ_ADAMANTITE_SCIMITAR_2 )
	AddBuyItem( 389637/**0.75*/, __OBJ_ADAMANTITE_BASTARD_SWORD )
	AddBuyItem( 1168911/**0.75*/, __OBJ_ADAMANTITE_BASTARD_SWORD_1 )
	AddBuyItem( 3896370/**0.75*/, __OBJ_ADAMANTITE_BASTARD_SWORD_2 )
	AddBuyItem( 420154/**0.75*/, __OBJ_ADAMANTITE_TWO_HANDED_SWORD )
	AddBuyItem( 1260462/**0.75*/, __OBJ_ADAMANTITE_TWO_HANDED_SWORD_1 )
	AddBuyItem( 4201540/**0.75*/, __OBJ_ADAMANTITE_TWO_HANDED_SWORD_2 )
	AddBuyItem( 16806160/**0.75*/, __OBJ_ADAMANTITE_TWO_HANDED_SWORD_3 )
	AddBuyItem( 553730/**0.75*/, __OBJ_ANCIENT_SCIMITAR )
	AddBuyItem( 1661190/**0.75*/, __OBJ_ANCIENT_SCIMITAR_1 )
	AddBuyItem( 5537300/**0.75*/, __OBJ_ANCIENT_SCIMITAR_2 )
	AddBuyItem( 746587/**0.75*/, __OBJ_ANCIENT_BASTARD_SWORD )
	AddBuyItem( 2239761/**0.75*/, __OBJ_ANCIENT_BASTARD_SWORD_1 )
	AddBuyItem( 7465870/**0.75*/, __OBJ_ANCIENT_BASTARD_SWORD_2 )
	AddBuyItem( 921581/**0.75*/, __OBJ_ANCIENT_TWO_HANDED_SWORD )
	AddBuyItem( 2764743/**0.75*/, __OBJ_ANCIENT_TWO_HANDED_SWORD_1 )
	AddBuyItem( 9215810/**0.75*/, __OBJ_ANCIENT_TWO_HANDED_SWORD_2 )
	AddBuyItem( 147737/**0.75*/, __OBJ_ADAMANTITE_BLADE )
	AddBuyItem( 443211/**0.75*/, __OBJ_ADAMANTITE_BLADE_1 )
	AddBuyItem( 1477370/**0.75*/, __OBJ_ADAMANTITE_BLADE_2 )
	AddBuyItem( 5909480/**0.75*/, __OBJ_ADAMANTITE_BLADE_3 )
	AddBuyItem( 230691/**0.75*/, __OBJ_ANCIENT_BLADE )
   //AddBuyItem( 230691/**0.75*/, __OBJ_ANCIENT_BLADE_DUAL )
	AddBuyItem( 692073/**0.75*/, __OBJ_ANCIENT_BLADE_1 )
   //AddBuyItem( 692073/**0.75*/, __OBJ_ANCIENT_BLADE1_DUAL )
	AddBuyItem( 2306910/**0.75*/, __OBJ_ANCIENT_BLADE_2 )
   //AddBuyItem( 2306910/**0.75*/, __OBJ_ANCIENT_BLADE2_DUAL )
	AddBuyItem( 9227640/**0.75*/, __OBJ_ANCIENT_BLADE_3 )
   //AddBuyItem( 9227640/**0.75*/, __OBJ_ANCIENT_BLADE3_DUAL )
SendBuyItemList

CmdAND(INTL( 1304, "BUY"),INTL( 11395, "SHIELD"))
INTL( 11396, "We have just the shield for you!")
CreateItemList
	AddBuyItem( 65284/**0.75*/, __OBJ_MITHRIL_SHIELD )
	AddBuyItem( 97417/**0.75*/, __OBJ_GOTHIC_SHIELD )
	AddBuyItem( 165234/**0.75*/, __OBJ_ADAMANTITE_SHIELD )
SendBuyItemList

CmdAND(INTL( 1304, "BUY"),INTL( 916, "ARMOR"))
INTL( 11397, "We have just the armor for you!")
CreateItemList
	AddBuyItem( 225282/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_ARMOR )
	AddBuyItem( 50140/**0.75*/, __OBJ_ADAMANTITE_PLATE_PROTECTOR )
	AddBuyItem( 66153/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_GAUNTLETS )
	AddBuyItem( 71658/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_HELMET )
	AddBuyItem( 75160/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_LEGGINGS )
	AddBuyItem( 64652/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_BOOTS )
SendBuyItemList

Command(INTL( 7994, "BOW"))
INTL( 11398, "We have Cedar Longbows, Cedar Reflex Bows, Cedar Recurve Bows, Cedar Compound Bows, Cedar Composite Bows, "
"Lancewood Reflex Bows, Lancewood Recurve Bows, Lancewood Compound Bows, Lancewood Composite Bows, "
"Black Locust Recurve Bows, Black Locust Compound Bows, and Black Locust Composite Bows. If you wish to buy "
"any of these items, just say \"buy\" \"bow\".")

CmdAND(INTL( 11393, "MELEE"),INTL( 914, "WEAPON"))
INTL( 11399, "We have Mithril Morning Stars, Ancient Morning Stars, High Metal Broad Axes, Mithril Battle Axes, "
"Mithril Broad Axes, Ancient Broad Axes, Mithril Long Swords, Mithril Broadswords, Mithril Scimitars, "
"Mithril Bastard Swords, Mithril Two-Handed Swords, Adamantite Broadswords, Adamantite Scimitars, "
"Adamantite Bastard Swords, Adamantite Two-Handed Swords, Ancient Scimitars, Ancient Bastard Swords, "
"Ancient Two-Handed Swords, Adamantite Blades, and Ancient Blades. If you wish to buy any of these items, "
"just say \"buy\" \"melee\" \"weapons\".")

Command(INTL( 11395, "SHIELD"))
INTL( 11400, "We have Mithril Shields, Gothic Shields and Adamantite Shields. If you wish "
"to buy any of these items, just say \"buy\" \"shields\".")

Command(INTL( 916, "ARMOR"))
INTL( 11401, "We have Adamantite Platemail Armors, Adamantite Plate Protectors, Adamantite Platemail Gauntlets, "
"Adamantite Platemail Helmets, Adamantite Platemail Leggings and Adamantite Platemail Boots. If you wish to buy "
"any of these items, just say \"buy\" \"armors\".")

Command2(INTL( 1304, "BUY"), INTL( 7195, "PURCHASE"))
INTL( 11388, "I have a \"wide\" \"selection\" of very special items. Other vendors won't even buy them from you. "
"Once you have them, they remain yours.")

Command(INTL( 1306, "SELL"))
INTL( 11418, "Unfortunately for you, there is nothing I need that you have.")

Command5(INTL( 697, "ASSHOLE"),INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 1919, "WHORE"),INTL( 698, " ASS "))
INTL( 11402, "Suit yourself! I have to be elsewhere anyway.")
CastSpellSelf(__SPELL_MOB_LORD_OF_THE_SHOPS_TELEPORT_SPELL_2)

Command4(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"))
INTL( 1075, "Farewell.")
CastSpellSelf(__SPELL_MOB_LORD_OF_THE_SHOPS_TELEPORT_SPELL_2)

Default
INTL( 11419, "I would urge you to hurry up and make your purchase. I will not be here much longer.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void LordoftheShops::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Lord of the Shops data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

		NPC_SELL( 762915/**0.75*/, __OBJ_CEDAR_LONGBOW_1 )
		NPC_SELL( 2543050/**0.75*/, __OBJ_CEDAR_LONGBOW_2 )
		NPC_SELL( 279071/**0.75*/, __OBJ_CEDAR_REFLEX_BOW )
		NPC_SELL( 837213/**0.75*/, __OBJ_CEDAR_REFLEX_BOW_1 )
		NPC_SELL( 2790710/**0.75*/, __OBJ_CEDAR_REFLEX_BOW_2 )
		NPC_SELL( 304986/**0.75*/, __OBJ_CEDAR_RECURVE_BOW )
		NPC_SELL( 914958/**0.75*/, __OBJ_CEDAR_RECURVE_BOW_1 )
		NPC_SELL( 3049860/**0.75*/, __OBJ_CEDAR_RECURVE_BOW_2 )
		NPC_SELL( 332053/**0.75*/, __OBJ_CEDAR_COMPOUND_BOW )
		NPC_SELL( 996159/**0.75*/, __OBJ_CEDAR_COMPOUND_BOW_1 )
		NPC_SELL( 3320530/**0.75*/, __OBJ_CEDAR_COMPOUND_BOW_2 )
		NPC_SELL( 360269/**0.75*/, __OBJ_CEDAR_COMPOSITE_BOW )
		NPC_SELL( 1080807/**0.75*/, __OBJ_CEDAR_COMPOSITE_BOW_1 )
		NPC_SELL( 3602690/**0.75*/, __OBJ_CEDAR_COMPOSITE_BOW_2 )
		NPC_SELL( 14410760/**0.75*/, __OBJ_CEDAR_COMPOSITE_BOW_3 )
		NPC_SELL( 420154/**0.75*/, __OBJ_LANCEWOOD_REFLEX_BOW )
		NPC_SELL( 1260462/**0.75*/, __OBJ_LANCEWOOD_REFLEX_BOW_1 )
		NPC_SELL( 4201540/**0.75*/, __OBJ_LANCEWOOD_REFLEX_BOW_2 )
		NPC_SELL( 451823/**0.75*/, __OBJ_LANCEWOOD_RECURVE_BOW )
		NPC_SELL( 1355469/**0.75*/, __OBJ_LANCEWOOD_RECURVE_BOW_1 )
		NPC_SELL( 4518230/**0.75*/, __OBJ_LANCEWOOD_RECURVE_BOW_2 )
		NPC_SELL( 484641/**0.75*/, __OBJ_LANCEWOOD_COMPOUND_BOW )
		NPC_SELL( 1453923/**0.75*/, __OBJ_LANCEWOOD_COMPOUND_BOW_1 )
		NPC_SELL( 4846410/**0.75*/, __OBJ_LANCEWOOD_COMPOUND_BOW_2 )
		NPC_SELL( 518611/**0.75*/, __OBJ_LANCEWOOD_COMPOSITE_BOW )
		NPC_SELL( 1555833/**0.75*/, __OBJ_LANCEWOOD_COMPOSITE_BOW_1 )
		NPC_SELL( 5186110/**0.75*/, __OBJ_LANCEWOOD_COMPOSITE_BOW_2 )
		NPC_SELL( 20744440/**0.75*/, __OBJ_LANCEWOOD_COMPOSITE_BOW_3 )
		NPC_SELL( 665993/**0.75*/, __OBJ_BLACK_LOCUST_RECURVE_BOW )
		NPC_SELL( 1997979/**0.75*/, __OBJ_BLACK_LOCUST_RECURVE_BOW_1 )
		NPC_SELL( 6659930/**0.75*/, __OBJ_BLACK_LOCUST_RECURVE_BOW_2 )
		NPC_SELL( 788609/**0.75*/, __OBJ_BLACK_LOCUST_COMPOUND_BOW )
		NPC_SELL( 2365827/**0.75*/, __OBJ_BLACK_LOCUST_COMPOUND_BOW_1 )
		NPC_SELL( 7886090/**0.75*/, __OBJ_BLACK_LOCUST_COMPOUND_BOW_2 )
		NPC_SELL( 921581/**0.75*/, __OBJ_BLACK_LOCUST_COMPOSITE_BOW )
		NPC_SELL( 2764743/**0.75*/, __OBJ_BLACK_LOCUST_COMPOSITE_BOW_1 )
		NPC_SELL( 9215810/**0.75*/, __OBJ_BLACK_LOCUST_COMPOSITE_BOW_2 )
		NPC_SELL( 692073/**0.75*/, __OBJ_MITHRIL_MORNINGSTAR_1 )
		NPC_SELL( 2306910/**0.75*/, __OBJ_MITHRIL_MORNINGSTAR_2 )
		NPC_SELL( 9227640/**0.75*/, __OBJ_MITHRIL_MORNINGSTAR_3 )
		NPC_SELL( 360269/**0.75*/, __OBJ_ANCIENT_MORNINGSTAR )
		NPC_SELL( 1080807/**0.75*/, __OBJ_ANCIENT_MORNINGSTAR_1 )
		NPC_SELL( 3602690/**0.75*/, __OBJ_ANCIENT_MORNINGSTAR_2 )
		NPC_SELL( 230691/**0.75*/, __OBJ_HIGH_METAL_BROAD_AXE )
		NPC_SELL( 692073/**0.75*/, __OBJ_HIGH_METAL_BROAD_AXE_1 )
		NPC_SELL( 2306910/**0.75*/, __OBJ_HIGH_METAL_BROAD_AXE_2 )
		NPC_SELL( 9227640/**0.75*/, __OBJ_HIGH_METAL_BROAD_AXE_3 )
		NPC_SELL( 332053/**0.75*/, __OBJ_MITHRIL_BATTLE_AXE )
		NPC_SELL( 996159/**0.75*/, __OBJ_MITHRIL_BATTLE_AXE_1 )
		NPC_SELL( 3320530/**0.75*/, __OBJ_MITHRIL_BATTLE_AXE_2 )
		NPC_SELL( 451823/**0.75*/, __OBJ_MITHRIL_BROAD_AXE )
		NPC_SELL( 1355469/**0.75*/, __OBJ_MITHRIL_BROAD_AXE_1 )
		NPC_SELL( 4518230/**0.75*/, __OBJ_MITHRIL_BROAD_AXE_2 )
		NPC_SELL( 18072920/**0.75*/, __OBJ_MITHRIL_BROAD_AXE_3 )
		NPC_SELL( 921581/**0.75*/, __OBJ_ANCIENT_BROAD_AXE )
		NPC_SELL( 2764743/**0.75*/, __OBJ_ANCIENT_BROAD_AXE_1 )
		NPC_SELL( 9215810/**0.75*/, __OBJ_ANCIENT_BROAD_AXE_2 )
		NPC_SELL( 186913/**0.75*/, __OBJ_MITHRIL_LONG_SWORD )
		NPC_SELL( 560739/**0.75*/, __OBJ_MITHRIL_LONG_SWORD_1 )
		NPC_SELL( 1869130/**0.75*/, __OBJ_MITHRIL_LONG_SWORD_2 )
		NPC_SELL( 208226/**0.75*/, __OBJ_MITHRIL_BROADSWORD )
		NPC_SELL( 624678/**0.75*/, __OBJ_MITHRIL_BROADSWORD_1 )
		NPC_SELL( 2082260/**0.75*/, __OBJ_MITHRIL_BROADSWORD_2 )
		NPC_SELL( 230691/**0.75*/, __OBJ_MITHRIL_SCIMITAR )
		NPC_SELL( 692073/**0.75*/, __OBJ_MITHRIL_SCIMITAR_1 )
		NPC_SELL( 2306910/**0.75*/, __OBJ_MITHRIL_SCIMITAR_2 )
		NPC_SELL( 254305/**0.75*/, __OBJ_MITHRIL_BASTARD_SWORD )
		NPC_SELL( 762915/**0.75*/, __OBJ_MITHRIL_BASTARD_SWORD_1 )
		NPC_SELL( 2543050/**0.75*/, __OBJ_MITHRIL_BASTARD_SWORD_2 )
		NPC_SELL( 279071/**0.75*/, __OBJ_MITHRIL_TWO_HANDED_SWORD )
		NPC_SELL( 837213/**0.75*/, __OBJ_MITHRIL_TWO_HANDED_SWORD_1 )
		NPC_SELL( 2790710/**0.75*/, __OBJ_MITHRIL_TWO_HANDED_SWORD_2 )
		NPC_SELL( 11162840/**0.75*/, __OBJ_MITHRIL_TWO_HANDED_SWORD_3 )
		NPC_SELL( 332053/**0.75*/, __OBJ_ADAMANTITE_BROADSWORD )
		NPC_SELL( 996159/**0.75*/, __OBJ_ADAMANTITE_BROADSWORD_1 )
		NPC_SELL( 3320530/**0.75*/, __OBJ_ADAMANTITE_BROADSWORD_2 )
		NPC_SELL( 360269/**0.75*/, __OBJ_ADAMANTITE_SCIMITAR )
		NPC_SELL( 1080807/**0.75*/, __OBJ_ADAMANTITE_SCIMITAR_1 )
		NPC_SELL( 3602690/**0.75*/, __OBJ_ADAMANTITE_SCIMITAR_2 )
		NPC_SELL( 389637/**0.75*/, __OBJ_ADAMANTITE_BASTARD_SWORD )
		NPC_SELL( 1168911/**0.75*/, __OBJ_ADAMANTITE_BASTARD_SWORD_1 )
		NPC_SELL( 3896370/**0.75*/, __OBJ_ADAMANTITE_BASTARD_SWORD_2 )
		NPC_SELL( 420154/**0.75*/, __OBJ_ADAMANTITE_TWO_HANDED_SWORD )
		NPC_SELL( 1260462/**0.75*/, __OBJ_ADAMANTITE_TWO_HANDED_SWORD_1 )
		NPC_SELL( 4201540/**0.75*/, __OBJ_ADAMANTITE_TWO_HANDED_SWORD_2 )
		NPC_SELL( 16806160/**0.75*/, __OBJ_ADAMANTITE_TWO_HANDED_SWORD_3 )
		NPC_SELL( 553730/**0.75*/, __OBJ_ANCIENT_SCIMITAR )
		NPC_SELL( 1661190/**0.75*/, __OBJ_ANCIENT_SCIMITAR_1 )
		NPC_SELL( 5537300/**0.75*/, __OBJ_ANCIENT_SCIMITAR_2 )
		NPC_SELL( 746587/**0.75*/, __OBJ_ANCIENT_BASTARD_SWORD )
		NPC_SELL( 2239761/**0.75*/, __OBJ_ANCIENT_BASTARD_SWORD_1 )
		NPC_SELL( 7465870/**0.75*/, __OBJ_ANCIENT_BASTARD_SWORD_2 )
		NPC_SELL( 921581/**0.75*/, __OBJ_ANCIENT_TWO_HANDED_SWORD )
		NPC_SELL( 2764743/**0.75*/, __OBJ_ANCIENT_TWO_HANDED_SWORD_1 )
		NPC_SELL( 9215810/**0.75*/, __OBJ_ANCIENT_TWO_HANDED_SWORD_2 )
		NPC_SELL( 147737/**0.75*/, __OBJ_ADAMANTITE_BLADE )
		NPC_SELL( 443211/**0.75*/, __OBJ_ADAMANTITE_BLADE_1 )
		NPC_SELL( 1477370/**0.75*/, __OBJ_ADAMANTITE_BLADE_2 )
		NPC_SELL( 5909480/**0.75*/, __OBJ_ADAMANTITE_BLADE_3 )
		NPC_SELL( 230691/**0.75*/, __OBJ_ANCIENT_BLADE )
		NPC_SELL( 692073/**0.75*/, __OBJ_ANCIENT_BLADE_1 )
		NPC_SELL( 2306910/**0.75*/, __OBJ_ANCIENT_BLADE_2 )
		NPC_SELL( 9227640/**0.75*/, __OBJ_ANCIENT_BLADE_3 )
      //NPC_SELL( 230691/**0.75*/, __OBJ_ANCIENT_BLADE_DUAL )
		//NPC_SELL( 692073*0.75, __OBJ_ANCIENT_BLADE1_DUAL )
		//NPC_SELL( 2306910*0.75, __OBJ_ANCIENT_BLADE2_DUAL )
		//NPC_SELL( 9227640*0.75, __OBJ_ANCIENT_BLADE3_DUAL )
		NPC_SELL( 65284/**0.75*/, __OBJ_MITHRIL_SHIELD )
		NPC_SELL( 97417/**0.75*/, __OBJ_GOTHIC_SHIELD )
		NPC_SELL( 165234/**0.75*/, __OBJ_ADAMANTITE_SHIELD )
		NPC_SELL( 225282/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_ARMOR )
		NPC_SELL( 50140/**0.75*/, __OBJ_ADAMANTITE_PLATE_PROTECTOR )
		NPC_SELL( 66153/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_GAUNTLETS )
		NPC_SELL( 71658/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_HELMET )
		NPC_SELL( 75160/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_LEGGINGS )
		NPC_SELL( 64652/**0.75*/, __OBJ_ADAMANTITE_PLATEMAIL_BOOTS )
		NPC_SOLD_ITEM(  INTL( 9467, "Thank you!") )
		NPC_FAILED_SELL( INTL( 9468, "You do not have enough gold coins."))
		NPC_BOUGHT_ITEM( INTL( 9469, "We have a deal.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
}


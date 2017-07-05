
#ifndef __Top_Package____NPC_Editor__
#define __Top_Package____NPC_Editor__

#include "../Core/DebugTools.h"
#include "../Core/AppStrings.h"

namespace NPC_Editor{

enum KeywordRelations
{
	And = 1, 
	Or = 2, 
	InOrder = 3
};
enum CommandAttributes
{
	BoostFormula = 1, 
	Flag = 2, 
	Item = 3, 
	Text = 4, 
	Spell = 5,
	Stats = 6
};
enum InstructionIds
{
    InsRoot = 0,
	InsKeyword = 1, 
	InsIf = 2, 
	InsElseIf = 3, 
	InsElse = 4, 
	InsFor = 5, 
	InsWhile = 6, 
	InsGiveItem = 7, 
	InsGiveXP = 8, 
	InsSetFlag = 9, 
	InsHealPlayer = 10, 
	InsSayText = 11, 
	InsBreakConversation = 12, 
	InsFightPlayer = 13, 
	InsTakeItem = 14, 
	InsTeleport = 15, 
	InsCastSpell = 16, 
	InsCastSpellSelf = 17, 
	InsGiveGold = 18, 
	InsTakeGold = 19,
    InsAssign = 20,
    InsSendSoldItemList = 21,
    InsSendBoughtItemList = 22,
    InsSendTrainSkillList = 23,
    InsSendTeachSkillList = 24,
	InsPrivateSystemMessage = 25,
	InsGlobalSystemMessage = 26,
	InsShoutMessage = 27,
	InsSetGlobalFlag = 28,
	InsGiveKarma = 29,
	InsSetStats = 30
};
enum InsertionRelation
{
	asChild, 
	asNext,
    asPrevious
};

enum SellTypes
{
    Armor = 2,
    Jewel = 32,
    JewelArmor = 34,
    JewelWeapon = 33,
    Junk = 64,
    MagicArmor = 10,
    MagicItem = 8,
    MagicJewel = 40,
    MagicJewelArmor = 42,
    MagicJewelWeapon = 41,
    MagicPotion = 24,
    MagicWeapon = 9,
    Pawnshop = 4,
    Potion = 16,
    Weapon = 1
};

}

#endif // __Top_Package____NPC_Editor__


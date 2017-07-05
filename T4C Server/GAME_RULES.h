// GAME_RULES.h: interface for the GAME_RULES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_RULES_H__4F604074_5613_11D1_BD7B_00E029058623__INCLUDED_)
#define AFX_GAME_RULES_H__4F604074_5613_11D1_BD7B_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "tfc_main.h"

#define MONSTER_CORPSE_CLEAN	1 MINUTE

#define PVP_LEVEL       1

class EXPORT GAME_RULES  
{
public:
	GAME_RULES();
	virtual ~GAME_RULES();

    static void Create( void );

	// Returns the blow precision of this attack
	static DWORD GetBlowPrecision(DWORD dwAttackSkill, DWORD dwDodgeSkill, DWORD dwAttackAgi, DWORD dwTargetAgi );
	static DWORD GetNaturalDamage(Unit *lpuUnit);

	static void HPregen( Unit *lpuRegen );
	static void ManaRegen( Unit *lpuRegen );
	static void FaithRegen( Unit *lpuRegen );

    static BOOL InPVP( Unit *lpuFirst, Unit *lpuSecond );
    static BOOL InSafeHaven( Unit *lpuFirst, Unit *lpuSecond );

	static void CalcStatBonus( int nStat, WORD wTrain, WORD wSkillTrain, Character *lpPlayer );

	static void DeathPenalties( Character *chUser, Unit *lpAttacker, TemplateList< Unit > *invSpillList, TemplateList< Unit > *equipSpillList, DWORD &goldLoss );

private:
    static BYTE bPVPRule;
    // For level restriction PVP.
    static WORD wLevelRestriction;
    static WORD wMinLevel;
};

#endif // !defined(AFX_GAME_RULES_H__4F604074_5613_11D1_BD7B_00E029058623__INCLUDED_)

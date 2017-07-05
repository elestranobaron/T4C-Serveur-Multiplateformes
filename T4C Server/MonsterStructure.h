////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTERSTRUCTURE_H
#define __MONSTERSTRUCTURE_H

#include "Unit.h"
#include "SharedStructures.h"
#include "Random.h"
#include <vector>

#pragma warning( disable : 4786 )

#define _NORMAL		0
#define _UNDEAD		1
#define _ANGEL		2
#define _NIGHT_ONLY	4
#define _DAY_ONLY	5

#define _CHEST_GUARD	1	// Monster troup around a chest and must guard it.

#define PHYSICAL_ATTACK     1
#define SPELL_ATTACK        2

//////////////////////////////////////////////////////////////////////////////////////////
// Attack structures for monsters
typedef struct _MONSTER_ATTACK{
    _MONSTER_ATTACK( void ){
        nMinRange = nMaxRange = AttackSkill = 0;
        AttackDoingPercentage = 100;
    };

    BOOL InRange( int nRange ){ return( nRange >= nMinRange && nRange <= nMaxRange ); };

    virtual int EXPORT Attack( Unit *self, Unit *target );

    int nMinRange;
    int nMaxRange;

	//DWORD PlusToAttack;
	//dice  DamageRoll;
    BoostFormula DamageRoll;
	int	  AttackSkill;
	int   AttackDoingPercentage;

    const virtual BYTE GetType( void ){ return PHYSICAL_ATTACK; };
} MONSTER_ATTACK, *LPMONSTER_ATTACK;

//////////////////////////////////////////////////////////////////////////////////////////
// Special spell attacks for monsters.
typedef struct _MONSTER_SPELL_ATTACK : public MONSTER_ATTACK{
    _MONSTER_SPELL_ATTACK( void ){
        wSpellID = 0;
    }

    int EXPORT Attack( Unit *self, Unit *target );
    
    WORD wSpellID;
    
    const virtual BYTE GetType( void ){ return SPELL_ATTACK; };
} MONSTER_SPELL_ATTACK, *LPMONSTER_SPELL_ATTACK;


struct MonsterAttack{
    WORD  wSpellID;     // SpellID, 0 if physical attack.
};

struct ItemToGive{
	UINT ItemID;
	double  ItemGivePercentage;

    // For STL operations.
    friend bool operator <  ( const ItemToGive &i, const ItemToGive &j );
    friend bool operator == ( const ItemToGive &i, const ItemToGive &j );
};

typedef struct _sDeadFlag
{
   int     nDeathGiveFlag;         // Flag to give on monster death.
   int     nDeathFlagValue;        // Value of flag to give on monster death.
   BOOL    boDeathFlagIncrement;   // TRUE if flag should increment by DeathFlagValue.
} sDeadFlag;

inline bool operator <  (const ItemToGive &i, const ItemToGive &j ){ return i.ItemID < j.ItemID; };
inline bool operator == (const ItemToGive &i, const ItemToGive &j ){ return i.ItemID == j.ItemID; };

struct EXPORT MonsterStructure{
    MonsterStructure();

    WORD wBaseReferenceID;  // Monster's base reference ID.

	LPTSTR name;		// name of the mob
	int level;			// level of the mob
	int appearance;		// icon that will be shown to the user
	int Corpse;			// Corpse to set upon death,
	WORD wUndead;		// Undead monster assigned to monster.	
    int	AC;				// AC of the mob
	int HP;				// HP of the mob
	int DodgeSkill;		// Dodge skill of the mob	

	BOOL boCanAttack;	// TRUE if the monster has an attack, FALSE otherwise.

	int block;			// Blocking to assign to monster.

    BOOL boCanExitBuilding; // TRUE if monster can exit a building. Good for NPCs.

	BYTE  speed;		// speed at which the creature moves (moves per 10 seconds of gameplay)
	dice  cAttackLag;	// attack lag, in dice roll rounds.
	BYTE  bLagChance;	// % the monster has of stopping.
	dice  cStopLen;	// Length of stop in dice roll rounds.

	char agressive;		// agressivness level towards default (non clan related) units
	WORD clan;			// Which clan (group of creature) is assigned to this monster

    WorldPos InitialPos;
    WORD     wLoXrange;
    WORD     wHiXrange;
    WORD     wLoYrange;
    WORD     wHiYrange;

	double XPperHit;		// XP per hit
	double XPperDeath;		// XP per death
	
    //int     nDeathGiveFlag;         // Flag to give on monster death.
    //int     nDeathFlagValue;        // Value of flag to give on monster death.
    //BOOL    boDeathFlagIncrement;   // TRUE if flag should increment by DeathFlagValue.

	vector< sDeadFlag > vOnDeathFlag;

	int MinGold;		// Min gold the monster may give
	int MaxGold;		// Max gold the monster may give

	int PhysicalAttackPercentage; // Percentage the attack has to be physical (instead of spell).
	
    vector< LPMONSTER_ATTACK > vlpRangeAttacks;
    vector< LPMONSTER_ATTACK > vlpMonsterAttacks;

	vector< ItemToGive >       vDeathItems;
    //ItemToGive	  *DeathItems;	// Array of items
	//int	NumberOfItemToGive;		// Number of items in the array

	int INT, WIL, STR, AGI, END, LCK, WIS;

    int AirResist, WaterResist, FireResist, EarthResist, LightResist, DarkResist;
    int AirPower,  WaterPower,  FirePower,  EarthPower,  LightPower,  DarkPower;

    WORD wBody, wFeet, wGloves, wHelm, wLegs, wWeapon, wShield, wCape;

	int creature;				// Type of creature.
	int behavior;				// Type of behavior upon creation.
	int groupmin;				// Minimum number of monsters to create.
	int groupmax;               // Maximum number of monsters to create.

    BOOL boPrivateTalk;         // If the NPC talks private with everyone.

    bool boInit;
};

typedef vector< LPMONSTER_ATTACK > attackvector;

#endif

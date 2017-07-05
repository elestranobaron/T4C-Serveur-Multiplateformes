#ifndef ___ITEM_H_041097_1911
#define ___ITEM_H_041097_1911

#include "BoostFormula.h"

#define SET_NAME( obj, newname )	if( obj.name ) delete obj.name;\
									obj.name = new char[ strlen( newname ) + 1];\
									strcpy( obj.name, newname );
#define CANNOT_SELL	0xFFFFFFFF

#define WEAPON		0x01
#define ARMOR		0x02
#define PAWNSHOP	0x04
#define MAGIC		0x08
#define POTION		0x10
#define JEWEL		0x20
#define JUNK		0x40

#define CANNOT_DROP_ITEM    0x01
#define CANNOT_GIVE_ITEM    0x02
#define CANNOT_ROB_ITEM     0x04
#define CANNOT_JUNK_ITEM    0x08
#define CANNOT_GET_ITEM     0x10
#define CANNOT_HIDE         0x20
#define JUNK_AT_SERAPH      0x40

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _OBJECT_SPELL{
	WORD wSpellID;
	WORD wHook;
} OBJECT_SPELL, *LPOBJECT_SPELL;
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _OBJECT_BOOST{
	WORD wStat;
	DWORD dwBoostID;
	BoostFormula  bfBoost;
	int  nMinWIS;
	int  nMinINT;
} OBJECT_BOOST, *LPOBJECT_BOOST;
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _OBJECT_GROUPITEMS{	
	TemplateList< WORD > tlItemBaseReferenceID;		// List of items in group.
} OBJECT_GROUPITEMS, *LPOBJECT_GROUPITEMS;
//////////////////////////////////////////////////////////////////////////////////////////
struct _item{
	LPSTR name;				// Name of the object
	WORD appearance;			// icon showed to the client
	WORD equip_position;		// position to which the object is equipped
	BYTE blocking;				// blocking to assign to the item.
    WORD itemStructureId;       // ID of the structure used to create this item.
	WORD sell_type;             // Type of item for selling purpose.
    WORD item_type;				// Type of item, WEAPON, ARMOR, etc
	DWORD cost;					// Price of item when sold.
    DWORD dwDropFlags;            // Drop flags.
	int size;					// Size of item
	signed char cRadiance;		// object's radiance.
	BYTE bResistance;			// Resistance of the object.
    bool uniqueItem;
    bool canSummon;             // True if ordinary GMs can summon this item    

    std::string GmItemLocation;

	// Specific to armor objects
	struct _armor{
		double AC;				// AC of the armor		
		WORD Dod;				// Dod
		WORD End;				// End
	} armor; // Pointer to an _armor structure, or NULL if object isn't an armor

	// Specific to weapons
	struct _weapon{
        BoostFormula cDamage;
        BoostFormula cDealtExhaust;

        WORD Att;				// Att
		WORD Str;				// Str
		WORD Agi;				// Agi
        bool ranged;
        bool infiniteAmmo;      // true if the weapon has infinite ammo.
	} weapon; // Pointer to a _weapon structure, or NULL if object isn't a weapon
	
	// Specific to objects that need 'locks'
	struct _lock{
		DWORD key;
		WORD wDifficulty;		// Strength of lock.
	} lock;
	
	// magic items should fill this entry
	struct _magic{
        int nMinWis;    // Min equip wis/int
        int nMinInt;
        int charges;
        WORD wStr;
	} magic;

	// books always have a text associated with them
	struct _text{
		CString	csText;
	} text;

	struct _container{
		TemplateList <OBJECT_GROUPITEMS> tlItemGroups;	// Group random items to spawn.
		DWORD dwUserRespawn;		// User respawn time.
		DWORD dwGlobalRespawn;		// Global respawn time.
		DWORD dwGold;				// Gold given by chest at each respawn.
	} container;

	struct _trap{
		WORD wDetect;
		WORD wDisarm;
	} trap;

	TemplateList <OBJECT_SPELL> tlSpells;
	TemplateList <OBJECT_BOOST> tlBoosts;	

	WORD MinLevel[4]; // Minimal wield level for each class	
};

#endif
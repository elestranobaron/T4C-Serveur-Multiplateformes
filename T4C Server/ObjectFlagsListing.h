#ifndef __OBJECTFLAGSDEF_H
#define __OBJECTFLAGSDEF_H

//#define __FLAG_OBJECT_TYPE         1  // Type of the object, sprite to load on client
//#define __FLAG_WEIGHT              2  // Weight of the object, for get/drop
//#define __FLAG_WEAPON_REQUIREMENT  3  // Weapon requirement, kinda like ego
//#define __FLAG_LEVEL               4  // Level of the item


// Normal arrow is a hmm wooden, normal arrow..!
//#define __FLAG_NORMAL_ARROW        8  // Defines normal arrows
//#define __FLAG_ARROW_MINDAM        9  // Min damage of arrows
//#define __FLAG_ARROW_MAXDAM        10 // Max damage of arrows

// Flags which tell where is the object equipped
//#define __FLAG_EQUIP_POSITION      11 // Tells the position where the object can be equipped, undefined means that it cannot be equipped
#define __FLAG_CANNOT_DISPELL      12 // Tells that no "DISPELL MAGIC" spell can destroy the effect of this object

//#define __FLAG_DOOR_KEY            13 // Key controlling the object, for safes or doors
#define __FLAG_BLOCKING            14 // Tells that the object is "blocking"

#define __FLAG_DOOR_LOCKED         15 // Tells that a door is locked (or a safe)
#define __FLAG_OPENED_DOOR         16 // Tells that a door is opened

//#define __FLAG_CHARACTER_TYPE      17 // Type of character (monster? PC? npc?_

//#define __FLAG_EQUIPPED_SPACEX	  18 // How much space an object takes, equipped X
//#define __FLAG_EQUIPPED_SPACEY	  19 // How much space an object takes, equipped Y

//#define __FLAG_OBJECT_XSPACE	  20 // How wide is an object (on floor)
//#define __FLAG_OBJECT_YSPACE	  21 // How large is an object (on floor)
//#define __FLAG_OBJECT_DIRECTION	  22 // direction vector of an object (0-360)

//#define __FLAG_BAG_SIZE			  23 // Size of a bag
//#define __FLAG_NB_OBJ_IN_BAG	  24 // Number of objects in bag

//#define __FLAG_CANNOT_GET		  25 // Flags that says we can't get the item.
//#define __FLAG_CANNOT_DROP		  26 // For curses or such

#define __FLAG_CHARGES			  27 // Flag that hold the number of charges on an item

#define __FLAG_TRAP_DISABLED	  28 // None zero if trap in object was disabled.

#define __FLAG_ICY_SABER		  29 //	Holds the icy sabre's strength.

#define __FLAG_DONT_RESPAWN		  30 // If non-zero, forbids a container object from respawning.

#define __FLAG_GOLD               31 // Quantity of gold on a Gold type of object.
#define __FLAG_USE_RANGE          32 // Range from which the object can be used.

#endif
// Here are listed all stat modifiers (including HP!) flags possible

#ifndef __STATMODIFIERFLAGSLISTING_H
#define __STATMODIFIERFLAGSLISTING_H

const BYTE _LAWFUL		= 0; // not aggressive at all
const BYTE _NEUTRAL		= 50; // 1/2 agressive
const BYTE _CHAOTIC		= 100; // always agressive


/*#define __FLAG_AGI					20000
#define __FLAG_CHA					20001
#define __FLAG_END					20002 
#define __FLAG_INT					20003 
#define __FLAG_LCK					20004 
#define __FLAG_STR					20005 
#define __FLAG_WIL					20006 
#define __FLAG_WIS					20007 */
#define __FLAG_GET_RANGE			20009 
#define __FLAG_THROW_RANGE			20010 
#define __FLAG_DAMAGE_MODIFIER		20011 
#define __FLAG_CLASS				20013 
//#define __FLAG_DODGE_SKILL			20015 
//#define __FLAG_ATTACK_SKILL			20016 

#define __FLAG_STUN					20017

#define __FLAG_MEDITATING			20018
#define __FLAG_PRAYING				20019

#define __FLAG_DEATH_LOCATION		20020

#define __FLAG_WARCRY_NOT_AFFECTED	20021
#define __FLAG_TRAP_DETECTED		20022
#define __FLAG_EVASIVNESS			20023
#define __FLAG_BERSERK				20024

#define __FLAG_ARM_EXTENT			20025

#define __FLAG_FIST_OF_ROCK			20026
#define __FLAG_FLY					20027
#define __FLAG_WALK_ON_WATER		20028
#define __FLAG_NPC_TALKTO           20029

#define __FLAG_AIR_RESIST           20030
#define __FLAG_WATER_RESIST         20031
#define __FLAG_FIRE_RESIST          20032
#define __FLAG_EARTH_RESIST         20033

#define __FLAG_ROBBING              20034

#define __FLAG_SEPARATING_GOLD      20035

#define __FLAG_SHOUT                20036


#define __FLAG_LIGHT_RESIST         20037
#define __FLAG_DARK_RESIST          20038
#define __FLAG_LIGHT_POWER          20039
#define __FLAG_DARK_POWER           20040

#define __FLAG_AIR_POWER            20041
#define __FLAG_WATER_POWER          20042
#define __FLAG_FIRE_POWER           20043
#define __FLAG_EARTH_POWER          20044

#define __FLAG_FIRST_AID_EXHAUST    20045

#define __FLAG_INVISIBILITY         20050
#define __FLAG_HIDDEN               20051
#define __FLAG_DETECT_INVISIBILITY  20052
#define __FLAG_DETECT_HIDDEN        20053
#define __FLAG_PEEKING				20054

#endif
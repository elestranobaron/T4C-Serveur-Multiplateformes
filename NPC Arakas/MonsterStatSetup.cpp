//////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include <NPCStructure.h>
#include <DLLCreatures.h>

NPCstructure::NPC LyriaNPC; 
NPCstructure::NPC _Jarko;                     
NPCstructure::NPC _Mhorgwloth;                
NPCstructure::NPC _RenegadeOrcLeader;         
NPCstructure::NPC Brigand_Leader;             
NPCstructure::NPC Priestess_Annabelle;        
NPCstructure::NPC Male_Brigand;               
NPCstructure::NPC Female_Brigand;             
NPCstructure::NPC YrianNPC;                
NPCstructure::NPC Old_Bald_Hermit;            
NPCstructure::NPC Lower_Rank_Druid;           
NPCstructure::NPC Samaritan;                  
NPCstructure::NPC _DorkenRotsmell;
NPCstructure::NPC NakedTorso_Smith;
NPCstructure::NPC _NPCGoblinScout;
NPCstructure::NPC _NPCGoblinWarrior;
NPCstructure::NPC ShopKeeper;
NPCstructure::NPC DunikusNPC; 
NPCstructure::NPC LantalirNPC; 

void CreateNPC( void );

INIT_MONSTER_STAT_SETUP							   

SET_MONSTER( Samaritan )
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 20 )
MOB_DEX                         ( 24 )
MOB_END                         ( 22 )
MOB_INT                         ( 20 )
MOB_WIS                         ( 21 )
MOB_WIL                         ( 25 )
MOB_LCK                         ( 22 )               

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE   ( 100 )
MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
MOB_DRESS_HELM ( ELVEN_HAT )
// MOB_DRESS_GLOVES 
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE 

SET_MONSTER( LantalirNPC )
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 20 )
MOB_DEX                         ( 24 )
MOB_END                         ( 22 )
MOB_INT                         ( 20 )
MOB_WIS                         ( 21 )
MOB_WIL                         ( 25 )
MOB_LCK                         ( 22 )               

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE   ( 100 )

MOB_DRESS_BODY ( MAGEROBE )
MOB_DRESS_HELM ( ELVEN_HAT )
// MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_WEAPON ( STAFF2 ) 

SET_MONSTER( DunikusNPC )
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 20 )
MOB_DEX                         ( 24 )
MOB_END                         ( 22 )
MOB_INT                         ( 20 )
MOB_WIS                         ( 21 )
MOB_WIL                         ( 25 )
MOB_LCK                         ( 22 )               

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE   ( 100 )

MOB_DRESS_BODY ( MAGEROBE )
MOB_DRESS_HELM ( ELVEN_HAT )
// MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_WEAPON ( STAFF2 ) 

SET_MONSTER( _NPCGoblinScout )
MOB_SPEED             ( 65, dice( 20, 100 ), 25, dice( 4, 500 ) )
MOB_NPC_APPEARANCE    ( GOBLIN )
MOB_AGRESSIVNESS      ( 100 )
MOB_CLAN              ( JARKO )
MOB_HP                ( 132 )
MOB_DODGE_SKILL       ( 42 )
MOB_AC                ( 4 )
MOB_LEVEL             ( 8 )
MOB_XP_PER_HIT        ( 2.06 )
MOB_XP_DEATH          ( 136 )
MOB_MIN_GOLD          ( 14 )
MOB_MAX_GOLD          ( 44 )
MOB_STR               ( 23 )
MOB_DEX               ( 22 )
MOB_END               ( 22 )
MOB_INT               ( 24 )
MOB_WIS               ( 22 )
MOB_WIL               ( 22 )
MOB_LCK               ( 16 )
MOB_DEATH_FLAG        (__GOBLINS_KILLED_BY_HERO, 1, TRUE )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 90 )
MOB_WATER_RESIST      ( 90 )
MOB_AIR_RESIST        ( 120 )
MOB_EARTH_RESIST      ( 60 )
MOB_LIGHT_RESIST      ( 5025 )
MOB_DARK_RESIST       ( 90 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 106 )
MOB_ATTACK_DMG_ROLL   (	"1d11+6 )" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 7  MAXdam: 17 

MOB_ITEM( __OBJ_GOBLIN_LEATHER_ARMOR, 0.4 )
MOB_ITEM( __OBJ_LEATHER_BELT,  1)
MOB_ITEM( __OBJ_LIGHT_HEALING_POTION,  5 )
MOB_ITEM( __OBJ_RING_OF_LIGHT, 1 )
MOB_ITEM( __OBJ_HEALING_POTION, 1)

SET_MONSTER( _NPCGoblinWarrior )
MOB_SPEED             ( 65, dice( 10, 450 ), 25, dice( 4, 500 ) )
MOB_AGRESSIVNESS  ( 50 ) 
MOB_APPEARANCE        ( GOBLIN ) 
MOB_CLAN              ( JARKO ) 
MOB_HP                ( 199 )
MOB_DODGE_SKILL       ( 58 )
MOB_AC                ( 6 )
MOB_LEVEL             ( 12 )
MOB_XP_PER_HIT        ( 2.37 )
MOB_XP_DEATH          ( 235.4 )
MOB_MIN_GOLD          ( 21 )
MOB_MAX_GOLD          ( 66 )
MOB_STR               ( 27 )
MOB_DEX               ( 25 )
MOB_END               ( 25 )
MOB_INT               ( 29 )
MOB_WIS               ( 25 )
MOB_WIL               ( 25 )
MOB_LCK               ( 17 )
MOB_DEATH_FLAG (  __GOBLINS_KILLED_BY_HERO, 1, TRUE)

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 88 )
MOB_WATER_RESIST      ( 88 )
MOB_AIR_RESIST        ( 117 )
MOB_EARTH_RESIST      ( 58 )
MOB_LIGHT_RESIST      ( 5025 )
MOB_DARK_RESIST       ( 88 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 154 )
MOB_ATTACK_DMG_ROLL   (	"1d14+9 )" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 10  MAXdam: 23 

MOB_ITEM( __OBJ_GOBLIN_BLADE, 0.4 ) 
MOB_ITEM( __OBJ_LIGHT_HEALING_POTION, 2 )
MOB_ITEM( __OBJ_IRON_KEY, 0.5 )

SET_MONSTER( ShopKeeper )
MOB_NPC_APPEARANCE              ( PUPPET ) 
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 20 )
MOB_DEX                         ( 24 )
MOB_END                         ( 22 )
MOB_INT                         ( 20 )
MOB_WIS                         ( 21 )
MOB_WIL                         ( 25 )
MOB_LCK                         ( 22 )               

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE   ( 100 )
MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_LEGS ( LEG_CLOTH1 )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( NakedTorso_Smith )
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 65 )
MOB_DEX                         ( 65 )
MOB_END                         ( 65 )
MOB_INT                         ( 65 )
MOB_WIS                         ( 65 )
MOB_WIL                         ( 65 )
MOB_LCK                         ( 65 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 17  MAXdam: 39 
//MOB_DRESS_BODY
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
//MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEATHER_PANTS )
//MOB_DRESS_WEAPON
//MOB_DRESS_SHIELD
//MOB_DRESS_CAPE

SET_MONSTER( _DorkenRotsmell ) // Boss
MOB_APPEARANCE    ( RED_GOBLINBOSS )
MOB_AGRESSIVNESS      ( 100 )
MOB_SPEED             ( 65, dice( 10, 375 ), 30, dice( 7, 250 ) )
MOB_CLAN              ( JARKO )
MOB_HP                ( 508 )
MOB_DODGE_SKILL       ( 70 )
MOB_AC                ( 7 )
MOB_LEVEL             ( 15 )
MOB_XP_PER_HIT        ( 2.66 )
MOB_XP_DEATH          ( 674.44 )
MOB_MIN_GOLD          ( 52 )
MOB_MAX_GOLD          ( 164 )
MOB_STR               ( 32 )
MOB_DEX               ( 28 )
MOB_END               ( 28 )
MOB_INT               ( 33 )
MOB_WIS               ( 28 )
MOB_WIL               ( 28 )
MOB_LCK               ( 18 )
MOB_DEATH_FLAG (  __GOBLINS_KILLED_BY_HERO, 1, TRUE)

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 86 )
MOB_WATER_RESIST      ( 86 )
MOB_AIR_RESIST        ( 115 )
MOB_EARTH_RESIST      ( 57 )
MOB_LIGHT_RESIST      ( 5025 )
MOB_DARK_RESIST       ( 86 )

MOB_CREATE_SPELL_ATTACK( 3, 15 )
MOB_ATTACK_SPELL( 10096 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 190)
MOB_ATTACK_DMG_ROLL   (	"1d17+12" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 17  MAXdam: 40

MOB_ITEM( __OBJ_HEALING_POTION, 30 )
MOB_ITEM( __OBJ_ROUND_SHIELD, 2 )
MOB_ITEM( __OBJ_GOLDEN_BRACELET, 2 )
MOB_ITEM( __OBJ_GOLDEN_RING, 1 )

SET_MONSTER( _Jarko ) // Boss
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_SPEED                       ( 65, dice( 10, 375 ), 30, dice( 7, 250 ) )
MOB_CLAN                        ( JARKO )
MOB_LEVEL                       ( 32 )
MOB_HP                          ( 1262 )
MOB_DODGE_SKILL                 ( 138 )
MOB_AC                          ( 16 )
MOB_XP_PER_HIT                  ( 4.15 )
MOB_XP_DEATH                    ( 2623.6 )
MOB_MIN_GOLD                    ( 114 )
MOB_MAX_GOLD                    ( 352 )
MOB_STR                         ( 47 )
MOB_DEX                         ( 43 )
MOB_END                         ( 43 )
MOB_INT                         ( 53 )
MOB_WIS                         ( 43 )
MOB_WIL                         ( 43 )
MOB_LCK                         ( 21 )
MOB_CAN_ATTACK                  (TRUE)

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 78 )
MOB_WATER_RESIST      ( 78 )
MOB_AIR_RESIST        ( 78 )
MOB_EARTH_RESIST      ( 78 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 300 )

MOB_DRESS_BODY ( NECROMANROBE )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
// MOB_DRESS_GLOVES 
MOB_DRESS_HELM ( HORNED_HELMET )
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
MOB_DRESS_WEAPON ( STAFF1 ) 
// MOB_DRESS_SHIELD
MOB_DRESS_CAPE ( REDCAPE )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL( 394 )
MOB_ATTACK_DMG_ROLL(	"1d40+29" )
MOB_ATTACK_PERCENTAGE( 100 )
               
MOB_CREATE_SPELL_ATTACK( 11, 20 )   // Mob Ice Shard spell
MOB_ATTACK_SPELL( 10086 )
MOB_ATTACK_PERCENTAGE( 40 )               

MOB_CREATE_SPELL_ATTACK( 11, 20 )   // Mob Drain life
MOB_ATTACK_SPELL( 10119 )
MOB_ATTACK_PERCENTAGE( 30 )               

MOB_CREATE_SPELL_ATTACK( 11, 20 )
MOB_ATTACK_SPELL( 10095 )           // Mob fireball spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_SPELL_ATTACK( 3, 10 )    // Mob poison arrow spell
MOB_ATTACK_SPELL( 10091 )
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_SPELL_ATTACK( 3, 10 )   // Mob Drain life
MOB_ATTACK_SPELL( 10119 )
MOB_ATTACK_PERCENTAGE( 25 )               

MOB_CREATE_SPELL_ATTACK( 3, 10 )    // Mob Ice Shard spell
MOB_ATTACK_SPELL( 10086 )
MOB_ATTACK_PERCENTAGE( 25 )               

MOB_CREATE_SPELL_ATTACK( 3, 10 )     // Mob firebolt spell
MOB_ATTACK_SPELL( 10096 )
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_SPELL_ATTACK( 0, 2 )
MOB_ATTACK_SPELL( 10090 )            // Mob freeze spell
MOB_ATTACK_PERCENTAGE( 100 )

MOB_ITEM( __OBJ_POTION_OF_MANA, 30 )
MOB_ITEM( __OBJ_JARKO_AMULET, 15 )
MOB_ITEM( __OBJ_JARKO_SPELLBOOK, 100 )
MOB_ITEM( __OBJ_WARLOCK_RING, 5 )
MOB_ITEM( __OBJ_IRON_STAFF, 15 )
MOB_ITEM( __OBJ_CLOAK_OF_DECEIT, 2.5 )

SET_MONSTER( Priestess_Annabelle )
MOB_NPC_APPEARANCE	( FEMALE_PUPPET )
MOB_AGRESSIVNESS		( -100 )
MOB_CLAN					( LIGHTHAVEN )
MOB_LEVEL				( 100 )
MOB_HP					( 1000000 )
MOB_DODGE_SKILL		( 65535 )
MOB_AC					( 1000000 )
MOB_XP_PER_HIT			( 0 )
MOB_XP_DEATH         ( 0 )
MOB_STR              ( 65 )
MOB_DEX              ( 63 )
MOB_END              ( 67 )
MOB_INT              ( 47 )
MOB_WIS              ( 87 )
MOB_WIL              ( 79 )
MOB_LCK              ( 54 )
MOB_CAN_ATTACK       (FALSE)

MOB_FIRE_POWER			( 100 )
MOB_WATER_POWER		( 100 )
MOB_AIR_POWER			( 100 )
MOB_EARTH_POWER		( 100 )
MOB_LIGHT_POWER		( 100 )
MOB_DARK_POWER			( 100 )

MOB_FIRE_RESIST		( 5000 )
MOB_WATER_RESIST		( 5000 )
MOB_AIR_RESIST			( 5000 )
MOB_EARTH_RESIST		( 5000 )
MOB_LIGHT_RESIST		( 5000 )
MOB_DARK_RESIST		( 5000 )
MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )

SET_MONSTER( Female_Brigand )
MOB_NPC_APPEARANCE              ( HUMAN_PAYSANNE )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 65 )
MOB_DEX                         ( 63 )
MOB_END                         ( 67 )
MOB_INT                         ( 47 )
MOB_WIS                         ( 87 )
MOB_WIL                         ( 79 )
MOB_LCK                         ( 54 )
MOB_CAN_ATTACK                  (FALSE)

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )


SET_MONSTER( Brigand_Leader )
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 65 )
MOB_DEX                         ( 65 )
MOB_END                         ( 65 )
MOB_INT                         ( 65 )
MOB_WIS                         ( 65 )
MOB_WIL                         ( 65 )
MOB_LCK                         ( 65 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL                (   250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE           (   100 )
MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
MOB_DRESS_HELM ( ELVEN_HAT ) 
MOB_DRESS_LEGS ( STUDDEDLEG )
MOB_DRESS_WEAPON ( DAGGER )
//MOB_DRESS_SHIELD
MOB_DRESS_CAPE ( REDCAPE )

SET_MONSTER( _Mhorgwloth )
MOB_NPC_APPEARANCE              ( TROLL )
MOB_AGRESSIVNESS                ( -100 )
MOB_SPEED                       ( 65, dice( 10, 375 ), 30, dice( 7, 250 ) )
MOB_CLAN                        ( ORKANIS )
MOB_LEVEL                       ( 30 )
MOB_HP                          ( 581 )
MOB_DODGE_SKILL                 ( 130 )                
MOB_AC                          ( 15 )
MOB_XP_PER_HIT                  ( 7.94 )
MOB_XP_DEATH                    ( 2308.44 )
MOB_MIN_GOLD                    ( 106 )
MOB_MAX_GOLD                    ( 330 )
MOB_STR                         ( 45 )
MOB_DEX                         ( 41 )
MOB_END                         ( 41 )
MOB_INT                         ( 51 )
MOB_WIS                         ( 41)
MOB_WIL                         ( 41 )
MOB_LCK                         ( 21 )
MOB_CAN_ATTACK                  (TRUE)

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 79 )
MOB_WATER_RESIST      ( 79 )
MOB_AIR_RESIST        ( 79 )
MOB_EARTH_RESIST      ( 79 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 79 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL                (   370 )
MOB_ATTACK_DMG_ROLL   (	"1d36+27" )
MOB_ATTACK_PERCENTAGE           (   100 )

MOB_ITEM( __OBJ_POTION_OF_MANA, 20 )
MOB_ITEM( __OBJ_TROLL_CLUB, 25 )

SET_MONSTER( _RenegadeOrcLeader ) // Boss
MOB_NPC_APPEARANCE              ( ORC )
MOB_AGRESSIVNESS                ( -100 )
MOB_SPEED                       ( 65, dice( 10, 375 ), 30, dice( 7, 250 ) )
MOB_CLAN                        ( JARKO )
MOB_LEVEL                       ( 25 )
MOB_HP                          ( 926 )
MOB_DODGE_SKILL                 ( 110 )
MOB_AC                          ( 12 )
MOB_XP_PER_HIT                  ( 3.49 )
MOB_XP_DEATH                    ( 1620.1 )
MOB_MIN_GOLD                    ( 88 )
MOB_MAX_GOLD                    ( 274 )
MOB_STR                         ( 40 )
MOB_DEX                         ( 37 )
MOB_END                         ( 37 )
MOB_INT                         ( 45 )
MOB_WIS                         ( 37 )
MOB_WIL                         ( 37 )
MOB_LCK                         ( 20 )
MOB_CAN_ATTACK                  (TRUE)

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 82 )
MOB_WATER_RESIST      ( 82 )
MOB_AIR_RESIST        ( 109 )
MOB_EARTH_RESIST      ( 54 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 82 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL                (   310 )
MOB_ATTACK_DMG_ROLL   (	"1d29+21" )
MOB_ATTACK_PERCENTAGE           (   100 )

MOB_ITEM( __OBJ_LIGHT_HEALING_POTION, 15 )
MOB_ITEM( __OBJ_GOLDEN_BRACELET, 9 )
MOB_ITEM( __OBJ_GOLDEN_RING, 5 )
MOB_ITEM( __OBJ_ROUND_SHIELD, 4 )

SET_MONSTER( Male_Brigand )
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 65 )
MOB_DEX                         ( 65 )
MOB_END                         ( 65 )
MOB_INT                         ( 65 )
MOB_WIS                         ( 65 )
MOB_WIL                         ( 65 )
MOB_LCK                         ( 65 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL                (   250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE           (   100 )
MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
MOB_DRESS_HELM ( LEATHER_HELM )
MOB_DRESS_LEGS ( STUDDEDLEG )
MOB_DRESS_WEAPON ( DAGGER )
//MOB_DRESS_SHIELD
//MOB_DRESS_CAPE 

SET_MONSTER( YrianNPC )
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 20 )
MOB_DEX                         ( 24 )
MOB_END                         ( 22 )
MOB_INT                         ( 20 )
MOB_WIS                         ( 21 )
MOB_WIL                         ( 25 )
MOB_LCK                         ( 22 )               

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE   ( 100 )

MOB_DRESS_BODY ( MAGEROBE )
// MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_WEAPON ( STAFF3 ) 

SET_MONSTER( Old_Bald_Hermit )
MOB_NPC_APPEARANCE              ( PUPPET )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 20 )
MOB_DEX                         ( 24 )
MOB_END                         ( 22 )
MOB_INT                         ( 20 )
MOB_WIS                         ( 21 )
MOB_WIL                         ( 25 )
MOB_LCK                         ( 22 )               

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE   ( 100 )
MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
// MOB_DRESS_GLOVES 
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE 

SET_MONSTER( Lower_Rank_Druid )
MOB_NPC_APPEARANCE              ( HUMAN_PEASANT )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 20 )
MOB_DEX                         ( 24 )
MOB_END                         ( 22 )
MOB_INT                         ( 20 )
MOB_WIS                         ( 21 )
MOB_WIL                         ( 25 )
MOB_LCK                         ( 22 )               
MOB_CAN_ATTACK                  (FALSE)

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )


SET_MONSTER( Samaritan )
MOB_NPC_APPEARANCE              ( HUMAN_PEASANT )
MOB_AGRESSIVNESS                ( -100 )
MOB_CLAN                        ( LIGHTHAVEN )
MOB_LEVEL                       ( 100 )
MOB_HP                          ( 1000000 )
MOB_DODGE_SKILL                 ( 65535 )
MOB_AC                          ( 1000000 )
MOB_XP_PER_HIT                  ( 0 )
MOB_XP_DEATH                    ( 0 )
MOB_STR                         ( 20 )
MOB_DEX                         ( 24 )
MOB_END                         ( 22 )
MOB_INT                         ( 20 )
MOB_WIS                         ( 21 )
MOB_WIL                         ( 25 )
MOB_LCK                         ( 22 )               
MOB_CAN_ATTACK                  (FALSE)

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 5000 )
MOB_WATER_RESIST      ( 5000 )
MOB_AIR_RESIST        ( 5000 )
MOB_EARTH_RESIST      ( 5000 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 5000 )

SET_MONSTER( LyriaNPC ) 
MOB_NPC_APPEARANCE	( FEMALE_PUPPET ) 
MOB_AGRESSIVNESS		( -100 )
MOB_CLAN					( LIGHTHAVEN )
MOB_LEVEL				( 100 )
MOB_HP					( 1000000 )
MOB_DODGE_SKILL		( 65535 )
MOB_AC					( 1000000 )
MOB_XP_PER_HIT			( 0 )
MOB_XP_DEATH			( 0 )
MOB_STR					( 20 )
MOB_DEX					( 24 )
MOB_END					( 22 )
MOB_INT					( 20 )
MOB_WIS					( 21 )
MOB_WIL					( 25 )
MOB_LCK					( 22 )               

MOB_FIRE_POWER			( 100 )
MOB_WATER_POWER		( 100 )
MOB_AIR_POWER			( 100 )
MOB_EARTH_POWER		( 100 )
MOB_LIGHT_POWER		( 100 )
MOB_DARK_POWER			( 100 )

MOB_FIRE_RESIST		( 5000 )
MOB_WATER_RESIST		( 5000 )
MOB_AIR_RESIST			( 5000 )
MOB_EARTH_RESIST		( 5000 )
MOB_LIGHT_RESIST		( 5000 )
MOB_DARK_RESIST		( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE   ( 100 )

MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
MOB_DRESS_HELM ( CHAIN_COIF )
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
MOB_DRESS_WEAPON(  SHORT_SWORD ) 


	CreateNPC();
CLOSE_MONSTER_STAT_SETUP
		
void MonsterStatDestroy(){
}






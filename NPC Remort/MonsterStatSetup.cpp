#include <NPCStructure.h>
#pragma hdrstop
#include <DLLCreatures.h>

//  -- Remort NPC start -- 

NPCstructure::NPC MakrshPtanghNPC; 
NPCstructure::NPC MakrshPtangh2NPC; 
NPCstructure::NPC MakrshPtanghSpawnerNPC; 


NPCstructure::NPC ArchibaldNPC;  
NPCstructure::NPC WardenAthenaNPC; 
NPCstructure::NPC WarlordGrauswaldNPC; 
NPCstructure::NPC PortalNPC;
NPCstructure::NPC DoorNPC;
NPCstructure::NPC FlippedDoorNPC;
NPCstructure::NPC WardenVortimerNPC;
NPCstructure::NPC WardenBacchusNPC;
NPCstructure::NPC ColosseumClerkNPC;

// Psykowasp hive 

NPCstructure::NPC PsykowaspQueenNPC;
NPCstructure::NPC PsykowaspConsortNPC;

// Madrigan's mad house. 

NPCstructure::NPC MadMadriganNPC;     // Level 35 NPC
NPCstructure::NPC DoktorSpineNPC;     // Level 30 NPC
NPCstructure::NPC DrVonPyreNPC;       // Level 30 NPC
NPCstructure::NPC MadPatientNPC;      // Level 15
NPCstructure::NPC LoonNPC;            // Level 17
NPCstructure::NPC CrazedNurseNPC;     // Level 18
NPCstructure::NPC RavingLunaticNPC;   // Level 20 
NPCstructure::NPC DerangedOrderlyNPC; // Level 22
NPCstructure::NPC MadManNPC;          // Level 25
NPCstructure::NPC MOBRunawayPatientNPC; 
// No Return Forest

NPCstructure::NPC ForestWandererNPC; 

// Colosseum

NPCstructure::NPC ArenaMob40NPC;      // Level 40
NPCstructure::NPC ArenaMob50NPC;      // Level 50
NPCstructure::NPC ArenaMob60NPC;      // Level 60
NPCstructure::NPC ArenaMob70NPC;      // Level 70
NPCstructure::NPC ArenaMob80NPC;      // Level 80
NPCstructure::NPC ArenaMob90NPC;      // Level 90
NPCstructure::NPC ArenaMob100NPC;     // Level 100
NPCstructure::NPC ArenaMob110NPC;     // Level 110
NPCstructure::NPC ArenaMob120NPC;     // Level 120
NPCstructure::NPC ArenaMob130NPC;     // Level 130
NPCstructure::NPC ArenaMob140NPC;     // Level 140
NPCstructure::NPC ArenaMob150NPC;     // Level 150
NPCstructure::NPC ArenaMob160NPC;     // Level 160
NPCstructure::NPC ArenaMob170NPC;     // Level 170
NPCstructure::NPC ArenaMob180NPC;     // Level 180
NPCstructure::NPC ArenaMob190NPC;     // Level 190
NPCstructure::NPC ArenaMob200NPC;     // Level 200
NPCstructure::NPC ArenaMob225NPC;     // Level 225
NPCstructure::NPC ArenaMob250NPC;     // Level 250
NPCstructure::NPC ArenaMob275NPC;     // Level 275
NPCstructure::NPC ArenaMob300NPC;     // Level 300
NPCstructure::NPC ArenaMob325NPC;     // Level 325
NPCstructure::NPC ArenaMob350NPC;     // Level 350
NPCstructure::NPC ArenaMob375NPC;     // Level 375
NPCstructure::NPC ArenaMob400NPC;     // Level 400
NPCstructure::NPC ArenaMob425NPC;     // Level 425
NPCstructure::NPC ArenaMob450NPC;     // Level 450
NPCstructure::NPC ArenaMob475NPC;     // Level 475
NPCstructure::NPC ArenaMob500NPC;     // Level 500


// XP Colosseum monsters 
NPCstructure::NPC ArenaMobXP40NPC;      // Level 40
NPCstructure::NPC ArenaMobXP50NPC;      // Level 50
NPCstructure::NPC ArenaMobXP60NPC;      // Level 60
NPCstructure::NPC ArenaMobXP70NPC;      // Level 70
NPCstructure::NPC ArenaMobXP80NPC;      // Level 80
NPCstructure::NPC ArenaMobXP90NPC;      // Level 90
NPCstructure::NPC ArenaMobXP100NPC;     // Level 100
NPCstructure::NPC ArenaMobXP110NPC;     // Level 110
NPCstructure::NPC ArenaMobXP120NPC;     // Level 120
NPCstructure::NPC ArenaMobXP130NPC;     // Level 130
NPCstructure::NPC ArenaMobXP140NPC;     // Level 140
NPCstructure::NPC ArenaMobXP150NPC;     // Level 150
NPCstructure::NPC ArenaMobXP160NPC;     // Level 160
NPCstructure::NPC ArenaMobXP170NPC;     // Level 170
NPCstructure::NPC ArenaMobXP180NPC;     // Level 180
NPCstructure::NPC ArenaMobXP190NPC;     // Level 190
NPCstructure::NPC ArenaMobXP200NPC;     // Level 200
NPCstructure::NPC ArenaMobXP225NPC;     // Level 225
NPCstructure::NPC ArenaMobXP250NPC;     // Level 250
NPCstructure::NPC ArenaMobXP275NPC;     // Level 275
NPCstructure::NPC ArenaMobXP300NPC;     // Level 300
NPCstructure::NPC ArenaMobXP325NPC;     // Level 325
NPCstructure::NPC ArenaMobXP350NPC;     // Level 350
NPCstructure::NPC ArenaMobXP375NPC;     // Level 375
NPCstructure::NPC ArenaMobXP400NPC;     // Level 400
NPCstructure::NPC ArenaMobXP425NPC;     // Level 425
NPCstructure::NPC ArenaMobXP450NPC;     // Level 450
NPCstructure::NPC ArenaMobXP475NPC;     // Level 475
NPCstructure::NPC ArenaMobXP500NPC;     // Level 500
NPCstructure::NPC ColosseumClerkXPNPC;  //DC Addition


void CreateNPC( void );

INIT_MONSTER_STAT_SETUP 

SET_MONSTER           ( MOBRunawayPatientNPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_CLAN              ( PEACE )  
MOB_HP                ( 396 )    
MOB_DODGE_SKILL       ( 98 )
MOB_AC                ( 11 )
MOB_LEVEL             ( 22 )
MOB_XP_PER_HIT        ( 3.24 )
MOB_XP_DEATH          ( 641.42 )
MOB_MIN_GOLD          ( 39 )
MOB_MAX_GOLD          ( 121 )
MOB_STR               ( 37 )
MOB_DEX               ( 34 )
MOB_END               ( 34 )
MOB_INT               ( 41 )
MOB_WIS               ( 34 )
MOB_WIL               ( 34 )
MOB_LCK               ( 19 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 83 )
MOB_WATER_RESIST      ( 83 )
MOB_AIR_RESIST        ( 83 )
MOB_EARTH_RESIST      ( 83 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 55 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 274 )
MOB_ATTACK_DMG_ROLL   ( "1d25+18" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 19  MAXdam: 43  Average: 31 

MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON( STAFF1 ) 
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

MOB_ITEM( __OBJ_MANA_ELIXIR, 1 ) 
MOB_ITEM( __OBJ_BROOM, 1 ) 
MOB_ITEM( __OBJ_J4_PERMIT, 100 ) 

SET_MONSTER( ArchibaldNPC ) 
MOB_NPC_APPEARANCE	( PUPPET )
MOB_AGRESSIVNESS		( -100 )
MOB_CLAN					( PEACE )
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
MOB_CAN_ATTACK        ( FALSE )

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

SET_MONSTER( ForestWandererNPC ) 
MOB_APPEARANCE			( INVISIBLE_THIEF )      // Appearance: 21042 Corpse: 15004
MOB_AGRESSIVNESS		( -100 )
MOB_CLAN					( PEACE )
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


SET_MONSTER( MakrshPtanghNPC ) 
MOB_AGRESSIVNESS      ( -100 ) 
MOB_APPEARANCE        ( LICH ) 
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 1000000 )     
MOB_DODGE_SKILL       ( 65535 )
MOB_AC                ( 1000000 )
MOB_LEVEL             ( 200 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 215 )
MOB_DEX               ( 194 )
MOB_END               ( 194 )
MOB_INT               ( 255 )
MOB_WIS               ( 194 )
MOB_WIL               ( 194 )
MOB_LCK               ( 55 )

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
MOB_CAN_ATTACK        ( FALSE )

SET_MONSTER( MakrshPtangh2NPC ) 
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( LICH ) 
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 52500 )     
MOB_DODGE_SKILL       ( 890 )
MOB_AC                ( 100 )
MOB_LEVEL             ( 200 )
MOB_XP_PER_HIT        ( 50 )//BLBL 60=>55 // steph 50 au lieu de 55
MOB_XP_DEATH          ( 200000 )
MOB_MIN_GOLD          ( 400 )
MOB_MAX_GOLD          ( 1500 )
MOB_STR               ( 215 )
MOB_DEX               ( 194 )
MOB_END               ( 194 )
MOB_INT               ( 255 )
MOB_WIS               ( 200 )
MOB_WIL               ( 200 )
MOB_LCK               ( 55 )

MOB_FIRE_POWER        ( 150 )
MOB_WATER_POWER       ( 200 )
MOB_AIR_POWER         ( 150 )
MOB_EARTH_POWER       ( 200 )
MOB_LIGHT_POWER       ( 150 )
MOB_DARK_POWER        ( 150 )

MOB_FIRE_RESIST       ( 124 )
MOB_WATER_RESIST      ( 252 )
MOB_AIR_RESIST        ( 188 )
MOB_EARTH_RESIST      ( 188 )
MOB_LIGHT_RESIST      ( 124 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10708 )
MOB_ATTACK_PERCENTAGE( 15 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10709 )
MOB_ATTACK_PERCENTAGE( 15 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10710 )
MOB_ATTACK_PERCENTAGE( 15 )
MOB_CREATE_SPELL_ATTACK( 0, 25 ) 
MOB_ATTACK_SPELL( 10596 )
MOB_ATTACK_PERCENTAGE( 5 )
MOB_CREATE_SPELL_ATTACK( 0, 25 ) 
MOB_ATTACK_SPELL( 10618 )
MOB_ATTACK_PERCENTAGE( 8 )//BLBL 10=>8

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2410 )
MOB_ATTACK_DMG_ROLL   ( "1d390+360" )//BLBLBL augmenté le bonus dégats de 319 à 360
MOB_ATTACK_PERCENTAGE ( 40 )

MOB_ITEM( __OBJ_BLACK_LOCUST_COMPOSITE_BOW_3, 3 ) //BLBLBL baisse le taux de drop de 4 à 1 // steph 3 au lieu de 1
MOB_ITEM( __OBJ_ANCIENT_TWO_HANDED_SWORD_3, 1 ) 
MOB_ITEM( __OBJ_ANCIENT_BROAD_AXE_3, 1 ) 
MOB_ITEM( __OBJ_ANCIENT_MORNINGSTAR_3, 1 ) 
MOB_ITEM( __OBJ_SHIELD_OF_THE_AGES, 2 ) 
MOB_ITEM( __OBJ_ANCIENT_PLATEMAIL_ARMOR, 1 ) 
MOB_ITEM( __OBJ_ANCIENT_PLATE_PROTECTOR, 4 ) 
MOB_ITEM( __OBJ_ANCIENT_PLATEMAIL_GAUNTLETS, 5 ) 
MOB_ITEM( __OBJ_ANCIENT_PLATEMAIL_HELMET, 2 ) 
MOB_ITEM( __OBJ_ANCIENT_PLATEMAIL_LEGGINGS, 4 ) 
MOB_ITEM( __OBJ_ANCIENT_PLATEMAIL_BOOTS, 5 ) 

SET_MONSTER           ( MakrshPtanghSpawnerNPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SKELETON_CENTAUR )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 6334 )
MOB_DODGE_SKILL       ( 620 )//BLBL 610=>620
MOB_AC                ( 80 )//BLBL 75=>80
MOB_LEVEL             ( 150 )
MOB_XP_PER_HIT        ( 9 )//BLBL 11.04 => 10.04 // steph 9 au lieu de 10.04
MOB_XP_DEATH          ( 34954.67 )
MOB_MIN_GOLD          ( 269 )
MOB_MAX_GOLD          ( 825 )
MOB_STR               ( 165 )
MOB_DEX               ( 149 )
MOB_END               ( 149 )
MOB_INT               ( 195 )
MOB_WIS               ( 149 )
MOB_WIL               ( 149 )
MOB_LCK               ( 45 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 31 )
MOB_WATER_RESIST      ( 63 )
MOB_AIR_RESIST        ( 47 )
MOB_EARTH_RESIST      ( 47 )
MOB_LIGHT_RESIST      ( 47 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10090 )
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1810 )
MOB_ATTACK_DMG_ROLL   ( "1d 258 + 242 " )//BLBL +202 => +242
MOB_ATTACK_PERCENTAGE ( 50 )
// MINdam: 203  MAXdam: 460  Average: 331.5 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// START OF ////////////////////////////////////////////////
///////////////////////////////////////////  MAD MADRIGAN'S MAD HOUSE ////////////////////////////////////////



SET_MONSTER( WardenVortimerNPC ) 
MOB_NPC_APPEARANCE	( PUPPET )
MOB_AGRESSIVNESS		( -100 )
MOB_CLAN					( PEACE )
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

SET_MONSTER( MadManNPC ) 
MOB_SPEED             ( 65, dice( 1, 1500, 750 ), 25, dice( 1, 500, 250 ) )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_CLAN              ( MADRIGAN )
MOB_HP                ( 463 )     
MOB_DODGE_SKILL       ( 110 )
MOB_AC                ( 12 )
MOB_LEVEL             ( 25 )
MOB_XP_PER_HIT        ( 3.50 )
MOB_XP_DEATH          ( 810.06 )
MOB_MIN_GOLD          ( 44 )
MOB_MAX_GOLD          ( 137 )
MOB_STR               ( 40 )
MOB_DEX               ( 37 )
MOB_END               ( 37 )
MOB_INT               ( 45 )
MOB_WIS               ( 37 )
MOB_WIL               ( 37 )
MOB_LCK               ( 20 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 82 )
MOB_WATER_RESIST      ( 82 )
MOB_AIR_RESIST        ( 82 )
MOB_EARTH_RESIST      ( 82 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 54 )

MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10122 )             // heal serious
MOB_ATTACK_PERCENTAGE( 10 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10119 )             // drain life
MOB_ATTACK_PERCENTAGE( 10 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10086 )             // ice shard
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10094 )             // stone shard
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10096 )             // fire bolt
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10120 )             // lightning bolt
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 310 )
MOB_ATTACK_DMG_ROLL   ( "1d29+21" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 22  MAXdam: 50  Average: 36 

MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON( OGRECLUB ) 
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

MOB_ITEM( __OBJ_BLOODSTAINED_BROADSWORD, 1 ) 
MOB_ITEM( __OBJ_RING_OF_THE_BERSERKER, 1 ) 
MOB_ITEM( __OBJ_STRAIGHT_JACKET_1, 3 ) 
MOB_ITEM( __OBJ_MANA_ELIXIR, 3 )
MOB_ITEM( __OBJ_POTION_OF_FURY, 5 ) 
MOB_ITEM( __OBJ_C2_PERMIT, 15 ) 
MOB_ITEM( __OBJ_F1_PERMIT, 30 ) 

SET_MONSTER           ( DerangedOrderlyNPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_CLAN              ( MADRIGAN )  
MOB_HP                ( 396 )    
MOB_DODGE_SKILL       ( 98 )
MOB_AC                ( 11 )
MOB_LEVEL             ( 22 )
MOB_XP_PER_HIT        ( 3.24 )
MOB_XP_DEATH          ( 641.42 )
MOB_MIN_GOLD          ( 39 )
MOB_MAX_GOLD          ( 121 )
MOB_STR               ( 37 )
MOB_DEX               ( 34 )
MOB_END               ( 34 )
MOB_INT               ( 41 )
MOB_WIS               ( 34 )
MOB_WIL               ( 34 )
MOB_LCK               ( 19 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 83 )
MOB_WATER_RESIST      ( 83 )
MOB_AIR_RESIST        ( 83 )
MOB_EARTH_RESIST      ( 83 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 55 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 274 )
MOB_ATTACK_DMG_ROLL   ( "1d25+18" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 19  MAXdam: 43  Average: 31 

MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON( STAFF1 ) 
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

MOB_ITEM( __OBJ_BROOM, 2 )
MOB_ITEM( __OBJ_TORCH, 1 )
MOB_ITEM( __OBJ_CROWN_OF_THE_VISIONARY, 1 ) 
MOB_ITEM( __OBJ_RING_OF_THE_ASSASSIN, 1 )  
MOB_ITEM( __OBJ_POTION_OF_MANA, 1 )
MOB_ITEM( __OBJ_C5_PERMIT, 2 ) 
MOB_ITEM( __OBJ_J3_PERMIT, 50 ) 

SET_MONSTER           ( RavingLunaticNPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_CLAN              ( MADRIGAN )
MOB_HP                ( 353 )
MOB_DODGE_SKILL       ( 90 )
MOB_AC                ( 10 )
MOB_LEVEL             ( 20 )
MOB_XP_PER_HIT        ( 3.08 )
MOB_XP_DEATH          ( 543.00 )
MOB_MIN_GOLD          ( 35 )
MOB_MAX_GOLD          ( 110 )
MOB_STR               ( 35 )
MOB_DEX               ( 32 )
MOB_END               ( 32 )
MOB_INT               ( 39 )
MOB_WIS               ( 32 )
MOB_WIL               ( 32 )
MOB_LCK               ( 19 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 84 )
MOB_WATER_RESIST      ( 84 )
MOB_AIR_RESIST        ( 84 )
MOB_EARTH_RESIST      ( 84 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 56 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 250 )
MOB_ATTACK_DMG_ROLL   ( "1d23+16")
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 17  MAXdam: 39  Average: 28 

// MOB_DRESS_BODY 
// MOB_DRESS_FEET 
// MOB_DRESS_LEGS 
MOB_DRESS_WEAPON ( GOLDEN_STAR ) 
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM( GOLDENCROWN ) 
// MOB_DRESS_SHIELD
MOB_DRESS_CAPE( REDCAPE ) 

MOB_ITEM( __OBJ_SHIMMERING_WHITE_ROBE, 3 ) 
MOB_ITEM( __OBJ_SILVER_SPOON_OF_THE_PROPHET, 1 ) 
MOB_ITEM( __OBJ_HELMET_OF_THE_CLAIRVOYANT, 1 ) 
MOB_ITEM( __OBJ_LIGHT_HEALING_POTION, 2 ) 
MOB_ITEM( __OBJ_MANA_ELIXIR, 2 ) 
MOB_ITEM( __OBJ_G4_PERMIT, 40 ) 
MOB_ITEM( __OBJ_I4_PERMIT, 20 ) 

SET_MONSTER           ( CrazedNurseNPC )
MOB_AGRESSIVNESS      ( 50 ) 
MOB_NPC_APPEARANCE    ( FEMALE_PUPPET ) 
MOB_CLAN              ( MADRIGAN )
MOB_HP                ( 313 )
MOB_DODGE_SKILL       ( 82 )
MOB_AC                ( 9 )
MOB_LEVEL             ( 18 )
MOB_XP_PER_HIT        ( 2.90 )
MOB_XP_DEATH          ( 453.29 )
MOB_MIN_GOLD          ( 32 )
MOB_MAX_GOLD          ( 99 )
MOB_STR               ( 33 )
MOB_DEX               ( 31 )
MOB_END               ( 31 )
MOB_INT               ( 36 )
MOB_WIS               ( 31 )
MOB_WIL               ( 31 )
MOB_LCK               ( 18 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 85 )
MOB_WATER_RESIST      ( 85 )
MOB_AIR_RESIST        ( 85 )
MOB_EARTH_RESIST      ( 85 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 56 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 226 )
MOB_ATTACK_DMG_ROLL   ( "1d21+14" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 15  MAXdam: 35  Average: 25 

MOB_DRESS_BODY ( WHITEROBE ) 
// MOB_DRESS_FEET 
// MOB_DRESS_LEGS 
MOB_DRESS_WEAPON ( DAGGER ) 
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

MOB_ITEM( __OBJ_J1_PERMIT, 10 ) 
MOB_ITEM( __OBJ_A3_PERMIT, 10 ) 
MOB_ITEM( __OBJ_B1_PERMIT, 20 )  
MOB_ITEM( __OBJ_C5_PERMIT,  5 ) 
MOB_ITEM( __OBJ_FINE_STEEL_DAGGER, 3 ) 
MOB_ITEM( __OBJ_SHIMMERING_WHITE_ROBE, 3 ) 
MOB_ITEM( __OBJ_DEIFIC_HEALING_POTION, 0.5 ) 
MOB_ITEM( __OBJ_CRITICAL_HEALING_POTION, 1 ) 
MOB_ITEM( __OBJ_SERIOUS_HEALING_POTION, 2 ) 
MOB_ITEM( __OBJ_HEALING_POTION, 4 ) 
MOB_ITEM( __OBJ_LIGHT_HEALING_POTION, 8 ) 

SET_MONSTER           ( LoonNPC )
MOB_AGRESSIVNESS      ( 75 ) 
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_CLAN              ( MADRIGAN )
MOB_HP                ( 293 )
MOB_DODGE_SKILL       ( 78 )
MOB_AC                ( 8 )
MOB_LEVEL             ( 17 )
MOB_XP_PER_HIT        ( 2.80 )
MOB_XP_DEATH          ( 410.70 )
MOB_MIN_GOLD          ( 30 )
MOB_MAX_GOLD          ( 93 )
MOB_STR               ( 32 )
MOB_DEX               ( 30 )
MOB_END               ( 30 )
MOB_INT               ( 35 )
MOB_WIS               ( 30 )
MOB_WIL               ( 30 )
MOB_LCK               ( 18 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 86 )
MOB_WATER_RESIST      ( 86 )
MOB_AIR_RESIST        ( 86 )
MOB_EARTH_RESIST      ( 86 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 57 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 214 )
MOB_ATTACK_DMG_ROLL   ( "1d20+13" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 14  MAXdam: 33  Average: 23.5 

MOB_DRESS_BODY ( LEATHER_ARMOR ) 
MOB_DRESS_FEET ( BLACKLEATHER_BOOT ) 
// MOB_DRESS_LEGS 
MOB_DRESS_WEAPON ( WARHAMMER) 
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

MOB_ITEM( __OBJ_D4_PERMIT, 15 ) 
MOB_ITEM( __OBJ_H2_PERMIT, 20 ) 

SET_MONSTER           ( MadPatientNPC )
MOB_AGRESSIVNESS      ( 75 ) 
MOB_APPEARANCE        ( ZOMBIE )
MOB_CLAN              ( MADRIGAN )
MOB_HP                ( 254 )
MOB_DODGE_SKILL       ( 70 )
MOB_AC                ( 7 )
MOB_LEVEL             ( 15 )
MOB_XP_PER_HIT        ( 2.66 )
MOB_XP_DEATH          ( 337.22 )
MOB_MIN_GOLD          ( 26 )
MOB_MAX_GOLD          ( 82 )
MOB_STR               ( 30 )
MOB_DEX               ( 28 )
MOB_END               ( 28 )
MOB_INT               ( 33 )
MOB_WIS               ( 28 )
MOB_WIL               ( 28 )
MOB_LCK               ( 18 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 86 )
MOB_WATER_RESIST      ( 86 )
MOB_AIR_RESIST        ( 86 )
MOB_EARTH_RESIST      ( 86 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 57 )

MOB_CREATE_SPELL_ATTACK( 0, 1 )
MOB_ATTACK_SPELL( 10359 )    
MOB_ATTACK_PERCENTAGE( 2 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 190 )
MOB_ATTACK_DMG_ROLL   ( "1d17+12" )
MOB_ATTACK_PERCENTAGE ( 98 )
// MINdam: 13  MAXdam: 29  Average: 21 

MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON ( DAGGER ) 
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

MOB_ITEM( __OBJ_STRAIGHT_JACKET_1, 5 ) 
MOB_ITEM( __OBJ_LIGHT_HEALING_POTION, 5 ) 
MOB_ITEM( __OBJ_A3_PERMIT, 10 ) 
MOB_ITEM( __OBJ_E5_PERMIT, 20 ) 

SET_MONSTER( DrVonPyreNPC ) 
MOB_SPEED             ( 65, dice( 1, 1500, 750 ), 25, dice( 1, 500, 250 ) )
MOB_AGRESSIVNESS      ( 75 ) 
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_CLAN              ( MADRIGAN )
MOB_HP                ( 581 )
MOB_DODGE_SKILL       ( 130 )
MOB_AC                ( 15 )
MOB_LEVEL             ( 30 )
MOB_XP_PER_HIT        ( 3.97 )
MOB_XP_DEATH          ( 1154.22 )
MOB_MIN_GOLD          ( 53 )
MOB_MAX_GOLD          ( 165 )
MOB_STR               ( 45 )
MOB_DEX               ( 41 )
MOB_END               ( 41 )
MOB_INT               ( 51 )
MOB_WIS               ( 41 )
MOB_WIL               ( 41 )
MOB_LCK               ( 21 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 53 )
MOB_WATER_RESIST      ( 106 )
MOB_AIR_RESIST        ( 79 )
MOB_EARTH_RESIST      ( 79 )
MOB_LIGHT_RESIST      ( 53 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 1, 10 )
MOB_ATTACK_SPELL( 10119 )       // drain life
MOB_ATTACK_PERCENTAGE( 98 )

MOB_CREATE_SPELL_ATTACK( 1, 10 )
MOB_ATTACK_SPELL( 10359 )       // drain life
MOB_ATTACK_PERCENTAGE( 2 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 370 )
MOB_ATTACK_DMG_ROLL   ( "1d36+27" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 28  MAXdam: 63  Average: 45.5 
// MINdam: 28  MAXdam: 63  Average: 45.5 
MOB_DRESS_BODY ( NECROMANROBE )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
// MOB_DRESS_GLOVES 
// MOB_DRESS_HELM ( HORNED_HELMET )
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
MOB_DRESS_WEAPON( DAGGER ) 
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE 

MOB_ITEM( __OBJ_BLOOD_DRINKER, 1 ) 			
MOB_ITEM( __OBJ_GARB_OF_THE_DEAD, 2 ) 
MOB_ITEM( __OBJ_SERIOUS_HEALING_POTION, 1 ) 
MOB_ITEM( __OBJ_MANASTONE, 1 ) 

SET_MONSTER( DoktorSpineNPC ) 
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_CLAN              ( MADRIGAN )
MOB_HP                ( 581 )     
MOB_DODGE_SKILL       ( 130 )
MOB_AC                ( 15 )
MOB_LEVEL             ( 30 )
MOB_XP_PER_HIT        ( 3.97 )
MOB_XP_DEATH          ( 1154.22 )
MOB_MIN_GOLD          ( 53 )
MOB_MAX_GOLD          ( 165 )
MOB_STR               ( 45 )
MOB_DEX               ( 41 )
MOB_END               ( 41 )
MOB_INT               ( 51 )
MOB_WIS               ( 41 )
MOB_WIL               ( 41 )
MOB_LCK               ( 21 )

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
MOB_DARK_RESIST       ( 53 )

MOB_CREATE_SPELL_ATTACK( 1, 8 ) 
MOB_ATTACK_SPELL( 10317 )             // terror 
MOB_ATTACK_PERCENTAGE( 1 ) 
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10122 )             // heal serious
MOB_ATTACK_PERCENTAGE( 9 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10119 )             // drain life
MOB_ATTACK_PERCENTAGE( 10 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10086 )             // ice shard
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10094 )             // stone shard
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10096 )             // fire bolt
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10120 )             // lightning bolt
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 370 )
MOB_ATTACK_DMG_ROLL   ( "1d36+27" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 28  MAXdam: 63  Average: 45.5 
MOB_DRESS_BODY ( NECROMANROBE )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
// MOB_DRESS_GLOVES 
MOB_DRESS_HELM ( HORNED_HELMET )
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE 
  
MOB_ITEM( __OBJ_BACKBREAKER, 1 ) 
MOB_ITEM( __OBJ_MANASTONE, 1 ) 
MOB_ITEM( __OBJ_LIGHT_HEALING_POTION, 1 ) 

SET_MONSTER( MadMadriganNPC ) 
MOB_SPEED             ( 65, dice( 1, 1500, 750 ), 25, dice( 1, 500, 250 ) )
MOB_AGRESSIVNESS      ( 50 ) 
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_CLAN              ( MADRIGAN ) 
MOB_HP                ( 710 ) 
MOB_DODGE_SKILL       ( 150 )
MOB_AC                ( 17 )
MOB_LEVEL             ( 35 )
MOB_XP_PER_HIT        ( 4.44 )
MOB_XP_DEATH          ( 1575.00 )
MOB_MIN_GOLD          ( 62 )
MOB_MAX_GOLD          ( 192 )
MOB_STR               ( 50 )
MOB_DEX               ( 46 )
MOB_END               ( 46 )
MOB_INT               ( 57 )
MOB_WIS               ( 46 )
MOB_WIL               ( 46 )
MOB_LCK               ( 22 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 77 )
MOB_WATER_RESIST      ( 77 )
MOB_AIR_RESIST        ( 77 )
MOB_EARTH_RESIST      ( 77 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 103 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 430 )
MOB_ATTACK_DMG_ROLL   ( "1d45+33")
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 34  MAXdam: 78  Average: 56 

MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10122 )       // heal serious
MOB_ATTACK_PERCENTAGE( 15 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10119 )       // drain life
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10094 )       // stone shard
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10096 )       // fire bolt
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10379 )       // piercing worms
MOB_ATTACK_PERCENTAGE( 5 )
MOB_CREATE_SPELL_ATTACK( 1, 8 )
MOB_ATTACK_SPELL( 10359 )       // mind rot
MOB_ATTACK_PERCENTAGE( 5 )

// MOB_DRESS_BODY
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
// MOB_DRESS_GLOVES 
MOB_DRESS_HELM ( GOLDENCROWN )
MOB_DRESS_LEGS ( PLATE_LEGS ) 
MOB_DRESS_WEAPON ( REAL_DARKSWORD ) 
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE 
							 
MOB_ITEM( __OBJ_RING_OF_THE_BERSERKER, 3 ) 
MOB_ITEM( __OBJ_MADRIGAN_KEY, 25 )  
MOB_ITEM( __OBJ_BONESWORD_OF_THE_BERSERKER, 2 )  
// MOB_ITEM( __OBJ_VOYEUR_CLOAK, 0.4 )
MOB_ITEM( __OBJ_ELVEN_LEATHER_LEGGINGS, 2 ) 
MOB_ITEM( __OBJ_ELVEN_LEATHER_HELMET, 2 )     
MOB_ITEM( __OBJ_ELVEN_LEATHER_ARMOR, 1 )     
MOB_ITEM( __OBJ_ELVEN_LEATHER_GLOVES, 2 )    
MOB_ITEM( __OBJ_ELVEN_LEATHER_BOOTS, 2 )     
MOB_ITEM( __OBJ_SERIOUS_HEALING_POTION, 5 ) 
MOB_ITEM( __OBJ_POTION_OF_FURY, 5 ) 
MOB_ITEM( __OBJ_SCROLL_OF_RECALL, 5 ) 


/////////////////////////////////////////////// MADRIGAN'S MAD HOUSE /////////////////////////////////////////
//////////////////////////////////////////////////// END HERE ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

SET_MONSTER( WarlordGrauswaldNPC ) 
MOB_NPC_APPEARANCE   ( PUPPET )
MOB_AGRESSIVNESS     ( -100 )
MOB_CLAN             ( LIGHTHAVEN )
MOB_LEVEL            ( 100 )    
MOB_HP               ( 1000000 )
MOB_DODGE_SKILL      ( 65535 )
MOB_AC               ( 1000000 )
MOB_XP_PER_HIT       ( 0 )
MOB_XP_DEATH         ( 0 )
MOB_STR              ( 50 )
MOB_DEX              ( 46 )
MOB_END              ( 46 )
MOB_INT              ( 57 )
MOB_WIS              ( 46 )
MOB_WIL              ( 46 )
MOB_LCK              ( 22 )               

MOB_FIRE_POWER       ( 100 )
MOB_WATER_POWER      ( 100 )
MOB_AIR_POWER        ( 100 )
MOB_EARTH_POWER      ( 100 )
MOB_LIGHT_POWER      ( 100 )
MOB_DARK_POWER       ( 100 )

MOB_FIRE_RESIST      ( 5000 )
MOB_WATER_RESIST     ( 5000 )
MOB_AIR_RESIST       ( 5000 )
MOB_EARTH_RESIST     ( 5000 )
MOB_LIGHT_RESIST     ( 5000 )
MOB_DARK_RESIST      ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 370 )
MOB_ATTACK_DMG_ROLL   (	"1d36+27" )
MOB_ATTACK_PERCENTAGE   ( 100 )
MOB_DRESS_BODY ( PLATE_ARMOR_W_SLEEVE )
MOB_DRESS_FEET ( PLATE_BOOT )
MOB_DRESS_GLOVES ( PLATE_GLOVE ) 
MOB_DRESS_LEGS ( PLATE_LEGS )
MOB_DRESS_HELM ( PLATE_HELM )

SET_MONSTER( WardenAthenaNPC ) 
MOB_AGRESSIVNESS      ( -100 ) 
MOB_NPC_APPEARANCE    ( FEMALE_PUPPET )
MOB_CLAN              ( ATHENA_KEEP )
MOB_HP                ( 500 )     
MOB_DODGE_SKILL       ( 131 )
MOB_AC                ( 15 )
MOB_LEVEL             ( 28 )
MOB_XP_PER_HIT        ( 4.08 )
MOB_XP_DEATH          ( 1020.51 )
MOB_MIN_GOLD          ( 50 )
MOB_MAX_GOLD          ( 154 )
MOB_STR               ( 43 )
MOB_DEX               ( 40 )
MOB_END               ( 40 )
MOB_INT               ( 48 )
MOB_WIS               ( 40 )
MOB_WIL               ( 40 )
MOB_LCK               ( 20 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 80 )
MOB_WATER_RESIST      ( 80 )
MOB_AIR_RESIST        ( 80 )
MOB_EARTH_RESIST      ( 80 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 107 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 350 )
MOB_ATTACK_DMG_ROLL   ( "1d37+24")
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 25  MAXdam: 61  Average: 43 

MOB_DRESS_BODY ( PLATE_ARMOR_W_SLEEVE )
MOB_DRESS_FEET ( PLATE_BOOT )
MOB_DRESS_GLOVES ( PLATE_GLOVE ) 
MOB_DRESS_LEGS ( PLATE_LEGS )
MOB_DRESS_HELM ( PLATE_HELM )

MOB_ITEM( __OBJ_CRITICAL_HEALING_POTION, 25 )

SET_MONSTER( WardenBacchusNPC ) 
MOB_NPC_APPEARANCE   ( PUPPET )
MOB_AGRESSIVNESS     ( -100 )
MOB_CLAN             ( LIGHTHAVEN )
MOB_LEVEL            ( 100 )    
MOB_HP               ( 1000000 )
MOB_DODGE_SKILL      ( 65535 )
MOB_AC               ( 1000000 )
MOB_XP_PER_HIT       ( 0 )
MOB_XP_DEATH         ( 0 )
MOB_STR              ( 50 )
MOB_DEX              ( 46 )
MOB_END              ( 46 )
MOB_INT              ( 57 )
MOB_WIS              ( 46 )
MOB_WIL              ( 46 )
MOB_LCK              ( 22 )               

MOB_FIRE_POWER       ( 100 )
MOB_WATER_POWER      ( 100 )
MOB_AIR_POWER        ( 100 )
MOB_EARTH_POWER      ( 100 )
MOB_LIGHT_POWER      ( 100 )
MOB_DARK_POWER       ( 100 )

MOB_FIRE_RESIST      ( 5000 )
MOB_WATER_RESIST     ( 5000 )
MOB_AIR_RESIST       ( 5000 )
MOB_EARTH_RESIST     ( 5000 )
MOB_LIGHT_RESIST     ( 5000 )
MOB_DARK_RESIST      ( 5000 )

MOB_CREATE_PHYSICAL_ATTACK               
MOB_ATTACK_SKILL        ( 370 )
MOB_ATTACK_DMG_ROLL   (	"1d36+27" )
MOB_ATTACK_PERCENTAGE   ( 100 )
MOB_DRESS_BODY ( PLATE_ARMOR_W_SLEEVE )
MOB_DRESS_FEET ( PLATE_BOOT )
MOB_DRESS_GLOVES ( PLATE_GLOVE ) 
MOB_DRESS_LEGS ( PLATE_LEGS )

SET_MONSTER           ( PsykowaspQueenNPC )
MOB_AGRESSIVNESS      ( 50 ) 
MOB_APPEARANCE        ( WASP )
MOB_CLAN              ( PSYKOWASP )
MOB_HP                ( 710 )     
MOB_DODGE_SKILL       ( 150 )
MOB_AC                ( 17 )
MOB_LEVEL             ( 35 )
MOB_XP_PER_HIT        ( 4.44 )
MOB_XP_DEATH          ( 1575.00 )
MOB_MIN_GOLD          ( 62 )
MOB_MAX_GOLD          ( 192 )
MOB_STR               ( 50 )
MOB_DEX               ( 46 )
MOB_END               ( 46 )
MOB_INT               ( 57 )
MOB_WIS               ( 46 )
MOB_WIL               ( 46 )
MOB_LCK               ( 22 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 77 )
MOB_WATER_RESIST      ( 77 )
MOB_AIR_RESIST        ( 51 )
MOB_EARTH_RESIST      ( 103 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 77 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 430 )
MOB_ATTACK_DMG_ROLL   ( "1d45+33" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 34  MAXdam: 78  Average: 56 

MOB_ITEM( __OBJ_ROYAL_HIVE_SAFE_CONDUCT, 25 )
MOB_ITEM( __OBJ_PSYKOWASP_QUEEN_EYES, 20 )
MOB_ITEM( __OBJ_PSYKOWASP_NECTAR, 10 ) 

SET_MONSTER           ( PsykowaspConsortNPC )
MOB_AGRESSIVNESS      ( 50 ) 
MOB_APPEARANCE        ( WASP )
MOB_CLAN              ( PSYKOWASP )
MOB_HP                ( 533 )  
MOB_DODGE_SKILL       ( 122 )
MOB_AC                ( 14 )
MOB_LEVEL             ( 28 )
MOB_XP_PER_HIT        ( 3.78 )
MOB_XP_DEATH          ( 1007.00 )
MOB_MIN_GOLD          ( 50 )
MOB_MAX_GOLD          ( 154 )
MOB_STR               ( 43 )
MOB_DEX               ( 40 )
MOB_END               ( 40 )
MOB_INT               ( 48 )
MOB_WIS               ( 40 )
MOB_WIL               ( 40 )
MOB_LCK               ( 20 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 107 )
MOB_WATER_RESIST      ( 53 )
MOB_AIR_RESIST        ( 53 )
MOB_EARTH_RESIST      ( 107 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 80 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 346 )
MOB_ATTACK_DMG_ROLL   ( "1d34+24")
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 25  MAXdam: 58  Average: 41.5 

MOB_ITEM( __OBJ_PSYKOWASP_NECTAR, 5 ) 

SET_MONSTER( PortalNPC )
MOB_AGRESSIVNESS      ( -100 ) 
MOB_OBJ_APPEARANCE    ( PORTAL )
MOB_CLAN              ( PEACE ) 
MOB_HP                ( 1000000 )
MOB_DODGE_SKILL       ( 65535 )
MOB_AC                ( 1000000 )
MOB_LEVEL             ( 100 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 500 )
MOB_DEX               ( 500 )
MOB_END               ( 500 )
MOB_INT               ( 500 )
MOB_WIS               ( 500 )
MOB_WIL               ( 500 )
MOB_LCK               ( 500 )

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
MOB_CAN_ATTACK        ( FALSE )

SET_MONSTER           ( DoorNPC )
MOB_AGRESSIVNESS      ( -100 ) 
MOB_OBJ_APPEARANCE    ( DOOR_TALK )
MOB_CLAN              ( PEACE )
MOB_HP                ( 1000000 )
MOB_DODGE_SKILL       ( 65535 )
MOB_AC                ( 1000000 )
MOB_LEVEL             ( 200 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 500 )
MOB_DEX               ( 500 )
MOB_END               ( 500 )
MOB_INT               ( 500 )
MOB_WIS               ( 500 )
MOB_WIL               ( 500 )
MOB_LCK               ( 500 )

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
MOB_CAN_ATTACK        ( FALSE )

SET_MONSTER           ( FlippedDoorNPC )
MOB_AGRESSIVNESS      ( -100 ) 
MOB_OBJ_APPEARANCE    ( DOOR_TALK_I )
MOB_CLAN              ( PEACE )
MOB_HP                ( 1000000 )
MOB_DODGE_SKILL       ( 65535 )
MOB_AC                ( 1000000 )
MOB_LEVEL             ( 200 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 500 )
MOB_DEX               ( 500 )
MOB_END               ( 500 )
MOB_INT               ( 500 )
MOB_WIS               ( 500 )
MOB_WIL               ( 500 )
MOB_LCK               ( 500 )

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
MOB_CAN_ATTACK        ( FALSE )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// START OF ////////////////////////////////////////////////
/////////////////////////////////////////////// COLOSSEUM MONSTERS ///////////////////////////////////////////
SET_MONSTER           ( ArenaMob40NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( BAT )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 847 )
MOB_DODGE_SKILL       ( 170 )
MOB_AC                ( 20 ) 
MOB_LEVEL             ( 40 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 55 )
MOB_DEX               ( 50 )
MOB_END               ( 50 )
MOB_INT               ( 63 )
MOB_WIS               ( 50 )
MOB_WIL               ( 50 )
MOB_LCK               ( 23 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 112 )
MOB_WATER_RESIST      ( 112 )
MOB_AIR_RESIST        ( 75 )
MOB_EARTH_RESIST      ( 150 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 112 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 490 )
MOB_ATTACK_DMG_ROLL   ( "1d 53 + 41 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 42  MAXdam: 94  Average: 68 

SET_MONSTER           ( ArenaMob50NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( RAT )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 1153 )
MOB_DODGE_SKILL       ( 210 )
MOB_AC                ( 25 )
MOB_LEVEL             ( 50 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 65 )
MOB_DEX               ( 59 )
MOB_END               ( 59 )
MOB_INT               ( 75 )
MOB_WIS               ( 59 )
MOB_WIL               ( 59 )
MOB_LCK               ( 25 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 105 )
MOB_WATER_RESIST      ( 105 )
MOB_AIR_RESIST        ( 139 )
MOB_EARTH_RESIST      ( 69 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 105 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 610 )
MOB_ATTACK_DMG_ROLL   ( "1d 76 + 59 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 60  MAXdam: 135  Average: 97.5 

SET_MONSTER           ( ArenaMob60NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SMALL_WORM )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 1497 )
MOB_DODGE_SKILL       ( 250 )
MOB_AC                ( 30 )
MOB_LEVEL             ( 60 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 75 )
MOB_DEX               ( 68 )
MOB_END               ( 68 )
MOB_INT               ( 87 )
MOB_WIS               ( 68 )
MOB_WIL               ( 68 )
MOB_LCK               ( 27 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 130 )
MOB_WATER_RESIST      ( 64 )
MOB_AIR_RESIST        ( 97 )
MOB_EARTH_RESIST      ( 97 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 97 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 730 )
MOB_ATTACK_DMG_ROLL   ( "1d 90 + 69 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 70  MAXdam: 159  Average: 114.5 

SET_MONSTER           ( ArenaMob70NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( OOZE )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 1879 )
MOB_DODGE_SKILL       ( 290 )
MOB_AC                ( 35 )
MOB_LEVEL             ( 70 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 85 )
MOB_DEX               ( 77 )
MOB_END               ( 77 )
MOB_INT               ( 99 )
MOB_WIS               ( 77 )
MOB_WIL               ( 77 )
MOB_LCK               ( 29 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 60 )
MOB_WATER_RESIST      ( 121 )
MOB_AIR_RESIST        ( 60 )
MOB_EARTH_RESIST      ( 121 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 91 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 850 )
MOB_ATTACK_DMG_ROLL   ( "1d 110 + 84 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 85  MAXdam: 194  Average: 139.5 

SET_MONSTER           ( ArenaMob80NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SKELETON )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 2301 )
MOB_DODGE_SKILL       ( 330 )
MOB_AC                ( 40 )
MOB_LEVEL             ( 80 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 95 )
MOB_DEX               ( 86 )
MOB_END               ( 86 )
MOB_INT               ( 111 )
MOB_WIS               ( 86 )
MOB_WIL               ( 86 )
MOB_LCK               ( 31 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 55 )
MOB_WATER_RESIST      ( 112 )
MOB_AIR_RESIST        ( 84 )
MOB_EARTH_RESIST      ( 84 )
MOB_LIGHT_RESIST      ( 84 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10614 ) // Mob arena life steal spell
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 970 )
MOB_ATTACK_DMG_ROLL   ( "1d 138 + 107 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 108  MAXdam: 245  Average: 176.5 

SET_MONSTER           ( ArenaMob90NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SPIDER )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 2761 )
MOB_DODGE_SKILL       ( 370 )
MOB_AC                ( 45 )
MOB_LEVEL             ( 90 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 105 )
MOB_DEX               ( 95 )
MOB_END               ( 95 )
MOB_INT               ( 123 )
MOB_WIS               ( 95 )
MOB_WIL               ( 95 )
MOB_LCK               ( 33 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 76 )
MOB_WATER_RESIST      ( 76 )
MOB_AIR_RESIST        ( 102 )
MOB_EARTH_RESIST      ( 51 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 76 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10609 ) // Mob arena lightning bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1090 )
MOB_ATTACK_DMG_ROLL   ( "1d 156 + 120 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 121  MAXdam: 276  Average: 198.5 

SET_MONSTER           ( ArenaMob100NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SNAKE )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 3259 )
MOB_DODGE_SKILL       ( 410 )
MOB_AC                ( 50 )
MOB_LEVEL             ( 100 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 115 )
MOB_DEX               ( 104 )
MOB_END               ( 104 )
MOB_INT               ( 135 )
MOB_WIS               ( 104 )
MOB_WIL               ( 104 )
MOB_LCK               ( 35 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 93 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1210 )
MOB_ATTACK_DMG_ROLL   ( "1d 172 + 134 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 135  MAXdam: 306  Average: 220.5 

SET_MONSTER           ( ArenaMob110NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( ZOMBIE )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 3797 )
MOB_DODGE_SKILL       ( 450 )
MOB_AC                ( 55 )
MOB_LEVEL             ( 110 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 125 )
MOB_DEX               ( 113 )
MOB_END               ( 113 )
MOB_INT               ( 147 )
MOB_WIS               ( 113 )
MOB_WIL               ( 113 )
MOB_LCK               ( 37 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 46 )
MOB_WATER_RESIST      ( 94 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 70 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10614 ) // Mob arena life steal spell
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1330 )
MOB_ATTACK_DMG_ROLL   ( "1d 190 + 147 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 148  MAXdam: 337  Average: 242.5 

SET_MONSTER           ( ArenaMob120NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( WASP )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 4373 )
MOB_DODGE_SKILL       ( 490 )
MOB_AC                ( 60 )
MOB_LEVEL             ( 120 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 135 )
MOB_DEX               ( 122 )
MOB_END               ( 122 )
MOB_INT               ( 159 )
MOB_WIS               ( 122 )
MOB_WIL               ( 122 )
MOB_LCK               ( 39 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 46 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1450 )
MOB_ATTACK_DMG_ROLL   ( "1d 207 + 161 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 162  MAXdam: 368  Average: 265 

SET_MONSTER           ( ArenaMob130NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( MUMMY )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 4988 )
MOB_DODGE_SKILL       ( 530 )
MOB_AC                ( 65 )
MOB_LEVEL             ( 130 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 145 )
MOB_DEX               ( 131 )
MOB_END               ( 131 )
MOB_INT               ( 171 )
MOB_WIS               ( 131 )
MOB_WIL               ( 131 )
MOB_LCK               ( 41 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 46 )
MOB_WATER_RESIST      ( 94 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 70 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10615 ) // Mob arena mass drain spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1570 )
MOB_ATTACK_DMG_ROLL   ( "1d 224 + 174 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 175  MAXdam: 398  Average: 286.5 

SET_MONSTER           ( ArenaMob140NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( GOBLIN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 5641 )
MOB_DODGE_SKILL       ( 570 )
MOB_AC                ( 70 )
MOB_LEVEL             ( 140 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 155 )
MOB_DEX               ( 140 )
MOB_END               ( 140 )
MOB_INT               ( 183 )
MOB_WIS               ( 140 )
MOB_WIL               ( 140 )
MOB_LCK               ( 43 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )
									 
MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5025 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10605 ) // Mob arena fireball spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1690 )
MOB_ATTACK_DMG_ROLL   ( "1d 241 + 188 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 189  MAXdam: 429  Average: 309 

SET_MONSTER           ( ArenaMob150NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( ORC )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 6334 )
MOB_DODGE_SKILL       ( 610 )
MOB_AC                ( 75 )
MOB_LEVEL             ( 150 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 165 )
MOB_DEX               ( 149 )
MOB_END               ( 149 )
MOB_INT               ( 195 )
MOB_WIS               ( 149 )
MOB_WIL               ( 149 )
MOB_LCK               ( 45 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10612 ) // Mob arena mass shatter spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1810 )
MOB_ATTACK_DMG_ROLL   ( "1d 258 + 202 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 203  MAXdam: 460  Average: 331.5 

SET_MONSTER           ( ArenaMob160NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( TARANTULA )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 7065 )
MOB_DODGE_SKILL       ( 650 )
MOB_AC                ( 80 )
MOB_LEVEL             ( 160 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 175 )
MOB_DEX               ( 158 )
MOB_END               ( 158 )
MOB_INT               ( 207 )
MOB_WIS               ( 158 )
MOB_WIL               ( 158 )
MOB_LCK               ( 47 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10609 ) // Mob arena lightning bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 50 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10616 ) // Mob arena heal serious spell
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1930 )
MOB_ATTACK_DMG_ROLL   ( "1d 275 + 215 " )
MOB_ATTACK_PERCENTAGE ( 80 )
// MINdam: 216  MAXdam: 490  Average: 353 

SET_MONSTER           ( ArenaMob170NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SCORPION )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 7834 )
MOB_DODGE_SKILL       ( 690 )
MOB_AC                ( 85 )
MOB_LEVEL             ( 170 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 185 )
MOB_DEX               ( 167 )
MOB_END               ( 167 )
MOB_INT               ( 219 )
MOB_WIS               ( 167 )
MOB_WIL               ( 167 )
MOB_LCK               ( 49 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 40 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 35 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10616 ) // Mob arena heal serious spell
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2050 )
MOB_ATTACK_DMG_ROLL   ( "1d 292 + 229 " )
MOB_ATTACK_PERCENTAGE ( 75 )
// MINdam: 230  MAXdam: 521  Average: 375.5 

SET_MONSTER           ( ArenaMob180NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( WOLF )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 8643 )
MOB_DODGE_SKILL       ( 730 )
MOB_AC                ( 90 )
MOB_LEVEL             ( 180 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 195 )
MOB_DEX               ( 176 )
MOB_END               ( 176 )
MOB_INT               ( 231 )
MOB_WIS               ( 176 )
MOB_WIL               ( 176 )
MOB_LCK               ( 51 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 40 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10616 ) // Mob arena heal serious spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2170 )
MOB_ATTACK_DMG_ROLL   ( "1d 310 + 242 " )
MOB_ATTACK_PERCENTAGE ( 70 )
// MINdam: 243  MAXdam: 552  Average: 397.5 

SET_MONSTER           ( ArenaMob190NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( ATROCITY )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 9490 )
MOB_DODGE_SKILL       ( 770 )
MOB_AC                ( 95 )
MOB_LEVEL             ( 190 )
MOB_XP_PER_HIT        ( 0)
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 205 )
MOB_DEX               ( 185 )
MOB_END               ( 185 )
MOB_INT               ( 243 )
MOB_WIS               ( 185 )
MOB_WIL               ( 185 )
MOB_LCK               ( 53 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 35 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10614 ) // Mob arena life steal spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10616 ) // Mob arena heal serious spell
MOB_ATTACK_PERCENTAGE( 35 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2290 )
MOB_ATTACK_DMG_ROLL   ( "1d 326 + 256 " )
MOB_ATTACK_PERCENTAGE ( 65 )
// MINdam: 257  MAXdam: 582  Average: 419.5 

SET_MONSTER           ( ArenaMob200NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( GOBLIN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 10375 )
MOB_DODGE_SKILL       ( 810 )
MOB_AC                ( 100 )
MOB_LEVEL             ( 200 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 215 )
MOB_DEX               ( 194 )
MOB_END               ( 194 )
MOB_INT               ( 255 )
MOB_WIS               ( 194 )
MOB_WIL               ( 194 )
MOB_LCK               ( 55 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5025 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 75 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10615 ) // Mob arena mass drain spell
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2410 )
MOB_ATTACK_DMG_ROLL   ( "1d 344 + 269 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 270  MAXdam: 613  Average: 441.5 

SET_MONSTER           ( ArenaMob225NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( KRAANIAN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 12761 )
MOB_DODGE_SKILL       ( 910 )
MOB_AC                ( 112 )
MOB_LEVEL             ( 225 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 240 )
MOB_DEX               ( 217 )
MOB_END               ( 217 )
MOB_INT               ( 285 )
MOB_WIS               ( 217 )
MOB_WIL               ( 217 )
MOB_LCK               ( 60 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10605 ) // Mob arena fireball spell
MOB_ATTACK_PERCENTAGE( 55 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10612 ) // Mob arena mass shatter spell
MOB_ATTACK_PERCENTAGE( 45 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2710 )
MOB_ATTACK_DMG_ROLL   ( "1d 387 + 303 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 304  MAXdam: 690  Average: 497 

SET_MONSTER           ( ArenaMob250NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( KRAANIANFLYING )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 15385 )
MOB_DODGE_SKILL       ( 1010 )
MOB_AC                ( 125 )
MOB_LEVEL             ( 250 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 265 )
MOB_DEX               ( 239 )
MOB_END               ( 239 )
MOB_INT               ( 315 )
MOB_WIS               ( 239 )
MOB_WIL               ( 239 )
MOB_LCK               ( 65 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 46 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 50 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10612 ) // Mob arena mass shatter spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 3010 )
MOB_ATTACK_DMG_ROLL   ( "1d 429 + 337 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 338  MAXdam: 766  Average: 552 

SET_MONSTER           ( ArenaMob275NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( KRAANIANMILIPEDE )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 18255 )
MOB_DODGE_SKILL       ( 1110 )
MOB_AC                ( 137 )
MOB_LEVEL             ( 275 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 290 )
MOB_DEX               ( 262 )
MOB_END               ( 262 )
MOB_INT               ( 345 )
MOB_WIS               ( 262 )
MOB_WIL               ( 262 )
MOB_LCK               ( 70 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10605 ) // Mob arena fireball spell
MOB_ATTACK_PERCENTAGE( 70 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10615 ) // Mob arena mass drain spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 3310 )
MOB_ATTACK_DMG_ROLL   ( "1d 472 + 371 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 372  MAXdam: 843  Average: 607.5 

SET_MONSTER           ( ArenaMob300NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( KRAANIANTANK )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 21361 )
MOB_DODGE_SKILL       ( 1210 )
MOB_AC                ( 150 )
MOB_LEVEL             ( 300 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 315 )
MOB_DEX               ( 284 )
MOB_END               ( 284 )
MOB_INT               ( 375 )
MOB_WIS               ( 284 )
MOB_WIL               ( 284 )
MOB_LCK               ( 75 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 45 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10615 ) // Mob arena mass drain spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 3610 )
MOB_ATTACK_DMG_ROLL   ( "1d 515 + 405 " )
MOB_ATTACK_PERCENTAGE ( 75 )
// MINdam: 406  MAXdam: 920  Average: 663 

SET_MONSTER           ( ArenaMob325NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( GREEN_TROLL )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 24716 )
MOB_DODGE_SKILL       ( 1310 )
MOB_AC                ( 162 )
MOB_LEVEL             ( 325 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 340 )
MOB_DEX               ( 307 )
MOB_END               ( 307 )
MOB_INT               ( 405 )
MOB_WIS               ( 307 )
MOB_WIL               ( 307 )
MOB_LCK               ( 80 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10612 ) // Mob arena mass shatter spell
MOB_ATTACK_PERCENTAGE( 50 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 3910 )
MOB_ATTACK_DMG_ROLL   ( "1d 559 + 438 " )
MOB_ATTACK_PERCENTAGE ( 70 )
// MINdam: 439  MAXdam: 997  Average: 718 

SET_MONSTER           ( ArenaMob350NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( ATROCITY )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 28306 )
MOB_DODGE_SKILL       ( 1410 )
MOB_AC                ( 175 )
MOB_LEVEL             ( 350 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 365 )
MOB_DEX               ( 329 )
MOB_END               ( 329 )
MOB_INT               ( 435 )
MOB_WIS               ( 329 )
MOB_WIL               ( 329 )
MOB_LCK               ( 85 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10609 ) // Mob arena lightning bolt spell
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 40 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 35 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 4210 )
MOB_ATTACK_DMG_ROLL   ( "1d 601 + 472 " )
MOB_ATTACK_PERCENTAGE ( 65 )
// MINdam: 473  MAXdam: 1073  Average: 773 

SET_MONSTER           ( ArenaMob375NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( DEMON )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 32144 )
MOB_DODGE_SKILL       ( 1510 )
MOB_AC                ( 187 )
MOB_LEVEL             ( 375 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 390 )
MOB_DEX               ( 352 )
MOB_END               ( 352 )
MOB_INT               ( 465 )
MOB_WIS               ( 352 )
MOB_WIL               ( 352 )
MOB_LCK               ( 90 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 94 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 94 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10605 ) // Mob arena fireball spell
MOB_ATTACK_PERCENTAGE( 40 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 40 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 4510 )
MOB_ATTACK_DMG_ROLL   ( "1d 644 + 506 " )
MOB_ATTACK_PERCENTAGE ( 60 )
// MINdam: 507  MAXdam: 1150  Average: 828.5 

SET_MONSTER           ( ArenaMob400NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( TAUNTING )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 36217 )
MOB_DODGE_SKILL       ( 1610 )
MOB_AC                ( 200 )
MOB_LEVEL             ( 400 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 415 )
MOB_DEX               ( 374 )
MOB_END               ( 374 )
MOB_INT               ( 495 )
MOB_WIS               ( 374 )
MOB_WIL               ( 374 )
MOB_LCK               ( 95 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 46 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10614 ) // Mob arena life steal spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 50 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 4810 )
MOB_ATTACK_DMG_ROLL   ( "1d 687 + 540 " )
MOB_ATTACK_PERCENTAGE ( 70 )
// MINdam: 541  MAXdam: 1227  Average: 884 

SET_MONSTER           ( ArenaMob425NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PLAYER_PRIEST )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 40540 )
MOB_DODGE_SKILL       ( 1710 )
MOB_AC                ( 212 )
MOB_LEVEL             ( 425 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 440 )
MOB_DEX               ( 397 )
MOB_END               ( 397 )
MOB_INT               ( 525 )
MOB_WIS               ( 397 )
MOB_WIL               ( 397 )
MOB_LCK               ( 100 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10607 ) // Mob arena glacier spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 5110 )
MOB_ATTACK_DMG_ROLL   ( "1d 729 + 574 " )
MOB_ATTACK_PERCENTAGE ( 50 )
// MINdam: 575  MAXdam: 1303  Average: 939 

SET_MONSTER           ( ArenaMob450NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PLAYER_THIEF )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 45097 )
MOB_DODGE_SKILL       ( 1810 )
MOB_AC                ( 225 )
MOB_LEVEL             ( 450 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 465 )
MOB_DEX               ( 419 )
MOB_END               ( 419 )
MOB_INT               ( 555 )
MOB_WIS               ( 419 )
MOB_WIL               ( 419 )
MOB_LCK               ( 105 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10613 ) // Mob arena boulders spell
MOB_ATTACK_PERCENTAGE( 35 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 33 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10620 ) // Mob arena teleport1 spell
MOB_ATTACK_PERCENTAGE( 4 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10621 ) // Mob arena teleport2 spell
MOB_ATTACK_PERCENTAGE( 4 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10622 ) // Mob arena teleport3 spell
MOB_ATTACK_PERCENTAGE( 4 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 5410 )
MOB_ATTACK_DMG_ROLL   ( "1d 772 + 608 " )
MOB_ATTACK_PERCENTAGE ( 55 )
// MINdam: 609  MAXdam: 1380  Average: 994.5 

SET_MONSTER           ( ArenaMob475NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PLAYER_SWORDMAN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 49903 )
MOB_DODGE_SKILL       ( 1910 )
MOB_AC                ( 237 )
MOB_LEVEL             ( 475 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 490 )
MOB_DEX               ( 442 )
MOB_END               ( 442 )
MOB_INT               ( 585 )
MOB_WIS               ( 442 )
MOB_WIL               ( 442 )
MOB_LCK               ( 110 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 10 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 5 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 5 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10607 ) // Mob arena glacier spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10613 ) // Mob arena boulders spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10620 ) // Mob arena teleport1 spell
MOB_ATTACK_PERCENTAGE( 5 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10621 ) // Mob arena teleport2 spell
MOB_ATTACK_PERCENTAGE( 5 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10622 ) // Mob arena teleport3 spell
MOB_ATTACK_PERCENTAGE( 5 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 5710 )
MOB_ATTACK_DMG_ROLL   ( "1d 816 + 641 " )
MOB_ATTACK_PERCENTAGE ( 60 )
// MINdam: 642  MAXdam: 1457  Average: 1049.5 

SET_MONSTER           ( ArenaMob500NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( AGMORKIAN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 54943 )
MOB_DODGE_SKILL       ( 2010 )
MOB_AC                ( 250 )
MOB_LEVEL             ( 500 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 515 )
MOB_DEX               ( 464 )
MOB_END               ( 464 )
MOB_INT               ( 615 )
MOB_WIS               ( 464 )
MOB_WIL               ( 464 )
MOB_LCK               ( 115 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 46 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10608 ) // Mob arena meteor spell
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10607 ) // Mob arena glacier spell
MOB_ATTACK_PERCENTAGE( 15 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10613 ) // Mob arena boulders spell
MOB_ATTACK_PERCENTAGE( 15 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 24 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10620 ) // Mob arena teleport1 spell
MOB_ATTACK_PERCENTAGE( 7 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10621 ) // Mob arena teleport2 spell
MOB_ATTACK_PERCENTAGE( 7 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10622 ) // Mob arena teleport3 spell
MOB_ATTACK_PERCENTAGE( 7 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 6010 )
MOB_ATTACK_DMG_ROLL   ( "1d 858 + 675 " )
MOB_ATTACK_PERCENTAGE ( 55 )
// MINdam: 676  MAXdam: 1533  Average: 1104.5 

SET_MONSTER( ColosseumClerkNPC )
MOB_NPC_APPEARANCE    ( PUPPET ) 
MOB_AGRESSIVNESS      ( -100 )
MOB_CLAN              ( PEACE )
MOB_LEVEL             ( 100 )
MOB_HP                ( 1000000 )
MOB_DODGE_SKILL       ( 65535 )
MOB_AC                ( 1000000 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 0 )
MOB_STR               ( 500 )
MOB_DEX               ( 500 )
MOB_END               ( 500 )
MOB_INT               ( 500 )
MOB_WIS               ( 500 )
MOB_WIL               ( 500 )
MOB_LCK               ( 500 )               
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
MOB_CAN_ATTACK        ( FALSE )

MOB_DRESS_BODY ( WHITEROBE )
MOB_DRESS_FEET ( LEATHER_BOOTS )

/////////////////////////////////////////////// COLOSSEUM MONSTERS ///////////////////////////////////////////
//////////////////////////////////////////////////// END HERE ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// START OF ////////////////////////////////////////////////
/////////////////////////////////////////////// XP COLOSSEUM MONSTERS ///////////////////////////////////////////
SET_MONSTER           ( ArenaMobXP40NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( BAT )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 847 )
MOB_DODGE_SKILL       ( 170 )
MOB_AC                ( 20 )
MOB_LEVEL             ( 40 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 3135 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 55 )
MOB_DEX               ( 50 )
MOB_END               ( 50 )
MOB_INT               ( 63 )
MOB_WIS               ( 50 )
MOB_WIL               ( 50 )
MOB_LCK               ( 23 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 112 )
MOB_WATER_RESIST      ( 112 )
MOB_AIR_RESIST        ( 75 )
MOB_EARTH_RESIST      ( 150 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 112 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 490 )
MOB_ATTACK_DMG_ROLL   ( "1d 53 + 41 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 42  MAXdam: 94  Average: 68 

SET_MONSTER           ( ArenaMobXP50NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( RAT )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 1153 )
MOB_DODGE_SKILL       ( 210 )
MOB_AC                ( 25 )
MOB_LEVEL             ( 50 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 5193 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 65 )
MOB_DEX               ( 59 )
MOB_END               ( 59 )
MOB_INT               ( 75 )
MOB_WIS               ( 59 )
MOB_WIL               ( 59 )
MOB_LCK               ( 25 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 105 )
MOB_WATER_RESIST      ( 105 )
MOB_AIR_RESIST        ( 139 )
MOB_EARTH_RESIST      ( 69 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 105 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 610 )
MOB_ATTACK_DMG_ROLL   ( "1d 76 + 59 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 60  MAXdam: 135  Average: 97.5 

SET_MONSTER           ( ArenaMobXP60NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SMALL_WORM )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 1497 )
MOB_DODGE_SKILL       ( 250 )
MOB_AC                ( 30 )
MOB_LEVEL             ( 60 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 7304 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 75 )
MOB_DEX               ( 68 )
MOB_END               ( 68 )
MOB_INT               ( 87 )
MOB_WIS               ( 68 )
MOB_WIL               ( 68 )
MOB_LCK               ( 27 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 130 )
MOB_WATER_RESIST      ( 64 )
MOB_AIR_RESIST        ( 97 )
MOB_EARTH_RESIST      ( 97 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 97 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 730 )
MOB_ATTACK_DMG_ROLL   ( "1d 90 + 69 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 70  MAXdam: 159  Average: 114.5 

SET_MONSTER           ( ArenaMobXP70NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( OOZE )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 1879 )
MOB_DODGE_SKILL       ( 290 )
MOB_AC                ( 35 )
MOB_LEVEL             ( 70 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 10164 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 85 )
MOB_DEX               ( 77 )
MOB_END               ( 77 )
MOB_INT               ( 99 )
MOB_WIS               ( 77 )
MOB_WIL               ( 77 )
MOB_LCK               ( 29 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 60 )
MOB_WATER_RESIST      ( 121 )
MOB_AIR_RESIST        ( 60 )
MOB_EARTH_RESIST      ( 121 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 91 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 850 )
MOB_ATTACK_DMG_ROLL   ( "1d 110 + 84 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 85  MAXdam: 194  Average: 139.5 

SET_MONSTER           ( ArenaMobXP80NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SKELETON )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 2301 )
MOB_DODGE_SKILL       ( 330 )
MOB_AC                ( 40 )
MOB_LEVEL             ( 80 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 14113 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 95 )
MOB_DEX               ( 86 )
MOB_END               ( 86 )
MOB_INT               ( 111 )
MOB_WIS               ( 86 )
MOB_WIL               ( 86 )
MOB_LCK               ( 31 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 55 )
MOB_WATER_RESIST      ( 112 )
MOB_AIR_RESIST        ( 84 )
MOB_EARTH_RESIST      ( 84 )
MOB_LIGHT_RESIST      ( 84 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10614 ) // Mob arena life steal spell
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 970 )
MOB_ATTACK_DMG_ROLL   ( "1d 138 + 107 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 108  MAXdam: 245  Average: 176.5 

SET_MONSTER           ( ArenaMobXP90NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SPIDER )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 2761 )
MOB_DODGE_SKILL       ( 370 )
MOB_AC                ( 45 )
MOB_LEVEL             ( 90 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 17921 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 105 )
MOB_DEX               ( 95 )
MOB_END               ( 95 )
MOB_INT               ( 123 )
MOB_WIS               ( 95 )
MOB_WIL               ( 95 )
MOB_LCK               ( 33 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 76 )
MOB_WATER_RESIST      ( 76 )
MOB_AIR_RESIST        ( 102 )
MOB_EARTH_RESIST      ( 51 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 76 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10609 ) // Mob arena lightning bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1090 )
MOB_ATTACK_DMG_ROLL   ( "1d 156 + 120 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 121  MAXdam: 276  Average: 198.5 

SET_MONSTER           ( ArenaMobXP100NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SNAKE )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 3259 )
MOB_DODGE_SKILL       ( 410 )
MOB_AC                ( 50 )
MOB_LEVEL             ( 100 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 22247 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 115 )
MOB_DEX               ( 104 )
MOB_END               ( 104 )
MOB_INT               ( 135 )
MOB_WIS               ( 104 )
MOB_WIL               ( 104 )
MOB_LCK               ( 35 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 93 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1210 )
MOB_ATTACK_DMG_ROLL   ( "1d 172 + 134 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 135  MAXdam: 306  Average: 220.5 

SET_MONSTER           ( ArenaMobXP110NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( ZOMBIE )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 3797 )
MOB_DODGE_SKILL       ( 450 )
MOB_AC                ( 55 )
MOB_LEVEL             ( 110 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 27114 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 125 )
MOB_DEX               ( 113 )
MOB_END               ( 113 )
MOB_INT               ( 147 )
MOB_WIS               ( 113 )
MOB_WIL               ( 113 )
MOB_LCK               ( 37 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 46 )
MOB_WATER_RESIST      ( 94 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 70 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10614 ) // Mob arena life steal spell
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1330 )
MOB_ATTACK_DMG_ROLL   ( "1d 190 + 147 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 148  MAXdam: 337  Average: 242.5 

SET_MONSTER           ( ArenaMobXP120NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( WASP )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 4373 )
MOB_DODGE_SKILL       ( 490 )
MOB_AC                ( 60 )
MOB_LEVEL             ( 120 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 32571 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 135 )
MOB_DEX               ( 122 )
MOB_END               ( 122 )
MOB_INT               ( 159 )
MOB_WIS               ( 122 )
MOB_WIL               ( 122 )
MOB_LCK               ( 39 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 46 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1450 )
MOB_ATTACK_DMG_ROLL   ( "1d 207 + 161 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 162  MAXdam: 368  Average: 265 

SET_MONSTER           ( ArenaMobXP130NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( MUMMY )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 4988 )
MOB_DODGE_SKILL       ( 530 )
MOB_AC                ( 65 )
MOB_LEVEL             ( 130 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 38537 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 145 )
MOB_DEX               ( 131 )
MOB_END               ( 131 )
MOB_INT               ( 171 )
MOB_WIS               ( 131 )
MOB_WIL               ( 131 )
MOB_LCK               ( 41 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 46 )
MOB_WATER_RESIST      ( 94 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 70 )
MOB_DARK_RESIST       ( 5025 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10615 ) // Mob arena mass drain spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1570 )
MOB_ATTACK_DMG_ROLL   ( "1d 224 + 174 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 175  MAXdam: 398  Average: 286.5 

SET_MONSTER           ( ArenaMobXP140NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( GOBLIN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 5641 )
MOB_DODGE_SKILL       ( 570 )
MOB_AC                ( 70 )
MOB_LEVEL             ( 140 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 45172 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 155 )
MOB_DEX               ( 140 )
MOB_END               ( 140 )
MOB_INT               ( 183 )
MOB_WIS               ( 140 )
MOB_WIL               ( 140 )
MOB_LCK               ( 43 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )
									 
MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5025 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10605 ) // Mob arena fireball spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1690 )
MOB_ATTACK_DMG_ROLL   ( "1d 241 + 188 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 189  MAXdam: 429  Average: 309 

SET_MONSTER           ( ArenaMobXP150NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( ORC )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 6334 )
MOB_DODGE_SKILL       ( 610 )
MOB_AC                ( 75 )
MOB_LEVEL             ( 150 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 52432 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 165 )
MOB_DEX               ( 149 )
MOB_END               ( 149 )
MOB_INT               ( 195 )
MOB_WIS               ( 149 )
MOB_WIL               ( 149 )
MOB_LCK               ( 45 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10612 ) // Mob arena mass shatter spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1810 )
MOB_ATTACK_DMG_ROLL   ( "1d 258 + 202 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 203  MAXdam: 460  Average: 331.5 

SET_MONSTER           ( ArenaMobXP160NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( TARANTULA )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 7065 )
MOB_DODGE_SKILL       ( 650 )
MOB_AC                ( 80 )
MOB_LEVEL             ( 160 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 63251 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 175 )
MOB_DEX               ( 158 )
MOB_END               ( 158 )
MOB_INT               ( 207 )
MOB_WIS               ( 158 )
MOB_WIL               ( 158 )
MOB_LCK               ( 47 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10609 ) // Mob arena lightning bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 50 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10616 ) // Mob arena heal serious spell
MOB_ATTACK_PERCENTAGE( 20 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 1930 )
MOB_ATTACK_DMG_ROLL   ( "1d 275 + 215 " )
MOB_ATTACK_PERCENTAGE ( 80 )
// MINdam: 216  MAXdam: 490  Average: 353 

SET_MONSTER           ( ArenaMobXP170NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( SCORPION )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 7834 )
MOB_DODGE_SKILL       ( 690 )
MOB_AC                ( 85 )
MOB_LEVEL             ( 170 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 106624 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 185 )
MOB_DEX               ( 167 )
MOB_END               ( 167 )
MOB_INT               ( 219 )
MOB_WIS               ( 167 )
MOB_WIL               ( 167 )
MOB_LCK               ( 49 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 40 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 35 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10616 ) // Mob arena heal serious spell
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2050 )
MOB_ATTACK_DMG_ROLL   ( "1d 292 + 229 " )
MOB_ATTACK_PERCENTAGE ( 75 )
// MINdam: 230  MAXdam: 521  Average: 375.5 

SET_MONSTER           ( ArenaMobXP180NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( WOLF )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 8643 )
MOB_DODGE_SKILL       ( 730 )
MOB_AC                ( 90 )
MOB_LEVEL             ( 180 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 159844 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 195 )
MOB_DEX               ( 176 )
MOB_END               ( 176 )
MOB_INT               ( 231 )
MOB_WIS               ( 176 )
MOB_WIL               ( 176 )
MOB_LCK               ( 51 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 40 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10616 ) // Mob arena heal serious spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2170 )
MOB_ATTACK_DMG_ROLL   ( "1d 310 + 242 " )
MOB_ATTACK_PERCENTAGE ( 70 )
// MINdam: 243  MAXdam: 552  Average: 397.5 

SET_MONSTER           ( ArenaMobXP190NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( ATROCITY )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 9490 )
MOB_DODGE_SKILL       ( 770 )
MOB_AC                ( 95 )
MOB_LEVEL             ( 190 )
MOB_XP_PER_HIT        ( 0)
MOB_XP_DEATH          ( 224009 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 205 )
MOB_DEX               ( 185 )
MOB_END               ( 185 )
MOB_INT               ( 243 )
MOB_WIS               ( 185 )
MOB_WIL               ( 185 )
MOB_LCK               ( 53 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 35 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10614 ) // Mob arena life steal spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10616 ) // Mob arena heal serious spell
MOB_ATTACK_PERCENTAGE( 35 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2290 )
MOB_ATTACK_DMG_ROLL   ( "1d 326 + 256 " )
MOB_ATTACK_PERCENTAGE ( 65 )
// MINdam: 257  MAXdam: 582  Average: 419.5 

SET_MONSTER           ( ArenaMobXP200NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( GOBLIN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 10375 )
MOB_DODGE_SKILL       ( 810 )
MOB_AC                ( 100 )
MOB_LEVEL             ( 200 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 300213 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 215 )
MOB_DEX               ( 194 )
MOB_END               ( 194 )
MOB_INT               ( 255 )
MOB_WIS               ( 194 )
MOB_WIL               ( 194 )
MOB_LCK               ( 55 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5025 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 75 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10615 ) // Mob arena mass drain spell
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2410 )
MOB_ATTACK_DMG_ROLL   ( "1d 344 + 269 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 270  MAXdam: 613  Average: 441.5 

SET_MONSTER           ( ArenaMobXP225NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( KRAANIAN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 12761 )
MOB_DODGE_SKILL       ( 910 )
MOB_AC                ( 112 )
MOB_LEVEL             ( 225 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 551278 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 240 )
MOB_DEX               ( 217 )
MOB_END               ( 217 )
MOB_INT               ( 285 )
MOB_WIS               ( 217 )
MOB_WIL               ( 217 )
MOB_LCK               ( 60 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10605 ) // Mob arena fireball spell
MOB_ATTACK_PERCENTAGE( 55 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10612 ) // Mob arena mass shatter spell
MOB_ATTACK_PERCENTAGE( 45 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 2710 )
MOB_ATTACK_DMG_ROLL   ( "1d 387 + 303 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 304  MAXdam: 690  Average: 497 

SET_MONSTER           ( ArenaMobXP250NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( KRAANIANFLYING )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 15385 )
MOB_DODGE_SKILL       ( 1010 )
MOB_AC                ( 125 )
MOB_LEVEL             ( 250 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 903534 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 265 )
MOB_DEX               ( 239 )
MOB_END               ( 239 )
MOB_INT               ( 315 )
MOB_WIS               ( 239 )
MOB_WIL               ( 239 )
MOB_LCK               ( 65 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 46 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 50 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10612 ) // Mob arena mass shatter spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 3010 )
MOB_ATTACK_DMG_ROLL   ( "1d 429 + 337 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 338  MAXdam: 766  Average: 552 

SET_MONSTER           ( ArenaMobXP275NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( KRAANIANMILIPEDE )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 18255 )
MOB_DODGE_SKILL       ( 1110 )
MOB_AC                ( 137 )
MOB_LEVEL             ( 275 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 1378015 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 290 )
MOB_DEX               ( 262 )
MOB_END               ( 262 )
MOB_INT               ( 345 )
MOB_WIS               ( 262 )
MOB_WIL               ( 262 )
MOB_LCK               ( 70 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 46 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10605 ) // Mob arena fireball spell
MOB_ATTACK_PERCENTAGE( 70 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10615 ) // Mob arena mass drain spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 3310 )
MOB_ATTACK_DMG_ROLL   ( "1d 472 + 371 " )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 372  MAXdam: 843  Average: 607.5 

SET_MONSTER           ( ArenaMobXP300NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( KRAANIANTANK )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 21361 )
MOB_DODGE_SKILL       ( 1210 )
MOB_AC                ( 150 )
MOB_LEVEL             ( 300 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 1996275 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 315 )
MOB_DEX               ( 284 )
MOB_END               ( 284 )
MOB_INT               ( 375 )
MOB_WIS               ( 284 )
MOB_WIL               ( 284 )
MOB_LCK               ( 75 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 45 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10615 ) // Mob arena mass drain spell
MOB_ATTACK_PERCENTAGE( 30 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 25 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 3610 )
MOB_ATTACK_DMG_ROLL   ( "1d 515 + 405 " )
MOB_ATTACK_PERCENTAGE ( 75 )
// MINdam: 406  MAXdam: 920  Average: 663 

SET_MONSTER           ( ArenaMobXP325NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( GREEN_TROLL )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 24716 )
MOB_DODGE_SKILL       ( 1310 )
MOB_AC                ( 162 )
MOB_LEVEL             ( 325 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 2781103 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 340 )
MOB_DEX               ( 307 )
MOB_END               ( 307 )
MOB_INT               ( 405 )
MOB_WIS               ( 307 )
MOB_WIL               ( 307 )
MOB_LCK               ( 80 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10612 ) // Mob arena mass shatter spell
MOB_ATTACK_PERCENTAGE( 50 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 3910 )
MOB_ATTACK_DMG_ROLL   ( "1d 559 + 438 " )
MOB_ATTACK_PERCENTAGE ( 70 )
// MINdam: 439  MAXdam: 997  Average: 718 

SET_MONSTER           ( ArenaMobXP350NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( ATROCITY )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 28306 )
MOB_DODGE_SKILL       ( 1410 )
MOB_AC                ( 175 )
MOB_LEVEL             ( 350 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 3757615 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 365 )
MOB_DEX               ( 329 )
MOB_END               ( 329 )
MOB_INT               ( 435 )
MOB_WIS               ( 329 )
MOB_WIL               ( 329 )
MOB_LCK               ( 85 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10609 ) // Mob arena lightning bolt spell
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 40 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 35 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 4210 )
MOB_ATTACK_DMG_ROLL   ( "1d 601 + 472 " )
MOB_ATTACK_PERCENTAGE ( 65 )
// MINdam: 473  MAXdam: 1073  Average: 773 

SET_MONSTER           ( ArenaMobXP375NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( DEMON )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 32144 )
MOB_DODGE_SKILL       ( 1510 )
MOB_AC                ( 187 )
MOB_LEVEL             ( 375 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 4953688 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 390 )
MOB_DEX               ( 352 )
MOB_END               ( 352 )
MOB_INT               ( 465 )
MOB_WIS               ( 352 )
MOB_WIL               ( 352 )
MOB_LCK               ( 90 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 94 )
MOB_AIR_RESIST        ( 94 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 94 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10605 ) // Mob arena fireball spell
MOB_ATTACK_PERCENTAGE( 40 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 40 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 4510 )
MOB_ATTACK_DMG_ROLL   ( "1d 644 + 506 " )
MOB_ATTACK_PERCENTAGE ( 60 )
// MINdam: 507  MAXdam: 1150  Average: 828.5 

SET_MONSTER           ( ArenaMobXP400NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( TAUNTING )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 36217 )
MOB_DODGE_SKILL       ( 1610 )
MOB_AC                ( 200 )
MOB_LEVEL             ( 400 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 6396077 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 415 )
MOB_DEX               ( 374 )
MOB_END               ( 374 )
MOB_INT               ( 495 )
MOB_WIS               ( 374 )
MOB_WIL               ( 374 )
MOB_LCK               ( 95 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 46 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10614 ) // Mob arena life steal spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10610 ) // Mob arena mass lightning spell
MOB_ATTACK_PERCENTAGE( 50 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 30 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 4810 )
MOB_ATTACK_DMG_ROLL   ( "1d 687 + 540 " )
MOB_ATTACK_PERCENTAGE ( 70 )
// MINdam: 541  MAXdam: 1227  Average: 884 

SET_MONSTER           ( ArenaMobXP425NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PLAYER_PRIEST )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 40540 )
MOB_DODGE_SKILL       ( 1710 )
MOB_AC                ( 212 )
MOB_LEVEL             ( 425 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 8113191 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 440 )
MOB_DEX               ( 397 )
MOB_END               ( 397 )
MOB_INT               ( 525 )
MOB_WIS               ( 397 )
MOB_WIL               ( 397 )
MOB_LCK               ( 100 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10607 ) // Mob arena glacier spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 50 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 5110 )
MOB_ATTACK_DMG_ROLL   ( "1d 729 + 574 " )
MOB_ATTACK_PERCENTAGE ( 50 )
// MINdam: 575  MAXdam: 1303  Average: 939 

SET_MONSTER           ( ArenaMobXP450NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PLAYER_THIEF )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 45097 )
MOB_DODGE_SKILL       ( 1810 )
MOB_AC                ( 225 )
MOB_LEVEL             ( 450 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 10138310 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 465 )
MOB_DEX               ( 419 )
MOB_END               ( 419 )
MOB_INT               ( 555 )
MOB_WIS               ( 419 )
MOB_WIL               ( 419 )
MOB_LCK               ( 105 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10613 ) // Mob arena boulders spell
MOB_ATTACK_PERCENTAGE( 35 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 33 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10620 ) // Mob arena teleport1 spell
// MOB_ATTACK_PERCENTAGE( 4 )
// MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10621 ) // Mob arena teleport2 spell
// MOB_ATTACK_PERCENTAGE( 4 )
// MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10622 ) // Mob arena teleport3 spell
// MOB_ATTACK_PERCENTAGE( 4 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 5410 )
MOB_ATTACK_DMG_ROLL   ( "1d 772 + 608 " )
MOB_ATTACK_PERCENTAGE ( 55 )
// MINdam: 609  MAXdam: 1380  Average: 994.5 

SET_MONSTER           ( ArenaMobXP475NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_NPC_APPEARANCE    ( PLAYER_SWORDMAN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 49903 )
MOB_DODGE_SKILL       ( 1910 )
MOB_AC                ( 237 )
MOB_LEVEL             ( 475 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 12501070 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 490 )
MOB_DEX               ( 442 )
MOB_END               ( 442 )
MOB_INT               ( 585 )
MOB_WIS               ( 442 )
MOB_WIL               ( 442 )
MOB_LCK               ( 110 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 70 )
MOB_WATER_RESIST      ( 70 )
MOB_AIR_RESIST        ( 70 )
MOB_EARTH_RESIST      ( 70 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10604 ) // Mob arena fire bolt spell
MOB_ATTACK_PERCENTAGE( 10 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10606 ) // Mob arena ice bolt spell
MOB_ATTACK_PERCENTAGE( 5 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10611 ) // Mob arena stone spell
MOB_ATTACK_PERCENTAGE( 5 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10607 ) // Mob arena glacier spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10613 ) // Mob arena boulders spell
MOB_ATTACK_PERCENTAGE( 20 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10620 ) // Mob arena teleport1 spell
// MOB_ATTACK_PERCENTAGE( 5 )
// MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10621 ) // Mob arena teleport2 spell
// MOB_ATTACK_PERCENTAGE( 5 )
// MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10622 ) // Mob arena teleport3 spell
// MOB_ATTACK_PERCENTAGE( 5 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 5710 )
MOB_ATTACK_DMG_ROLL   ( "1d 816 + 641 " )
MOB_ATTACK_PERCENTAGE ( 60 )
// MINdam: 642  MAXdam: 1457  Average: 1049.5 

SET_MONSTER           ( ArenaMobXP500NPC )
MOB_AGRESSIVNESS      ( 100 ) 
MOB_APPEARANCE        ( AGMORKIAN )
MOB_CLAN              ( LIGHTHAVEN )
MOB_HP                ( 54943 )
MOB_DODGE_SKILL       ( 2010 )
MOB_AC                ( 250 )
MOB_LEVEL             ( 500 )
MOB_XP_PER_HIT        ( 0 )
MOB_XP_DEATH          ( 15236180 )
MOB_MIN_GOLD          ( 0 )
MOB_MAX_GOLD          ( 0 )
MOB_STR               ( 515 )
MOB_DEX               ( 464 )
MOB_END               ( 464 )
MOB_INT               ( 615 )
MOB_WIS               ( 464 )
MOB_WIL               ( 464 )
MOB_LCK               ( 115 )

MOB_FIRE_POWER        ( 100 )
MOB_WATER_POWER       ( 100 )
MOB_AIR_POWER         ( 100 )
MOB_EARTH_POWER       ( 100 )
MOB_LIGHT_POWER       ( 100 )
MOB_DARK_POWER        ( 100 )

MOB_FIRE_RESIST       ( 94 )
MOB_WATER_RESIST      ( 46 )
MOB_AIR_RESIST        ( 46 )
MOB_EARTH_RESIST      ( 94 )
MOB_LIGHT_RESIST      ( 5000 )
MOB_DARK_RESIST       ( 70 )

MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10608 ) // Mob arena meteor spell
MOB_ATTACK_PERCENTAGE( 25 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10607 ) // Mob arena glacier spell
MOB_ATTACK_PERCENTAGE( 15 )
MOB_CREATE_SPELL_ATTACK( 2, 25 )
MOB_ATTACK_SPELL( 10613 ) // Mob arena boulders spell
MOB_ATTACK_PERCENTAGE( 15 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
MOB_ATTACK_SPELL( 10617 ) // Mob arena healing spell
MOB_ATTACK_PERCENTAGE( 24 )
MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10620 ) // Mob arena teleport1 spell
// MOB_ATTACK_PERCENTAGE( 7 )
// MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10621 ) // Mob arena teleport2 spell
// MOB_ATTACK_PERCENTAGE( 7 )
// MOB_CREATE_SPELL_ATTACK( 0, 25 )
// MOB_ATTACK_SPELL( 10622 ) // Mob arena teleport3 spell
// MOB_ATTACK_PERCENTAGE( 7 )

MOB_CREATE_PHYSICAL_ATTACK
MOB_ATTACK_SKILL      ( 6010 )
MOB_ATTACK_DMG_ROLL   ( "1d 858 + 675 " )
MOB_ATTACK_PERCENTAGE ( 55 )
// MINdam: 676  MAXdam: 1533  Average: 1104.5 


	CreateNPC();
CLOSE_MONSTER_STAT_SETUP

void MonsterStatDestroy(){
}
 









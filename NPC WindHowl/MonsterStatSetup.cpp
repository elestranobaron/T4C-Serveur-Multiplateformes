//////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include <NPCStructure.h>
#include <DLLCreatures.h>

NPCstructure::NPC GwenNPC; 
NPCstructure::NPC MirakNiraNPC; 
NPCstructure::NPC Lord_SunRock;              
NPCstructure::NPC Nobleman;                  
NPCstructure::NPC Thief_TheLurker;           
NPCstructure::NPC Mage;                      
NPCstructure::NPC Wizard_Liurn_Clar;         
NPCstructure::NPC Female_NPC;                
NPCstructure::NPC Priest;                    
NPCstructure::NPC Guard_One;                 
NPCstructure::NPC Guard_Two;                 
NPCstructure::NPC Guard_Three;               // full plate
NPCstructure::NPC GuntertagDestroyNPC;       
NPCstructure::NPC Shopkeeper;                
NPCstructure::NPC Peasant;                   
NPCstructure::NPC PirateHarockHarr;          
NPCstructure::NPC SailorRedBeard;            
NPCstructure::NPC DrunkNPC; 
NPCstructure::NPC HumanDrunkNPC; 
NPCstructure::NPC MalaarNPC;
NPCstructure::NPC JurnistakrKiraNPC;
NPCstructure::NPC SamilAlgderNPC;
NPCstructure::NPC BrotherNiussNPC;
NPCstructure::NPC LaonianRikarrNPC;
NPCstructure::NPC BrotherHarforrNPC;
NPCstructure::NPC YolakNPC;
NPCstructure::NPC MushnNPC; 
NPCstructure::NPC MiramLakyNPC; 
NPCstructure::NPC IroualKnowallNPC; 
NPCstructure::NPC GreyarEedyNPC; 

void CreateNPC( void );
 
INIT_MONSTER_STAT_SETUP

SET_MONSTER( IroualKnowallNPC )
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
MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( GreyarEedyNPC )
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
MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( MiramLakyNPC )
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
MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( MushnNPC )
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
MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( YolakNPC )
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

MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( LaonianRikarrNPC )
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
MOB_END               ( 22 )
MOB_INT               ( 20 )
MOB_WIS               ( 21 )
MOB_WIL               ( 25 )
MOB_LCK               ( 22 )               

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

MOB_DRESS_BODY ( WHITEROBE )
// MOB_DRESS_FEET ( LEATHER_BOOTS )
// MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON ( MORNING_STAR )
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( BrotherHarforrNPC )
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
MOB_END               ( 22 )
MOB_INT               ( 20 )
MOB_WIS               ( 21 )
MOB_WIL               ( 25 )
MOB_LCK               ( 22 )               

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

MOB_DRESS_BODY ( WHITEROBE )
// MOB_DRESS_FEET ( LEATHER_BOOTS )
// MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON ( MORNING_STAR )
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( BrotherNiussNPC )
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

MOB_DRESS_BODY ( WHITEROBE )
// MOB_DRESS_FEET ( LEATHER_BOOTS )
// MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON ( FLAIL )
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( SamilAlgderNPC )
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


MOB_DRESS_BODY ( WHITEROBE )
// MOB_DRESS_FEET ( LEATHER_BOOTS )
// MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON ( GOLDEN_STAR )
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( MalaarNPC )
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

MOB_DRESS_BODY ( WHITEROBE )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
MOB_DRESS_WEAPON ( HAMMER )
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( JurnistakrKiraNPC )
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

MOB_DRESS_BODY ( WHITEROBE )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( HumanDrunkNPC )
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

MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( DrunkNPC )
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

MOB_DRESS_BODY ( BODY_CLOTH1 )
MOB_DRESS_FEET ( LEATHER_BOOTS )
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( PirateHarockHarr )
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

MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
MOB_DRESS_HELM ( CHAIN_COIF )
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
MOB_DRESS_WEAPON ( BATTLE_SWORD )

SET_MONSTER( SailorRedBeard )
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

MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM ( CHAIN_COIF )
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON ( BATTLE_SWORD )

SET_MONSTER( Shopkeeper )
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
// MOB_DRESS_GLOVES
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEG_CLOTH1 )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( GuntertagDestroyNPC )
MOB_NPC_APPEARANCE              ( ORC )   // If it's not that it's NPC_ORC
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

MOB_CREATE_PHYSICAL_ATTACK         // Level 25
MOB_ATTACK_SKILL      ( 310 )
MOB_ATTACK_DMG_ROLL   (	"1d29+21" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 22  MAXdam: 50

SET_MONSTER( Guard_Three )
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

MOB_CREATE_PHYSICAL_ATTACK         // Level 25
MOB_ATTACK_SKILL      ( 310 )
MOB_ATTACK_DMG_ROLL   (	"1d29+21" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 22  MAXdam: 50

MOB_DRESS_BODY ( PLATE_ARMOR )
MOB_DRESS_FEET ( PLATE_BOOT )
MOB_DRESS_GLOVES ( PLATE_GLOVE ) 
MOB_DRESS_HELM ( PLATE_HELM )
MOB_DRESS_LEGS ( PLATE_LEGS )
MOB_DRESS_WEAPON ( AXE )
MOB_DRESS_SHIELD ( ROMAN_SHIELD )
MOB_DRESS_CAPE ( REDCAPE )

SET_MONSTER( Guard_Two )
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

MOB_CREATE_PHYSICAL_ATTACK         // Level 25
MOB_ATTACK_SKILL      ( 310 )
MOB_ATTACK_DMG_ROLL   (	"1d29+21" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 22  MAXdam: 50

MOB_DRESS_BODY ( CHAIN_BODY )
MOB_DRESS_FEET ( PLATE_BOOT )
MOB_DRESS_GLOVES ( LEATHER_GLOVE) 
MOB_DRESS_HELM ( CHAIN_COIF )
MOB_DRESS_LEGS ( CHAIN_LEGS )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( Guard_One )
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

MOB_CREATE_PHYSICAL_ATTACK         // Level 25
MOB_ATTACK_SKILL      ( 310 )
MOB_ATTACK_DMG_ROLL   (	"1d29+21" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 22  MAXdam: 50

MOB_DRESS_BODY ( CHAIN_BODY )
MOB_DRESS_FEET ( PLATE_BOOT )
MOB_DRESS_GLOVES ( LEATHER_GLOVE) 
MOB_DRESS_HELM ( CHAIN_COIF )
MOB_DRESS_LEGS ( CHAIN_LEGS )
MOB_DRESS_WEAPON ( BATTLE_SWORD )
MOB_DRESS_SHIELD ( ROMAN_SHIELD )
MOB_DRESS_CAPE ( REDCAPE )

SET_MONSTER( Priest )
MOB_NPC_APPEARANCE              ( PLAYER_PRIEST )
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

MOB_CREATE_PHYSICAL_ATTACK         // Level 20
MOB_ATTACK_SKILL      ( 250 )
MOB_ATTACK_DMG_ROLL   (	"1d23+16" )
MOB_ATTACK_PERCENTAGE ( 100 )
// MINdam: 17  MAXdam: 39

SET_MONSTER( Lord_SunRock )
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
MOB_DRESS_BODY ( CHAIN_BODY ) 
MOB_DRESS_FEET ( PLATE_BOOT )
MOB_DRESS_GLOVES ( LEATHER_GLOVE) 
MOB_DRESS_HELM ( CHAIN_COIF )
MOB_DRESS_LEGS ( CHAIN_LEGS )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
MOB_DRESS_CAPE ( REDCAPE )

SET_MONSTER( Nobleman )
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
MOB_DRESS_BODY ( CHAIN_BODY ) 
MOB_DRESS_FEET ( PLATE_BOOT )
MOB_DRESS_GLOVES ( LEATHER_GLOVE ) 
MOB_DRESS_HELM ( CHAIN_COIF )
MOB_DRESS_LEGS ( LEATHER_PANTS )
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE

SET_MONSTER( Wizard_Liurn_Clar )
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
MOB_DRESS_BODY ( NECROMANROBE )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
// MOB_DRESS_GLOVES 
MOB_DRESS_HELM ( HORNED_HELMET )
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE 

SET_MONSTER( Mage )
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
MOB_DRESS_BODY ( NECROMANROBE )
MOB_DRESS_FEET ( BLACKLEATHER_BOOT )
// MOB_DRESS_GLOVES 
// MOB_DRESS_HELM
MOB_DRESS_LEGS ( LEATHER_PANTS ) 
// MOB_DRESS_WEAPON
// MOB_DRESS_SHIELD
// MOB_DRESS_CAPE 

SET_MONSTER( Peasant )
MOB_NPC_APPEARANCE              ( HUMAN_PEASANT )
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


SET_MONSTER( Female_NPC )
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


SET_MONSTER( Thief_TheLurker )
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
MOB_ATTACK_SKILL        ( 310 )
MOB_ATTACK_DMG_ROLL   (	"1d29+21" )
MOB_ATTACK_PERCENTAGE   ( 100 )
MOB_DRESS_BODY ( LEATHER_ARMOR )
MOB_DRESS_FEET ( LEATHER_BOOTS )
MOB_DRESS_GLOVES ( LEATHER_GLOVE )
// MOB_DRESS_HELM 
MOB_DRESS_LEGS ( STUDDEDLEG )
MOB_DRESS_WEAPON ( DAGGER )
// MOB_DRESS_SHIELD
MOB_DRESS_CAPE ( REDCAPE )


SET_MONSTER( MirakNiraNPC )
MOB_NPC_APPEARANCE	( FEMALE_PUPPET )
MOB_AGRESSIVNESS		( -100 )
MOB_CLAN					( LIGHTHAVEN )
MOB_LEVEL				( 100 )
MOB_HP					( 1000000 )
MOB_DODGE_SKILL		( 65535 )
MOB_AC					( 1000000 )
MOB_XP_PER_HIT			( 0 )
MOB_XP_DEATH			( 0 )
MOB_STR					( 65 )
MOB_DEX					( 63 )
MOB_END					( 67 )
MOB_INT					( 47 )
MOB_WIS					( 87 )
MOB_WIL					( 79 )
MOB_LCK					( 54 )
MOB_CAN_ATTACK			(FALSE)

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

SET_MONSTER( GwenNPC ) 
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

	CreateNPC();
CLOSE_MONSTER_STAT_SETUP
		
void MonsterStatDestroy(){
}

#pragma hdrstop
#include <NPC.H>

#include "GMassistant.h"
#include "IslandPortal1.h"
#include "IslandPortal10.h"
#include "IslandPortal11.h"
#include "IslandPortal12.h"
#include "IslandPortal13.h"
#include "IslandPortal14.h"
#include "IslandPortal15.h"
#include "IslandPortal16.h"
#include "IslandPortal17.h"
#include "IslandPortal18.h"
#include "IslandPortal19.h"
#include "IslandPortal2.h"
#include "IslandPortal20.h"
#include "IslandPortal21.h"
#include "IslandPortal22.h"
#include "IslandPortal23.h"
#include "IslandPortal24.h"
#include "IslandPortal25.h"
#include "IslandPortal26.h"
#include "IslandPortal27.h"
#include "IslandPortal28.h"
#include "IslandPortal29.h"
#include "IslandPortal3.h"
#include "IslandPortal30.h"
#include "IslandPortal31.h"
#include "IslandPortal32.h"
#include "IslandPortal33.h"
#include "IslandPortal34.h"
#include "IslandPortal35.h"
#include "IslandPortal4.h"
#include "IslandPortal5.h"
#include "IslandPortal6.h"
#include "IslandPortal7.h"
#include "IslandPortal8.h"
#include "IslandPortal9.h"
#include "PortalA.h"
#include "PortalB.h"
#include "PortalC.h"
#include "StaticDungeonPortal1.h"
#include "StaticDungeonPortal2.h"
#include "HealingWell.h"
#include "IsolatedIslandPortal.h"
#include "LightHavenPortal.h"
#include "SanctuaryPortal.h"
#include "SilverSkyPortal.h"
#include "WindHowlPortal.h"
#include "HealingPlant.h"
#include "DemoPortal1.h"
#include "DemoPortal2.h"
#include "DemoPortal3.h"
#include "DemoPortal4.h"
#include "DemoPortal5.h"
#include "DemoPortal6.h"
#include "NPCForestGuardian.h"
#include "NPCRat.h"
#include "NPCTombRaider.h"
#include "Sabrina.h"
#include "PortalD.h"
#include "PortalE.h"
#include "PortalF.h"
#include "PortalG.h"
#include "PortalH.h"
#include "PortalI.h"
#include "PortalJ.h"
#include "PortalK.h"
#include "PortalL.h"
#include "PortalM.h"
#include "PortalN.h"
#include "PortalO.h"
#include "PortalP.h"
#include "PortalQ.h"
#include "PortalR.h"
#include "PortalS.h"
#include "PortalT.h"
#include "PortalU.h"
#include "PortalV.h"
#include "PortalW.h"
#include "PortalX.h"
#include "PortalY.h"
#include "PortalZ.h"
#include "EmptyDungeonPortal.h"
#include "IslandMadnessPortal.h"
#include "ScatteredBonesPortal.h"
#include "LighthavenArenaClerk.h"

// NPC object definitions.

GMassistant                             GMASSISTANT;
IslandPortal1                           ISLANDPORTAL1;
IslandPortal10                          ISLANDPORTAL10;
IslandPortal11                          ISLANDPORTAL11;
IslandPortal12                          ISLANDPORTAL12;
IslandPortal13                          ISLANDPORTAL13;
IslandPortal14                          ISLANDPORTAL14;
IslandPortal15                          ISLANDPORTAL15;
IslandPortal16                          ISLANDPORTAL16;
IslandPortal17                          ISLANDPORTAL17;
IslandPortal18                          ISLANDPORTAL18;
IslandPortal19                          ISLANDPORTAL19;
IslandPortal2                           ISLANDPORTAL2;
IslandPortal20                          ISLANDPORTAL20;
IslandPortal21                          ISLANDPORTAL21;
IslandPortal22                          ISLANDPORTAL22;
IslandPortal23                          ISLANDPORTAL23;
IslandPortal24                          ISLANDPORTAL24;
IslandPortal25                          ISLANDPORTAL25;
IslandPortal26                          ISLANDPORTAL26;
IslandPortal27                          ISLANDPORTAL27;
IslandPortal28                          ISLANDPORTAL28;
IslandPortal29                          ISLANDPORTAL29;
IslandPortal3                           ISLANDPORTAL3;
IslandPortal30                          ISLANDPORTAL30;
IslandPortal31                          ISLANDPORTAL31;
IslandPortal32                          ISLANDPORTAL32;
IslandPortal33                          ISLANDPORTAL33;
IslandPortal34                          ISLANDPORTAL34;
IslandPortal35                          ISLANDPORTAL35;
IslandPortal4                           ISLANDPORTAL4;
IslandPortal5                           ISLANDPORTAL5;
IslandPortal6                           ISLANDPORTAL6;
IslandPortal7                           ISLANDPORTAL7;
IslandPortal8                           ISLANDPORTAL8;
IslandPortal9                           ISLANDPORTAL9;
PortalA                                 PORTALA;
PortalB                                 PORTALB;
PortalC                                 PORTALC;
StaticDungeonPortal1                    STATICDUNGEONPORTAL1;
StaticDungeonPortal2                    STATICDUNGEONPORTAL2;
HealingWell                             HEALINGWELL;
IsolatedIslandPortal                    ISOLATEDISLANDPORTAL;
LightHavenPortal                        LIGHTHAVENPORTAL;
SanctuaryPortal                         SANCTUARYPORTAL;
SilverSkyPortal                         SILVERSKYPORTAL;
WindHowlPortal                          WINDHOWLPORTAL;
HealingPlant                            HEALINGPLANT;
DemoPortal1                             DEMOPORTAL1;
DemoPortal2                             DEMOPORTAL2;
DemoPortal3                             DEMOPORTAL3;
DemoPortal4                             DEMOPORTAL4;
DemoPortal5                             DEMOPORTAL5;
DemoPortal6                             DEMOPORTAL6;
NPCForestGuardian                       NPCFORESTGUARDIAN;
NPCRat                                  NPCRAT;
NPCTombRaider                           NPCTOMBRAIDER;
Sabrina                                 SABRINA;
PortalD                                 PORTALD;
PortalE                                 PORTALE;
PortalF                                 PORTALF;
PortalG                                 PORTALG;
PortalH                                 PORTALH;
PortalI                                 PORTALI;
PortalJ                                 PORTALJ;
PortalK                                 PORTALK;
PortalL                                 PORTALL;
PortalM                                 PORTALM;
PortalN                                 PORTALN;
PortalO                                 PORTALO;
PortalP                                 PORTALP;
PortalQ                                 PORTALQ;
PortalR                                 PORTALR;
PortalS                                 PORTALS;
PortalT                                 PORTALT;
PortalU                                 PORTALU;
PortalV                                 PORTALV;
PortalW                                 PORTALW;
PortalX                                 PORTALX;
PortalY                                 PORTALY;
PortalZ                                 PORTALZ;
EmptyDungeonPortal                      EMPTYDUNGEONPORTAL;
IslandMadnessPortal                     ISLANDMADNESSPORTAL;
ScatteredBonesPortal                    SCATTEREDBONESPORTAL;
LighthavenArenaClerk                    LIGHTHAVENARENACLERK;

// NPC registration.

INIT_NPC_DATA

    REGISTER_NPC( GMASSISTANT )
    REGISTER_NPC( ISLANDPORTAL1 )
    REGISTER_NPC( ISLANDPORTAL10 )
    REGISTER_NPC( ISLANDPORTAL11 )
    REGISTER_NPC( ISLANDPORTAL12 )
    REGISTER_NPC( ISLANDPORTAL13 )
    REGISTER_NPC( ISLANDPORTAL14 )
    REGISTER_NPC( ISLANDPORTAL15 )
    REGISTER_NPC( ISLANDPORTAL16 )
    REGISTER_NPC( ISLANDPORTAL17 )
    REGISTER_NPC( ISLANDPORTAL18 )
    REGISTER_NPC( ISLANDPORTAL19 )
    REGISTER_NPC( ISLANDPORTAL2 )
    REGISTER_NPC( ISLANDPORTAL20 )
    REGISTER_NPC( ISLANDPORTAL21 )
    REGISTER_NPC( ISLANDPORTAL22 )
    REGISTER_NPC( ISLANDPORTAL23 )
    REGISTER_NPC( ISLANDPORTAL24 )
    REGISTER_NPC( ISLANDPORTAL25 )
    REGISTER_NPC( ISLANDPORTAL26 )
    REGISTER_NPC( ISLANDPORTAL27 )
    REGISTER_NPC( ISLANDPORTAL28 )
    REGISTER_NPC( ISLANDPORTAL29 )
    REGISTER_NPC( ISLANDPORTAL3 )
    REGISTER_NPC( ISLANDPORTAL30 )
    REGISTER_NPC( ISLANDPORTAL31 )
    REGISTER_NPC( ISLANDPORTAL32 )
    REGISTER_NPC( ISLANDPORTAL33 )
    REGISTER_NPC( ISLANDPORTAL34 )
    REGISTER_NPC( ISLANDPORTAL35 )
    REGISTER_NPC( ISLANDPORTAL4 )
    REGISTER_NPC( ISLANDPORTAL5 )
    REGISTER_NPC( ISLANDPORTAL6 )
    REGISTER_NPC( ISLANDPORTAL7 )
    REGISTER_NPC( ISLANDPORTAL8 )
    REGISTER_NPC( ISLANDPORTAL9 )
    REGISTER_NPC( PORTALA )
    REGISTER_NPC( PORTALB )
    REGISTER_NPC( PORTALC )
    REGISTER_NPC( STATICDUNGEONPORTAL1 )
    REGISTER_NPC( STATICDUNGEONPORTAL2 )
    REGISTER_NPC( HEALINGWELL )
    REGISTER_NPC( ISOLATEDISLANDPORTAL )
    REGISTER_NPC( LIGHTHAVENPORTAL )
    REGISTER_NPC( SANCTUARYPORTAL )
    REGISTER_NPC( SILVERSKYPORTAL )
    REGISTER_NPC( WINDHOWLPORTAL )
    REGISTER_NPC( HEALINGPLANT )
    REGISTER_NPC( DEMOPORTAL1 )
    REGISTER_NPC( DEMOPORTAL2 )
    REGISTER_NPC( DEMOPORTAL3 )
    REGISTER_NPC( DEMOPORTAL4 )
    REGISTER_NPC( DEMOPORTAL5 )
    REGISTER_NPC( DEMOPORTAL6 )
    REGISTER_NPC( NPCFORESTGUARDIAN )
    REGISTER_NPC( NPCRAT )
    REGISTER_NPC( NPCTOMBRAIDER )
    REGISTER_NPC( SABRINA )
    REGISTER_NPC( PORTALD )
    REGISTER_NPC( PORTALE )
    REGISTER_NPC( PORTALF )
    REGISTER_NPC( PORTALG )
    REGISTER_NPC( PORTALH )
    REGISTER_NPC( PORTALI )
    REGISTER_NPC( PORTALJ )
    REGISTER_NPC( PORTALK )
    REGISTER_NPC( PORTALL )
    REGISTER_NPC( PORTALM )
    REGISTER_NPC( PORTALN )
    REGISTER_NPC( PORTALO )
    REGISTER_NPC( PORTALP )
    REGISTER_NPC( PORTALQ )
    REGISTER_NPC( PORTALR )
    REGISTER_NPC( PORTALS )
    REGISTER_NPC( PORTALT )
    REGISTER_NPC( PORTALU )
    REGISTER_NPC( PORTALV )
    REGISTER_NPC( PORTALW )
    REGISTER_NPC( PORTALX )
    REGISTER_NPC( PORTALY )
    REGISTER_NPC( PORTALZ )
    REGISTER_NPC( EMPTYDUNGEONPORTAL )
    REGISTER_NPC( ISLANDMADNESSPORTAL )
    REGISTER_NPC( SCATTEREDBONESPORTAL )
    REGISTER_NPC( LIGHTHAVENARENACLERK )

END_INIT_NPC_DATA

// NPC creation.

INIT_NPC_CREATION

    CREATE_NPC( GMASSISTANT )
    CREATE_NPC( ISLANDPORTAL1 )
    CREATE_NPC( ISLANDPORTAL10 )
    CREATE_NPC( ISLANDPORTAL11 )
    CREATE_NPC( ISLANDPORTAL12 )
    CREATE_NPC( ISLANDPORTAL13 )
    CREATE_NPC( ISLANDPORTAL14 )
    CREATE_NPC( ISLANDPORTAL15 )
    CREATE_NPC( ISLANDPORTAL16 )
    CREATE_NPC( ISLANDPORTAL17 )
    CREATE_NPC( ISLANDPORTAL18 )
    CREATE_NPC( ISLANDPORTAL19 )
    CREATE_NPC( ISLANDPORTAL2 )
    CREATE_NPC( ISLANDPORTAL20 )
    CREATE_NPC( ISLANDPORTAL21 )
    CREATE_NPC( ISLANDPORTAL22 )
    CREATE_NPC( ISLANDPORTAL23 )
    CREATE_NPC( ISLANDPORTAL24 )
    CREATE_NPC( ISLANDPORTAL25 )
    CREATE_NPC( ISLANDPORTAL26 )
    CREATE_NPC( ISLANDPORTAL27 )
    CREATE_NPC( ISLANDPORTAL28 )
    CREATE_NPC( ISLANDPORTAL29 )
    CREATE_NPC( ISLANDPORTAL3 )
    CREATE_NPC( ISLANDPORTAL30 )
    CREATE_NPC( ISLANDPORTAL31 )
    CREATE_NPC( ISLANDPORTAL32 )
    CREATE_NPC( ISLANDPORTAL33 )
    CREATE_NPC( ISLANDPORTAL34 )
    CREATE_NPC( ISLANDPORTAL35 )
    CREATE_NPC( ISLANDPORTAL4 )
    CREATE_NPC( ISLANDPORTAL5 )
    CREATE_NPC( ISLANDPORTAL6 )
    CREATE_NPC( ISLANDPORTAL7 )
    CREATE_NPC( ISLANDPORTAL8 )
    CREATE_NPC( ISLANDPORTAL9 )
    CREATE_NPC( PORTALA )
    CREATE_NPC( PORTALB )
    CREATE_NPC( PORTALC )
    CREATE_NPC( STATICDUNGEONPORTAL1 )
    CREATE_NPC( STATICDUNGEONPORTAL2 )
    CREATE_NPC( HEALINGWELL )
    CREATE_NPC( ISOLATEDISLANDPORTAL )
    CREATE_NPC( LIGHTHAVENPORTAL )
    CREATE_NPC( SANCTUARYPORTAL )
    CREATE_NPC( SILVERSKYPORTAL )
    CREATE_NPC( WINDHOWLPORTAL )
    CREATE_NPC( HEALINGPLANT )
    CREATE_NPC( DEMOPORTAL1 )
    CREATE_NPC( DEMOPORTAL2 )
    CREATE_NPC( DEMOPORTAL3 )
    CREATE_NPC( DEMOPORTAL4 )
    CREATE_NPC( DEMOPORTAL5 )
    CREATE_NPC( DEMOPORTAL6 )
    CREATE_NPC( NPCFORESTGUARDIAN )
    CREATE_NPC( NPCRAT )
    CREATE_NPC( NPCTOMBRAIDER )
    CREATE_NPC( SABRINA )
    CREATE_NPC( PORTALD )
    CREATE_NPC( PORTALE )
    CREATE_NPC( PORTALF )
    CREATE_NPC( PORTALG )
    CREATE_NPC( PORTALH )
    CREATE_NPC( PORTALI )
    CREATE_NPC( PORTALJ )
    CREATE_NPC( PORTALK )
    CREATE_NPC( PORTALL )
    CREATE_NPC( PORTALM )
    CREATE_NPC( PORTALN )
    CREATE_NPC( PORTALO )
    CREATE_NPC( PORTALP )
    CREATE_NPC( PORTALQ )
    CREATE_NPC( PORTALR )
    CREATE_NPC( PORTALS )
    CREATE_NPC( PORTALT )
    CREATE_NPC( PORTALU )
    CREATE_NPC( PORTALV )
    CREATE_NPC( PORTALW )
    CREATE_NPC( PORTALX )
    CREATE_NPC( PORTALY )
    CREATE_NPC( PORTALZ )
    CREATE_NPC( EMPTYDUNGEONPORTAL )
    CREATE_NPC( ISLANDMADNESSPORTAL )
    CREATE_NPC( SCATTEREDBONESPORTAL )
    CREATE_NPC( LIGHTHAVENARENACLERK )

END_INIT_NPC_CREATION

#pragma hdrstop
#include "DoppelgangerPortal6a.h"

DoppelgangerPortal6a::DoppelgangerPortal6a()
{}

DoppelgangerPortal6a::~DoppelgangerPortal6a()
{}

extern NPCstructure::NPC PortalNPC;

void DoppelgangerPortal6a::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[12731]A radiating portal" );
    npc.InitialPos.X = 280;
    npc.InitialPos.Y = 2510;
    npc.InitialPos.world = 0;
}
void DoppelgangerPortal6a::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DoppelgangerPortal6a::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DoppelgangerPortal6a::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT Agreement = 1;

InitTalk

Begin
""
IF(IsInRange(4))
IF(USER_LEVEL >= 50 || CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 2)//BLBLBL BL added limit on level 50
	IF(ACK_DOPPELGANGER == 1) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 12006, "The portal's energy has been depleted and is no longer operational.")) 
		BREAK 
	ELSE 
	IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 1)
//		IF(CheckFlag(__FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER) == 9)
/* V2 fix for the Doppel portal abuse of logging within a portal and re-killing the same doppelganger - Aedus (15Mar06) */
		IF(CheckFlag(__FLAG_ADDON_PORTAL_1_CLEARED) == 1 && CheckFlag(__FLAG_ADDON_PORTAL_2_CLEARED) == 1 &&
		   CheckFlag(__FLAG_ADDON_PORTAL_3_CLEARED) == 1 && CheckFlag(__FLAG_ADDON_PORTAL_4_CLEARED) == 1 &&
		   CheckFlag(__FLAG_ADDON_PORTAL_5_CLEARED) == 1 && CheckFlag(__FLAG_ADDON_PORTAL_6_CLEARED) == 1 &&
		   CheckFlag(__FLAG_ADDON_PORTAL_7_CLEARED) == 1 && CheckFlag(__FLAG_ADDON_PORTAL_8_CLEARED) == 1 )
			PRIVATE_SYSTEM_MESSAGE(INTL( 12007, "The portal's surface is clear. You step through and appear somewhere else."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12008, "You feel as though your body will not survive long on this plane of existence..."))
			CastSpellTarget(__SPELL_DOPPELGANGER_RETURN_TELEPORT)
			GiveFlag(__FLAG_ADDON_DOPPELGANGER_PORTAL_USED_TO_ENTER, 6)
			TELEPORT(2959, 1394, 1)
			BREAK
		ELSEIF(CheckFlag(__FLAG_ADDON_PORTAL_6_CLEARED) == 1)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12009, "The portal's surface is clear. When you step through, nothing happens."))
			BREAK
		ELSE
			IF(CheckFlag(__FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER) == 0)
				PRIVATE_SYSTEM_MESSAGE(INTL( 12010, "You can see your own reflection swirling in the portal's mists."))
				Conversation
				INTL( 12042, "At last! I've finally found you! I'm glad to see you noticed my little \"creations\".")
			ELSEIF(CheckFlag(__FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER) == 1)
				Conversation
				INTL( 12043, "Back so soon? What do you say? Will you meet me on a neutral plane so that we may find a "
				"solution to this problem?")
				SetYesNo(Agreement)
			ELSE
				Conversation
				INTL( 12044, "Argh, there you are! So you beat me last time. I must defeat you if I'm... Alright, let's "
				"try this again, but without any tricks this time. What do you say? Will you meet with me "
				"on a neutral plane so that we may find a solution to this problem?")
				SetYesNo(Agreement)
			ENDIF
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12009, "The portal's surface is clear. When you step through, nothing happens."))
		BREAK
	ENDIF
	ENDIF
ELSE//BLBLBL BL added limit on level 50
	PRIVATE_SYSTEM_MESSAGE(INTL( 13034, "You must be level 50 or X2 at least to inspect this portal."))
	BREAK
ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12014, "You must step closer to the portal to inspect it."))
	BREAK
ENDIF


Command(INTL( 12015, "CREATION"))
INTL( 12045, "I created eight of these portals in the hopes that you would find them. You see, your newfound powers "
"granted you by your rebirth did not just come from out of thin air. When you gained those powers, I lost "
"some of mine and it has to \"stop\"!")

Command(INTL( 7346, "STOP"))
INTL( 12046, "If you step through the portal, it will bring you to a neutral plane where I'm sure we can come to some "
"sort of an agreement. Well, what do you say? Will you meet me on equal terms so that we may find a solution "
"to this problem?")
IF(CheckFlag(__FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER) == 0)
	GiveFlag(__FLAG_ADDON_USER_KNOWS_ABOUT_DOPPELGANGER, 1)
ENDIF
SetYesNo(Agreement)

YES(Agreement)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12018, "You step through the portal and appear somewhere else."))
	PRIVATE_SYSTEM_MESSAGE(INTL( 12008, "You feel as though your body will not survive long on this plane of existence..."))
/* V2 Fix (Aug 07, 2007) - Allow a player to reenter the same dopple fight until they kill him */
	IF(CheckFlag(__FLAG_V2_DOPPLE_PORTAL_FIX) == 0)
		IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_DOPPELGANGER_ROOM) == 25)
			GiveGlobalFlag(__GLOBAL_FLAG_ADDON_DOPPELGANGER_ROOM, 1)
			GiveFlag(__FLAG_V2_DOPPLE_PORTAL_FIX, 1)
		ELSE
			GiveFlag(__FLAG_V2_DOPPLE_PORTAL_FIX, CheckGlobalFlag(__GLOBAL_FLAG_ADDON_DOPPELGANGER_ROOM) + 1)
			GiveGlobalFlag(__GLOBAL_FLAG_ADDON_DOPPELGANGER_ROOM, CheckGlobalFlag(__GLOBAL_FLAG_ADDON_DOPPELGANGER_ROOM) + 1)
		ENDIF
	ENDIF
	GiveFlag(__FLAG_ADDON_DOPPELGANGER_PORTAL_USED_TO_ENTER, 6)
	CastSpellTarget(__SPELL_DOPPELGANGER_RETURN_TELEPORT)
//	SWITCH(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_DOPPELGANGER_ROOM))
/* V2 Fix (Aug 07, 2007) - Allow a player to reenter the same dopple fight until they kill him */
	SWITCH(CheckFlag(__FLAG_V2_DOPPLE_PORTAL_FIX))
		CASE(1)
			TELEPORT(2790, 1030, 1)
		ENDCASE
		CASE(2)
			TELEPORT(2850, 1030, 1)
		ENDCASE
		CASE(3)
			TELEPORT(2910, 1030, 1)
		ENDCASE
		CASE(4)
			TELEPORT(2970, 1030, 1)
		ENDCASE
		CASE(5)
			TELEPORT(3030, 1030, 1)
		ENDCASE
		CASE(6)
			TELEPORT(2790, 1090, 1)
		ENDCASE
		CASE(7)
			TELEPORT(2850, 1090, 1)
		ENDCASE
		CASE(8)
			TELEPORT(2910, 1090, 1)
		ENDCASE
		CASE(9)
			TELEPORT(2970, 1090, 1)
		ENDCASE
		CASE(10)
			TELEPORT(3030, 1090, 1)
		ENDCASE
		CASE(11)
			TELEPORT(2790, 1150, 1)
		ENDCASE
		CASE(12)
			TELEPORT(2850, 1150, 1)
		ENDCASE
		CASE(13)
			TELEPORT(2910, 1150, 1)
		ENDCASE
		CASE(14)
			TELEPORT(2970, 1150, 1)
		ENDCASE
		CASE(15)
			TELEPORT(3030, 1150, 1)
		ENDCASE
		CASE(16)
			TELEPORT(2790, 1210, 1)
		ENDCASE
		CASE(17)
			TELEPORT(2850, 1210, 1)
		ENDCASE
		CASE(18)
			TELEPORT(2910, 1210, 1)
		ENDCASE
		CASE(19)
			TELEPORT(2970, 1210, 1)
		ENDCASE
		CASE(20)
			TELEPORT(3030, 1210, 1)
		ENDCASE
		CASE(21)
			TELEPORT(2790, 1270, 1)
		ENDCASE
		CASE(22)
			TELEPORT(2850, 1270, 1)
		ENDCASE
		CASE(23)
			TELEPORT(2910, 1270, 1)
		ENDCASE
		CASE(24)
			TELEPORT(2970, 1270, 1)
		ENDCASE
		CASE(25)
			TELEPORT(3030, 1270, 1)
		ENDCASE
    ENDSWITCH
	BREAK
NO(Agreement)
	Conversation
	INTL( 12019, "Argh! I will have my power back even if I have to kill you in the process!")
	BREAK
YesNoELSE(Agreement)
	Conversation
	INTL( 12020, "Well? Will you meet me on a neutral plane so that we may find a solution to this problem?")
	SetYesNo(Agreement)

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12021, "What? Where are you going? Get back here and finish our business!")
BREAK

Default
INTL( 4019, "I don't have time for this.")

EndTalk

}

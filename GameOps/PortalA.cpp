#pragma hdrstop
#include "PortalA.h"

PortalA::PortalA()
{}

PortalA::~PortalA()
{}

extern NPCstructure::NPC IslandPortalNPC;

void PortalA::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
}
void PortalA::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}



void PortalA::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PortalA::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A) != 0)
	IF (IsInRange(4))
		UseC						  
		BYTE bPositionWorld = (dfGlobalFlags.ViewFlag( __GLOBAL_FLAG_DYNAMIC_PORTAL_A) & 0xFF);
		WORD wPositionY = (dfGlobalFlags.ViewFlag( __GLOBAL_FLAG_DYNAMIC_PORTAL_A) & 0xFFF00) >> 8;
		WORD wPositionX = (dfGlobalFlags.ViewFlag( __GLOBAL_FLAG_DYNAMIC_PORTAL_A) & 0xFFF00000) >> 20;
		TELEPORT( wPositionX, wPositionY, bPositionWorld)				
		IF(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_GP) > 0) 
			GiveGold(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_GP))  	
		ENDIF
		IF(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP) > 0) 
			GiveXP(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP))  
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7350, "You've been awarded %u experience points!"), CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP)))
		ENDIF 
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF	 
		
	/* Ok, this code has been temporarily trashed because NPCatoi apparently doesn't support negatives.
	// PORTAL REWARD START TEST (GOLD) 
		IF(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_GP) > 0) 
			GiveGold(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_GP))  	
		ELSEIF((CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_GP) < 0) && (Gold != 0))
			IF (-CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_GP) > Gold) 				
				TakeGold(Gold) 				
			ELSE				
				TakeGold(-CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_GP) )
			ENDIF
		ENDIF 
	// PORTAL REWARD START (XP) 	
		IF(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP) > 0) 
			GiveXP(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP))  
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7350, "You've been awarded %u experience points!"), CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP)))
		ELSEIF((CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP) < 0) && (USER_XP != 0))
			IF (-CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP) > USER_XP) 			
				// The user loses all its experience points. (down to 0) 
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7351, "You've been drained of %I64u experience points!"), USER_XP))
				GiveXP(-USER_XP)
			ELSE
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7352, "You've been drained of %u experience points!"), -CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP)))
				GiveXP(CheckGlobalFlag(__GLOBAL_FLAG_DYNAMIC_PORTAL_A_XP))
			ENDIF
		ENDIF  
	// PORTAL REWARD END TEST	*/	
ELSE
	IF (IsInRange(4))
		UseC
		BYTE bPositionWorld = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFF);
		WORD wPositionY = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFFF00) >> 8;
		WORD wPositionX = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFFF00000) >> 20;
		IF(target->ViewFlag(__FLAG_DEATH_LOCATION) != 0)
			TELEPORT( wPositionX, wPositionY, bPositionWorld)
		ELSE
			TELEPORT(2941, 1062, 0)
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF
ENDIF
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk

}
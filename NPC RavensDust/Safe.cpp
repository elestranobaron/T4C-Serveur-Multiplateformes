///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Safe.h"

Safe::Safe()
{}

Safe::~Safe()
{}

extern NPCstructure::NPC SafeNPC;

void Safe::Create( void )
{
      npc = ( SafeNPC );
      SET_NPC_NAME( "[2979]A safe" );  
      npc.InitialPos.X = 1372;//2797;//1372; 
      npc.InitialPos.Y = 2323;//222;//2323;
      npc.InitialPos.world = 0;//4;//0;
 npc.boPrivateTalk = TRUE;
}

void Safe::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}

}

void Safe::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}


void Safe::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{
InitTalk

//  __QUEST_VAULT_CODE_ONE      Given by Rondy.
//  __QUEST_VAULT_CODE_TWO      Given by Geram. 
//  __QUEST_VAULT_CODE_THREE    Given by Talon Irongaze.

Begin
INTL( 6208, "You are looking at the safe of the bank. {Type} {HELP} {for} "
"{assistance.}")

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 6209, "{You} {are} {trying} {to} {talk} {to} {an} {object,} {weirdo!}")

Command3(INTL( 488, "WHAT DO YOU"),INTL( 489, "WORK"),INTL( 487, "OCCUPATION"))
INTL( 6209, "{You} {are} {trying} {to} {talk} {to} {an} {object,} {weirdo!}")

Command(INTL( 554, "HELP"))
INTL( 6210, "The safe's combination is composed of 3 numbers that can be anywhere "
"between 1 and 100 inclusively. To rotate the safe's wheel, you can "
"type {RIGHT} 10 to rotate the wheel 10 numbers to the right or type {LEFT} "
"if you wish to rotate it in the opposite direction.")

ParamCmd(INTL( 6211, "RIGHT $"))
""
IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) > CurrentRound) && (CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) != 0))
	Conversation
	INTL( 6212, "{The} {safe} {has} {just} {been} {robbed.} {It} {would} {be} {foolish} {to} {try} {again} {so} {soon.}")
	BREAK		
ELSE
	;int nCode = NUM_PARAM( 0 );
	IF ((nCode < 1 ) || (nCode > 100)) 
	   Conversation
	   INTL( 6213, "{The} {safe's} {combination} {is} {composed} {of} {numbers} {between} "
	   "{1} {and} {100} {inclusively.}") 
	ELSE
		IF (CheckFlag(__FLAG_SAFE_NUMBER) == 0)   
			IF (CheckFlag(__QUEST_VAULT_CODE_ONE) == nCode)
				Conversation
				INTL( 6214, "{Click!}")
				GiveFlag(__FLAG_SAFE_NUMBER, 1)
			ELSE
				RemFlag(__FLAG_SAFE_NUMBER)
				SWITCH(rnd.roll(dice(1,4)))
					CASE(1)
						Conversation
						INTL( 6215, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {throws} {you} {directly} {in} {jail!}")
						TELEPORT( 209,2338,1 )
						BREAK
					ENDCASE
					CASE(2)
						IF (USER_HP > 2)
							Conversation
							FORMAT(INTL( 6216, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {inflicts} {you} {%u} {damages!}"),(USER_HP/2));
							target->SetHP( (USER_HP/2), true )
						ELSE
							Conversation
							INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
						ENDIF
					ENDCASE
					CASE(3)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
					CASE(4)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
				ENDSWITCH
				BREAK
			ENDIF
		ELSEIF (CheckFlag(__FLAG_SAFE_NUMBER) == 1)   
			RemFlag(__FLAG_SAFE_NUMBER)		
			SWITCH(rnd.roll(dice(1,4)))
					CASE(1)
						Conversation
						INTL( 6215, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {throws} {you} {directly} {in} {jail!}")
						TELEPORT( 209,2338,1 )
						BREAK
					ENDCASE
					CASE(2)
						IF (USER_HP > 2)
							Conversation
							FORMAT(INTL( 6216, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {inflicts} {you} {%u} {damages!}"),(USER_HP/2));
							target->SetHP( (USER_HP/2), true )
						ELSE
							Conversation
							INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
						ENDIF
					ENDCASE
					CASE(3)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
					CASE(4)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
				ENDSWITCH				
				BREAK
		ELSE // 2 
			IF (CheckFlag(__QUEST_VAULT_CODE_THREE) == nCode)				
				//IF (CheckFlag(__FLAG_USER_HAS_ROBBED_THE_SAFE_BEFORE) == 1) 
				//	;int nStolenGoldPieces = (rnd.roll(dice(8,100,500))); //									
				//	Conversation
				//	FORMAT(INTL( 6218, "{Success!} {You've} {just} {opened} {the} {chest!} {You} {stole} {%u} "
				//	"{gold} {pieces} {from} {the} {bank!}"), nStolenGoldPieces) 									
				// ELSE
					;int nStolenGoldPieces = (rnd.roll(dice(8,1000,800))); 
					// Conversation
					PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 6219, "{Success!} {You've} {just} {opened} {the} {chest!} {You} {stole} {%u} "
					"{gold} {pieces} {from} {the} {bank!}"), nStolenGoldPieces)) 
					;int nExpReward = 10000; 	
					GiveXP(nExpReward)
					GiveGold(nStolenGoldPieces)
					// Conversation
					PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 					
					RemFlag(__QUEST_VAULT_CODE_ONE)
					RemFlag(__FLAG_SAFE_NUMBER)
					RemFlag(__QUEST_VAULT_CODE_TWO)
					RemFlag(__QUEST_VAULT_CODE_THREE)
					GiveGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED_BY, CheckFlag(__FLAG_SHADEEN_PLAYER_B))
					GiveGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED, 10 MINUTES TDELAY) // Delay is set at 10 minutes. 
					GiveFlag( __FLAG_THIEF, CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED))	// Timer			
					GiveFlag(__FLAG_USER_HAS_ROBBED_THE_SAFE_BEFORE,1) 
					BREAK					
				// ENDIF
			ELSE
				RemFlag(__FLAG_SAFE_NUMBER)
				SWITCH(rnd.roll(dice(1,4)))
					CASE(1)
						Conversation
						INTL( 6215, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {throws} {you} {directly} {in} {jail!}")
						TELEPORT( 209,2338,1 )
						BREAK
					ENDCASE
					CASE(2)
						IF (USER_HP > 2)
							Conversation
							FORMAT(INTL( 6216, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {inflicts} {you} {%u} {damages!}"),(USER_HP/2));
							target->SetHP( (USER_HP/2), true )
						ELSE
							Conversation
							INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
						ENDIF
					ENDCASE
					CASE(3)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
					CASE(4)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
				ENDSWITCH								
				BREAK
			ENDIF
		ENDIF	
	ENDIF
ENDIF

ParamCmd(INTL( 6220, "LEFT $"))
""
IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) > CurrentRound) && (CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) != 0))
	Conversation
	INTL( 6212, "{The} {safe} {has} {just} {been} {robbed.} {It} {would} {be} {foolish} {to} {try} {again} {so} {soon.}")
	BREAK		
ELSE
	;int nCode = NUM_PARAM( 0 );
	IF ((nCode < 1 ) || (nCode > 100)) 
	   Conversation
	   INTL( 6221, "{The} {safe's} {combination} {is} {composed} {of} {numbers} {between} "
	   "{1} {and} {100} {inclusively.}") 
	ELSE
		IF (CheckFlag(__FLAG_SAFE_NUMBER) == 0)   		
			RemFlag(__FLAG_SAFE_NUMBER)		
			SWITCH(rnd.roll(dice(1,4)))
					CASE(1)
						Conversation
						INTL( 6215, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {throws} {you} {directly} {in} {jail!}")
						TELEPORT( 209,2338,1 )
						BREAK
					ENDCASE
					CASE(2)
						IF (USER_HP > 2)
							Conversation
							FORMAT(INTL( 6216, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {inflicts} {you} {%u} {damages!}"),(USER_HP/2));
							target->SetHP( (USER_HP/2), true )
						ELSE
							Conversation
							INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
						ENDIF
					ENDCASE
					CASE(3)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
					CASE(4)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
				ENDSWITCH					
				BREAK
		ELSEIF (CheckFlag(__FLAG_SAFE_NUMBER) == 1)   
			IF (CheckFlag(__QUEST_VAULT_CODE_TWO) == nCode)
				Conversation
				INTL( 6214, "{Click!}")
				GiveFlag(__FLAG_SAFE_NUMBER, 2)
			ELSE
				RemFlag(__FLAG_SAFE_NUMBER)
				SWITCH(rnd.roll(dice(1,4)))
					CASE(1)
						Conversation
						INTL( 6215, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {throws} {you} {directly} {in} {jail!}")
						TELEPORT( 209,2338,1 )
						BREAK
					ENDCASE
					CASE(2)						
						IF (USER_HP > 2)
							Conversation
							FORMAT(INTL( 6216, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {inflicts} {you} {%u} {damages!}"),(USER_HP/2));
							target->SetHP( (USER_HP/2), true )
						ELSE
							Conversation
							INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
						ENDIF
					ENDCASE
					CASE(3)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
					CASE(4)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
				ENDSWITCH					
				BREAK
			ENDIF
		ELSE // 2 			
			RemFlag(__FLAG_SAFE_NUMBER)			
			SWITCH(rnd.roll(dice(1,4)))
					CASE(1)
						Conversation
						INTL( 6215, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {throws} {you} {directly} {in} {jail!}")
						TELEPORT( 209,2338,1 )
						BREAK
					ENDCASE
					CASE(2)
						IF (USER_HP > 2)
							Conversation
							FORMAT(INTL( 6216, "{Failure!} {The} {safe's} {magical} {defense} {mechanism} {inflicts} {you} {%u} {damages!}"),(USER_HP/2));
							target->SetHP( (USER_HP/2), true )
						ELSE
							Conversation
							INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
						ENDIF
					ENDCASE
					CASE(3)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
					CASE(4)
						Conversation
						INTL( 6217, "{Failure!} {The} {safe} {is} {still} {locked.}")
					ENDCASE
				ENDSWITCH
				BREAK
		ENDIF	
	ENDIF
ENDIF

Command(INTL( 6222, "RIGHT"))
INTL( 6223, "If you wish to rotate the wheel to the right, you must provide a number. "
"For example, you could type RIGHT 10 and you would rotate the wheel to the "
"right by 10 numbers.")

Command(INTL( 6224, "LEFT"))
INTL( 6225, "If you wish to rotate the wheel to the left, you must provide a number. "
"For example, you could type LEFT 10 and you would rotate the wheel to the "
"left by 10 numbers.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 6209, "{You} {are} {trying} {to} {talk} {to} {an} {object,} {weirdo!}")
BREAK

Command4(INTL( 520, "QUIT"),INTL( 521, "EXIT"),INTL( 519, "LEAVE"),INTL( 518, "BYE"))
INTL( 1864, "...")
BREAK

Default
INTL( 6226, "{Type} {HELP} {for} {assistance.}")

EndTalk
}
	
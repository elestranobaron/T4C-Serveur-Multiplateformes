///////////////////////////////////////////////////////////////////////////////////////
// Here are defined the "NPC pseudo-script" functions
#ifndef __NPCMACROSCRIPTLNG_H
#define __NPCMACROSCRIPTLNG_H

#include "SysopCmd.h"
#include "TFCException.h"
#include "DynamicFlags.h"
#include "T4CLog.h"
#include "DynObjListing.h"
#include "IntlText.h"
#include "Format.h"
/*
#ifdef  EXPORT
#define EXPORT_COPY EXPORT
#undef  EXPORT
#endif

#ifdef  IMPORT
#define IMPORT_COPY IMPORT
#undef  IMPORT
#endif


#define IMPORT __declspec( dllimport )
#define EXPORT __declspec( dllexport )
*/
using namespace vir;

struct _SKILLITEM{
	char cCanHave; 
	CString csSkillName;
    CString reqDesc;
	WORD wID;
	WORD wMaxLearnPnts;
	WORD wCurPnts;
	DWORD dwSkillCost;
    DWORD dwIcon;
};

struct _OBJECTITEM{
	DWORD	dwPrice;
	DWORD	dwID;
	WORD	wAppearance;
    BYTE    bCanEquip;
    DWORD   dwQty;
	CString csItemName;
    CString reqDesc;
};

// TODO
// AddTalkFlag
// CurePlayer
// BlessPlayer

extern DynamicFlags IMPORT dfGlobalFlags;

int EXPORT NPCatoi( const char *lpszString );
void EXPORT NPCFormatMsg( CString &msg, CString &parammsg );

void EXPORT RemortTo( Unit *self, DWORD x, DWORD y, DWORD world );

#define REMORT_TO( ixe, why, world ) RemortTo( target, ixe, why, world );

//////////////////////////////////////////////////////////////////////////////////////////
// Allows constant variables within the NPC text
#define CONSTANT	;const int 

#define INTL(ID, X)        IntlText::GetString( ID, ( target == NULL ? _DEFAULT_LNG : target->GetLang() ), X )

/////////////////////////////////////////////////////////////////////////////////////
// Breaks a conversation
void EXPORT BreakFunc( Unit *npc, Unit *target );
#define BREAK ;BreakFunc( self, target );

//////////////////////////////////////////////////////////////////////////////////////////
#define ShowBackpack				;TFCPacket sending;\
									sending << (RQ_SIZE)RQ_ViewBackpack;\
									sending << (char)1;\
									sending << (long)target->GetID();\
									target->PacketBackpack( sending );\
									target->SendPlayerMessage( sending );

/////////////////////////////////////////////////////////////////////////////////////
// Starts a conversation, OS is the Opening Statement
#define InitTalk ;char lpszDummy[ 16 ];\
    lpszDummy[ 0 ] = 0;\
    bool xSendBackpackUpdate = false;\
    static int YesNo;\
    USER_SKILL sUserSkill;\
    sUserSkill.SetSkillID( 0 );\
    sUserSkill.SetSkillPnts( 0 );\
    CString lpcsParams[ 5 ];\
    TFormat FORMAT;\
    BOOL boOpenStatement = FALSE;\
    Character *lpChar = NULL;\
    Players *lpUser = NULL;\
    if( target->GetType() == U_PC ){\
        lpChar = static_cast< Character * >( target );\
        lpUser = reinterpret_cast< Players * >( lpChar->GetPlayer() );\
    }\
    CString msg = (LPCTSTR)valueIN;/* allows single word commands */\
    CString parammsg;\
    NPCFormatMsg( msg, parammsg );\
    CString output;\
    BYTE NPCbehavior = self->IsDoing(); \
    if(  /* If not currently talking */ \
        NPCbehavior == nothing || NPCbehavior == wandering\
    ){ \
        YesNo = 0;\
        self->Do(talking);\
        if( !self->IsPrivateTalk() ){\
            self->SetTarget(target);\
        };\
        boOpenStatement = TRUE;\
        NPCbehavior = talking;\
    }\
    /* If after all the NPC isn't talking. */\
    if(NPCbehavior != talking){\
        return;\
    }\
    /* If the player isn't the NPCs target and the NPC isn't a private talk NPC.*/\
    if( !( self->GetTarget() == target || self->IsPrivateTalk() ) ){\
        BreakFunc( NULL, target );\
        target->SendPrivateMessage( CString( INTL( 7290, "Sorry but I am talking to someone else." ) ), self, npc.dwTextColor );\
        return;\
    }\
    self->SetIdleTime(TFCMAIN::GetRound());
                            
#define Begin        if( msg == "  " || boOpenStatement ){ output += 

/////////////////////////////////////////////////////////////////////////////////////
// Statement to output when someone says something odd.
#define Default        		;} else{ \
									output +=

#define EndTalk            ;} /* Begin */\
                           ;if( !output.IsEmpty() ){\
                                if( self->IsPrivateTalk() ){\
                                    target->SendPrivateMessage( output, self, npc.dwTextColor );\
                                }else{\
                                    self->Talk( (LPCTSTR)output, npc.dwTextColor, target );\
                                }\
                            }\
                            if( xSendBackpackUpdate && target != NULL ){\
                                ShowBackpack;\
                            }


#define NPCFUNC_PROTOTYPE CString &output, Unit *self, Unit *target, Character *lpChar, int &YesNo
#define NPCFUNC_PARAM     output, self, target, lpChar, YesNo

#define MAKE_FUNC( FuncName )  static void NPC##FuncName ( NPCFUNC_PROTOTYPE, bool &xSendBackpackUpdate ){
#define END_FUNC ;};

#define CALL_FUNC( FuncName )  ;NPC##FuncName  ( NPCFUNC_PARAM, xSendBackpackUpdate );


#define IsInRange( range ) /* Square range:  dx <= r && dy <= r */\
    ( abs( self->GetWL().X - target->GetWL().X ) <= range &&\
      abs( self->GetWL().Y - target->GetWL().Y ) <= range )


#define IsInRangeRadial( range ) /* Radial range: dx^2 + dy^2 <= r^2 */\
    ( ( abs( self->GetWL().X - target->GetWL().X ) * \
              abs( self->GetWL().X - target->GetWL().X ) + \
              abs( self->GetWL().Y - target->GetWL().Y ) * \
              abs( self->GetWL().Y - target->GetWL().Y ) ) <= range * range );
									 
bool EXPORT __IsBlocked( Unit *self, Unit *target );
#define IsBlocked	__IsBlocked( self, target )

/////////////////////////////////////////////////////////////////////////////////////
// Begins a module to be executing upon the string command "cmd"

bool EXPORT NPCKeyWord( const CString &msg, const char *cmd );

#define Command(cmd)			;} else if( NPCKeyWord( msg, cmd ) && !YesNo) { output += 

#define Command2(cmd1, cmd2)     ;} else if( ( NPCKeyWord( msg, cmd1 ) || NPCKeyWord( msg, cmd2 ) ) && !YesNo) { output += 

#define Command3(cmd1, cmd2, cmd3)     ;} else if( ( NPCKeyWord( msg, cmd1 ) || NPCKeyWord( msg, cmd2 ) || NPCKeyWord( msg, cmd3 ) ) && !YesNo) { output += 

#define Command4(cmd1, cmd2, cmd3, cmd4)     ;} else if( ( NPCKeyWord( msg, cmd1 ) || NPCKeyWord( msg, cmd2 ) || NPCKeyWord( msg, cmd3 ) || NPCKeyWord( msg, cmd4 ) ) && !YesNo) { output += 

#define Command5(cmd1, cmd2, cmd3, cmd4, cmd5)     ;} else if( ( NPCKeyWord( msg, cmd1 ) || NPCKeyWord( msg, cmd2 ) || NPCKeyWord( msg, cmd3 ) || NPCKeyWord( msg, cmd4 ) || NPCKeyWord( msg, cmd5 ) ) && !YesNo) { output += 

#define PARAM( __num )		lpcsParams[ __num ]
#define NUM_PARAM( __num )	NPCatoi( (LPCTSTR)lpcsParams[ __num ] )

bool EXPORT NPCGetParameters( const char *cmd, CString &parammsg, CString *lpcsParams );
#define ParamCmd( __cmd ) ;}else if( NPCGetParameters( __cmd, parammsg, lpcsParams ) && !YesNo ){
                      
//////////////////////////////////////////////////////////////////////////////////////////////////
// Allows a 'IF' a the Command level of the script indentation
#define CmdIF					;} else if
#define DO						{

// TODO
#define AddTalkFlag( flag )

//////////////////////////////////////////////////////////////////////////////////////////
// Command where all the keywords must be there
#define CmdAND( cmd1, cmd2 )	;} else if( NPCKeyWord( msg, cmd1 ) && NPCKeyWord( msg, cmd2 ) && !YesNo ){ output +=

#define CmdAND3( cmd1, cmd2, cmd3 )	;} else if( NPCKeyWord( msg, cmd1 ) && NPCKeyWord( msg, cmd2 ) && NPCKeyWord( msg, cmd3 ) && !YesNo ){ output +=

#define CmdAND4( cmd1, cmd2, cmd3, cmd4 )	;} else if( NPCKeyWord( msg, cmd1 ) && NPCKeyWord( msg, cmd2 ) && NPCKeyWord( msg, cmd3 ) && NPCKeyWord( msg, cmd4 ) && !YesNo ){ output +=

#define CmdAND5( cmd1, cmd2, cmd3, cmd4, cmd5 )	;} else if( NPCKeyWord( msg, cmd1 ) && NPCKeyWord( msg, cmd2 ) && NPCKeyWord( msg, cmd3 ) && NPCKeyWord( msg, cmd4 ) && NPCKeyWord( msg, cmd5 ) && !YesNo ){ output +=

///////////////////////////////////////////////////////////////////////////////////////////
// Returns TRUE if cmd1 and cmd2 are in order
BOOL EXPORT _ORDER ( CString Message, LPCTSTR cmd1, LPCTSTR cmd2, LPCTSTR cmd3 = NULL, LPCTSTR cmd4 = NULL, LPCTSTR cmd5 = NULL);

//////////////////////////////////////////////////////////////////////////////////////////
// Returns the message string
#define MESSAGE		msg


//////////////////////////////////////////////////////////////////////////////////////////
void EXPORT TeleportFunc( int x, int y, int world, Unit *target );
#define TELEPORT( x, y, wl ) ;TeleportFunc( x, y, wl, target );

								

//////////////////////////////////////////////////////////////////////////////////////////
// Determines if __item can be equipped.
#define CanUserEquip( __item )    ( lpChar == NULL ? FALSE : lpChar->CanEquip( __item, NULL, FALSE ) )
						 
/////////////////////////////////////////////////////////////////////////////////////
// Simply makes the 'C/C++' available again
#define UseC		;

#define C( __num )	;output += itoa( __num, lpszDummy, 10 );\
					output += 

/////////////////////////////////////////////////////////////////////////////////////
// Returns to conversation
#define Conversation	; output += 


//////////////////////////////////////////////////////////////////////////////////////////
// Makes the NPC fight the player.
#define FIGHT   ;self->SetTarget( target );\
                 self->Do( fighting );

/////////////////////////////////////////////////////////////////////////////////////
// standard 'if'
#define IF(state)				;if(state){

/////////////////////////////////////////////////////////////////////////////////////
// standard 'else'
#define ELSE					;}else{

/////////////////////////////////////////////////////////////////////////////////////
// standard 'else if'
#define ELSEIF(state)			;}else if(state){

/////////////////////////////////////////////////////////////////////////////////////
// closing if (obligatory)
#define ENDIF					;}

/////////////////////////////////////////////////////////////////////////////////////
// Simplifies the syntax..
#define OR						||
#define AND						&&

//////////////////////////////////////////////////////////////////////////////////////////
// A simple 'FOR'
#define FOR( from, to )			;{ int nCount; for( nCount = from; nCount < to; nCount++ ){

#define ENDFOR					;}}
					
/////////////////////////////////////////////////////////////////////////////////////
// script implementation of ViewFlag
#define CheckFlag(flag)					target->ViewFlag(flag)

/////////////////////////////////////////////////////////////////////////////////////
// script implementation of AddFlag
#define GiveFlag(flag, value)			;target->SetFlag(flag, value)

/////////////////////////////////////////////////////////////////////////////////////
// script implementation of RemoveFlag
#define RemFlag(flag)					;target->RemoveFlag(flag)

//////////////////////////////////////////////////////////////////////////////////////////
// Gives and check global server flags.
#define CheckGlobalFlag( flag )         dfGlobalFlags.ViewFlag( flag )

#define GiveGlobalFlag( flag, value )   ;dfGlobalFlags.SetFlag( flag, value )

#define RemGlobalFlag( flag )           ;dfGlobalFlags.RemoveFlag( flag )

//////////////////////////////////////////////////////////////////////////////////////////
// Gives flags on given units.
#define CheckUnitFlag( __unit, flag )       ( __unit != NULL ? __unit->ViewFlag( flag ) : 0 )

#define GiveUnitFlag( __unit, flag, value ) ;if( __unit != NULL ) __unit->SetFlag( flag, value );

#define RemUnitFlag( __unit, flag )       ;if( __unit != NULL ) __unit->RemoveFlag( flag );

//////////////////////////////////////////////////////////////////////////////////////////
// Gets the name of a static unit.
#define GetStaticItemName( OBJECT_ID, VAR ) ;{ Objects *lpTHEObj = new Objects;\
    if( lpTHEObj->Create( U_OBJECT, OBJECT_ID ) ){\
        VAR = lpTHEObj->GetName( target->GetLang() );\
    }else{\
        VAR = "unknown unit "#OBJECT_ID;\
    } lpTHEObj->DeleteUnit();\
}

#define GetStaticMonsterName( MONSTER_ID, VAR ) ;{ Creatures *lpMob = new Creatures;\
    if( lpMob->Create( U_NPC, MONSTER_ID ) ){\
        VAR = lpMob->GetName( target->GetLang() );\
    }else{\
        VAR = "unknown unit "#MONSTER_ID;\
    } lpMob->DeleteUnit();\
}

//////////////////////////////////////////////////////////////////////////////////////////
// Used to create the value in a __FLAG_DEATH_LOCATION flag
// 12bits X position
// 12bits Y position
// 8 bits  world position.
#define SetDeathLocation( X, Y, WORLD )	 ;target->SetFlag\
 (\
 __FLAG_DEATH_LOCATION, \
 ( ( (DWORD)( (WORD)X ) << 20 ) + ( (DWORD)( (WORD)Y ) << 8 ) + (DWORD)( (BYTE)WORLD ) )\
 )


//////////////////////////////////////////////////////////////////////////////////////////
// NPC flag checking
#define CheckNPCFlag( flag )			self->ViewFlag( flag )

//////////////////////////////////////////////////////////////////////////////////////////
// Give npc flag.
#define GiveNPCFlag( flag, value )		;self->SetFlag( flag, value )

//////////////////////////////////////////////////////////////////////////////////////////
// Remove npc flag.
#define RemNPCFlag( flag )				;self->RemoveFlag( flag )

// Destroy the NPC
#define SELF_DESTRUCT   ;self->VaporizeUnit();

//////////////////////////////////////////////////////////////////////////////////////////
// Returns the current round
#define CurrentRound		TFCMAIN::GetRound()
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the current round
#define ACK_COLOSSEUM		TFCMAIN::GetColosseum()

//////////////////////////////////////////////////////////////////////////////////////////
// Returns the value of the Doppelganger. 
#define ACK_DOPPELGANGER		TFCMAIN::GetDoppelganger()

//////////////////////////////////////////////////////////////////////////////////////////
// Returns the value of the BattleMode. 
#define BATTLE_MODE			TFCMAIN::GetBattleMode()

//////////////////////////////////////////////////////////////////////////////////////////
// Returns the value of the BattleMode Config. 
#define XPTM1KILLTM2			TFCMAIN::GetXptm1killtm2()
#define GOLDTM1KILLTM2			TFCMAIN::GetGoldtm1killtm2()
#define	KARMATM1KILLTM2			TFCMAIN::GetKarmatm1killtm2()
#define XPTM2KILLTM1			TFCMAIN::GetXptm2killtm1()
#define GOLDTM2KILLTM1			TFCMAIN::GetGoldtm2killtm1()
#define KARMATM2KILLTM1			TFCMAIN::GetKarmatm2killtm1()
#define XPLOSTSAMETEAM			TFCMAIN::GetXplostsameteam()
#define GOLDLOSTSAMETEAM		TFCMAIN::GetGoldlostsameteam()
#define KARMAGAINTK				TFCMAIN::GetKarmagaintk()
#define KARMALOSTTK				TFCMAIN::GetKarmalosttk()

#define BONUSKILL1				TFCMAIN::GetBonuskill1()
#define BONUSKILL2				TFCMAIN::GetBonuskill2()
#define BONUSKILL3				TFCMAIN::GetBonuskill3()
#define XPBONUS1				TFCMAIN::GetXpbonus1()
#define XPBONUS2				TFCMAIN::GetXpbonus2()
#define XPBONUS3				TFCMAIN::GetXpbonus3()
#define GOLDBONUS1				TFCMAIN::GetGoldbonus1()
#define GOLDBONUS2				TFCMAIN::GetGoldbonus2()
#define GOLDBONUS3				TFCMAIN::GetGoldbonus3()

//////////////////////////////////////////////////////////////////////////////////////////
// Returns the value of the MaxRemorts. 
#define ACK_MAXREMORTS		TFCMAIN::GetMaxRemorts()

//////////////////////////////////////////////////////////////////////////////////////////
// Case switch encapsulation functions
#define SWITCH( __expression )			;switch( __expression ){

#define ENDSWITCH ;};

#define CASE( __num )		;case __num:
#define ENDCASE				;break;

#define OTHERWISE			;default:


void EXPORT __CastSpell( DWORD dwSpellID, Unit *caster, Unit *target );
#define CastSpellSelf( SPELLID )   ;__CastSpell( SPELLID, self, self );
#define CastSpellTarget( SPELLID ) ;__CastSpell( SPELLID, self, target );
#define CastSpellAny( SPELLID, theTarget ) ;__CastSpell( SPELLID, self, theTarget );

#define INIT_HANDLER   {;bool xSendBackpackUpdate = false;

#define CLOSE_HANDLER    }

/////////////////////////////////////////////////////////////////////////////////////
// Gives the item 'item' to the player talking to the NPC
BOOL EXPORT __GiveItem( Unit *self, Unit *target, WORD wItemID, BOOL boEcho = TRUE, bool boGiveAbsolute = true, bool boBackpackUpdate = true );
#define GiveItem(item)		 ;__GiveItem( self, target, item, false, true, false );xSendBackpackUpdate = true;

//////////////////////////////////////////////////////////////////////////////////////////
#define GiveItemNoEcho( item ) (xSendBackpackUpdate=true, __GiveItem( self, target, item, false, true, false ))

//#define GiveItemNoEchoNotAbsolute( item ) __GiveItem( self, target, item, false, false, true )

// Give item with no update, not absolute
#define GiveItemNoUpdateNotAbsolute( item ) (xSendBackpackUpdate=true,__GiveItem( self, target, item, false, false, false ))



/////////////////////////////////////////////////////////////////////////////////////
// CheckItem, this function returns TRUE if the item exists
int EXPORT __CheckItem(Unit *target, WORD item);
#define CheckItem( __item )	__CheckItem( target, __item )

////////////////////////////////////////////////////////////////////////////////////
// removes the item from a player's backpack
void EXPORT TakeItemFunc( UINT itemID, Unit *target );
#define TakeItem(item)	;TakeItemFunc( item, target ); xSendBackpackUpdate = true;

//////////////////////////////////////////////////////////////////////////////////////////
// Remove an item using its handle.
void EXPORT TakeItemHandleFunc( Unit *&handle, Unit *target );
#define TakeItemHandle( __handle ) ;TakeItemHandleFunc( __handle, target ); xSendBackpackUpdate = true;

//////////////////////////////////////////////////////////////////////////////////////////
// Returns an handle to the item of static reference __item.
LPVOID EXPORT __GetItemHandle( Unit *target, int nItem );
#define GetItemHandle( __item, __handle ) ;Unit *__handle = (Unit *)__GetItemHandle( target, __item )

#define IS_VALID( __pnt )   __pnt != NULL

///////////////////////////////////////////////////////////////////////////////////////
// Gives gold to the unit
void EXPORT GiveGoldFunc( int amount, Unit *target, bool echo );
#define GiveGold(amount)        ;GiveGoldFunc( amount, target, true ); xSendBackpackUpdate = true;
#define GiveGoldNoEcho(amount ) ;GiveGoldFunc( amount, target, false ); xSendBackpackUpdate = true;

//////////////////////////////////////////////////////////////////////////////////////
// Removes gold from the unit
void EXPORT TakeGoldFunc( int amount, Unit *target, bool echo );
#define TakeGold(amount)       ;TakeGoldFunc( amount, target, true ); xSendBackpackUpdate = true;
#define TakeGoldNoEcho(amount) ;TakeGoldFunc( amount, target, false ); xSendBackpackUpdate = true;

//////////////////////////////////////////////////////////////////////////////////////////
// Gives xp to the player.
void EXPORT GiveXPFunc( int amount, Unit *npc, Unit *target );
#define GiveXP( amount ) ;GiveXPFunc( amount, self, target );

//////////////////////////////////////////////////////////////////////////////////////////
#define XP_TO_LEVEL       target->XPtoLevel()

#define GiveKarma( amount ) ;target->SetKarma( target->GetKarma() + amount );


//////////////////////////////////////////////////////////////////////////////////////////
// Summons a monster
void EXPORT SummonFunc( LPCTSTR mobID, int absx, int absy, int world, Unit *npc, Unit *target );
#define SUMMON( __mob, absx, absy )  ;SummonFunc( __mob, absx, absy, self->GetWL().world, self, target );
#define SUMMON2( __mob, absx, absy, wl )  ;SummonFunc( __mob, absx, absy, wl, self, target );

#define FROM_NPC( ___pos, __c_axis ) (self->GetWL().##__c_axis + ___pos)
#define FROM_USER( ___pos, __c_axis ) (target->GetWL().##__c_axis + ___pos)


//////////////////////////////////////////////////////////////////////////////////////////
// Macros for bank transaction logging.
void EXPORT LogGoldWithdrawFunc( int currentGold, int goldWithdrew, LPCTSTR bankName, Character *lpChar );
#define LOG_GOLD_WITHDRAW( CurrentGold, GoldWidthdrew, BankName ) ;LogGoldWithdrawFunc( CurrentGold, GoldWidthdrew, BankName, lpChar );

//////////////////////////////////////////////////////////////////////////////////////////
// Log gold deposits.
void EXPORT LogGoldDepositFunc( int currentGold, int goldDeposited, LPCTSTR bankName, Character *lpChar );
#define LOG_GOLD_DEPOSIT( CurrentGold, GoldDeposited, BankName ) ;LogGoldDepositFunc( CurrentGold, GoldDeposited, BankName, lpChar );

//////////////////////////////////////////////////////////////////////////////////////////
// Updates the gold
#define UpdateGold		target->SetGold( target->GetGold() );

/////////////////////////////////////////////////////////////////////////////////////
// This functions returns the quantity of gold on the unit for boolean ops
#define Gold					target->GetGold()

////////////////////////////////////////////////////////////////////////////////////////
// Heal players of hitpnts
void EXPORT HealPlayerFunc( int hitPnts, Unit *target );
#define HealPlayer(hitpnts)	;HealPlayerFunc( hitpnts, target );

//////////////////////////////////////////////////////////////////////////////////////////
// Cures a players of desease, TODO
#define CurePlayer( deseaseflag )

//////////////////////////////////////////////////////////////////////////////////////////
// Blesses a player
#define BlessPlayer( something )

////////////////////////////////////////////////////////////////////////////////////////
// Puts a Yes/No condition 
#define SetYesNo(value)			; YesNo = value;

////////////////////////////////////////////////////////////////////////////////////////
// Command for "YES" using YesNo
#define YES(value)				;} else if( NPCKeyWord( msg, INTL( 4123," YES " ) ) && YesNo == value) { SetYesNo(0);

////////////////////////////////////////////////////////////////////////////////////////
// Command for "NO" using YesNo
#define NO(value)				;} else if( NPCKeyWord( msg, INTL( 7261, " NO " ) ) && YesNo == value) { SetYesNo(0);

/////////////////////////////////////////////////////////////////////////////////////////
// If another thing then Yes no No is said..
#define YesNoELSE(value)		;} else if(YesNo == value) { SetYesNo(0);

////////////////////////////////////////////////////////////////////////////////////////
// This macro SHOUTs something
void EXPORT ShoutFunc( LPCTSTR msg, Unit *npc, Unit *target );
#define SHOUT(msg) ;ShoutFunc( msg, self, target );


void EXPORT ChatterShoutFunc( LPCTSTR msg, Unit *npc, Unit *target );
#define CHATTER_SHOUT(msg) ;ChatterShoutFunc( msg, self, target );

void EXPORT NewChatterShoutFunc( string Channel, LPCTSTR msg, Unit *npc, Unit *target );
#define NEW_CHATTER_SHOUT(Channel, msg) ;NewChatterShoutFunc(Channel, msg, self, target);

void EXPORT SysMsgFunc( LPCTSTR msg, Unit *npc, Unit *target, bool privateMsg );
#define GLOBAL_SYSTEM_MESSAGE( msg ) ;SysMsgFunc( msg, self, target, false );

#define PRIVATE_SYSTEM_MESSAGE( msg ) ;SysMsgFunc( msg, self, target, true );


////////////////////////////////////////////////////////////////////////////////////////////
// Add a player to a clan
#define AddClan(clan)		;target->SetClan(clan);

////////////////////////////////////////////////////////////////////////////////////////////
// Creates a skill list to be later sent to the client
#define CreateSkillList		;{  BOOL boCantLearn = TRUE;\
								TemplateList <_SKILLITEM> tlSkillList;

//////////////////////////////////////////////////////////////////////////////////////////
// Fetches a user's skill points. 0 if the player hasn't learned the skill.
#define UserSkill( SKILL__ )   (target->GetSkill( SKILL__ ) == NULL ? 0 : target->GetSkill( SKILL__ )->GetSkillPnts( target ) )
#define TrueUserSkill( SKILL__ ) (target->GetSkill( SKILL__ ) == NULL ? 0 : target->GetSkill( SKILL__ )->GetTrueSkillPnts() )

    

#define USER_STR		target->GetSTR()
#define USER_END		target->GetEND()
#define USER_AGI		target->GetAGI()
#define USER_WIS		target->GetWIS()
#define USER_INT		target->GetINT()
#define USER_TRUE_STR		target->GetTrueSTR()
#define USER_TRUE_END		target->GetTrueEND()
#define USER_TRUE_AGI		target->GetTrueAGI()
#define USER_TRUE_WIS		target->GetTrueWIS()
#define USER_TRUE_INT		target->GetTrueINT()
#define USER_TRUE_ATTACK    target->GetTrueATTACK()
#define USER_TRUE_DODGE     target->GetTrueDODGE()
#define USER_LEVEL		target->GetLevel()
#define USER_HP         target->GetHP()
#define USER_MAXHP      target->GetMaxHP()
#define USER_TRUE_MAXHP target->GetTrueMaxHP()
#define USER_MANA       target->GetMana()
#define USER_MAX_MANA   target->GetMaxMana()
#define USER_TRUE_MAX_MANA target->GetTrueMaxMana()
#define USER_NAME       target->GetName(_DEFAULT_LNG)
#define USER_AIR_RESIST   target->GetAirResist()
#define USER_WATER_RESIST target->GetWaterResist()
#define USER_EARTH_RESIST target->GetEarthResist()
#define USER_FIRE_RESIST  target->GetFireResist()
#define USER_DARK_RESIST  target->GetDarkResist()
#define USER_LIGHT_RESIST target->GetLightResist()
#define USER_AIR_POWER    target->GetAirPower()
#define USER_WATER_POWER  target->GetWaterPower()
#define USER_EARTH_POWER  target->GetEarthPower()
#define USER_FIRE_POWER   target->GetFirePower()
#define USER_DARK_POWER   target->GetDarkPower()
#define USER_LIGHT_POWER  target->GetLightPower()

#define USER_TRUE_AIR_RESIST   target->GetTrueAirResist()
#define USER_TRUE_WATER_RESIST target->GetTrueWaterResist()
#define USER_TRUE_EARTH_RESIST target->GetTrueEarthResist()
#define USER_TRUE_FIRE_RESIST  target->GetTrueFireResist()
#define USER_TRUE_DARK_RESIST  target->GetTrueDarkResist()
#define USER_TRUE_LIGHT_RESIST target->GetTrueLightResist()
#define USER_TRUE_AIR_POWER    target->GetTrueAirPower()
#define USER_TRUE_WATER_POWER  target->GetTrueWaterPower()
#define USER_TRUE_EARTH_POWER  target->GetTrueEarthPower()
#define USER_TRUE_FIRE_POWER   target->GetTrueFirePower()
#define USER_TRUE_DARK_POWER   target->GetTrueDarkPower()
#define USER_TRUE_LIGHT_POWER  target->GetTrueLightPower()
#define USER_ATTACK       target->GetATTACK()
#define USER_DODGE        target->GetDODGE()
#define USER_GENDER       target->GetGender()
#define USER_XP           target->GetXP()
#define SET_INT( cnt )    ;target->SetINT( cnt );
#define SET_END( cnt )    ;target->SetEND( cnt );
#define SET_STR( cnt )    ;target->SetSTR( cnt );
#define SET_AGI( cnt )    ;target->SetAGI( cnt );
#define SET_WIL( cnt )    ;target->SetWIL( cnt );
#define SET_WIS( cnt )    ;target->SetWIS( cnt );
#define SET_LCK( cnt )    ;target->SetLCK( cnt );
#define SET_ATTACK( cnt ) ;target->SetATTACK( cnt );
#define SET_DODGE( cnt )  ;target->SetDODGE( cnt );

#define SET_APPEARANCE( cnt )	;target->SetAppearance( cnt );

#define SET_FIRE_RESIST( __cnt )  ;target->SetFireResist ( __cnt );
#define SET_WATER_RESIST( __cnt ) ;target->SetWaterResist( __cnt );
#define SET_EARTH_RESIST( __cnt ) ;target->SetEarthResist( __cnt );
#define SET_AIR_RESIST( __cnt )   ;target->SetAirResist  ( __cnt );
#define SET_DARK_RESIST( cnt )    ;target->SetDarkResist ( cnt );
#define SET_LIGHT_RESIST( cnt )   ;target->SetLightResist( cnt );
#define SET_FIRE_POWER( __cnt )   ;target->SetFirePower ( __cnt );
#define SET_WATER_POWER( __cnt )  ;target->SetWaterPower( __cnt );
#define SET_EARTH_POWER( __cnt )  ;target->SetEarthPower( __cnt );
#define SET_AIR_POWER( __cnt )    ;target->SetAirPower  ( __cnt );
#define SET_DARK_POWER( cnt )     ;target->SetDarkPower ( cnt );
#define SET_LIGHT_POWER( cnt )    ;target->SetLightPower( cnt );

#define NPC_STR		self->GetSTR()
#define NPC_END		self->GetEND()
#define NPC_AGI		self->GetAGI()
#define NPC_WIL		self->GetWIL()
#define NPC_WIS		self->GetWIS()
#define NPC_INT		self->GetINT()
#define NPC_LCK		self->GetLCK()
#define NPC_HP      self->GetHP()
#define NPC_MAXHP   self->GetMaxHP()
#define NPC_NAME    self->GetName(target->GetLang())
#define NPC_AIR_RESIST   self->GetAirResist()
#define NPC_WATER_RESIST self->GetWaterResist()
#define NPC_EARTH_RESIST self->GetEarthResist()
#define NPC_FIRE_RESIST  self->GetFireResist()
#define NPC_AIR_POWER    self->GetAirPower()
#define NPC_WATER_POWER  self->GetWaterPower()
#define NPC_EARTH_POWER  self->GetEarthPower()
#define NPC_FIRE_POWER   self->GetFirePower()

#define USER_KARMA  target->GetKarma()
#define NPC_KARMA   self->GetKarma()

#define SET_KARMA(__cnt)   self->SetKarma( __cnt );

/////////////////////////////////////////////////////////////////////////////////////////////
// Adds a skill to the skill list.
void EXPORT AddTeachSkillFunc( int skillID, DWORD skillCost, DWORD skillPnts, BOOL &boCantLearn, TemplateList< _SKILLITEM > &tlSkillList, Unit *target );
#define AddTeachSkill( THE_SKILL, __InitialStrength, __SkillCost ) ;AddTeachSkillFunc( THE_SKILL, __SkillCost, __InitialStrength, boCantLearn, tlSkillList, target );

//////////////////////////////////////////////////////////////////////////////////////////
// Add skill for a training list
void EXPORT AddTrainSkillFunc( int skillId, int maxPnts, DWORD skillCost, BOOL &boCantLearn, TemplateList< _SKILLITEM > &tlSkillList, Unit *target );
#define AddTrainSkill( THE_SKILL, __MaxPnts, __SkillCost ) ;AddTrainSkillFunc( THE_SKILL, __MaxPnts, __SkillCost, boCantLearn, tlSkillList, target );

//////////////////////////////////////////////////////////////////////////////////////////
// Send 'text' if PC can't have any of the skills
#define CantLearnSkill( text )				if( boCantLearn ){ output = text; }

///////////////////////////////////////////////////////////////////////////////////////////////
// Sends a skill list to the client
void EXPORT SendTrainSkillListFunc( BOOL boCantLearn, TemplateList< _SKILLITEM > &tlSkillList, Unit *target );
#define SendTrainSkillList	 ;SendTrainSkillListFunc( boCantLearn, tlSkillList, target ); };

//////////////////////////////////////////////////////////////////////////////////////////
// Sends a skill list to the client
void EXPORT SendTeachSkillListFunc( BOOL boCantLearn, TemplateList< _SKILLITEM > &tlSkillList, Unit *target );
#define SendTeachSkillList  ;SendTeachSkillListFunc( boCantLearn, tlSkillList, target ); };

/////////////////////////////////////////////////////////////////////////////////////////////
// Creates a list of objects.
#define CreateItemList			;{	TemplateList <_OBJECTITEM> tlItemList;

/////////////////////////////////////////////////////////////////////////////////////////////
// Adds an item to a buy list.
void EXPORT AddBuyItemFunc( DWORD price, DWORD id, TemplateList< _OBJECTITEM > &tlItemList, Character *lpChar );
#define AddBuyItem(PRICE, ID ) ;AddBuyItemFunc( PRICE, ID, tlItemList, lpChar );

//////////////////////////////////////////////////////////////////////////////////////////
// Adds an item to a sell list.
void EXPORT AddSellItemFunc( DWORD itemType, DWORD lowPriceRange, DWORD hiPriceRange, TemplateList< _OBJECTITEM > &tlItemList, Character *lpChar );
#define AddSellItem( ItemType, LowPriceRange, HiPriceRange ) ;AddSellItemFunc( ItemType, LowPriceRange, HiPriceRange, tlItemList, lpChar );

///////////////////////////////////////////////////////////////////////////////////////////////
// Sends a shop buying list to the client
void EXPORT SendBuyItemListFunc( TemplateList< _OBJECTITEM > &tlItemList, Unit *target );
#define SendBuyItemList	;SendBuyItemListFunc( tlItemList, target ); };

///////////////////////////////////////////////////////////////////////////////////////////////
// Sends a shop selling list to the client

void EXPORT SendSellItemListFunc( CString &output, LPCTSTR text, TemplateList< _OBJECTITEM > &tlItemList, Unit *target );
#define SendSellItemList( text ) ;SendSellItemListFunc( output, text, tlItemList, target ); };

/////////////////////////////////////////////////////////////////////////////////////////
// Returns TRUE if skill can be taugh
#define CanTeach(THE_SKILL)		{CString dummy;Skills::IsSkillLearnable(THE_SKILL, target, dummy);}


////////////////////////////////////////////////////////////////////////////////////////
// OnNPCDataExchange
////////////////////////////////////////////////////////////////////////////////////////
// Begins a OnNPCDataExchange message function
#define NPC_DATA_EXCHANGE	{LPNPC_DATA dataIN  = (LPNPC_DATA)valueIN;\
							LPNPC_DATA dataOUT = (LPNPC_DATA)valueOUT;\
                            bool xSendBackpackUpdate = false;\
							switch( dataIN->DataID ){
////////////////////////////////////////////////////////////////////////////////////////
// Ends an exchange module
#define CLOSE_NPC_DATA_EXCHANGE	;};}
							
//////////////////////////////////////////////////////////////////////////////////////////
// Handle a teaching block
#define NPC_DATA_TEACH		case __TEACH_DATA:{ BOOL SkillTaught = FALSE;\
								LPTEACH_DATA TeachData = (LPTEACH_DATA)dataIN->Data;\
								SKILL *lpSkill;
								

//////////////////////////////////////////////////////////////////////////////////////////
// Init a list of skills to be taught
#define NPC_TEACH_SKILL_LIST		switch( TeachData->wSkillID ){

//////////////////////////////////////////////////////////////////////////////////////////
#define CLOSE_NPC_TEACH_SKILL_LIST	};

/////////////////////////////////////////////////////////////////////////////////////////
// This function returns TRUE if skill has been taught
// __InitialStrength = Skill point deduction!
// __SkillCost       = Cost in gold $$$
BOOL EXPORT __TeachSkill(Unit *lpuWho, DWORD dwSkill, WORD wInitialStrength, DWORD dwGoldCost );
#define TEACH_SKILL( THE_SKILL, __InitialStrength, __SkillCost )  case THE_SKILL :\
	/* if its a skill */\
	if( THE_SKILL < SPELL_ID_OFFSET ){\
		lpSkill = Skills::GetSkill( THE_SKILL );\
		if( lpSkill ){\
            CString dummy;\
			if( Skills::IsSkillLearnable(THE_SKILL, target, dummy) ){\
				SkillTaught = __TeachSkill( target, THE_SKILL,__InitialStrength, __SkillCost ); \
			}\
		}\
	}else{ /* if its a spell */\
		LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpell( THE_SKILL );\
		if( lpSpell ){\
            CString dummy;\
			if( SpellMessageHandler::IsSpellLearnable( THE_SKILL, target, dummy ) ) {\
				SkillTaught = __TeachSkill( target, THE_SKILL, __InitialStrength, __SkillCost );\
			}\
		}\
	} break;

									


//////////////////////////////////////////////////////////////////////////////////////////
// Ends an NPC teach block
#define CLOSE_NPC_DATA_TEACH ;}break;

//////////////////////////////////////////////////////////////////////////////////////////
// Handle a teaching block
#define NPC_DATA_TRAIN		case __TRAIN_DATA:{ BOOL SkillTrained = FALSE;\
								LPTRAIN_DATA TrainData = (LPTRAIN_DATA)dataIN->Data;\
								switch( TrainData->wSkillID ){

/////////////////////////////////////////////////////////////////////////////////////////
// This function returns TRUE if skill has been taught
// __MAX  = Max skill points trainer can train.
// __COST = Gold$$ cost per skill point learned.
BOOL EXPORT __TrainSkill( Unit *lpuTarget, WORD wSkillID, WORD wTrainPnts, DWORD wCost, WORD wMax );
#define TRAIN_SKILL( THE_SKILL, _MAX, _COST )  case THE_SKILL :{\
										 SkillTrained = __TrainSkill(target, THE_SKILL, TrainData->wSkillPnts, _COST, _MAX );\
									} break;


//////////////////////////////////////////////////////////////////////////////////////////
// Ends an NPC teach block
#define CLOSE_NPC_DATA_TRAIN ;}}break;

	
////////////////////////////////////////////////////////////////////////////////////////
// Begins a shop block, to be used only in a OnNPCDataExchange function
// MoneyData = 0	Nothing happened
// MoneyData = 1	User bought an item
// MoneyData = 2	User didn't have the cash to buy an item
// MoneyData = 3	User sold an item
// MoneyData = 4    User refused to sell an item

bool EXPORT NPC_BUYFunc( Unit *npc, Unit *target, WORD ItemType, DWORD LowPriceRange, DWORD HiPriceRange, int &MoneyData, LPSHOP_DATA shop );

#define NPC_SHOP_DATA				case __SHOP_DATA:{\
									int MoneyData = 0;\
									LPSHOP_DATA shop = (LPSHOP_DATA)dataIN->Data;\
									if(0){

////////////////////////////////////////////////////////////////////////////////////////
// Ends a shop
#define CLOSE_NPC_SHOP_DATA			;}};

////////////////////////////////////////////////////////////////////////////////////////
// The 'Sell' portion of a shop (If user __BUYes, NPC sells!)
#define NPC_SELL(price, item)		;}else if(shop->Action == __BUY && shop->Item == item){\
										int _i = 0;\
										MoneyData = 2;\
										while( _i < shop->wQuantity && MoneyData != 4 ){\
											if(Gold >= price){ \
                                                if( MoneyData == 2 ){   MoneyData = 1;\
                                                }\
												TRACE( "\r\n\r\nBOUGHT ITEM %u at price %u", item, price );\
                                                if( !GiveItemNoUpdateNotAbsolute(item) ){\
                                                    MoneyData = 4;\
                                                }else{\
                                                    TakeGoldNoEcho(price)  \
                                                }\
											}\
											TRACE("*");\
                                            _i++;\
										};
									  


/////////////////////////////////////////////////////////////////////////////////////////
// The 'buy' portion of a shop (offer)
#define NPC_BUY( ItemType, LowPriceRange, HiPriceRange ) ;}{\
                                                              NPC_BUYFunc( self, target, ItemType, LowPriceRange, HiPriceRange, MoneyData, shop );



									
									

/////////////////////////////////////////////////////////////////////////////////////////
// Shouts 'msg' when an item was sold
#define NPC_SOLD_ITEM(msg)		;}if(MoneyData == 1){ SHOUT(msg);

/////////////////////////////////////////////////////////////////////////////////////////
// Shouts 'msg' when an item failed to be sold
#define NPC_FAILED_SELL(msg)	;}if(MoneyData == 2){ SHOUT(msg);

#define NPC_TOO_HEAVY           ;}if(MoneyData == 4){ SHOUT(msg);

////////////////////////////////////////////////////////////////////////////////////////
// Shouts 'msg' when an item was bought
#define NPC_BOUGHT_ITEM( msg )		;}if(MoneyData == 3){ SHOUT(msg);

#define USE_OBJECT( Name )	static const int __OBJ_##Name\
							= Unit::GetIDFromName( #Name\
							, U_OBJECT );



//////////////////////////////////////////////////////////////////////////////////////////
// Defining NPC and/or monster classes macro helpers.

//////////////////////////////////////////////////////////////////////////////////////////
// Defines an NPC structure
#define DEFINE_NPC( __name ) ;class _##__name\
    : public NPCstructure {\
    void Create( void );/* NPCs require a Create function to initialize their position and name */

//////////////////////////////////////////////////////////////////////////////////////////
// Defines a 'more complex' SimpleMonster structure.
#define DEFINE_MONSTER( __name ) ;class _##__name\
: public SimpleMonster {\
    public:
    

// Define definition of the different message handlers
#define USE_OnAttack            void OnAttack( UNIT_FUNC_PROTOTYPE );
#define USE_OnAttacked          void OnAttacked( UNIT_FUNC_PROTOTYPE );
#define USE_OnDeath             void OnDeath( UNIT_FUNC_PROTOTYPE );
#define USE_OnTalk              void OnTalk( UNIT_FUNC_PROTOTYPE );
#define USE_OnNPCDataExchange   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

// Defines the actual functions.
#define NPC_Create( __name )   void _##__name\
::Create( void ){


#define NPC_OnAttack( __name )  void _##__name\
::OnAttack( UNIT_FUNC_PROTOTYPE ){\
    NPCstructure::OnAttack( UNIT_FUNC_PARAM );

#define NPC_OnAttacked( __name )  void _##__name\
::OnAttacked( UNIT_FUNC_PROTOTYPE ){\
    NPCstructure::OnAttacked( UNIT_FUNC_PARAM );

#define NPC_OnDeath( __name )  void _##__name\
::OnDeath( UNIT_FUNC_PROTOTYPE ){\
    NPCstructure::OnDeath( UNIT_FUNC_PARAM );

#define NPC_OnTalk( __name )  void _##__name\
::OnTalk( UNIT_FUNC_PROTOTYPE ){\
    NPCstructure::OnTalk( UNIT_FUNC_PARAM );

#define NPC_OnNPCDataExchange( __name )  void _##__name\
::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )\
    {\
        LPNPC_DATA dataIN  = (LPNPC_DATA)valueIN;\
		PNPC_DATA dataOUT = (LPNPC_DATA)valueOUT;\
		switch( dataIN->DataID ){

#define MOB_OnAttack( __name )  void _##__name\
::OnAttack( UNIT_FUNC_PROTOTYPE ){\
    SimpleMonster::OnAttack( UNIT_FUNC_PARAM );

#define MOB_OnAttacked( __name )  void _##__name\
::OnAttacked( UNIT_FUNC_PROTOTYPE ){\
    SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );

#define MOB_OnDeath( __name )  void _##__name\
::OnDeath( UNIT_FUNC_PROTOTYPE ){\
    SimpleMonster::OnDeath( UNIT_FUNC_PARAM );

#define MOB_OnTalk( __name )  void _##__name\
::OnTalk( UNIT_FUNC_PROTOTYPE ){\
    SimpleMonster::OnTalk( UNIT_FUNC_PARAM );

//////////////////////////////////////////////////////////////////////////////////////////
// Set of functions which do not call the default message handler.
#define NPC_OnAttackOVR( __name )  void _##__name\
::OnAttack( UNIT_FUNC_PROTOTYPE ){    

#define NPC_OnAttackedOVR( __name )  void _##__name\
::OnAttacked( UNIT_FUNC_PROTOTYPE ){
    

#define NPC_OnDeathOVR( __name )  void _##__name\
::OnDeath( UNIT_FUNC_PROTOTYPE ){
    
#define NPC_OnTalkOVR( __name )  void _##__name\
::OnTalk( UNIT_FUNC_PROTOTYPE ){


#define END_BLOCK };


/*
// Undefine export.
#undef  EXPORT
#undef  IMPORT

// If export was set before this .h, restore it.
#ifdef  EXPORT_COPY
#define EXPORT EXPORT_COPY
#endif

#ifdef  IMPORT_COPY
#define IMPORT IMPORT_COPY
#endif
*/

#endif

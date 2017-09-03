// BoostFormula.cpp: implementation of the BoostFormula class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "BoostFormula.h"
#include "Unit.h"
#include <math.h>
#include "Random.h"
#include "IntlText.h"
#include "NPCmacroScriptLng.h"
#include "tfc_main.h"
# define TRACE printf

// Token values
#define OPER_ADD                1
#define OPER_SUB                2
#define OPER_MUL                3
#define OPER_DIV                4
#define OPER_POW                5
#define OPER_RND                6
#define OPER_EQUAL              7
#define OPER_DIFFERENT          8
#define OPER_GREATER            9
#define OPER_GREATER_EQUAL      10
#define OPER_LESSER             11
#define OPER_LESSER_EQUAL       12

#define TYPE_NUMBER             1
#define TYPE_SELF_INT           2
#define TYPE_SELF_STR           3       
#define TYPE_SELF_END           4
#define TYPE_SELF_WIS           6
#define TYPE_SELF_AGI           36
#define TYPE_SELF_HP            8
#define TYPE_SELF_MAXHP         9
#define TYPE_SELF_MANA          10
#define TYPE_SELF_MAXMANA       11
#define TYPE_SELF_ATTACK        12
#define TYPE_SELF_DODGE         13
#define TYPE_SELF_LEVEL         14
#define TYPE_TARGET_INT         22
#define TYPE_TARGET_STR         23
#define TYPE_TARGET_END         24
#define TYPE_TARGET_WIS         26
#define TYPE_TARGET_AGI         37
#define TYPE_TARGET_HP          28
#define TYPE_TARGET_MAXHP       29
#define TYPE_TARGET_MANA        30
#define TYPE_TARGET_MAXMANA     31
#define TYPE_TARGET_ATTACK      32
#define TYPE_TARGET_DODGE       33
#define TYPE_TARGET_LEVEL       34
#define TYPE_TARGET_ELEMENT     35
#define TYPE_X_ARGUMENT         38
#define TYPE_Y_ARGUMENT         39
#define TYPE_R_ARGUMENT         40
#define TYPE_SELF_AIR_RESIST    41
#define TYPE_SELF_FIRE_RESIST   42 
#define TYPE_SELF_WATER_RESIST  43  
#define TYPE_SELF_EARTH_RESIST  44  
#define TYPE_SELF_AIR_POWER     45
#define TYPE_SELF_FIRE_POWER    46
#define TYPE_SELF_WATER_POWER   47
#define TYPE_SELF_EARTH_POWER   48
#define TYPE_TARGET_AIR_RESIST    49
#define TYPE_TARGET_FIRE_RESIST   50 
#define TYPE_TARGET_WATER_RESIST  51  
#define TYPE_TARGET_EARTH_RESIST  52  
#define TYPE_TARGET_AIR_POWER     53
#define TYPE_TARGET_FIRE_POWER    54
#define TYPE_TARGET_WATER_POWER   55
#define TYPE_TARGET_EARTH_POWER   56
#define TYPE_SELF_LIGHT_RESIST    57
#define TYPE_SELF_DARK_RESIST     58
#define TYPE_SELF_LIGHT_POWER     59
#define TYPE_SELF_DARK_POWER      60
#define TYPE_TARGET_LIGHT_RESIST  61
#define TYPE_TARGET_DARK_RESIST   62
#define TYPE_TARGET_LIGHT_POWER   63
#define TYPE_TARGET_DARK_POWER    64
#define TYPE_SELF_TRUE_INT        65
#define TYPE_SELF_TRUE_STR        66       
#define TYPE_SELF_TRUE_END        67
#define TYPE_SELF_TRUE_WIS        69
#define TYPE_SELF_TRUE_AGI        70
#define TYPE_SELF_TRUE_ATTACK     72
#define TYPE_SELF_TRUE_DODGE      73
#define TYPE_SELF_TRUE_AIR_RESIST       74
#define TYPE_SELF_TRUE_FIRE_RESIST      75
#define TYPE_SELF_TRUE_WATER_RESIST     76
#define TYPE_SELF_TRUE_EARTH_RESIST     77
#define TYPE_SELF_TRUE_DARK_RESIST      78
#define TYPE_SELF_TRUE_LIGHT_RESIST     79
#define TYPE_SELF_TRUE_AIR_POWER        80
#define TYPE_SELF_TRUE_FIRE_POWER       81
#define TYPE_SELF_TRUE_WATER_POWER      82
#define TYPE_SELF_TRUE_EARTH_POWER      83
#define TYPE_SELF_TRUE_DARK_POWER       84
#define TYPE_SELF_TRUE_LIGHT_POWER      85
#define TYPE_TARGET_TRUE_INT            86
#define TYPE_TARGET_TRUE_STR            87
#define TYPE_TARGET_TRUE_END            88
#define TYPE_TARGET_TRUE_WIS            90
#define TYPE_TARGET_TRUE_AGI            91
#define TYPE_TARGET_TRUE_ATTACK         93
#define TYPE_TARGET_TRUE_DODGE          94
#define TYPE_TARGET_TRUE_AIR_RESIST     95
#define TYPE_TARGET_TRUE_FIRE_RESIST    96
#define TYPE_TARGET_TRUE_WATER_RESIST   97
#define TYPE_TARGET_TRUE_EARTH_RESIST   98
#define TYPE_TARGET_TRUE_DARK_RESIST    99
#define TYPE_TARGET_TRUE_LIGHT_RESIST   100
#define TYPE_TARGET_TRUE_AIR_POWER      101
#define TYPE_TARGET_TRUE_FIRE_POWER     102
#define TYPE_TARGET_TRUE_WATER_POWER    103
#define TYPE_TARGET_TRUE_EARTH_POWER    104
#define TYPE_TARGET_TRUE_DARK_POWER     105
#define TYPE_TARGET_TRUE_LIGHT_POWER    106
#define TYPE_SELF_AC                    107
#define TYPE_TARGET_AC                  108
#define TYPE_TARGET_TYPE                109
#define TYPE_RANGE                      110
#define TYPE_INFINITE                   111
#define TYPE_SELF_GOLD                  112
#define TYPE_TARGET_GOLD                113
#define TYPE_TARGET_KARMA				114
#define TYPE_SELF_KARMA					115
#define TYPE_TIMESTAMP					116
#define TYPE_GLOBAL_HOUR				117
#define TYPE_GLOBAL_MINUTE				118
#define TYPE_GLOBAL_SECOND				119
#define TYPE_SELF_WEIGHT				120
#define TYPE_SELF_MAXWEIGHT				121
#define TYPE_TARGET_WEIGHT				122
#define TYPE_TARGET_MAXWEIGHT			123
#define TYPE_ISBLOCKING					124
#define TYPE_SELF_POSX					125
#define TYPE_SELF_POSY					126
#define TYPE_SELF_POSW					127
#define TYPE_TARGET_POSX				128
#define TYPE_TARGET_POSY				129
#define TYPE_TARGET_POSW				130
#define TYPE_SELF_GENDER				131
#define TYPE_TARGET_GENDER				132
#define TYPE_SELF_TRUE_MAXHP			133
#define TYPE_TARGET_TRUE_MAXHP			134
#define TYPE_SELF_APPEARANCE			135
#define TYPE_TARGET_APPEARANCE			136
#define TYPE_SELF_TRUE_MAXMANA			137
#define TYPE_TARGET_TRUE_MAXMANA		138
#define TYPE_TARGET_CRIME 				139
#define TYPE_TARGET_HONOR 		   		140
#define TYPE_SELF_CRIME					141
#define TYPE_SELF_HONOR   		   		142
#define TYPE_SELF_TYPE					143
#define TYPE_TARGET_XP					144
#define TYPE_SELF_XP					145
#define TYPE_SELF_LUCK					146
#define	TYPE_TARGET_LUCK				147
#define TYPE_SELF_TRUE_LUCK				148
#define	TYPE_TARGET_TRUE_LUCK			149

#define FUNC_LOG                1
#define FUNC_IF                 2
#define FUNC_SELF_SKILL         3
#define FUNC_SELF_VIEW_FLAG     4
#define FUNC_TARGET_VIEW_FLAG   5
#define FUNC_ITEM_COUNT         6
#define FUNC_EQUIPPED           7
#define FUNC_TARGET_SKILL       8
#define FUNC_TARGET_TRUE_SKILL  9
#define FUNC_SELF_TRUE_SKILL    10
#define FUNC_VAR                11
#define FUNC_TARGET_ITEM_COUNT  12
#define FUNC_TARGET_EQUIPPED    13
#define FUNC_GLOBAL_VIEW_FLAG   14

#define IF_GREATER              1
#define IF_LESSER               2
#define IF_EQUAL                3
#define IF_GREATER_EQUAL        4
#define IF_LESSER_EQUAL         5
#define IF_NOT_EQUAL            6

extern Random rnd;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////
BoostFormula::BoostFormula()
{    
    // Create the first operand.
    memset( &opFirstOperand, 0, sizeof( OPERAND ) );
    opFirstOperand.bValueType = TYPE_NUMBER;
    csOriginalFormula = "0";
}

BoostFormula::~BoostFormula()
{
    // Destroy all operand objects.
    tlOperands.AnnihilateList();
}

//////////////////////////////////////////////////////////////////////////////////////////
inline int RangeToTarget
// Returns the distance between 2 points in the world.
//
(
 WorldPos from, // From pos
 WorldPos to    // To pos
)
// Return: int, the distance between from & to.
//////////////////////////////////////////////////////////////////////////////////////////
{
	return (sqrt((double)(( from.X - to.X ) * ( from.X - to.X ) + ( from.Y - to.Y ) * ( from.Y - to.Y )))); // steph ajout de (double)
}

inline BOOL IsBlockingBoost( Unit *self, Unit *target )
{
	if( (self != NULL) && (target != NULL))
	{
		WorldPos tempPos;
		WorldMap *wlWorld = TFCMAIN::GetWorld( self->GetWL().world );
		Unit *lpCollisionUnit = NULL;

		if (wlWorld->GetCollisionPos( self->GetWL(), target->GetWL(), &tempPos, &lpCollisionUnit, false, false )) {
			return TRUE;
		}

		return FALSE;
	} else {
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL BoostFormula::SetFormula
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the formula to use.
// 
(
 CString csFormula // The formula
)
// Return: BOOL, TRUE if the formula was compiled properly.
//////////////////////////////////////////////////////////////////////////////////////////
{
    BOOL boReturn = TRUE;
    // If formula isn't empty.
	
    if( !csFormula.IsEmpty() ){
        // Nb Tokens = NbParenthesis + NbOperators + 1
        int nStrLen = csFormula.GetLength();    
        int i, j;    
    
        char *lpszStringFormula = csFormula.GetBuffer( 0 );

        //////////////////////////////////////////////////////////////////////////////////////////    
        // Apply pre-processor.
    
        // Change 'd' for operator @
        for( i = 1; i < nStrLen; i++ ){
            if( lpszStringFormula[ i ] == 'd' || lpszStringFormula[ i ] == 'D' ){
                // If this is a single 'd', apply patch to point to operator @
                if( (isdigit( lpszStringFormula[ i + 1 ] ) || 
                    lpszStringFormula[ i + 1 ] == ' ' ||
                    lpszStringFormula[ i + 1 ] == '(')
                    &&
                    (isdigit( lpszStringFormula[ i - 1 ] ) || 
                    lpszStringFormula[ i - 1 ] == ' ' ||
                    lpszStringFormula[ i - 1 ] == ')')
                ){
                    lpszStringFormula[ i ] = '@';
                }
            }
        }
        j = 0;
        // Remove white spaces.
        for( i = 0; i < nStrLen; i++ ){
            if( lpszStringFormula[ i ] == ' ' ){
                j++;
            }
        }
        // Create a new buffer for spaceless formula
        char *lpszFormula = new char [ nStrLen + 1 - j ];
        // Copy white-spaceless string
        j = 0;
        for( i = 0; i < nStrLen; i++ ){
            if( lpszStringFormula[ i ] != ' ' ){
                lpszFormula[ j++ ] = lpszStringFormula[ i ];
            }
        }    
        lpszFormula[ j ] = 0;
        nStrLen = j;

        // Copy formula for storing.
        csOriginalFormula = lpszFormula;
    
        // release the string buffer.
        csFormula.ReleaseBuffer();
    
        TRACE( "\r\n--Formula before parsing: \"%s\"", lpszFormula );
    
        // Reset the first operand.        
        memset( &opFirstOperand, 0, sizeof( OPERAND ) );
        opFirstOperand.bValueType = TYPE_NUMBER;
    
        // Destroy any previous operands if formula is to be reset.
        tlOperands.AnnihilateList();
    
        if( !ParseFormula( lpszFormula, &opFirstOperand ) ){
            boReturn = FALSE;

            // Destroy all operands and set an empty first operand which will always return 0.
            tlOperands.AnnihilateList();

            // Reset first operand.
            memset( &opFirstOperand, 0, sizeof( OPERAND ) );
            opFirstOperand.bValueType = TYPE_NUMBER;
            
            csOriginalFormula = "0";
        }
        // Delete formula
        delete lpszFormula;
    }else{
        tlOperands.AnnihilateList();

        // Reset the first operand.
        memset( &opFirstOperand, 0, sizeof( OPERAND ) );
        opFirstOperand.bValueType = TYPE_NUMBER;        
    }
    
    // Parse whole formula
    return boReturn;
}

int nTab = 0;

#define GOTAB   {int z; TRACE( "\r\n" ); for( z = 0; z < nTab; z++ ) TRACE( "\t" );};

//////////////////////////////////////////////////////////////////////////////////////////
double BoostFormula::GetOperandValue
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the value of a token. Recursive
// 
(
 LPOPERAND lpOperand,   // The token to fetch the value from. 
 LPVOID lpself,            // For self.* functions.
 LPVOID lptarget,          // For target.* functions.
 double dblX,           // X argument.
 double dblY,           // Y argument.
 double dblR,            // R argument.
 VarMap *varMap,
 int method				// Compute the normal, min or max value
)
// Return: double, the token's value.
//////////////////////////////////////////////////////////////////////////////////////////
{
    Unit *self = (Unit *)lpself;
    Unit *target = (Unit *)lptarget;

    double dblFinalValue = 0;

    // If an operator was defined.
    if( lpOperand->bOperator != 0 ){
        // Make sure operands are ok.
        if( lpOperand->lpLeftOperand != NULL && lpOperand->lpRightOperand != NULL ){
            // Get right and left arguments.
            double dblLeftValue  = GetOperandValue( lpOperand->lpLeftOperand,  self, target, dblX, dblY, dblR, varMap, method );
            double dblRightValue = GetOperandValue( lpOperand->lpRightOperand, self, target, dblX, dblY, dblR, varMap, method );

            // Do operation.
            switch( lpOperand->bOperator ){
            case OPER_ADD:
                dblFinalValue = dblLeftValue + dblRightValue;                
                break;
            case OPER_SUB:
                dblFinalValue = dblLeftValue - dblRightValue;                
                break;
            case OPER_MUL:
                dblFinalValue = dblLeftValue * dblRightValue;                
                break;
            case OPER_DIV:
                // If this would make a division by 0.
                if( dblRightValue == 0 ){
                    // Log a critical error.
                    _LOG_DEBUG
                        LOG_CRIT_ERRORS,
                        "DIVISION BY ZERO: In boost formula %s.",
                        (LPCTSTR)csOriginalFormula
                    LOG_
                    if( self != NULL ){
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "DEV0: self name=%s.",
                            self->GetName(_DEFAULT_LNG).c_str()
                        LOG_
                    }
                    if( target != NULL ){
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "DEV0: target name=%s.",
                            target->GetName(_DEFAULT_LNG).c_str()
                        LOG_
                    }
                }else{
                    dblFinalValue = dblLeftValue / dblRightValue;                
                }
                break;
            case OPER_POW:
                dblFinalValue = pow( dblLeftValue, dblRightValue );                
                break;
            case OPER_RND:
				if (method == COMPUTE_NORMAL)
				{
					dblFinalValue = rnd( dice( static_cast< int >( dblLeftValue ), static_cast< int >( dblRightValue ) ) );
					TRACE( "\r\n--rnd( %u, %u ) = %f", (WORD)dblLeftValue, (WORD)dblRightValue, dblFinalValue );
				}
				else if (method == COMPUTE_MIN)
				{
					// Since we are casting 'dblLeftValue' dices with value 1, this is the min value to return
					dblFinalValue = dblLeftValue;
				}
				else
				{
					// Since we are cast 'dblLeftValue' dices of 'dblRightValue' faces
					// the result of the max dice rolling is 
					dblFinalValue = dblLeftValue * dblRightValue;
				}
                break;
            case OPER_EQUAL:
                dblFinalValue = dblLeftValue == dblRightValue;
                break;
            case OPER_DIFFERENT:
                dblFinalValue = dblLeftValue != dblRightValue;
                break;
            case OPER_GREATER:
                dblFinalValue = dblLeftValue > dblRightValue;
                break;
            case OPER_GREATER_EQUAL:
                dblFinalValue = dblLeftValue >= dblRightValue;
                break;
            case OPER_LESSER:
                dblFinalValue = dblLeftValue < dblRightValue;
                break;
            case OPER_LESSER_EQUAL:
                dblFinalValue = dblLeftValue <= dblRightValue;
                break;
            }
        }
    }else
    // Otherwise if this operand evaluates to a function.
    if( lpOperand->bFunction != 0 ){
        switch( lpOperand->bFunction ){
        //////////////////////////////////////////////////////////////////////////////////////////        
        // IF block
        case FUNC_IF:{
            // Get right and left arguments.
            double dblLeftValue  = GetOperandValue( lpOperand->lpLeftOperand,  self, target, dblX, dblY, dblR, varMap, method );
            double dblRightValue = GetOperandValue( lpOperand->lpRightOperand, self, target, dblX, dblY, dblR, varMap, method );
            BOOL boResult = FALSE;

            // Get comparison.
            switch( (int)lpOperand->dblValue ){
            case IF_EQUAL:
                TRACE( "\r\nEvaluating %f = %f", dblLeftValue, dblRightValue );
                if( dblLeftValue == dblRightValue ){
                    boResult = TRUE;
                }
            break;
            case IF_GREATER:
                TRACE( "\r\nEvaluating %f > %f", dblLeftValue, dblRightValue );
                if( dblLeftValue > dblRightValue ){
                    boResult = TRUE;
                }
            break;
            case IF_LESSER:
                TRACE( "\r\nEvaluating %f < %f", dblLeftValue, dblRightValue );
                if( dblLeftValue < dblRightValue ){
                    boResult = TRUE;
                }
            break;
            case IF_GREATER_EQUAL:
                TRACE( "\r\nEvaluating %f >= %f", dblLeftValue, dblRightValue );
                if( dblLeftValue >= dblRightValue ){
                    boResult = TRUE;
                }
            break;
            case IF_LESSER_EQUAL:
                TRACE( "\r\nEvaluating %f <= %f", dblLeftValue, dblRightValue );
                if( dblLeftValue <= dblRightValue ){
                    boResult = TRUE;
                }
            break;
            case IF_NOT_EQUAL:
                TRACE( "\r\nEvaluating %f <> %f", dblLeftValue, dblRightValue );
                if( dblLeftValue != dblRightValue ){
                    boResult = TRUE;
                }
            };
            
            // If result was TRUE.
            if( boResult ){                
                // Fetch TRUE value.
                dblFinalValue = GetOperandValue( &( lpOperand->lpFunctionParameters[ 1 ] ), self, target, dblX, dblY, dblR, varMap, method );
                TRACE( " TRUE, returning %f.", dblFinalValue );
            }
            // If result was FALSE.
            else{
                // Fetch FALSE value
                dblFinalValue = GetOperandValue( &( lpOperand->lpFunctionParameters[ 0 ] ), self, target, dblX, dblY, dblR, varMap, method );
                TRACE( " FALSE, returning %f.", dblFinalValue );
            }
        } break;
        ////////////////////////////////
        case FUNC_SELF_SKILL:{
            DWORD skillId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );

            LPUSER_SKILL userSkill = self->GetSkill( skillId );
            if( userSkill != NULL ){
                dblFinalValue = userSkill->GetSkillPnts( self );
            }else{
                dblFinalValue = 0;
            }
        }break;
        //////////////////////////////
        case FUNC_TARGET_SKILL:{
            if( target != NULL ){
                DWORD skillId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );

                LPUSER_SKILL userSkill = target->GetSkill( skillId );
                if( userSkill != NULL ){
                    dblFinalValue = userSkill->GetSkillPnts( self );
                }else{
                    dblFinalValue = 0;
                }
            }else{
                dblFinalValue = 0;
            }
        }break;
        //////////////////////////////
        case FUNC_SELF_TRUE_SKILL:{
            if( self != NULL ){
                DWORD skillId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );

                LPUSER_SKILL userSkill = self->GetSkill( skillId );
                if( userSkill != NULL ){
                    dblFinalValue = userSkill->GetTrueSkillPnts();
                }else{
                    dblFinalValue = 0;
                }
            }else{
                dblFinalValue = 0;
            }
        }break;

        //////////////////////////////
        case FUNC_TARGET_TRUE_SKILL:{
            if( target != NULL ){
                DWORD skillId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );

                LPUSER_SKILL userSkill = target->GetSkill( skillId );
                if( userSkill != NULL ){
                    dblFinalValue = userSkill->GetTrueSkillPnts();
                }else{
                    dblFinalValue = 0;
                }
            }else{
                dblFinalValue = 0;
            }
        }break;
        //////////////////////////////
        case FUNC_SELF_VIEW_FLAG:{
            DWORD flagId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );
            
            dblFinalValue = self->ViewFlag( flagId );
        } break;
        ////////////////////////////////
        case FUNC_TARGET_VIEW_FLAG:{
            if( target != NULL ){
                DWORD flagId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );
                
                dblFinalValue = target->ViewFlag( flagId );
            }else{
                dblFinalValue = 0;
            }
        } break;
        ////////////////////////////////
        case FUNC_ITEM_COUNT:{
            DWORD itemId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );
            dblFinalValue = __CheckItem( self, itemId );
        } break;
        ////////////////////////////////
        case FUNC_TARGET_ITEM_COUNT:{
            if( target != NULL ){
				DWORD itemId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );
                
                dblFinalValue = __CheckItem( target, itemId );
            }else{
                dblFinalValue = 0;
            }
        } break;
        ////////////////////////////////
        case FUNC_EQUIPPED:{
            if( self->GetType() == U_PC ){
                DWORD itemId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );
                dblFinalValue = static_cast< Character * >( self )->EquipCount( itemId );
            }else{
                dblFinalValue = 0;
            }
        } break;
        ////////////////////////////////
        case FUNC_TARGET_EQUIPPED:{
            if( target != NULL && target->GetType() == U_PC){
				DWORD itemId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );
                dblFinalValue = static_cast< Character * >( target )->EquipCount( itemId );
            }else{
                dblFinalValue = 0;
            }
        } break;
        /////////////////////////////////
        case FUNC_VAR:{
            if( varMap != NULL ){
                // The left operand points to a char * in the case of var func.
                CString *varName = reinterpret_cast< CString * >( lpOperand->lpLeftOperand );
                dblFinalValue = (*varMap)[ string( *varName ) ];
            }else{
                dblFinalValue = 0;
            }
        } break;
		case FUNC_GLOBAL_VIEW_FLAG:{
            DWORD GlobalflagId = GetOperandValue( lpOperand->lpLeftOperand, self, target, dblX, dblY, dblR, varMap, method );
            
            dblFinalValue = CheckGlobalFlag( GlobalflagId );
        } break;

        }
    }
    // Otherwise operand is a value.
    else{
        switch( lpOperand->bValueType ){			
        case TYPE_NUMBER:           dblFinalValue = lpOperand->dblValue; break;            
        case TYPE_SELF_INT:         dblFinalValue = self != NULL ? self->GetINT() : 0; break;
        case TYPE_SELF_STR:         dblFinalValue = self != NULL ? self->GetSTR() : 0; break;
        case TYPE_SELF_END:         dblFinalValue = self != NULL ? self->GetEND() : 0; break;
        case TYPE_SELF_WIS:         dblFinalValue = self != NULL ? self->GetWIS() : 0; break;
        case TYPE_SELF_AGI:         dblFinalValue = self != NULL ? self->GetAGI() : 0; break;
        case TYPE_SELF_HP:          dblFinalValue = self != NULL ? self->GetHP() : 0; break;
        case TYPE_SELF_MAXHP:       dblFinalValue = self != NULL ? self->GetMaxHP() : 0; break;
        case TYPE_SELF_MANA:        dblFinalValue = self != NULL ? self->GetMana() : 0; break;
        case TYPE_SELF_MAXMANA:     dblFinalValue = self != NULL ? self->GetMaxMana() : 0; break;
        case TYPE_SELF_ATTACK:      dblFinalValue = self != NULL ? self->GetATTACK() : 0; break;
        case TYPE_SELF_DODGE:       dblFinalValue = self != NULL ? self->GetDODGE() : 0; break;
        case TYPE_SELF_LEVEL:       dblFinalValue = self != NULL ? self->GetLevel() : 0; break;        
        case TYPE_TARGET_INT:       dblFinalValue = target != NULL ? target->GetINT() : 0; break;
        case TYPE_TARGET_STR:       dblFinalValue = target != NULL ? target->GetSTR() : 0; break;
        case TYPE_TARGET_END:       dblFinalValue = target != NULL ? target->GetEND() : 0; break;
        case TYPE_TARGET_WIS:       dblFinalValue = target != NULL ? target->GetWIS() : 0; break;
        case TYPE_TARGET_AGI:       dblFinalValue = target != NULL ? target->GetAGI() : 0; break;
        case TYPE_TARGET_HP:        dblFinalValue = target != NULL ? target->GetHP() : 0; break;
        case TYPE_TARGET_MAXHP:     dblFinalValue = target != NULL ? target->GetMaxHP() : 0; break;
        case TYPE_TARGET_MANA:      dblFinalValue = target != NULL ? target->GetMana() : 0; break;
        case TYPE_TARGET_MAXMANA:   dblFinalValue = target != NULL ? target->GetMaxMana() : 0; break;
        case TYPE_TARGET_ATTACK:    dblFinalValue = target != NULL ? target->GetATTACK() : 0; break;
        case TYPE_TARGET_DODGE:     dblFinalValue = target != NULL ? target->GetDODGE() : 0; break;
        case TYPE_TARGET_LEVEL:     dblFinalValue = target != NULL ? target->GetLevel() : 0; break;
        case TYPE_X_ARGUMENT:       dblFinalValue = dblX; break;
        case TYPE_Y_ARGUMENT:       dblFinalValue = dblY; break;
        case TYPE_R_ARGUMENT:       dblFinalValue = dblR; break;
        case TYPE_TARGET_ELEMENT:   dblFinalValue = 0;
        case TYPE_SELF_AIR_RESIST:     dblFinalValue = self != NULL ? self->GetAirResist()       : 0; break;
        case TYPE_SELF_FIRE_RESIST:    dblFinalValue = self != NULL ? self->GetFireResist()      : 0; break;
        case TYPE_SELF_WATER_RESIST:   dblFinalValue = self != NULL ? self->GetWaterResist()     : 0; break;
        case TYPE_SELF_EARTH_RESIST:   dblFinalValue = self != NULL ? self->GetEarthResist()     : 0; break;
        case TYPE_SELF_AIR_POWER:      dblFinalValue = self != NULL ? self->GetAirPower()        : 0; break;
        case TYPE_SELF_FIRE_POWER:     dblFinalValue = self != NULL ? self->GetFirePower()       : 0; break;
        case TYPE_SELF_WATER_POWER:    dblFinalValue = self != NULL ? self->GetWaterPower()      : 0; break;
        case TYPE_SELF_EARTH_POWER:    dblFinalValue = self != NULL ? self->GetEarthPower()      : 0; break;
        case TYPE_TARGET_AIR_RESIST:   dblFinalValue = target != NULL ? target->GetAirResist()   : 0; break;
        case TYPE_TARGET_FIRE_RESIST:  dblFinalValue = target != NULL ? target->GetFireResist()  : 0; break;
        case TYPE_TARGET_WATER_RESIST: dblFinalValue = target != NULL ? target->GetWaterResist() : 0; break;
        case TYPE_TARGET_EARTH_RESIST: dblFinalValue = target != NULL ? target->GetEarthResist() : 0; break;
        case TYPE_TARGET_AIR_POWER:    dblFinalValue = target != NULL ? target->GetAirPower()    : 0; break;
        case TYPE_TARGET_FIRE_POWER:   dblFinalValue = target != NULL ? target->GetFirePower()   : 0; break;
        case TYPE_TARGET_WATER_POWER:  dblFinalValue = target != NULL ? target->GetWaterPower()  : 0; break;
        case TYPE_TARGET_EARTH_POWER:  dblFinalValue = target != NULL ? target->GetEarthPower()  : 0; break;
        case TYPE_SELF_LIGHT_RESIST:   dblFinalValue = self != NULL ? self->GetLightResist()     : 0; break;
        case TYPE_SELF_DARK_RESIST:    dblFinalValue = self != NULL ? self->GetDarkResist()      : 0; break;
        case TYPE_SELF_LIGHT_POWER:    dblFinalValue = self != NULL ? self->GetLightPower()      : 0; break;
        case TYPE_SELF_DARK_POWER:     dblFinalValue = self != NULL ? self->GetDarkPower()       : 0; break;
        case TYPE_TARGET_LIGHT_RESIST: dblFinalValue = target != NULL ? target->GetLightResist() : 0; break;
        case TYPE_TARGET_DARK_RESIST:  dblFinalValue = target != NULL ? target->GetDarkResist()  : 0; break;
        case TYPE_TARGET_LIGHT_POWER:  dblFinalValue = target != NULL ? target->GetLightPower()  : 0; break;
        case TYPE_TARGET_DARK_POWER:   dblFinalValue = target != NULL ? target->GetDarkPower()   : 0; break;
        case TYPE_SELF_TRUE_INT:       dblFinalValue = self != NULL ? self->GetTrueINT()         : 0; break;
        case TYPE_SELF_TRUE_STR:       dblFinalValue = self != NULL ? self->GetTrueSTR()         : 0; break;
        case TYPE_SELF_TRUE_END:       dblFinalValue = self != NULL ? self->GetTrueEND()         : 0; break;
        case TYPE_SELF_TRUE_WIS:       dblFinalValue = self != NULL ? self->GetTrueWIS()         : 0; break;
        case TYPE_SELF_TRUE_AGI:       dblFinalValue = self != NULL ? self->GetTrueAGI()         : 0; break;
        case TYPE_SELF_TRUE_ATTACK:    dblFinalValue = self != NULL ? self->GetTrueATTACK()      : 0; break;
        case TYPE_SELF_TRUE_DODGE:     dblFinalValue = self != NULL ? self->GetTrueDODGE()       : 0; break;
        case TYPE_SELF_TRUE_AIR_RESIST:     dblFinalValue = self != NULL ? self->GetTrueAirResist()   : 0; break;
        case TYPE_SELF_TRUE_FIRE_RESIST:    dblFinalValue = self != NULL ? self->GetTrueFireResist()  : 0; break;
        case TYPE_SELF_TRUE_WATER_RESIST:   dblFinalValue = self != NULL ? self->GetTrueWaterResist() : 0; break;
        case TYPE_SELF_TRUE_EARTH_RESIST:   dblFinalValue = self != NULL ? self->GetTrueEarthResist() : 0; break;
        case TYPE_SELF_TRUE_DARK_RESIST:    dblFinalValue = self != NULL ? self->GetTrueDarkResist()  : 0; break;
        case TYPE_SELF_TRUE_LIGHT_RESIST:   dblFinalValue = self != NULL ? self->GetTrueLightResist() : 0; break;
        case TYPE_SELF_TRUE_AIR_POWER:      dblFinalValue = self != NULL ? self->GetTrueAirPower()    : 0; break;   
        case TYPE_SELF_TRUE_FIRE_POWER:     dblFinalValue = self != NULL ? self->GetTrueFirePower()   : 0; break;
        case TYPE_SELF_TRUE_WATER_POWER:    dblFinalValue = self != NULL ? self->GetTrueWaterPower()  : 0; break;
        case TYPE_SELF_TRUE_EARTH_POWER:    dblFinalValue = self != NULL ? self->GetTrueEarthPower()  : 0; break;
        case TYPE_SELF_TRUE_DARK_POWER:     dblFinalValue = self != NULL ? self->GetTrueDarkPower()   : 0; break;
        case TYPE_SELF_TRUE_LIGHT_POWER:    dblFinalValue = self != NULL ? self->GetTrueLightPower()  : 0; break;
        case TYPE_TARGET_TRUE_INT:     dblFinalValue = target != NULL ? target->GetTrueINT()     : 0; break;
        case TYPE_TARGET_TRUE_STR:     dblFinalValue = target != NULL ? target->GetTrueSTR()     : 0; break;
        case TYPE_TARGET_TRUE_END:     dblFinalValue = target != NULL ? target->GetTrueEND()     : 0; break;
        case TYPE_TARGET_TRUE_WIS:     dblFinalValue = target != NULL ? target->GetTrueWIS()     : 0; break;
        case TYPE_TARGET_TRUE_AGI:     dblFinalValue = target != NULL ? target->GetTrueAGI()     : 0; break;
        case TYPE_TARGET_TRUE_ATTACK:  dblFinalValue = target != NULL ? target->GetTrueATTACK()  : 0; break;
        case TYPE_TARGET_TRUE_DODGE:   dblFinalValue = target != NULL ? target->GetTrueDODGE()   : 0; break;
        case TYPE_TARGET_TRUE_AIR_RESIST:   dblFinalValue = target != NULL ? target->GetTrueAirResist()   : 0; break;
        case TYPE_TARGET_TRUE_FIRE_RESIST:  dblFinalValue = target != NULL ? target->GetTrueFireResist()  : 0; break;
        case TYPE_TARGET_TRUE_WATER_RESIST: dblFinalValue = target != NULL ? target->GetTrueWaterResist() : 0; break;
        case TYPE_TARGET_TRUE_EARTH_RESIST: dblFinalValue = target != NULL ? target->GetTrueEarthResist() : 0; break;
        case TYPE_TARGET_TRUE_DARK_RESIST:  dblFinalValue = target != NULL ? target->GetTrueDarkResist()  : 0; break;
        case TYPE_TARGET_TRUE_LIGHT_RESIST: dblFinalValue = target != NULL ? target->GetTrueLightResist() : 0; break;
        case TYPE_TARGET_TRUE_AIR_POWER:    dblFinalValue = target != NULL ? target->GetTrueAirPower()    : 0; break;
        case TYPE_TARGET_TRUE_FIRE_POWER:   dblFinalValue = target != NULL ? target->GetTrueFirePower()   : 0; break;
        case TYPE_TARGET_TRUE_WATER_POWER:  dblFinalValue = target != NULL ? target->GetTrueWaterPower()  : 0; break;
        case TYPE_TARGET_TRUE_EARTH_POWER:  dblFinalValue = target != NULL ? target->GetTrueEarthPower()  : 0; break;
        case TYPE_TARGET_TRUE_DARK_POWER:   dblFinalValue = target != NULL ? target->GetTrueDarkPower()   : 0; break;
        case TYPE_TARGET_TRUE_LIGHT_POWER:  dblFinalValue = target != NULL ? target->GetTrueLightPower()  : 0; break;
        case TYPE_SELF_AC:              dblFinalValue = self != NULL ? self->GetAC() : 0; break;
        case TYPE_TARGET_AC:            dblFinalValue = target != NULL ? target->GetAC() : 0; break;
        case TYPE_TARGET_TYPE:          dblFinalValue = target != NULL ? target->GetType() : 0; break;
        case TYPE_INFINITE:             dblFinalValue = 1 * pow((double) 10, 308.f ); break; // steph ajout de (double)
        case TYPE_SELF_GOLD:            dblFinalValue = self != NULL ? self->GetGold() : 0; break;
        case TYPE_TARGET_GOLD:          dblFinalValue = target != NULL ? target->GetGold() : 0; break;
		case TYPE_TARGET_KARMA:			dblFinalValue = target != NULL ? target->GetKarma() : 0; break;
		case TYPE_SELF_KARMA:			dblFinalValue = self != NULL ? self->GetKarma() : 0; break;
		case TYPE_TIMESTAMP:			dblFinalValue = TFCMAIN::GetRound(); break;
		case TYPE_GLOBAL_HOUR:			dblFinalValue = TFCTime::Hour(); break;
		case TYPE_GLOBAL_MINUTE:		dblFinalValue = TFCTime::Minute(); break;
		case TYPE_GLOBAL_SECOND:		dblFinalValue = TFCTime::Second(); break;
		case TYPE_RANGE:				dblFinalValue = (self != NULL ? (target != NULL ? RangeToTarget(self->GetWL(), target->GetWL()) : 100) : 100); break;
		case TYPE_SELF_WEIGHT:			dblFinalValue = self != NULL ? self->GetWeight() : 0; break;
		case TYPE_SELF_MAXWEIGHT:		dblFinalValue = self != NULL ? self->GetMaxWeight() : 0; break;
		case TYPE_TARGET_WEIGHT:		dblFinalValue = target != NULL ? target->GetWeight() : 0; break;
		case TYPE_TARGET_MAXWEIGHT:		dblFinalValue = target != NULL ? target->GetMaxWeight() : 0; break;
		case TYPE_ISBLOCKING:			dblFinalValue = IsBlockingBoost(self, target); break;
		case TYPE_SELF_POSX:			dblFinalValue = self != NULL ? self->GetWL().X : 0; break;
		case TYPE_SELF_POSY:			dblFinalValue = self != NULL ? self->GetWL().Y : 0; break;
		case TYPE_SELF_POSW:			dblFinalValue = self != NULL ? self->GetWL().world : 0; break;
		case TYPE_TARGET_POSX:			dblFinalValue = target != NULL ? target->GetWL().X : 0; break;
		case TYPE_TARGET_POSY:			dblFinalValue = target != NULL ? target->GetWL().Y : 0; break;
		case TYPE_TARGET_POSW:			dblFinalValue = target != NULL ? target->GetWL().world : 0; break;
		case TYPE_SELF_GENDER:			dblFinalValue = self != NULL ? self->GetGender() : 0; break;
		case TYPE_TARGET_GENDER:		dblFinalValue = target != NULL ? target->GetGender() : 0; break;
        case TYPE_SELF_TRUE_MAXHP:		dblFinalValue = self != NULL ? self->GetTrueMaxHP() : 0; break;
        case TYPE_TARGET_TRUE_MAXHP:	dblFinalValue = target != NULL ? target->GetTrueMaxHP() : 0; break;
        case TYPE_SELF_APPEARANCE:		dblFinalValue = self != NULL ? self->GetAppearance() : 0; break;
        case TYPE_TARGET_APPEARANCE:	dblFinalValue = target != NULL ? target->GetAppearance() : 0; break;
        case TYPE_SELF_TRUE_MAXMANA:	dblFinalValue = self != NULL ? self->GetTrueMaxMana() : 0; break;
        case TYPE_TARGET_TRUE_MAXMANA:	dblFinalValue = target != NULL ? target->GetTrueMaxMana() : 0; break;
		case TYPE_SELF_TYPE:            dblFinalValue = self != NULL ? self->GetType() : 0; break;
        case TYPE_TARGET_XP:            dblFinalValue = target != NULL ? (double)target->GetXP() : 0; break;
        case TYPE_SELF_XP:              dblFinalValue = self != NULL ? (double)self->GetXP() : 0; break;
		case TYPE_SELF_LUCK:            dblFinalValue = self != NULL ? (double)self->GetLCK() : 0; break;
        case TYPE_TARGET_LUCK:          dblFinalValue = target != NULL ? (double)target->GetLCK() : 0; break;
		case TYPE_SELF_TRUE_LUCK:       dblFinalValue = self != NULL ? (double)self->GetTrueLCK() : 0; break;
        case TYPE_TARGET_TRUE_LUCK:     dblFinalValue = target != NULL ? (double)target->GetTrueLCK() : 0; break;

        default: dblFinalValue = 0;
        }
    }

    return dblFinalValue;
}

//////////////////////////////////////////////////////////////////////////////////////////
double BoostFormula::GetBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the boost according to the boost formula.
//
(
 LPVOID self,
 LPVOID target,
 double dblX,
 double dblY,
 double dblR,
 VarMap *varMap
)
// Return: double, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    Unit *lpuSelf = (Unit *)self;
    Unit *lpuTarget = (Unit *)target;

    return GetOperandValue( &opFirstOperand, lpuSelf, lpuTarget, dblX, dblY, dblR, varMap );
}

//////////////////////////////////////////////////////////////////////////////////////////
double BoostFormula::GetMinBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the boost according to the boost formula.
//
(
 LPVOID self,
 LPVOID target,
 double dblX,
 double dblY,
 double dblR,
 VarMap *varMap
)
// Return: double, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    Unit *lpuSelf = (Unit *)self;
    Unit *lpuTarget = (Unit *)target;

    return GetOperandValue( &opFirstOperand, lpuSelf, lpuTarget, dblX, dblY, dblR, varMap, COMPUTE_MIN );
}

//////////////////////////////////////////////////////////////////////////////////////////
double BoostFormula::GetMaxBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the boost according to the boost formula.
//
(
 LPVOID self,
 LPVOID target,
 double dblX,
 double dblY,
 double dblR,
 VarMap *varMap
)
// Return: double, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    Unit *lpuSelf = (Unit *)self;
    Unit *lpuTarget = (Unit *)target;

    return GetOperandValue( &opFirstOperand, lpuSelf, lpuTarget, dblX, dblY, dblR, varMap, COMPUTE_MAX );
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL BoostFormula::SkipToNextParenthesis
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 int &nCounter,         // Current byte counter.
 char *lpszString       // String.
)
// Return: BOOL, TRUE if no error occured.
//////////////////////////////////////////////////////////////////////////////////////////
{
    BOOL boReturn = TRUE;
    WORD wParenthesisCount = 0;
    int nInitialPos = nCounter;

    do{
        if( lpszString[ nCounter ] == '(' ){
            wParenthesisCount++;
        }else if( lpszString[ nCounter ] == ')' ){
            wParenthesisCount--;
        }else if( lpszString[ nCounter ] == 0 ){
            boReturn = FALSE;
        }
        nCounter++;
    }while( wParenthesisCount != 0 && boReturn );

    if( !boReturn ){        
        _LOG_DEBUG
            LOG_DEBUG_LVL2,
            "Formula error: Could not find matching parenthesis at position %u in this chunck: '%s'.",
            nInitialPos,
            lpszString
        LOG_
    }

    return boReturn;
}
//////////////////////////////////////////////////////////////////////////////////////////
BOOL BoostFormula::ParseFormula
//////////////////////////////////////////////////////////////////////////////////////////
// Finds the lowest priority operator and chuncks it into other strings.
// 
(
 char *lpszFormula,     // The current formula chunck.
 LPOPERAND lpOperand    // The operand object which will hold the information.
)
// Return: BOOL, TRUE if parsing didnt' find any error.
//////////////////////////////////////////////////////////////////////////////////////////
{   
    BOOL boError = FALSE;

    int nOperatorPos = -1;
    int nOperatorPosExtent = 0;
    int nLowestPriority = 256;
    BYTE bOperator = 0;
    int i;
    int nStrLen = strlen( lpszFormula );

    TRACE( "\r\nParsing string %s.", lpszFormula );

    // Strip all parenthesis blocks.
    BOOL boOK = TRUE;
    while( boOK && !boError ){
        // First, check if this is a parenthesis block.
        if( lpszFormula[ 0 ] == '(' ){
            //WORD wNbParenthesis = 0; // ?
            i = 0;

            if( !SkipToNextParenthesis( i, lpszFormula ) ){
                boError = TRUE;
            }

            // If matching is the the last one.
            if( i == nStrLen ){
                // This is a parenthesis block.
                // Strip first and last parenthesis.
                nStrLen--;
                lpszFormula[ nStrLen ] = 0;
                lpszFormula++;            
            }else{
                // This wasn't a parenthesis block, so stop removing them.
                boOK = FALSE;
            }
        }else{
            // This chunck didn't begin with a parenthesis.
            boOK = FALSE;
        }
    }


    // Find the lowest priority operator in this string.
    for( i = 0; i < nStrLen; i++ ){
        switch( lpszFormula[ i ] ){
        //////////////////////////////////////////////////////////////////////////////////////////
        case '-':
            if( 12 < nLowestPriority ){
                TRACE( "-- Found ( - )" );
                nOperatorPos = i;
                nLowestPriority = 12;
                bOperator = OPER_SUB;
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////        
        case '+':
            if( 11 < nLowestPriority ){
                TRACE( "-- Found ( + )" );
                nOperatorPos = i;
                nLowestPriority = 11;
                bOperator = OPER_ADD;
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////        
        case '/':
            if( 14 < nLowestPriority ){
                TRACE( "-- Found ( / )" );
                nOperatorPos = i;
                nLowestPriority = 13;
                bOperator = OPER_DIV;
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////        
        case '*':
            if( 13 < nLowestPriority ){
                TRACE( "-- Found ( * )" );
                nOperatorPos = i;
                nLowestPriority = 13;
                bOperator = OPER_MUL;
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////          
        case '^':
            if( 15 < nLowestPriority ){
                TRACE( "-- Found ( ^ )" );
                nOperatorPos = i;
                nLowestPriority = 14;
                bOperator = OPER_POW;
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////
        // For conditional boost formulas
        case '<':
            if( 5 < nLowestPriority ){
                nOperatorPos = i;
                if( lpszFormula[ i + 1 ] == '=' ){
                    bOperator = OPER_LESSER_EQUAL;                    
                    i++;
                    nOperatorPosExtent = 1;
                }else if( lpszFormula[ i + 1 ] == '>' ){
                    bOperator = OPER_DIFFERENT;
                    i++;
                    nOperatorPosExtent = 1;
                }else{
                    bOperator = OPER_LESSER;                    
                }                
                nLowestPriority = 5;
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////        
        case '>':
            if( 5 < nLowestPriority ){
                nOperatorPos = i;
                if( lpszFormula[ i + 1 ] == '=' ){
                    bOperator = OPER_GREATER_EQUAL;
                    i++;
                    nOperatorPosExtent = 1;
                }else{
                    bOperator = OPER_GREATER;
                }                
                nLowestPriority = 5;                
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////
        case '=':
            if( 5 < nLowestPriority ){
                nOperatorPos = i;                
                bOperator = OPER_EQUAL;
                nLowestPriority = 5;
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////        
        case '@':
            if( 16 < nLowestPriority ){
                TRACE( "-- Found ( @ )" );
                nOperatorPos = i;
                nLowestPriority = 15;
                bOperator = OPER_RND;
            }
            break;
        //////////////////////////////////////////////////////////////////////////////////////////        
        // If a parenthesis was found, skip to the next parenthesis block.
        case '(':{
            //WORD wNbParenthesis = 0; // ?
            
            if( !SkipToNextParenthesis( i, lpszFormula ) ){
                boError = TRUE;
            }
            i--;
        } break;
        }
    }

    // If a new operator was found
    if( nOperatorPos != -1 ){
        // First formula begins at this formula's beginning.
        char *lpcLeftFormula = lpszFormula;
        char *lpcRightFormula = lpszFormula + nOperatorPos + nOperatorPosExtent + 1;
        
        // Chop string in two.
        lpszFormula[ nOperatorPos ] = 0;

        LPOPERAND lpLeftOperand = new OPERAND;
        LPOPERAND lpRightOperand = new OPERAND;

        tlOperands.AddToTail( lpLeftOperand );
        tlOperands.AddToTail( lpRightOperand );

        // Reset the operand values.
        memset( lpLeftOperand, 0, sizeof( OPERAND ) );
        memset( lpRightOperand, 0, sizeof( OPERAND ) );

        // Set this operand's parameters
        TRACE( " -- Operator %u.", bOperator );
        lpOperand->bOperator = bOperator;
        lpOperand->dblValue = 0;
        lpOperand->lpLeftOperand = lpLeftOperand;
        lpOperand->lpRightOperand = lpRightOperand;

        // Parse the right operand
        if( !ParseFormula( lpcLeftFormula, lpLeftOperand ) ){            
            boError = TRUE;
        }else{
            if( !ParseFormula( lpcRightFormula, lpRightOperand ) ){
                boError = TRUE;
            }
        }
        
    }
    // If none was found, fetch this operand's value.
    else{
        // If its an empty parameter, assume number 0.
        if( lpszFormula[ 0 ] == 0 ){
            lpOperand->dblValue = 0;
            lpOperand->bValueType = TYPE_NUMBER;           
        }else 
        // If parameter is a number.
        if( isdigit( lpszFormula[ 0 ] ) ){
            lpOperand->dblValue = 0;
            i = 0;
            while( isdigit( lpszFormula[ i ] ) ){
                lpOperand->dblValue *= 10;
                lpOperand->dblValue += lpszFormula[ i ] - '0';
                i++;
            }
            // If this was a decimal separator.
            if( lpszFormula[ i ] == '.' ){
                i++;
                int nTenth = 1;
                while( isdigit( lpszFormula[ i ] ) ){
                    lpOperand->dblValue += ( ( lpszFormula[ i ] - '0' ) * pow((double) 10, -nTenth ) ); // steph ajout de (double)
                    i++;
                    nTenth++;
                }
            }

            lpOperand->bValueType = TYPE_NUMBER;
            TRACE( " -- Found value %f", lpOperand->dblValue );
        }else 
        // If parameter is a string.
        if( isalpha( lpszFormula[ 0 ] ) ){
            // Fetch the string
            CString csFunc;
            i = 0;
            do{
                csFunc += lpszFormula[ i ];
                i++;
            }while( isalpha( lpszFormula[ i ] ) || lpszFormula[ i ] == '.' || lpszFormula[ i ] == '_' );
            
            csFunc.MakeLower();

            //////////////////////////////////////////////////////////////////////////////////////////
            // Check for controls
			bool _keepChecking = false;

            if( csFunc ==       "self.int" ){
                lpOperand->bValueType = TYPE_SELF_INT;                
            }else if( csFunc == "self.str" ){
                lpOperand->bValueType = TYPE_SELF_STR;
            }else if( csFunc == "self.end" ){
                lpOperand->bValueType = TYPE_SELF_END;
            }else if( csFunc == "self.wis" ){
                lpOperand->bValueType = TYPE_SELF_WIS;
            }else if( csFunc == "self.agi" ){
                lpOperand->bValueType = TYPE_SELF_AGI;                
            }else if( csFunc == "self.hp" ){
                lpOperand->bValueType = TYPE_SELF_HP;
            }else if( csFunc == "self.maxhp" ){
                lpOperand->bValueType = TYPE_SELF_MAXHP;
            }else if( csFunc == "self.mana" ){
                lpOperand->bValueType = TYPE_SELF_MANA;
            }else if( csFunc == "self.maxmana" ){
                lpOperand->bValueType = TYPE_SELF_MAXMANA;
            }else if( csFunc == "self.attack" ){
                lpOperand->bValueType = TYPE_SELF_ATTACK;
            }else if( csFunc == "self.dodge" ){
                lpOperand->bValueType = TYPE_SELF_DODGE;
            }else if( csFunc == "self.level" ){
                lpOperand->bValueType = TYPE_SELF_LEVEL;
            }else
                  if( csFunc == "target.int" ){
                lpOperand->bValueType = TYPE_TARGET_INT;                
            }else if( csFunc == "target.str" ){
                lpOperand->bValueType = TYPE_TARGET_STR;
            }else if( csFunc == "target.end" ){
                lpOperand->bValueType = TYPE_TARGET_END;
            }else if( csFunc == "target.wis" ){
                lpOperand->bValueType = TYPE_TARGET_WIS;
            }else if( csFunc == "target.agi" ){
                lpOperand->bValueType = TYPE_TARGET_AGI;  
            }else if( csFunc == "target.hp" ){
                lpOperand->bValueType = TYPE_TARGET_HP;
            }else if( csFunc == "target.maxhp" ){
                lpOperand->bValueType = TYPE_TARGET_MAXHP;
            }else if( csFunc == "target.mana" ){
                lpOperand->bValueType = TYPE_TARGET_MANA;
            }else if( csFunc == "target.maxmana" ){
                lpOperand->bValueType = TYPE_TARGET_MAXMANA;
            }else if( csFunc == "target.attack" ){
                lpOperand->bValueType = TYPE_TARGET_ATTACK;
            }else if( csFunc == "target.dodge" ){
                lpOperand->bValueType = TYPE_TARGET_DODGE;
            }else if( csFunc == "target.element" ){                
                lpOperand->bValueType = TYPE_TARGET_ELEMENT;
            }else if( csFunc == "target.level" ){
                lpOperand->bValueType = TYPE_TARGET_LEVEL;
            }else if( csFunc == "x" || csFunc == "arrow_dmg" ){
                lpOperand->bValueType = TYPE_X_ARGUMENT;
            }else if( csFunc == "y" ){
                lpOperand->bValueType = TYPE_Y_ARGUMENT;
            }else if( csFunc == "r" ){
                lpOperand->bValueType = TYPE_R_ARGUMENT;
            }else if( csFunc == "self.r_air" ){
                lpOperand->bValueType = TYPE_SELF_AIR_RESIST;
            }else if( csFunc == "self.r_fire" ){
                lpOperand->bValueType = TYPE_SELF_FIRE_RESIST;
            }else if( csFunc == "self.r_water" ){
                lpOperand->bValueType = TYPE_SELF_WATER_RESIST;
            }else if( csFunc == "self.r_earth" ){
                lpOperand->bValueType = TYPE_SELF_EARTH_RESIST;
            }else if( csFunc == "self.air" ){
                lpOperand->bValueType = TYPE_SELF_AIR_POWER;
            }else if( csFunc == "self.fire" ){
                lpOperand->bValueType = TYPE_SELF_FIRE_POWER;
            }else if( csFunc == "self.water" ){
                lpOperand->bValueType = TYPE_SELF_WATER_POWER;
            }else if( csFunc == "self.earth" ){
                lpOperand->bValueType = TYPE_SELF_EARTH_POWER;
            }else if( csFunc == "target.r_air" ){
                lpOperand->bValueType = TYPE_TARGET_AIR_RESIST;
            }else if( csFunc == "target.r_fire" ){
                lpOperand->bValueType = TYPE_TARGET_FIRE_RESIST;
            }else if( csFunc == "target.r_water" ){
                lpOperand->bValueType = TYPE_TARGET_WATER_RESIST;
            }else if( csFunc == "target.r_earth" ){
                lpOperand->bValueType = TYPE_TARGET_EARTH_RESIST;
            }else if( csFunc == "target.air" ){
                lpOperand->bValueType = TYPE_TARGET_AIR_POWER;
            }else if( csFunc == "target.fire" ){
                lpOperand->bValueType = TYPE_TARGET_FIRE_POWER;
            }else if( csFunc == "target.water" ){
                lpOperand->bValueType = TYPE_TARGET_WATER_POWER;
            }else if( csFunc == "target.earth" ){
                lpOperand->bValueType = TYPE_TARGET_EARTH_POWER;
            }else if( csFunc == "self.r_light" ){
                lpOperand->bValueType = TYPE_SELF_LIGHT_RESIST;
            }else if( csFunc == "self.r_dark" ){
                lpOperand->bValueType = TYPE_SELF_DARK_RESIST;
            }else if( csFunc == "self.light" ){
                lpOperand->bValueType = TYPE_SELF_LIGHT_POWER;
            }else if( csFunc == "self.dark" ){
                lpOperand->bValueType = TYPE_SELF_DARK_POWER;
            }else if( csFunc == "target.r_light" ){
                lpOperand->bValueType = TYPE_TARGET_LIGHT_RESIST;
            }else if( csFunc == "target.r_dark" ){
                lpOperand->bValueType = TYPE_TARGET_DARK_RESIST;
            }else if( csFunc == "target.light" ){
                lpOperand->bValueType = TYPE_TARGET_LIGHT_POWER;
            }else if( csFunc == "target.dark" ){
                lpOperand->bValueType = TYPE_TARGET_DARK_POWER;
            }else if( csFunc == "self.true_int" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_INT;
            }else if( csFunc == "self.true_str" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_STR;
            }else if( csFunc == "self.true_end" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_END;
            }else if( csFunc == "self.true_wis" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_WIS;
            }else if( csFunc == "self.true_agi" ){            
                lpOperand->bValueType = TYPE_SELF_TRUE_AGI;
            }else if( csFunc == "self.true_attack" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_ATTACK;
            }else if( csFunc == "self.true_dodge" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_DODGE;
            }else if( csFunc == "self.true_r_air" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_AIR_RESIST;
            }else if( csFunc == "self.true_r_fire" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_FIRE_RESIST;
            }else if( csFunc == "self.true_r_water" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_WATER_RESIST;
            }else if( csFunc == "self.true_r_earth" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_EARTH_RESIST;
            }else if( csFunc == "self.true_r_dark" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_DARK_RESIST;
            }else if( csFunc == "self.true_r_light" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_LIGHT_RESIST;
            }else if( csFunc == "self.true_air" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_AIR_POWER;
            }else if( csFunc == "self.true_fire" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_FIRE_POWER;
            }else if( csFunc == "self.true_water" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_WATER_POWER;
            }else if( csFunc == "self.true_earth" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_EARTH_POWER;
            }else if( csFunc == "self.true_dark" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_DARK_POWER;
            }else if( csFunc == "self.true_light" ){
                lpOperand->bValueType = TYPE_SELF_TRUE_LIGHT_POWER;
            }else if( csFunc == "target.true_int" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_INT;
            }else if( csFunc == "target.true_str" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_STR;
            }else if( csFunc == "target.true_end" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_END;
            }else if( csFunc == "target.true_wis" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_WIS;
            }else if( csFunc == "target.true_agi" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_AGI;
            }else if( csFunc == "target.true_attack" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_ATTACK;
            }else if( csFunc == "target.true_dodge" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_DODGE;
            }else if( csFunc == "target.true_r_air" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_AIR_RESIST;
            }else if( csFunc == "target.true_r_fire" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_FIRE_RESIST;
            }else if( csFunc == "target.true_r_water" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_WATER_RESIST;
            }else if( csFunc == "target.true_r_earth" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_EARTH_RESIST;
            }else if( csFunc == "target.true_r_dark" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_DARK_RESIST;
            }else if( csFunc == "target.true_r_light" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_LIGHT_RESIST;
            }else if( csFunc == "target.true_air" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_AIR_POWER;
            }else if( csFunc == "target.true_fire" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_FIRE_POWER;
            }else if( csFunc == "target.true_water" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_WATER_POWER;
            }else if( csFunc == "target.true_earth" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_EARTH_POWER;
            }else if( csFunc == "target.true_dark" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_DARK_POWER;
            }else if( csFunc == "target.true_light" ){
                lpOperand->bValueType = TYPE_TARGET_TRUE_LIGHT_POWER;
            }else if( csFunc == "target.ac" ){
                lpOperand->bValueType = TYPE_TARGET_AC;
            }else if( csFunc == "self.ac" ){
                lpOperand->bValueType = TYPE_SELF_AC;
            }else if( csFunc == "target.type" ){
                lpOperand->bValueType = TYPE_TARGET_TYPE;
			}else if( csFunc == "target.xp" ){
                lpOperand->bValueType = TYPE_TARGET_XP;
            }else if( csFunc == "self.type" ){
                lpOperand->bValueType = TYPE_SELF_TYPE;
            }else if( csFunc == "self.xp" ){
                lpOperand->bValueType = TYPE_SELF_XP;
            }else if( csFunc == "self.gold" ){
                lpOperand->bValueType = TYPE_SELF_GOLD;
            }else if( csFunc == "target.gold" ){
                lpOperand->bValueType = TYPE_TARGET_GOLD;
            }else if( csFunc == "range" ){
                lpOperand->bValueType = TYPE_RANGE;                          
            }else if( csFunc == "infinite" ){
                lpOperand->bValueType = TYPE_INFINITE;     
			} else _keepChecking = true;

			if (!_keepChecking) {
			}else if ( csFunc == "target.karma" ){
                lpOperand->bValueType = TYPE_TARGET_KARMA;
			}else if ( csFunc == "self.karma" ){
                lpOperand->bValueType = TYPE_SELF_KARMA;
			}else if ( csFunc == "currenttime" ){
				lpOperand->bValueType = TYPE_TIMESTAMP;
			}else if ( csFunc == "target.range" ){
				lpOperand->bValueType = TYPE_RANGE;
			}else if ( csFunc == "global.hour" ){
				lpOperand->bValueType = TYPE_GLOBAL_HOUR;
			}else if ( csFunc == "global.minute" ){
				lpOperand->bValueType = TYPE_GLOBAL_MINUTE;
			}else if ( csFunc == "global.second" ){
				lpOperand->bValueType = TYPE_GLOBAL_SECOND;
			}else if( csFunc == "self.weight" ){
				lpOperand->bValueType = TYPE_SELF_WEIGHT;
			}else if( csFunc == "self.maxweight" ){
				lpOperand->bValueType = TYPE_SELF_MAXWEIGHT;
			}else if( csFunc == "target.weight" ){
				lpOperand->bValueType = TYPE_TARGET_WEIGHT;
			}else if( csFunc == "target.maxweight" ){
				lpOperand->bValueType = TYPE_TARGET_MAXWEIGHT;
			}else if( csFunc == "isblocking" ){
				lpOperand->bValueType = TYPE_ISBLOCKING;
			}else if( csFunc == "self.posx" ){
				lpOperand->bValueType = TYPE_SELF_POSX;
			}else if( csFunc == "self.posy" ){
				lpOperand->bValueType = TYPE_SELF_POSY;
			}else if( csFunc == "self.posw" ){
				lpOperand->bValueType = TYPE_SELF_POSW;
			}else if( csFunc == "target.posx" ){
				lpOperand->bValueType = TYPE_TARGET_POSX;
			}else if( csFunc == "target.posy" ){
				lpOperand->bValueType = TYPE_TARGET_POSY;
			}else if( csFunc == "target.posw" ){
				lpOperand->bValueType = TYPE_TARGET_POSW;
			}else if( csFunc == "self.gender" ){
				lpOperand->bValueType = TYPE_SELF_GENDER;
			}else if( csFunc == "target.gender" ){
				lpOperand->bValueType = TYPE_TARGET_GENDER;
			}else if( csFunc == "self.true_maxhp" ){
				lpOperand->bValueType = TYPE_SELF_TRUE_MAXHP;
			}else if( csFunc == "target.true_maxhp" ){
				lpOperand->bValueType = TYPE_TARGET_TRUE_MAXHP;
 			}else if( csFunc == "self.appearance" ){
				lpOperand->bValueType = TYPE_SELF_APPEARANCE;
			}else if( csFunc == "target.appearance" ){
				lpOperand->bValueType = TYPE_TARGET_APPEARANCE;
			}else if( csFunc == "self.true_maxmana" ){
				lpOperand->bValueType = TYPE_SELF_TRUE_MAXMANA;
			}else if( csFunc == "target.true_maxmana" ){
				lpOperand->bValueType = TYPE_TARGET_TRUE_MAXMANA;
			}else if( csFunc == "self.luck" ){
				lpOperand->bValueType = TYPE_SELF_LUCK;
			}else if( csFunc == "target.luck" ){
				lpOperand->bValueType = TYPE_TARGET_LUCK;
			}else if( csFunc == "self.true_luck" ){
				lpOperand->bValueType = TYPE_SELF_TRUE_LUCK;
			}else if( csFunc == "target.true_luck" ){
				lpOperand->bValueType = TYPE_TARGET_TRUE_LUCK;
           //////////////////////////////////////////////////////////////////////////////////////////
            // Functions
            }else  if( csFunc == "skill" || csFunc == "spell" ){
                // Uses only 1 operand which is the value in the skill.
                lpOperand->bFunction = FUNC_SELF_SKILL;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid skill/spell parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "true_skill" || csFunc == "true_spell" ){
                // Uses only 1 operand which is the value in the skill.
                lpOperand->bFunction = FUNC_SELF_TRUE_SKILL;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid true_skill/true_spell parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else  if( csFunc == "target.skill" || csFunc == "target.spell" ){
                // Uses only 1 operand which is the value in the skill.
                lpOperand->bFunction = FUNC_TARGET_SKILL;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid target.skill/target.spell parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else  if( csFunc == "target.true_skill" || csFunc == "target.true_spell" ){
                // Uses only 1 operand which is the value in the skill.
                lpOperand->bFunction = FUNC_TARGET_TRUE_SKILL;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid target.true_skill/target.true_spell parameter."
                    LOG_
                    boError = TRUE;
                }

            //////////////////////////////////////////////////
            }else if( csFunc == "self.viewflag" ){
                lpOperand->bFunction = FUNC_SELF_VIEW_FLAG;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid flagid parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "target.viewflag" ){
                lpOperand->bFunction = FUNC_TARGET_VIEW_FLAG;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid flagid parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "global.viewflag" ){
                lpOperand->bFunction = FUNC_GLOBAL_VIEW_FLAG;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid flagid parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "itemcount" || csFunc == "self.itemcount" ){
                lpOperand->bFunction = FUNC_ITEM_COUNT;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid itemid parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "target.itemcount" ){
                lpOperand->bFunction = FUNC_TARGET_ITEM_COUNT;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid itemid parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "var" ){
                lpOperand->bFunction = FUNC_VAR;                                
                
                CString *varName = new CString;
                
                if( lpszFormula[ i ] == '(' ){
                    i++;
                }
                while( lpszFormula[ i ] != ')' ){                    
                    if( lpszFormula[ i ] == 0 ){
                        _LOG_DEBUG
                            LOG_DEBUG_LVL2,
                            "Formula error: closing ) parenthesis not found while getting variable name from var function."
                        LOG_
                        delete varName;
                        boError = TRUE;
                        break;
                    }
                    *varName += lpszFormula[ i ];
                    i++;
                }
                if( !boError ){
                    varName->TrimRight();
                    varName->TrimLeft();
                    varName->MakeUpper();

                    lpOperand->lpLeftOperand = (LPOPERAND)varName;
                    tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "equipcount" || csFunc == "self.equipcount" ){
                lpOperand->bFunction = FUNC_EQUIPPED;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                
                
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid itemid parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "target.equipcount" ){
                lpOperand->bFunction = FUNC_TARGET_EQUIPPED;
                lpOperand->lpLeftOperand = new OPERAND;                
                tlOperands.AddToTail( lpOperand->lpLeftOperand );                

                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );

                if( !ParseFormula( lpszFormula + i, lpOperand->lpLeftOperand ) ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL2,
                        "Formula error: invalid itemid parameter."
                    LOG_
                    boError = TRUE;
                }
            //////////////////////////////////////////////////
            }else if( csFunc == "if" ){
                // if( x < z ? dsf : sdfsf )

                // IF blocks have 2 more parameters

                lpOperand->lpFunctionParameters = new OPERAND[ 2 ];
                lpOperand->lpRightOperand = new OPERAND;
                lpOperand->lpLeftOperand = new OPERAND;

                tlOperands.AddToTail( lpOperand->lpRightOperand );
                tlOperands.AddToTail( lpOperand->lpLeftOperand );
                tlOperands.AddToTail( lpOperand->lpFunctionParameters );
                //tlOperands.AddToTail( lpOperand->lpFunctionParameters[ 1 ] );

                lpOperand->bFunction = FUNC_IF;
                memset( lpOperand->lpRightOperand, 0, sizeof( OPERAND ) );
                memset( lpOperand->lpLeftOperand,  0, sizeof( OPERAND ) );
                memset( &(lpOperand->lpFunctionParameters[0]), 0, sizeof( OPERAND ) );
                memset( &(lpOperand->lpFunctionParameters[1]), 0, sizeof( OPERAND ) );
                
                // find the whole 1st evaluator substring.                
                int nFirstParamStart = i+1;
                int nFirstParamEnd = -1;
                int nSecondParamStart = -1;
                //int nSecondParamEnd = -1; // ?
                BYTE bComparison = 0;
                do{
                    i++;
                    switch( lpszFormula[ i ] ){
                    case '<':                        
                        nFirstParamEnd = i;
                        if( lpszFormula[ i + 1 ] == '>' ){
                            TRACE( "( <> )" );
                            i += 2;
                            bComparison = IF_NOT_EQUAL;
                        }else if( lpszFormula[ i + 1 ] == '=' ){
                            TRACE( "( <= )" );
                            i += 2;                            
                            bComparison = IF_LESSER_EQUAL;
                        }else{
                            TRACE( "( < )" );
                            i++;
                            nSecondParamStart = i;
                            bComparison = IF_LESSER;
                        }
                        nSecondParamStart = i;
                        break;
                    case '>':                        
                        nFirstParamEnd = i;
                        if( lpszFormula[ i + 1 ] == '=' ){
                            TRACE( "( >= )" );
                            i += 2;                            
                            bComparison = IF_GREATER_EQUAL;
                        }else{
                            TRACE( "( > )" );
                            i++;                            
                            bComparison = IF_GREATER;
                        }
                        nSecondParamStart = i;
                        break;
                    case '=':
                        TRACE( "( = )" );
                        nFirstParamEnd = i;
                        i++;
                        nSecondParamStart = i;
                        bComparison = IF_EQUAL;
                        break;
                    case '\0':
                        nFirstParamEnd = 0;
                        break;
                    }
                }while( nFirstParamEnd == -1 );

                if( nFirstParamEnd != -1 && nSecondParamStart != -1 ){
                    lpOperand->dblValue = bComparison;

                    // Fetch first argument
                    char *lpszFirstParam = lpszFormula + nFirstParamStart;
                    lpszFormula[ nFirstParamEnd ] = 0;
                    TRACE( "\r\n-IF( %s ", lpszFirstParam );
                    if( !ParseFormula( lpszFirstParam, lpOperand->lpLeftOperand ) ){
                        boError = TRUE;
                    }
    
                    // Then fetch second argument.
                    while( lpszFormula[ i ] != '?' && !boError ){                        
                        // If a parenthesis was encountered
                        if( lpszFormula[ i ] == '(' ){
                            //  Skip it.
                            if( !SkipToNextParenthesis( i, lpszFormula ) ){
                                boError = TRUE;
                            }
                            // -- to counter the effect of the upcoming ++.
                            i--;
                        }                        
                        if( lpszFormula[ i ] == 0 ){
                            boError = TRUE;
                            _LOG_DEBUG
                                LOG_DEBUG_LVL2,
                                "Formula error: Could not find IF operator ?."
                            LOG_
                        }
                        i++;
                    }
                    if( !boError ){
                        char *lpszSecondParam = lpszFormula + nSecondParamStart;
                        lpszFormula[ i ] = 0;
                        TRACE( "- %s ) then ", lpszSecondParam );                        
                        if( !ParseFormula( lpszSecondParam, lpOperand->lpRightOperand ) ){
                            boError = TRUE;
                        }

                        // Now fetch the return paths.                        
                        i++;
                        char *lpszTrue = lpszFormula + i;
                        while( lpszFormula[ i ] != ':' && !boError ){                            
                            // Skip any parenthesis.
                            if( lpszFormula[ i ] == '(' ){
                                if( !SkipToNextParenthesis( i, lpszFormula ) ){
                                    boError = TRUE;
                                }
                            }else{
                                i++;
                            }
                        }
                        lpszFormula[ i ] = 0;
                        i++;
                        char *lpszFalse = lpszFormula + i;
                        while( lpszFormula[ i ] != ')' && !boError ){                            
                            if( lpszFormula[ i ] == '(' ){
                                if( !SkipToNextParenthesis( i, lpszFormula ) ){
                                    boError = TRUE;
                                }
                            }else{
                                i++;
                            }
                        }                        
                        if( !boError ){
                            // Since the false statement is always at the end if
                            // the if statement, make the parser also flush
                            // the if's last parenthesis.                            
                            lpszFormula[ i ] = 0;
                            i++;
                            TRACE( " \"%s\" else \"%s\"", lpszTrue, lpszFalse );
                            if( ParseFormula( lpszTrue, &lpOperand->lpFunctionParameters[ 1 ] ) ){
                                TRACE( "FALSE=%s.", lpszFalse );                                
                                if( !ParseFormula( lpszFalse, &lpOperand->lpFunctionParameters[ 0 ] ) ){
                                    boError = TRUE;
                                }
                            }else{
                                boError = TRUE;
                            }
                        }else{
                            _LOG_DEBUG
                                LOG_DEBUG_LVL2,
                                "Formula error: couldn't successfully parse return paths in IF expression."
                            LOG_
                        }
                    }
                }else{                    
                    _LOG_DEBUG
                        LOG_DEBUG_LVL1,
                        "Formula error: Could not find conditional arguments in IF expresioon."
                    LOG_
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////
            // Not a function nor a control.
            else{
                boError = TRUE;
                _LOG_DEBUG
                    LOG_DEBUG_LVL2,
                    "Formula error: Invalid keyword/function name %s.",
                    (LPCTSTR)csFunc
                LOG_
            }
        }
        // Otherwise this is not a valid parameter.
        else{            
            // TODO ERROR
            boError = TRUE;
            _LOG_DEBUG
                LOG_DEBUG_LVL2,
                "Formula error: Invalid or unknown character %c.",
                lpszFormula[ 0 ]
            LOG_
        }
    }

    if( boError ){
        return FALSE;
    }
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
char *BoostFormula::GetOriginalFormula( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the original boost formula associated to the class.
// 
// Return: char, the returned string.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return (char*)( (LPCTSTR)csOriginalFormula );
}

CString BoostFormula::TranslateStringFormula
//////////////////////////////////////////////////////////////////////////////////////////
// Get a StringFormula and process it
// 
// Return: CString with formulas replaced :)
//////////////////////////////////////////////////////////////////////////////////////////
(
 CString csStringFormula,
 Unit *self,
 Unit *target,
 VarMap *varMap
){
	// previousPosition <-- [regular text here] --> currentPosition <-- [BoostFormula here] --> nextPosition
	int currentPosition = csStringFormula.Find("$~",0);
	int nextPosition;
	int previousPosition = 0;
	if (currentPosition == -1) {
		return(csStringFormula);
	} else {
		CString temp;
		CString csTranslatedString;
		BoostFormula bfTemp;
		while (currentPosition != -1) {
			csTranslatedString += csStringFormula.Mid(previousPosition,currentPosition-previousPosition);

			currentPosition += 2;
			nextPosition = csStringFormula.Find("$~", currentPosition);
			if (nextPosition != -1) {
				temp = csStringFormula.Mid(currentPosition,nextPosition-currentPosition);
				if ( temp.CompareNoCase("target.name") == 0 ) {
					csTranslatedString += target->GetName(_DEFAULT_LNG);
				} else if ( temp.CompareNoCase("self.name") == 0 ) {
					csTranslatedString += self->GetName(_DEFAULT_LNG);;
				} else if ( bfTemp.SetFormula( temp ) ) {
					temp.Format("%1.0f", bfTemp.GetBoost(self, target, 0, 0, 0, varMap));
					csTranslatedString += temp;
				} else {
					csTranslatedString += "$~ !! $~";
				}
			} else {
				csTranslatedString += csStringFormula.Mid(currentPosition);
				previousPosition = csStringFormula.GetLength();
				break;
			}
			previousPosition = nextPosition+2;
			currentPosition = csStringFormula.Find("$~", previousPosition);
		}
		csTranslatedString += csStringFormula.Mid(previousPosition);
		return(csTranslatedString);
	}
}

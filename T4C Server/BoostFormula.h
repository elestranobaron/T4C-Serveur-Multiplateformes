// BoostFormula.h: interface for the BoostFormula class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOSTFORMULA_H__67C507F8_166F_11D2_8376_00E02922FA40__INCLUDED_)
#define AFX_BOOSTFORMULA_H__67C507F8_166F_11D2_8376_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "vdlist.h"
#include <map>

// Boost calculation parameter
#define COMPUTE_NORMAL			1
#define COMPUTE_MIN				2
#define COMPUTE_MAX				3

class Unit;

class EXPORT BoostFormula  
{
public:
    typedef std::map< std::string, double > VarMap;

    BoostFormula();
	virtual ~BoostFormula();

    BOOL   SetFormula( CString csFormula );
    double GetBoost( LPVOID self, LPVOID target = NULL, double dblX = 0, double dblY = 0, double dblR = 0, VarMap *varMap = NULL );
	double GetMinBoost( LPVOID self, LPVOID target = NULL, double dblX = 0, double dblY = 0, double dblR = 0, VarMap *varMap = NULL );
    double GetMaxBoost( LPVOID self, LPVOID target = NULL, double dblX = 0, double dblY = 0, double dblR = 0, VarMap *varMap = NULL );
	char *GetOriginalFormula( void );

	static CString TranslateStringFormula(CString csStringFormula, Unit *self, Unit *target = NULL, VarMap *varMap = NULL );

private:    
    typedef struct _OPERAND{
        BYTE   bOperator;        
        double dblValue;
        BYTE   bValueType;
        BYTE   bFunction;
        
        _OPERAND *lpFunctionParameters;
        _OPERAND *lpLeftOperand;
        _OPERAND *lpRightOperand;    
    } OPERAND, *LPOPERAND;

    double GetOperandValue( LPOPERAND lpOperand, LPVOID self, LPVOID target, double dblX, double dblY, double dblR, VarMap *varMap, int method = COMPUTE_NORMAL );
    BOOL ParseFormula( char *lpszFormula, LPOPERAND lpOperand );
    BOOL SkipToNextParenthesis( int &nCounter, char *lpszString );

    OPERAND opFirstOperand;
    
    CString csOriginalFormula;

    // List of operands used by the formula, for easy deletion.
    TemplateList< OPERAND > tlOperands;
};

#endif // !defined(AFX_BOOSTFORMULA_H__67C507F8_166F_11D2_8376_00E02922FA40__INCLUDED_)

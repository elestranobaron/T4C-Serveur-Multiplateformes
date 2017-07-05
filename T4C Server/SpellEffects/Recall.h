// Recall.h: interface for the Recall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECALL_H__EEC5C7E8_287F_11D2_83B4_00E02922FA40__INCLUDED_)
#define AFX_RECALL_H__EEC5C7E8_287F_11D2_83B4_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../SpellEffectManager.h"

class Recall : SpellEffect
{
public:
	Recall();
	virtual ~Recall();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

private:
    BoostFormula recallX;
    BoostFormula recallY;
    BoostFormula recallW;

};

#endif // !defined(AFX_RECALL_H__EEC5C7E8_287F_11D2_83B4_00E02922FA40__INCLUDED_)

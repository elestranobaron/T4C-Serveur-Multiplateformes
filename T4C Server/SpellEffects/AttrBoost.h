// AttrBoost.h: interface for the AttrBoost class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTRBOOST_H__78DFAECF_1C1E_11D2_8397_00E02922FA40__INCLUDED_)
#define AFX_ATTRBOOST_H__78DFAECF_1C1E_11D2_8397_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\SpellEffectManager.h"

class AttrBoost : SpellEffect
{
public:
	AttrBoost();
	virtual ~AttrBoost();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

    static void BoostRemoval( EFFECT_FUNC_PROTOTYPE );

private:
    WORD         wBoostedStat;
    BoostFormula bBoost;
    BOOL         boRealtime;
};

#endif // !defined(AFX_ATTRBOOST_H__78DFAECF_1C1E_11D2_8397_00E02922FA40__INCLUDED_)

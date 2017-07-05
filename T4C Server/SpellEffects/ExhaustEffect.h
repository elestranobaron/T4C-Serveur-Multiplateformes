// ExhaustEffect.h: interface for the ExhaustEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXHAUSTEFFECT_H__2C1527D9_AD0F_11D3_85D6_00E02922FA40__INCLUDED_)
#define AFX_EXHAUSTEFFECT_H__2C1527D9_AD0F_11D3_85D6_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SpellEffectManager.h"
#include "../BoostFormula.h"

class ExhaustEffect : public SpellEffect  
{
public:
	ExhaustEffect();
	virtual ~ExhaustEffect();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

private:
    BoostFormula mentalExhaust;
    BoostFormula attackExhaust;
    BoostFormula moveExhaust;

    BoostFormula successPercent;

};

#endif // !defined(AFX_EXHAUSTEFFECT_H__2C1527D9_AD0F_11D3_85D6_00E02922FA40__INCLUDED_)

// DrainLife.h: interface for the DrainLife class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAINLIFE_H__6C16ECCC_738F_11D2_8444_00E02922FA40__INCLUDED_)
#define AFX_DRAINLIFE_H__6C16ECCC_738F_11D2_8444_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "HealthEffect.h"

// This effect will do damage to a target and give it to the caster.
class DrainLife : public HealthEffect
{
public:
    // Simply override the CallEffect
    void CallEffect( SPELL_EFFECT_PROTOTYPE );
    BOOL InputParameter( CString csParam, WORD wParamID );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

private:
    BoostFormula cDamageModifier;
};

#endif // !defined(AFX_DRAINLIFE_H__6C16ECCC_738F_11D2_8444_00E02922FA40__INCLUDED_)

// DispellEffect.h: interface for the DispellEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPELLEFFECT_H__0AB5FACB_A462_11D3_85C9_00E02922FA40__INCLUDED_)
#define AFX_DISPELLEFFECT_H__0AB5FACB_A462_11D3_85C9_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\SpellEffectManager.h"

class DispellEffect : public SpellEffect  
{
public:
    // Simply override the CallEffect
    void CallEffect( SPELL_EFFECT_PROTOTYPE );
    BOOL InputParameter( CString csParam, WORD wParamID );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );
private:
    void Dispell( Unit *caster, Unit *target );

    DWORD targetSpellID;
    BoostFormula successPercentage;
};

#endif // !defined(AFX_DISPELLEFFECT_H__0AB5FACB_A462_11D3_85C9_00E02922FA40__INCLUDED_)

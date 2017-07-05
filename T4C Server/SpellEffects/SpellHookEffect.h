// SpellHookEffect.h: interface for the SpellHookEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPELLHOOKEFFECT_H__38165725_1A5B_11D2_837C_00E02922FA40__INCLUDED_)
#define AFX_SPELLHOOKEFFECT_H__38165725_1A5B_11D2_837C_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../SpellEffectManager.h"

class SpellHookEffect : public SpellEffect  
{
public:
	SpellHookEffect();
	virtual ~SpellHookEffect();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );
protected:
    static void SpellTrigger( EFFECT_FUNC_PROTOTYPE );

    WORD  wSpellID;
    WORD  wHook;
    DWORD dwEffectID;

    BoostFormula initialDelay;
    BoostFormula cSpellHookChance;
};

#endif // !defined(AFX_SPELLHOOKEFFECT_H__38165725_1A5B_11D2_837C_00E02922FA40__INCLUDED_)

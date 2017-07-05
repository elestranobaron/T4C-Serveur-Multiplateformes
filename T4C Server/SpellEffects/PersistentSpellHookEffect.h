// PersistentSpellHookEffect.h: interface for the PersistentSpellHookEffect class.
// The difference between this and the SpellHookEffect is that this one wont wear off 
// when Characters die.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSISTENTSPELLHOOKEFFECT_H__38165725_1A5B_11D2_837D_00E02922FA40__INCLUDED_)
#define AFX_PERSISTENTSPELLHOOKEFFECT_H__38165725_1A5B_11D2_837D_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SpellHookEffect.h"


class PersistentSpellHookEffect : public SpellHookEffect
{
	public:
    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

	private:
    static void PersistentSpellTrigger( EFFECT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_PERSISTENTSPELLHOOKEFFECT_H__38165725_1A5B_11D2_837D_00E02922FA40__INCLUDED_)

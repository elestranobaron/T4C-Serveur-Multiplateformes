// Invisibility.h: interface for the Invisibility class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INVISIBILITY_H__E966D07D_B313_11D3_85DE_00E02922FA40__INCLUDED_)
#define AFX_INVISIBILITY_H__E966D07D_B313_11D3_85DE_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SpellEffectManager.h"


class Invisibility : public SpellEffect
{
public:
	Invisibility();
	virtual ~Invisibility();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static void Init( void );
    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

    static void InvisibilityRemoval( EFFECT_FUNC_PROTOTYPE );
private:
    void BroadcastInvisibility( Unit *self );

    BoostFormula successPercentage;
    DWORD popupVisualEffect;
};

#endif // !defined(AFX_INVISIBILITY_H__E966D07D_B313_11D3_85DE_00E02922FA40__INCLUDED_)

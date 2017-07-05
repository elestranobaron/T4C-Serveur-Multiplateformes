// FlagAdding.h: interface for the FlagAdding class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLAGADDING_H__D3A55176_0F58_11D2_8362_00E02922FA40__INCLUDED_)
#define AFX_FLAGADDING_H__D3A55176_0F58_11D2_8362_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../SpellEffectManager.h"

class FlagAdding : public SpellEffect  
{
public:
	FlagAdding();
	virtual ~FlagAdding();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static void Init( void );
    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );
    static void FlagRemoval( EFFECT_FUNC_PROTOTYPE );

private:
    DWORD dwFlagID;
    BoostFormula flagValue;
    DWORD dwDuration;
	DWORD dwGlobal;
};

#endif // !defined(AFX_FLAGADDING_H__D3A55176_0F58_11D2_8362_00E02922FA40__INCLUDED_)

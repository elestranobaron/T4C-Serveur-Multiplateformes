// DetectHidden.h: interface for the DetectHidden class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DETECTHIDDEN_H__58ED3D02_B49F_11D3_85E0_00E02922FA40__INCLUDED_)
#define AFX_DETECTHIDDEN_H__58ED3D02_B49F_11D3_85E0_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DetectInvisibility.h"

class DetectHidden : public SpellEffect  
{
public:
	DetectHidden();
	virtual ~DetectHidden();
    
    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static void Init( void );
    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

    static void DetectHiddenRemoval( EFFECT_FUNC_PROTOTYPE );
private:
    
    DWORD popoffVisualEffect;
    BoostFormula successPercentage;

};

#endif // !defined(AFX_DETECTHIDDEN_H__58ED3D02_B49F_11D3_85E0_00E02922FA40__INCLUDED_)

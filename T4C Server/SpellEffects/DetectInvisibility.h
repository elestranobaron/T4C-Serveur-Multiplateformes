// DetectInvisibility.h: interface for the DetectInvisibility class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DETECTINVISIBILITY_H__D287BE59_B3D5_11D3_85DF_00E02922FA40__INCLUDED_)
#define AFX_DETECTINVISIBILITY_H__D287BE59_B3D5_11D3_85DF_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\SpellEffectManager.h"

class DetectInvisibility : public SpellEffect  
{
public:
	DetectInvisibility();
	virtual ~DetectInvisibility();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static void Init( void );
    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

    static void DetectInvisibilityRemoval( EFFECT_FUNC_PROTOTYPE );

    static void SendInvisibleList( DWORD flagId, Unit *self, DWORD popup );
    static void SendNewlyVisibleList( DWORD flagId, Unit *self, DWORD popup );

private:
    
    DWORD popoffVisualEffect;
    BoostFormula successPercentage;

};

#endif // !defined(AFX_DETECTINVISIBILITY_H__D287BE59_B3D5_11D3_85DF_00E02922FA40__INCLUDED_)

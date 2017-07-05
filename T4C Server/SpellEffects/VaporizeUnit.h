// VaporizeUnit.h: interface for the VaporizeUnit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VAPORIZEUNIT_H__8FAD5A3E_0349_11D3_84F8_00E02922FA40__INCLUDED_)
#define AFX_VAPORIZEUNIT_H__8FAD5A3E_0349_11D3_84F8_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../SpellEffectManager.h"

class VaporizeUnit : public SpellEffect  
{
public:
	VaporizeUnit();
	virtual ~VaporizeUnit();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

private:
};

#endif // !defined(AFX_VAPORIZEUNIT_H__8FAD5A3E_0349_11D3_84F8_00E02922FA40__INCLUDED_)

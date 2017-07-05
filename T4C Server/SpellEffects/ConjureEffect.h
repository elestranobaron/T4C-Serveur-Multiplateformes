// ConjureEffect.h: interface for the ConjureEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONJUREEFFECT_H__38165724_1A5B_11D2_837C_00E02922FA40__INCLUDED_)
#define AFX_CONJUREEFFECT_H__38165724_1A5B_11D2_837C_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\SpellEffectManager.h"

class ConjureEffect : public SpellEffect  
{
public:
	ConjureEffect();
	virtual ~ConjureEffect();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

private:
	void HandleError();
    DWORD wConjureID;
    BYTE bConjureType;
	WorldPos wlDestinationPos; //Optional position for the summon.
	BoostFormula bfPosX, bfPosY, bfPosW; //Formulas used for position calculation.
	BYTE bmUserDefinedPosition; // 0x07 if the user specified a position for the summon.
	CString csConjureID;
	enum { NOT_LOADED, FAILED, LOADED };
	BYTE bError;
};

#endif // !defined(AFX_CONJUREEFFECT_H__38165724_1A5B_11D2_837C_00E02922FA40__INCLUDED_)

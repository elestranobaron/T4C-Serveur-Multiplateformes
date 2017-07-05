// RecallDeathPos.h: interface for the RecallDeathPos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECALLDEATHPOS_H__D01E756A_BF83_11D2_849B_00E02922FA40__INCLUDED_)
#define AFX_RECALLDEATHPOS_H__D01E756A_BF83_11D2_849B_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../SpellEffectManager.h"

class RecallDeathPos : public SpellEffect  
{
public:
	RecallDeathPos();
	virtual ~RecallDeathPos();

    BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );
};

#endif // !defined(AFX_RECALLDEATHPOS_H__D01E756A_BF83_11D2_849B_00E02922FA40__INCLUDED_)

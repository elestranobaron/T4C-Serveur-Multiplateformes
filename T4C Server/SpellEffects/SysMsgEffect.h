// SysMsgEffect.h: interface for the SysMsgEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSMSGEFFECT_H__3083F3AE_1C84_498D_A424_A5E03C5DEC63__INCLUDED_)
#define AFX_SYSMSGEFFECT_H__3083F3AE_1C84_498D_A424_A5E03C5DEC63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\SpellEffectManager.h"
#include "..\NPCmacroScriptLng.h"

class SysMsgEffect  : public SpellEffect 
{
public:
	SysMsgEffect();
	virtual ~SysMsgEffect();

	BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

private:
	void HandleError( BYTE bResType, CString csMsg );
	enum { NOT_LOADED, FAILED, LOADED };
	BYTE m_bError;

	enum { GLOBAL, PRIVATE };
	CString m_csMsg;
	BYTE m_bResType;
};

#endif // !defined(AFX_SYSMSGEFFECT_H__3083F3AE_1C84_498D_A424_A5E03C5DEC63__INCLUDED_)

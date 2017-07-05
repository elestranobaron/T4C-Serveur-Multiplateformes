// UnitEffectManager.h: interface for the SpellEffectManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERALEFFECTMANAGER_H__F64E97D4_C25B_11D1_AD9B_00E029058623__INCLUDED_)
#define AFX_GENERALEFFECTMANAGER_H__F64E97D4_C25B_11D1_AD9B_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "vdlist.h"
#include "EffectListing.h"

class Unit;

#define EFFECT_FUNC_PROTOTYPE	WORD wMessageID, DWORD dwEffect, Unit *self, Unit *medium, Unit *target, LPVOID lpEffectData, LPVOID lpUserData
typedef void (*LPEFFECT_PROC)( EFFECT_FUNC_PROTOTYPE );

#define CREATE_EFFECT( _Unit, _Type, _Effect, _Func, _Data, _Timer, _TotalTime, _SpellID, __FlagID ){ \
				LPUNIT_EFFECT lpEffect = new UNIT_EFFECT;\
				lpEffect->bEffectType = _Type;\
				lpEffect->dwEffect = _Effect;\
				lpEffect->lpFunc = _Func;\
				lpEffect->lpData = _Data;\
				lpEffect->dwTimer = _Timer;\
                lpEffect->dwTotalDuration = _TotalTime;\
                lpEffect->bindedSpellID = _SpellID;\
                lpEffect->bindedFlag = __FlagID;\
				_Unit->AddEffect( lpEffect );}

typedef struct _UNIT_EFFECT{
	BYTE			bEffectType;	// MSG_On* type of effect.
	DWORD			dwEffect;		// ID of the effect.
	LPEFFECT_PROC	lpFunc;			// Effect procedure.
	LPVOID			lpData;			// Pointer to an effect defined data.
	DWORD			dwTimer;			// Reserved effect data.
    DWORD           dwTotalDuration;
    DWORD           bindedSpellID;  // ID of the spell (or skill) which triggered this effect.
    DWORD           bindedFlag;     // ID of a binded flag, 0 if none.
} UNIT_EFFECT, *LPUNIT_EFFECT;

#define REGISTER_EFFECT( __effect, __proc ) UnitEffectManager::RegisterEffect( __effect, __proc );

class EXPORT UnitEffectManager  
{
public:
	static void RegisterEffect( DWORD dwEffect, LPEFFECT_PROC lpFunc );
	static LPEFFECT_PROC GetEffectProc( DWORD wEffect );

	static void Destroy();
private:
	struct EFFECT_LIST{
		DWORD			dwEffect;
		LPEFFECT_PROC	lpFunc;
	};

	static TemplateList <EFFECT_LIST> tlEffectList;
};

#endif // !defined(AFX_SPELLEFFECTMANAGER_H__F64E97D4_C25B_11D1_AD9B_00E029058623__INCLUDED_)

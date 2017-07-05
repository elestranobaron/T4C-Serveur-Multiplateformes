// SetStatEffect.h: interface for the SetStatEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETSTATEFFECT_H__E625E99F_B76E_47D6_85F0_8395421F847C__INCLUDED_)
#define AFX_SETSTATEFFECT_H__E625E99F_B76E_47D6_85F0_8395421F847C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\SpellEffectManager.h"
#include "..\NPCmacroScriptLng.h"

class SetStatEffect : public SpellEffect 
{
public:
	SetStatEffect();
	virtual ~SetStatEffect();

	BOOL InputParameter( CString csParam, WORD wParamID );
    void CallEffect( SPELL_EFFECT_PROTOTYPE );

    static SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

private:
	enum { STR, END, AGI, WIS, INT, APPEARANCE, 
		AIR_POWER, DARK_POWER, EARTH_POWER, FIRE_POWER, LIGHT_POWER, WATER_POWER,
		AIR_RESIST, DARK_RESIST, EARTH_RESIST, FIRE_RESIST, LIGHT_RESIST, WATER_RESIST };
	BoostFormula cSetVal;
	BoostFormula successPercent;
	WORD wSetType;
};

#endif // !defined(AFX_SETSTATEFFECT_H__E625E99F_B76E_47D6_85F0_8395421F847C__INCLUDED_)

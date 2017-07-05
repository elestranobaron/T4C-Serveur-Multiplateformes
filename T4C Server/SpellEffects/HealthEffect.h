// HealthEffect.h: interface for the HealthEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEALTHEFFECT_H__65AF1064_0C35_11D2_835C_00E02922FA40__INCLUDED_)
#define AFX_HEALTHEFFECT_H__65AF1064_0C35_11D2_835C_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "../SpellEffectManager.h"
#include "../BoostFormula.h"

// This is the base class for health effects.

class HealthEffect : public SpellEffect  
{
public:
	HealthEffect();
	virtual ~HealthEffect();

    // Virtual to allow other classes to override them. cHealth and cRadialHealth should be setup anyway.
    virtual BOOL InputParameter( CString csParam, WORD wParamID );
    virtual void CallEffect( SPELL_EFFECT_PROTOTYPE );
    
    virtual int  DealHealthEffect( SPELL_EFFECT_PROTOTYPE );

    static  SpellEffect *NewFunc( LPSPELL_STRUCT lpSpell );

protected:
    int DoUnitDamage( Unit *self, Unit *target, LPSPELL_STRUCT lpSpell, double dblHealth );
    int DoUnitHealing( Unit *self, Unit *target, LPSPELL_STRUCT lpSpell, double dblHealth );


    BoostFormula cHealth;
    BoostFormula cRadialHealth;
    BoostFormula successPercent;

};

#endif // !defined(AFX_HEALTHEFFECT_H__65AF1064_0C35_11D2_835C_00E02922FA40__INCLUDED_)

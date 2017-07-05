// SpellEffectManager.h: interface for the SpellEffectManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPELLEFFECTMANAGER_H__65AF1061_0C35_11D2_835C_00E02922FA40__INCLUDED_)
#define AFX_SPELLEFFECTMANAGER_H__65AF1061_0C35_11D2_835C_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SpellEffect.h"
#include "SpellEffectStructureListing.h"

typedef SpellEffect *( *LPNEW_FUNC )( LPSPELL_STRUCT lpSpell );

class __declspec( dllexport ) SpellEffectManager  
{
public:
 	static void RegisterSuperstructure( LPNEW_FUNC lpFunc, WORD wID );	
	static SpellEffect *GetEffectObject( WORD wID, LPSPELL_STRUCT lpSpell );

    static void Destroy();
private:
	struct REGISTERED_SUPERSTRUCTURE{
		LPNEW_FUNC lpFunc;
		WORD wID;
	};
	
	static TemplateList < REGISTERED_SUPERSTRUCTURE > tlRegisteredEffects;
};

#define REGISTER_SPELL_EFFECT( __obj, __func, __id, __initfunc )  typedef class _INIT##__obj\
{public: _INIT##__obj\
    ( void ){ SpellEffectManager::RegisterSuperstructure( __func, __id ); if( __initfunc != NULL ){ __initfunc(); } }\
} INIT; static INIT __init;

#endif // !defined(AFX_SPELLEFFECTMANAGER_H__65AF1061_0C35_11D2_835C_00E02922FA40__INCLUDED_)

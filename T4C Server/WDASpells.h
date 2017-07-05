// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDASpells.h
//      Project:   T4C Server
//      Plateform: Windows NT
//      Creation:  8/3/1999
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         8/3/1999        1.0       FL             Initial developpement
//
//      Description
//          This class is the placeholder for all spells. You only need to interface this class
//
//      WDASpells CONTAINS-MANY WDASpellEffects
//                each WDASpellEffects CONTAINS-MANY WDASpellEffectsParameters.
//      WDASpells CONTAINS-MANY WDASpellRequirements.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDASPELLS_H__FFB498A7_D575_11D2_84B1_00E02922FA40__INCLUDED_)
#define AFX_WDASPELLS_H__FFB498A7_D575_11D2_84B1_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"
#include <vector>
#include <string>

#include "WDASpellEffects.h"
#include "WDASpellRequirements.h"

class WDASpells : public WDATable  
{
public:
    WDASpells( vir::Logger &cLogger );
	virtual ~WDASpells();

    // Spell structure
    struct SpellData{
        SpellData() :
            m_ReadOnly(false),
            dwSpellID(0),
            dwElement(0),
            dwAreaRange(0),
            dwVisualEffect(0),
            dwRangeVisualEffect(0),
            dwTargetType(0),
            dwAttackType(0),
            dwMinWis(0),
            dwMinInt(0),
            dwMinLevel(0),
            boLineOfSight(0),
            boPVPcheck(0),
            boAttackSpell(0),
            dwIcon(0)
        {}


        std::vector< WDASpellEffects >      vSpellEffects;
        std::vector< WDASpellRequirements > vSpellRequirements;
        
        bool        m_ReadOnly;
        DWORD       dwSpellID;
        std::string csName;
        std::string csMentalExhaust;
        std::string csMoveExhaust;
        std::string csAttackExhaust;
        std::string bsDuration;
        std::string bsTimerFrequency;
        DWORD       dwElement;
        std::string bsManaCost;
        DWORD       dwAreaRange;
        DWORD       dwVisualEffect;
        DWORD       dwRangeVisualEffect;
        DWORD       dwTargetType;
        DWORD       dwAttackType;
        DWORD       dwMinWis;
        DWORD       dwMinInt;
        DWORD       dwMinLevel;
        bool        boLineOfSight;
        bool        boPVPcheck;
        bool        boAttackSpell;
        DWORD       dwIcon;
        std::string csSuccessPercentage;
        std::string csDesc;
    };

    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // Loads the worlds from a DAO support    
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    // Returns all the spells.
    virtual std::vector< SpellData > &GetSpells( void );
	
	SpellData *GetSpell( DWORD spellID );
    
    DWORD GetNextSpellID();

private:
    // Contains all the spells.
    std::vector< SpellData > vSpells;


};

#endif // !defined(AFX_WDASPELLS_H__FFB498A7_D575_11D2_84B1_00E02922FA40__INCLUDED_)

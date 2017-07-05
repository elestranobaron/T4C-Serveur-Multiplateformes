// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDASpellEffects.h
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
//          You CANNOT reference this class. WDASpellEffects is contained and used by WDASpells
//      only.
//
//      WDASpellEffects CONTAINS-MANY WDASpellEffectsParameters.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDASPELLEFFECTS_H__FFB498A8_D575_11D2_84B1_00E02922FA40__INCLUDED_)
#define AFX_WDASPELLEFFECTS_H__FFB498A8_D575_11D2_84B1_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"
#include <vector>
#include "WDASpellEffectParameters.h"

class WDASpells;
class WDASpellEffects : public WDATable  
{
public:
    // WDASpells CONTAINS-MANY WDASpellEffects, make it a friend.
    friend WDASpells;
	
    WDASpellEffects( vir::Logger &cLogger, vir::DEBUG_LEVEL dlMapHighDebug );
	virtual ~WDASpellEffects();
    
    // Accessors
    DWORD GetEffectStructureID( void );
    std::vector< WDASpellEffectParameters > &GetParams( void );
    
    // Provide a deep-copy operator.
    void operator = ( const WDASpellEffects &cParam ){
        dwEffectStructureID = cParam.dwEffectStructureID;
        vParams = cParam.vParams;
    }
    
    void Setup( DWORD structureID ){
        dwEffectStructureID = structureID;        
    }

    bool operator == (const WDASpellEffects &l );

// Disable public, loading/saving only WDASpells can.
private:
    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // Loads the worlds from a DAO support    
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    // Data
    DWORD                                   dwEffectStructureID;
    std::vector< WDASpellEffectParameters > vParams;

};

#endif // !defined(AFX_WDASPELLEFFECTS_H__FFB498A8_D575_11D2_84B1_00E02922FA40__INCLUDED_)

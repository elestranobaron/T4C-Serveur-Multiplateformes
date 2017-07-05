// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDASpellEffectParameters.h
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
//          You CANNOT reference this class. It is only used by WDASpellEffects.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDASPELLEFFECTPARAMETERS_H__FFB498A9_D575_11D2_84B1_00E02922FA40__INCLUDED_)
#define AFX_WDASPELLEFFECTPARAMETERS_H__FFB498A9_D575_11D2_84B1_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"
#include <vector>

class WDASpellEffects;
//class WDASpellEffects::SpellEffectData;

class WDASpellEffectParameters : public WDATable  
{
public:
    WDASpellEffectParameters( vir::Logger &cLogger, vir::DEBUG_LEVEL dlMapDebugHigh );
    friend WDASpellEffects;
    
	virtual ~WDASpellEffectParameters();

    // Accessors
    std::string &GetParamValue();
    DWORD        GetParamID();

    // Provide a deep-copy = operator.
    void operator =( const WDASpellEffectParameters &cParam ){
        dwParamID = cParam.dwParamID;
        csParamValue = cParam.csParamValue;
    };
    
    bool operator==( const WDASpellEffectParameters &l );
    
    void Setup( DWORD paramID, std::string paramValue ){
        dwParamID = paramID;
        csParamValue = paramValue;
    }

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

    std::string csParamValue;
    DWORD       dwParamID;
};

#endif // !defined(AFX_WDASPELLEFFECTPARAMETERS_H__FFB498A9_D575_11D2_84B1_00E02922FA40__INCLUDED_)

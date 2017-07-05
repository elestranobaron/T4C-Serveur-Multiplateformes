// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDASpellRequirements.h
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
//          You CANNOT interface this class, used only by WDASpells.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDASPELLREQUIREMENTS_H__FFB498AA_D575_11D2_84B1_00E02922FA40__INCLUDED_)
#define AFX_WDASPELLREQUIREMENTS_H__FFB498AA_D575_11D2_84B1_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"

class WDASpells;
class WDASpellRequirements : public WDATable  
{
public:
    WDASpellRequirements( vir::Logger &cLogger, vir::DEBUG_LEVEL dlMapHighDebug );
    friend WDASpells;

	virtual ~WDASpellRequirements();

    // Accessor
    DWORD GetRequiredSpellID( void );

    // Deep-copy operator
    void operator = ( const WDASpellRequirements &cParam ){
        dwRequiredSpellID = cParam.dwRequiredSpellID;
    }

    void Setup( DWORD spellID ){
        dwRequiredSpellID = spellID;
    }
    
// Hide load/save
private:
    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // Loads the worlds from a DAO support    
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    DWORD dwRequiredSpellID;
};

#endif // !defined(AFX_WDASPELLREQUIREMENTS_H__FFB498AA_D575_11D2_84B1_00E02922FA40__INCLUDED_)

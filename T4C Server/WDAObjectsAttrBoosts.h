// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDAObjectsAttrBoosts.h
//      Project:   T4C Server
//      Plateform: Windows NT
//      Creation:  9/3/1999
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         9/3/1999        1.0       FL             Initial developpement
//
//      Description
//          You should not interface this class directly, use WDAObjects. See WDAObjects.h
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDAOBJECTSATTRBOOSTS_H__FECB9F3B_D648_11D2_84B2_00E02922FA40__INCLUDED_)
#define AFX_WDAOBJECTSATTRBOOSTS_H__FECB9F3B_D648_11D2_84B2_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"

class WDAObjects;
class WDAObjectsAttrBoosts : public WDATable  
{
public:
    // Only usable by WDAObjects.
    friend WDAObjects;
	
    WDAObjectsAttrBoosts( vir::Logger &cLogger, vir::DEBUG_LEVEL dlDebugHigh );
	virtual ~WDAObjectsAttrBoosts();

    // Accessors
    DWORD       GetStat( void );
    std::string GetBoost( void );
    DWORD       GetMinInt( void );
    DWORD       GetMinWis( void );
    DWORD       GetID( void );

    void Setup( DWORD stat, std::string boost, DWORD minInt, DWORD minWis, DWORD id ){
        dwStat = stat;
        bsBoost = boost;
        dwMinInt = minInt;
        dwMinWis = minWis;
        dwID = id;
    }    

    // Deep-copy operator
    void operator = ( const WDAObjectsAttrBoosts &cParam ){
        dwStat = cParam.dwStat;
        bsBoost = cParam.bsBoost;
        dwMinInt = cParam.dwMinInt;
        dwMinWis = cParam.dwMinWis;
        dwID     = cParam.dwID;
    };

private:    
    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // AreaLinks::CreateFrom does not need cRecord, it builds directly from the cDatabase.
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    // Data.
    DWORD       dwID;
    DWORD       dwStat;
    std::string bsBoost;
    DWORD       dwMinInt;
    DWORD       dwMinWis;
};

#endif // !defined(AFX_WDAOBJECTSATTRBOOSTS_H__FECB9F3B_D648_11D2_84B2_00E02922FA40__INCLUDED_)

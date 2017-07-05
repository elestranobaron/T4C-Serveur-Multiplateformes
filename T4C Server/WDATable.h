// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDATable.h
//      Project:   T4C Server
//      Plateform: Windows NT
//      Creation:  5/3/1999
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         5/3/1999        1.0       FL             Initial developpement
//
//      Description
//          Base abstract class for WDA tables.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#ifndef AFX_WDATABLE_H__8D88CCE9_D321_11D2_84AD_00E02922FA40__INCLUDED_
#define AFX_WDATABLE_H__8D88CCE9_D321_11D2_84AD_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDAFile.h"
#include "Logger.h"

#ifndef NO_DAO_SUPPORT
//    #include <afxdao.h>
#endif

class WDATable
{
public:
    virtual ~WDATable();

    virtual void SaveTo( WDAFile &wdaFile ) = 0;
    
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly ) = 0;

    virtual void MapDebugLogLevel( vir::DEBUG_LEVEL dl );
    virtual void MapDebugHighLogLevel( vir::DEBUG_LEVEL dl );
    virtual void MapInfoLogLevel( vir::DEBUG_LEVEL dl );

#ifndef NO_DAO_SUPPORT
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase ) = 0;
#endif

    virtual void DisableIntlStrings();

protected:
    WDATable( vir::Logger &cOutputLogger );

    vir::DEBUG_LEVEL dlInfo;
    vir::DEBUG_LEVEL dlDebug;
    vir::DEBUG_LEVEL dlDebugHigh;
    vir::Logger &cOutput;

    bool m_DisableIntlStrings;

    std::string GetBareString( std::string str );
};

#endif // !defined(AFX_WDATABLE_H__8D88CCE9_D321_11D2_84AD_00E02922FA40__INCLUDED_)

// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDAObjectsContainerItems.h
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
//          This class is handled by WDAObjects, you should not interface this class
//      directly.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDAOBJECTSCONTAINERITEMS_H__FECB9F38_D648_11D2_84B2_00E02922FA40__INCLUDED_)
#define AFX_WDAOBJECTSCONTAINERITEMS_H__FECB9F38_D648_11D2_84B2_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"
#include <string>

class WDAObjectsContainerGroups;
class WDAObjectsContainerItems : public WDATable  
{
public:
    // Only WDAObjectsContainerGroups can access this class. See WDAObjects.h
    friend WDAObjectsContainerGroups;
    
    WDAObjectsContainerItems( vir::Logger &cLogger, vir::DEBUG_LEVEL dlDebugHigh );
    virtual ~WDAObjectsContainerItems();

    // Accessors
    const std::string &GetItemID() const;

    // Deep copy operator
    void operator = ( const WDAObjectsContainerItems &cParam ){
        csItemID = cParam.csItemID;
    };
    
    bool operator == (const WDAObjectsContainerItems &cParam ){
        return csItemID == cParam.csItemID;
    }

    void Setup( std::string itemID ){
        csItemID = itemID;
    }

private:
    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // Creates from a single record.
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    // Data
    std::string csItemID;
    
};

#endif // !defined(AFX_WDAOBJECTSCONTAINERITEMS_H__FECB9F38_D648_11D2_84B2_00E02922FA40__INCLUDED_)

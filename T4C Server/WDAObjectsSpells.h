// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDAObjectsSpells.h
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
//          You should not interface this class directly, use WDAObjects instead.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDAOBJECTSSPELLS_H__FECB9F3A_D648_11D2_84B2_00E02922FA40__INCLUDED_)
#define AFX_WDAOBJECTSSPELLS_H__FECB9F3A_D648_11D2_84B2_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"

class WDAObjects;
class WDAObjectsSpells : public WDATable  
{
public:
    // Only viewable by WDAObjects.
    friend WDAObjects;
	
    WDAObjectsSpells( vir::Logger &cLogger, vir::DEBUG_LEVEL dlHighDebug );
	virtual ~WDAObjectsSpells();

    // Accessors
    DWORD GetSpellID( void );
    DWORD GetMessageHook( void );
    DWORD GetLevel( void );
    
    void Setup( DWORD spellID, DWORD messageHook, DWORD level ){
        dwSpellID = spellID;
        dwMessageHook = messageHook;
        dwLevel = level;
    }

    // Deep-copy operator
    void operator = ( const WDAObjectsSpells &cParam ){
       dwSpellID = cParam.dwSpellID;
       dwMessageHook = cParam.dwMessageHook;
       dwLevel = cParam.dwLevel;
    };

    bool operator == (const WDAObjectsSpells &c ){
        return dwSpellID == c.dwSpellID && dwMessageHook == c.dwMessageHook && dwLevel == c.dwLevel;
    }
    
private:    
    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // Create from DAO support.
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    DWORD dwSpellID;
    DWORD dwMessageHook;
    DWORD dwLevel;

};

#endif // !defined(AFX_WDAOBJECTSSPELLS_H__FECB9F3A_D648_11D2_84B2_00E02922FA40__INCLUDED_)

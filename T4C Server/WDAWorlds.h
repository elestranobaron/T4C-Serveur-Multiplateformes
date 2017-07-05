// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDAWorlds.h
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
//          This table holds worlds data.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#ifndef AFX_WDAWORLDS_H__0F034DCF_D33D_11D2_84AD_00E02922FA40__INCLUDED_
#define AFX_WDAWORLDS_H__0F034DCF_D33D_11D2_84AD_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "WDATable.h"
#include <vector>
#include <string>

class WDAWorlds : public WDATable  
{
public:
	// Construction
    WDAWorlds( vir::Logger &cTraceLogger );
	virtual ~WDAWorlds();

    // Structures.
    struct WorldData{
        WorldData() : 
            m_ReadOnly(false),
            wWorldID(0),
            wWorldSizeX(0),
            wWorldSizeY(0),
            lpbData(NULL)
        {}        

        bool                m_ReadOnly;
        WORD                wWorldID;        
        std::string         csWorldName;
        WORD                wWorldSizeX;
        WORD                wWorldSizeY;
        LPBYTE              lpbData;
    };

    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // Loads the worlds from a DAO support    
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    // Returns the worlds.
    virtual std::vector< WorldData > &GetWorlds( void );

private:
    std::vector< WorldData > vWorlds;
};

#endif

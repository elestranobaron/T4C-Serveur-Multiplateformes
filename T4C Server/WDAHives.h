// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDAHives.h
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
//          This class handles hives.
//
//      Class containment hierarchy
//
//      WDAHives CONTAINS-MANY WDALarvae    
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDAHIVES_H__5453C343_D66A_11D2_84B3_00E02922FA40__INCLUDED_)
#define AFX_WDAHIVES_H__5453C343_D66A_11D2_84B3_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"
#include "WDALarvae.h"
#include <vector>

class WDAHives : public WDATable  
{
public:
    WDAHives( vir::Logger &cLogger );
	virtual ~WDAHives();

    struct WorldPos{
        WorldPos() : X(0), Y(0), world(0){}
        
        bool operator==( const WorldPos &r ) const{
            return X     == r.X && 
                   Y     == r.Y && 
                   world == r.world;
        }

        int X, Y, world;
    };

    struct HiveData{
        HiveData() : 
            m_ReadOnly( false ),
            dwMinEmergeTime(0),
            dwMaxEmergeTime(0),
            dwMaxChildren(0),
            dwEmergenceRange(0)
        {}

        std::vector< WDALarvae > vLarvae;       // Larvae handled by the hive.
        std::vector< WorldPos >  vLocations;    // List of positions where the hive appears.
        
        bool  m_ReadOnly;
        DWORD dwMinEmergeTime;
        DWORD dwMaxEmergeTime;
        DWORD dwMaxChildren;
        DWORD dwEmergenceRange;
        std::string m_HiveName;
    };
    
    // Accessors
    std::vector< HiveData > &GetHives( void );

    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // Create hives from a DAO support
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

private:
    // Data
    std::vector< HiveData > vHives;
};

#endif // !defined(AFX_WDAHIVES_H__5453C343_D66A_11D2_84B3_00E02922FA40__INCLUDED_)

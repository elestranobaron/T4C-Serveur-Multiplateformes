// WDAHives.cpp: implementation of the WDAHives class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDAHives.h"
#include "format.h"
#include <map>

using namespace std;
using namespace vir;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDAHives::WDAHives( Logger &cLogger ) : WDATable( cLogger )
{

}

WDAHives::~WDAHives()
{

}

    // Accessors
//////////////////////////////////////////////////////////////////////////////////////////
std::vector< WDAHives::HiveData > &WDAHives::GetHives( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns all the hives.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vHives;
}

    
//////////////////////////////////////////////////////////////////////////////////////////
void WDAHives::SaveTo
//////////////////////////////////////////////////////////////////////////////////////////
// Saves to a wdaFile
// 
(
 WDAFile &wdaFile // The wdaFile
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nWriting hives."
        "\n"
    );

    DWORD savedHivesSize = 0;
    vector< HiveData >::iterator i;
    for( i = vHives.begin(); i != vHives.end(); i++ ){
        if( !(*i).m_ReadOnly ){
            savedHivesSize++;
        }
    }

    // Write the quantity of hives.
    wdaFile.Write( savedHivesSize );

    // Scroll through all hives.
    for( i = vHives.begin(); i != vHives.end(); i++ ){
        HiveData &cHive = (*i);

        if( cHive.m_ReadOnly ){
            continue;
        }

        // Write the hive data.
        TFormat cFormat;
        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\nWriting hive. EmergeTime: min %u, max %u. Max Child %u, range %u.",
                cHive.dwMinEmergeTime,
                cHive.dwMaxEmergeTime,
                cHive.dwMaxChildren,
                cHive.dwEmergenceRange
            )
        );

        wdaFile.Write( cHive.dwMinEmergeTime );
        wdaFile.Write( cHive.dwMaxEmergeTime );
        wdaFile.Write( cHive.dwMaxChildren );
        wdaFile.Write( cHive.dwEmergenceRange );
        wdaFile.Write( cHive.m_HiveName );

        // Save the larvae
        {
            // Write the quantity of larvae.
            wdaFile.Write( static_cast< DWORD >( cHive.vLarvae.size() ) );

            // Scroll through all larvae for this hive.
            vector< WDALarvae >::iterator j;
            for( j = cHive.vLarvae.begin(); j != cHive.vLarvae.end(); j++ ){
                // Save that larva.
                (*j).SaveTo( wdaFile );
            }
        }
        // Save the hive's locations
        {
            // Write the quantity of locations.
            wdaFile.Write( static_cast< DWORD >( cHive.vLocations.size() ) );

            // Scroll through all locations.
            vector< WorldPos >::iterator j;
            for( j = cHive.vLocations.begin(); j != cHive.vLocations.end(); j++ ){
                // Directly write the world pos.
                wdaFile.Write( (*j).X );
                wdaFile.Write( (*j).Y );
                wdaFile.Write( (*j).world );
            }
        }
    }
}    
    
//////////////////////////////////////////////////////////////////////////////////////////
void WDAHives::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Creates from a wdaFile.
// 
(
 WDAFile &wdaFile, // The wdaFile 
 bool createReadOnly
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nLoading hives."
        "\n"
    );
    
    // Read the quantity of hives.
    DWORD dwSize = 0xABCDEF;
    wdaFile.Read( dwSize );

    // Scroll through all hives.
    DWORD i;
    for( i = 0; i != dwSize; i++ ){
        HiveData cHive;

        wdaFile.Read( cHive.dwMinEmergeTime );
        wdaFile.Read( cHive.dwMaxEmergeTime );
        wdaFile.Read( cHive.dwMaxChildren );
        wdaFile.Read( cHive.dwEmergenceRange );
        wdaFile.Read( cHive.m_HiveName );

        // Write the hive data.
        TFormat cFormat;
        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\nFound hive. EmergeTime: min %u, max %u. Max Child %u, range %u.",
                cHive.dwMinEmergeTime,
                cHive.dwMaxEmergeTime,
                cHive.dwMaxChildren,
                cHive.dwEmergenceRange
            )
        );


        // Load the larvae
        {
            // Write the quantity of larvae.
            DWORD dwQ = 0xABCDEF;
            wdaFile.Read( dwQ );

            // Scroll through all larvae for this hive.
            DWORD j;
            for( j = 0; j != dwQ; j++ ){
                // Load that larva
                WDALarvae cLarva( cOutput, dlDebugHigh );
                cLarva.CreateFrom( wdaFile, createReadOnly );

                // Add this larva to the list of larvae in this hive.
                cHive.vLarvae.push_back( cLarva );
            }
        }
        // Load the hive's locations
        {
            // Read the quantity of locations.
            DWORD dwQ = 0xABCDEF;
            wdaFile.Read( dwQ );

            // Scroll through all locations.
            DWORD j;
            for( j = 0; j != dwQ; j++ ){
                WorldPos wlPos;
                // Directly read the world pos.
                wdaFile.Read( wlPos.X );
                wdaFile.Read( wlPos.Y );
                wdaFile.Read( wlPos.world );

                // Add this location
                cHive.vLocations.push_back( wlPos );
            }
        }
    
        cHive.m_ReadOnly = createReadOnly;
        // Add this hive to the list of hives.
        vHives.push_back( cHive );   
    }

}
#ifndef NO_DAO_SUPPORT    
    
//////////////////////////////////////////////////////////////////////////////////////////
void WDAHives::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
//  Creates the hives from a recordset.
// 
(
 CDaoRecordset &cRecord, // The recordset
 CDaoDatabase &cDatabase // The database.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( cRecord.IsEOF() ){
        return;
    }

    cOutput.Log(
        dlInfo,
        "\n----- DAO -----"
        "\nLoading hives."
        "\n"
    );

    map< DWORD, DWORD > hiveMap;

    cRecord.MoveFirst();
    TFormat cFormat;

    while( !cRecord.IsEOF() ){
        COleVariant oleData;

        HiveData cHive;
        DWORD dwLarvaeGroupID;

        bool boLoadHive = true;

        // Load the hive data.
        cRecord.GetFieldValue( "LarvaeGroupID", oleData );
        dwLarvaeGroupID = V_I4( &oleData );
        
        cRecord.GetFieldValue( "MinEmergeTime", oleData );
        cHive.dwMinEmergeTime = V_I4( &oleData );

        cRecord.GetFieldValue( "MaxEmergeTime", oleData );
        cHive.dwMaxEmergeTime = V_I4( &oleData );

        cRecord.GetFieldValue( "MaxChildren", oleData );
        cHive.dwMaxChildren = V_I4( &oleData );

        cRecord.GetFieldValue( "EmergenceRange", oleData );
        cHive.dwEmergenceRange = V_I4( &oleData );

        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\nFound hive %u. EmergeTime: min %u, max %u. Max Child %u, range %u.",
                dwLarvaeGroupID,
                cHive.dwMinEmergeTime,
                cHive.dwMaxEmergeTime,
                cHive.dwMaxChildren,
                cHive.dwEmergenceRange
            )
        );
        
    
        // If we should add this hive.
        if( boLoadHive ){
            // Add it to the list of hives.
            vHives.push_back( cHive );

            hiveMap[ dwLarvaeGroupID ] = vHives.size() - 1;
        }

        cRecord.MoveNext(); 
    }
    
    {
        map< DWORD, DWORD >::iterator i;
        for( i = hiveMap.begin(); i != hiveMap.end(); i++ ){
            char sql[ 1024 ];

            CDaoRecordset recGroup( &cDatabase );

            sprintf( 
                sql, 
                "SELECT * FROM LarvaeGroups WHERE LarvaeGroupID=%u",
                (*i).first
            );

            recGroup.Open( dbOpenSnapshot, sql );

            if( !recGroup.IsEOF() ){
                recGroup.MoveFirst();

                COleVariant oleData;
                recGroup.GetFieldValue( "LarvaeGroupName", oleData );

                vHives[ (*i).second ].m_HiveName = V_BSTRT( &oleData );
            }
        }
    }

    // Load the larvae in this hive.
    {
        CDaoRecordset recLarvae( &cDatabase );

        recLarvae.Open( 
            dbOpenSnapshot,
            "SELECT * FROM Larvae"
        );

        if( !recLarvae.IsEOF() ){
            
            // Scroll through all larvae in this hive
            for( recLarvae.MoveFirst(); !recLarvae.IsEOF(); recLarvae.MoveNext() ){
                COleVariant oleData;
                recLarvae.GetFieldValue( "LarvaeGroupID", oleData );
                DWORD hiveID = V_I4( &oleData );                

                // Find the associated spell.
                map< DWORD, DWORD >::iterator j;
                j = hiveMap.find( hiveID );
                if( j == hiveMap.end() ){
                    continue;
                }

                // Create all larvae.
                WDALarvae cLarvae( cOutput, dlDebugHigh );

                cLarvae.CreateFrom( recLarvae, cDatabase );

                // Add this larvae to the hive.
                vHives[ (*j).second ].vLarvae.push_back( cLarvae );
            }
        }
    }
    // Load the hive positions
    {
        CDaoRecordset recWorldHives( &cDatabase );

        recWorldHives.Open( 
            dbOpenSnapshot,
            "SELECT * FROM WorldHives"
        );

        // If the hive has world positions
        if( !recWorldHives.IsEOF() ){
            
            for( recWorldHives.MoveFirst(); !recWorldHives.IsEOF(); recWorldHives.MoveNext() ){
                COleVariant oleData;
                recWorldHives.GetFieldValue( "LarvaeGroupID", oleData );
                DWORD hiveID = V_I4( &oleData );                

                // Find the associated spell.
                map< DWORD, DWORD >::iterator j;
                j = hiveMap.find( hiveID );
                if( j == hiveMap.end() ){
                    continue;
                }

                
                WorldPos wlPos;
                
                // Fetch the location
                recWorldHives.GetFieldValue( "wlX", oleData );
                wlPos.X = V_I4( &oleData );
                recWorldHives.GetFieldValue( "wlY", oleData );
                wlPos.Y = V_I4( &oleData );
                recWorldHives.GetFieldValue( "wlWorld", oleData );
                wlPos.world = V_I4( &oleData );

                // Add the location to the list of locations
                vHives[ (*j).second ].vLocations.push_back( wlPos );
            }
        }
    }               

}
#endif

// WDAAreaLinks.cpp: implementation of the WDAAreaLinks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDAAreaLinks.h"
#include "Format.h"

using namespace std;
using namespace vir;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDAAreaLinks::WDAAreaLinks( Logger &cTraceLogger ) : WDATable( cTraceLogger )
{

}

WDAAreaLinks::~WDAAreaLinks()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
void WDAAreaLinks::SaveTo
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 WDAFile &wdaFile // The WDAfile to save the area links to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nWriting area links."
        "\n"
    );

    vector< AreaLinkData >::iterator i;

    DWORD savedAreaLinksSize = 0;
    for( i = vAreaLinks.begin(); i != vAreaLinks.end(); i++ ){
        if( !(*i).m_ReadOnly ){
            savedAreaLinksSize++;
        }
    }

    

    // Write the quantity of area links
    wdaFile.Write( savedAreaLinksSize );

    // Scroll through all area links.
    for( i = vAreaLinks.begin(); i != vAreaLinks.end(); i++ ){
        if( (*i).m_ReadOnly ){
            continue;
        }

        TFormat cFormat;
        cOutput.Log( dlDebugHigh,
            cFormat( "\r\nWriting area link from %u, %u, %u to %u, %u, %u.",
                (*i).wlSourcePos.X, (*i).wlSourcePos.Y, (*i).wlSourcePos.world,
                (*i).wlTargetPos.X, (*i).wlTargetPos.Y, (*i).wlTargetPos.world
            )
        );

        // Write source pos.
        wdaFile.Write( (*i).wlSourcePos.X );
        wdaFile.Write( (*i).wlSourcePos.Y );
        wdaFile.Write( (*i).wlSourcePos.world );
        // Write target pos.
        wdaFile.Write( (*i).wlTargetPos.X );
        wdaFile.Write( (*i).wlTargetPos.Y );        
        wdaFile.Write( (*i).wlTargetPos.world );

    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void WDAAreaLinks::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
//  Create from a WDA file.
// 
(
 WDAFile &wdaFile, // The wda file to create the area links from.
 bool     createReadOnly
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD dwSize = 0xABCDEF;

    TFormat cFormat;
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nLoading area links."
        "\n"
    );

    // Read the quantity of area links.
    wdaFile.Read( dwSize );

    cOutput.Log(
        dlDebugHigh,
        cFormat(
            "\nFound %u area links.",
            dwSize
        )
    );

    // The quantity wasn't read.
    //ASSERT( dwSize != 0xABCDEF );

    DWORD i;
    for( i = 0; i < dwSize; i++ ){
        AreaLinkData cAreaData;

        // Fetch source pos.
        wdaFile.Read( cAreaData.wlSourcePos.X );
        wdaFile.Read( cAreaData.wlSourcePos.Y );
        wdaFile.Read( cAreaData.wlSourcePos.world );
        // Fetch target pos.
        wdaFile.Read( cAreaData.wlTargetPos.X );
        wdaFile.Read( cAreaData.wlTargetPos.Y );
        wdaFile.Read( cAreaData.wlTargetPos.world );
        
        cOutput.Log( dlDebugHigh,
            cFormat( "\r\nFound area link from %u, %u, %u to %u, %u, %u.",
                cAreaData.wlSourcePos.X, cAreaData.wlSourcePos.Y, cAreaData.wlSourcePos.world,
                cAreaData.wlTargetPos.X, cAreaData.wlTargetPos.Y, cAreaData.wlTargetPos.world
            )
        );

        cAreaData.m_ReadOnly = createReadOnly;

        // Add area link
        vAreaLinks.push_back( cAreaData );
    }
}

#ifndef NO_DAO_SUPPORT

//////////////////////////////////////////////////////////////////////////////////////////
void WDAAreaLinks::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
//  Creates the area links from a database and recordset.
// 
(
 CDaoRecordset &cRecord, // The recordset containing all AreaLink records.
 CDaoDatabase &cDatabase // Unused.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- DAO -----"
        "\nLoading area links."
        "\n"
    );

    // If no records
    if( cRecord.IsEOF() ){
        return;
    }
    
    cRecord.MoveFirst();

    while( !cRecord.IsEOF() ){
        COleVariant oleData;

        AreaLinkData cAreaData;

        // Fetch the area link's data.
        cRecord.GetFieldValue( "PosX", oleData );
        cAreaData.wlSourcePos.X = oleData.lVal;
        cRecord.GetFieldValue( "PosY", oleData );
        cAreaData.wlSourcePos.Y = oleData.lVal;
        cRecord.GetFieldValue( "PosWorld", oleData );
        cAreaData.wlSourcePos.world = oleData.lVal;
        cRecord.GetFieldValue( "TargetX", oleData );
        cAreaData.wlTargetPos.X = oleData.lVal;
        cRecord.GetFieldValue( "TargetY", oleData );
        cAreaData.wlTargetPos.Y = oleData.lVal;
        cRecord.GetFieldValue( "TargetWorld", oleData );
        cAreaData.wlTargetPos.world = oleData.lVal;

        TFormat cFormat;
        cOutput.Log( dlDebugHigh,
            cFormat( "\r\nFound area link from %u, %u, %u to %u, %u, %u.",
                cAreaData.wlSourcePos.X, cAreaData.wlSourcePos.Y, cAreaData.wlSourcePos.world,
                cAreaData.wlTargetPos.X, cAreaData.wlTargetPos.Y, cAreaData.wlTargetPos.world
            )
        );

        vAreaLinks.push_back( cAreaData );

        cRecord.MoveNext();
    }

}
#endif

//////////////////////////////////////////////////////////////////////////////////////////
vector< WDAAreaLinks::AreaLinkData > &WDAAreaLinks::GetAreaLinks( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the loaded data.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vAreaLinks;
}
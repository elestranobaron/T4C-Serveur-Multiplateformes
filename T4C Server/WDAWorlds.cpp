// WDAWorlds.cpp: implementation of the WDAWorlds class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDAWorlds.h"
#include "Format.h"
#include <iterator>

using namespace std;
using namespace vir;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDAWorlds::WDAWorlds( Logger &cTraceLogger ) : WDATable( cTraceLogger )
{

}

WDAWorlds::~WDAWorlds()
{
}


//////////////////////////////////////////////////////////////////////////////////////////
void WDAWorlds::SaveTo
//////////////////////////////////////////////////////////////////////////////////////////
//  Saves the worlds to a WDA file
// 
(
 WDAFile &wdaFile // The file to save the worlds to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nWriting worlds."
        "\n"
    );

    // Write the quantity of worlds
    wdaFile.Write( static_cast< DWORD >( vWorlds.size() ) );


    // Scroll through the list of worlds.
    vector< WorldData >::iterator i;
    for( i = vWorlds.begin(); i != vWorlds.end(); i++ ){
        WorldData &cWorldData = (*i);

        TFormat tFormat;
        cOutput.Log(
            dlDebug,
            tFormat( "\r\nWriting world %s (%u), MaxX %u, MaxY %u.",
                cWorldData.csWorldName.c_str(),
                cWorldData.wWorldID,
                cWorldData.wWorldSizeX,
                cWorldData.wWorldSizeY
            )
        );

        wdaFile.Write( cWorldData.wWorldID );
        wdaFile.Write( cWorldData.csWorldName );
        wdaFile.Write( cWorldData.wWorldSizeX );
        wdaFile.Write( cWorldData.wWorldSizeY );
        wdaFile.Write( cWorldData.lpbData, cWorldData.wWorldSizeX * cWorldData.wWorldSizeY / 2 );

        // Delete world data now that it has been saved.
        delete cWorldData.lpbData;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
void WDAWorlds::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
//  Creates the worlds from a WDA file.
// 
(
 WDAFile &wdaFile, // The WDA file.
 bool createReadOnly
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nLoading worlds."
        "\n"
    );

    // Read the quantity of worlds
    DWORD dwSize = 0xABCDEF;
    wdaFile.Read( dwSize );

    ///TRACE( "\ndwSize=%u.", dwSize );

    // Scroll through the list of worlds.
    DWORD i;
    for( i = 0; i != dwSize; i++ ){
        WorldData cWorldData;

        wdaFile.Read( cWorldData.wWorldID );
        wdaFile.Read( cWorldData.csWorldName );
        wdaFile.Read( cWorldData.wWorldSizeX );
        wdaFile.Read( cWorldData.wWorldSizeY );

        TFormat tFormat;
        cOutput.Log(
            dlDebug,
            tFormat( "Found world %u, %s [%ux%u].",
                cWorldData.wWorldID,    
                cWorldData.csWorldName.c_str(),                
                cWorldData.wWorldSizeX,
                cWorldData.wWorldSizeY
            )
        );
        
        cWorldData.lpbData = new BYTE[ cWorldData.wWorldSizeX * cWorldData.wWorldSizeY / 2 ];
        wdaFile.Read( cWorldData.lpbData, cWorldData.wWorldSizeX * cWorldData.wWorldSizeY / 2 );
                    
        cWorldData.m_ReadOnly = createReadOnly;
        // Add world to list.
        vWorlds.push_back( cWorldData );
    }

}

#ifndef NO_DAO_SUPPORT    

//////////////////////////////////////////////////////////////////////////////////////////
void WDAWorlds::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
//  Creates the worlds from a DAO support.
// 
(
 CDaoRecordset &cRecord, // The recordset of worlds.
 CDaoDatabase &cDatabase // Unused.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- DAO -----"
        "\nLoading worlds."
        "\n"
    );

    // If there aren't any records.
    if( cRecord.IsEOF() ){
        return;
    }

    cRecord.MoveFirst();

    while( !cRecord.IsEOF() ){
        COleVariant oleData;

        WorldData cWorldData;

        // Fetch the area link's data.
        cRecord.GetFieldValue( "ID", oleData );
        cWorldData.wWorldID = V_I2( &oleData );
        cRecord.GetFieldValue( "Name", oleData );        
        cWorldData.csWorldName = V_BSTRT( &oleData );
        cRecord.GetFieldValue( "WorldMaxX", oleData );
        cWorldData.wWorldSizeX = V_I2( &oleData );
        cRecord.GetFieldValue( "WorldMaxY", oleData );
        cWorldData.wWorldSizeY = V_I2( &oleData );
        

        BYTE *lpbWorldData;

        cRecord.GetFieldValue( "BinaryMap", oleData );
        TFormat tFormat;
        cOutput.Log(
            dlDebug,
            tFormat( "Found world %u, %s [%ux%u].",
                cWorldData.wWorldID,    
                cWorldData.csWorldName.c_str(),                
                cWorldData.wWorldSizeX,
                cWorldData.wWorldSizeY
            )
        );
        
        switch( SafeArrayAccessData( oleData.parray, (void**)(&lpbWorldData) ) ){
        case S_OK:                        
            // Reserve enough memory for copying.
            cWorldData.lpbData = new BYTE[ cWorldData.wWorldSizeX * cWorldData.wWorldSizeY / 2 ];

            copy(
                lpbWorldData,
                lpbWorldData + ( cWorldData.wWorldSizeX * cWorldData.wWorldSizeY / 2 ),
                cWorldData.lpbData
            );

            vWorlds.push_back( cWorldData );

            SafeArrayUnaccessData( oleData.parray );

            break;
        case E_INVALIDARG:
            cOutput.Log( dlDebug, "\r\nInvalid world area array." );
            break;
        case E_UNEXPECTED:
            cOutput.Log( dlDebug, "\r\nThe world area array could not be locked." );
            break;
        };

        cRecord.MoveNext();
    }


}
#endif

//////////////////////////////////////////////////////////////////////////////////////////
vector< WDAWorlds::WorldData > &WDAWorlds::GetWorlds( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the worlds.
// 
// Return: std::vector< WorldData >, the worlds. 
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vWorlds;
}



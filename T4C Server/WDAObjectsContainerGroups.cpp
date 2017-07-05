// WDAObjectsContainerGroups.cpp: implementation of the WDAObjectsContainerGroups class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDAObjectsContainerGroups.h"
#include "Format.h"

using namespace std;
using namespace vir;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDAObjectsContainerGroups::WDAObjectsContainerGroups( Logger &cLogger, DEBUG_LEVEL dlDebugHigh ) : WDATable( cLogger )
{
    MapDebugHighLogLevel( dlDebugHigh );
}

WDAObjectsContainerGroups::~WDAObjectsContainerGroups()
{

}

// Accessors
//////////////////////////////////////////////////////////////////////////////////////////
vector< WDAObjectsContainerItems > &WDAObjectsContainerGroups::GetItems( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the vector of items in this container group.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vItems;
}

  
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjectsContainerGroups::SaveTo
//////////////////////////////////////////////////////////////////////////////////////////
// Saves to a wdaFile
// 
(
 WDAFile &wdaFile // The wdaFile
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Write the quantity of items in this container.
    wdaFile.Write( static_cast< DWORD >( vItems.size() ) );

    // Then write all items in the container.
    vector< WDAObjectsContainerItems >::iterator i;

    cOutput.Log(
        dlDebugHigh,
        "\n Container: "
    );

    for( i = vItems.begin(); i != vItems.end(); i++ ){
        (*i).SaveTo( wdaFile );
    }
}
    
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjectsContainerGroups::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Creates from a wdaFile.
// 
(
 WDAFile &wdaFile, // The wdaFile
 bool createReadOnly
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD dwSize = 0xABCDEF;

    // Read the quantity of container items.
    wdaFile.Read( dwSize );

    cOutput.Log(
        dlDebugHigh,
        "\n Container: "
    );

    // Load all container items.
    DWORD i;
    for( i = 0; i != dwSize; i++ ){        
        // Create a new WDAObjectsContainerItem from the wdaFile
        WDAObjectsContainerItems cItem( cOutput, dlDebugHigh );
        cItem.CreateFrom( wdaFile, createReadOnly );

        // Add it to the list of container items.
        vItems.push_back( cItem );
    }

}

//////////////////////////////////////////////////////////////////////////////////////////
bool WDAObjectsContainerGroups::operator == ( const WDAObjectsContainerGroups &g )
{
    if( g.vItems.size() != vItems.size() ){
        return false;
    }

    int i;
    for( i = 0; i < vItems.size(); i++ ){
        if( !( vItems[ i ] == g.vItems[ i ] ) ){
            return false;            
        }
    }
    return true;
}

#ifndef NO_DAO_SUPPORT    
    
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjectsContainerGroups::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Create from DAO support
// 
(
 CDaoRecordset &cRecord, // The sole recordset from which to create this item group.
 CDaoDatabase &cDatabase // The database object from which we fetch the items.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // This class should never get an empty or out-of-bound recordset.
    ASSERT( !cRecord.IsEOF() );

    COleVariant oleData;

    DWORD dwContainerID;
    
    cRecord.GetFieldValue( "ID", oleData );

    dwContainerID = V_I4( &oleData );

    TFormat cFormat;
    cOutput.Log(
        dlDebugHigh,
        cFormat(
            "\nContainer %u: ",
            dwContainerID
        )
    );

    // Fetch all items which are handled by this container group.
    CDaoRecordset recItems( &cDatabase );

    recItems.Open( 
        dbOpenSnapshot, 
        cFormat(
            "SELECT * FROM Objects_ContainerItems WHERE ContainerGroupID=%u",
            dwContainerID
        )
    );

    // If the container isn't empty
    if( !recItems.IsEOF() ){

        // Scroll through all items.
        recItems.MoveFirst();

        while( !recItems.IsEOF() ){
            WDAObjectsContainerItems cItem( cOutput, dlDebugHigh );

            // Create the item from this record.
            cItem.CreateFrom( recItems, cDatabase );

            // Add the item to the list of items.
            vItems.push_back( cItem );

            recItems.MoveNext();
        }
    }else{
        cOutput.Log(
            dlDebugHigh,
            "WARNING: Container is empty!"
        );
    }

}
#endif

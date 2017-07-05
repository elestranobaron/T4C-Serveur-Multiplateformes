// WDAObjectsWorldObjects.cpp: implementation of the WDAObjectsWorldObjects class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDAObjectsWorldObjects.h"
#include "Format.h"

using namespace std;
using namespace vir;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDAObjectsWorldObjects::WDAObjectsWorldObjects( Logger &cLogger, DEBUG_LEVEL dlHigh ) : WDATable( cLogger )
{
    m_ReadOnly = false;
    MapDebugHighLogLevel( dlHigh );
}

WDAObjectsWorldObjects::~WDAObjectsWorldObjects()
{

}

// Accessors
//////////////////////////////////////////////////////////////////////////////////////////
WDAObjectsWorldObjects::WorldPos WDAObjectsWorldObjects::GetPos( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the position of this item.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return wlPos;
}
//////////////////////////////////////////////////////////////////////////////////////////
const std::string &WDAObjectsWorldObjects::GetItemID( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the ID of this item
//////////////////////////////////////////////////////////////////////////////////////////
{
    return csItemID;
}

 
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjectsWorldObjects::SaveTo
//////////////////////////////////////////////////////////////////////////////////////////
 // Saves to a wdaFile
// 
(
 WDAFile &wdaFile // The wdaFile
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFormat cFormat;
    cOutput.Log(
        dlDebugHigh,
        cFormat(
            "\n Wrote object %s at %u, %u, %u.",
            csItemID.c_str(),
            wlPos.X,
            wlPos.Y,
            wlPos.world
        )
    );

    wdaFile.Write( csItemID );
    wdaFile.Write( wlPos.X );
    wdaFile.Write( wlPos.Y );
    wdaFile.Write( wlPos.world );
}   
 
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjectsWorldObjects::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Creates from a wdaFile.
// 
(
 WDAFile &wdaFile, // The wdafile
 bool createReadOnly
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    wdaFile.Read( csItemID );
    wdaFile.Read( wlPos.X );
    wdaFile.Read( wlPos.Y );
    wdaFile.Read( wlPos.world );

    TFormat cFormat;
    cOutput.Log(
        dlDebugHigh,
        cFormat(
            "\n Found object %s at %u, %u, %u.",
            csItemID.c_str(),
            wlPos.X,
            wlPos.Y,
            wlPos.world
        )
    );

    m_ReadOnly = createReadOnly;

}

#ifndef NO_DAO_SUPPORT    
 
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjectsWorldObjects::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Create from DAO support
// 
(
 CDaoRecordset &cRecord, // The record
 CDaoDatabase &cDatabase // Used to fetch the item associated to a color ID.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // This function cannot be passed an empty or out-of-bounds record.
    ASSERT( !cRecord.IsEOF() );

    if( cRecord.IsEOF() ){
        return;
    }

    COleVariant oleData;

    DWORD dwColorID;

    cRecord.GetFieldValue( "ObjectColorID", oleData );
    dwColorID = V_I4( &oleData );

    cRecord.GetFieldValue( "wlX", oleData );
    wlPos.X = V_I4( &oleData );

    cRecord.GetFieldValue( "wlY", oleData );
    wlPos.Y = V_I4( &oleData );

    cRecord.GetFieldValue( "wlWorld", oleData );
    wlPos.world = V_I4( &oleData );

    CDaoRecordset recColorID( &cDatabase );

    TFormat cFormat;
    recColorID.Open( 
        dbOpenSnapshot,
        cFormat(
            "SELECT * FROM ObjectsColorIDs WHERE ObjectColorID=%u",
            dwColorID
        )
    );

    if( !recColorID.IsEOF() ){
        recColorID.GetFieldValue( "ObjectID", oleData );
        csItemID = V_BSTRT( &oleData );

        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\n Found object %s at %u, %u, %u.",
                csItemID.c_str(),
                wlPos.X,
                wlPos.Y,
                wlPos.world
            )
        );
    }else{
        cOutput.Log(
            dlDebug,
            cFormat(
                "\n WARNING: Object at %u, %u, %u doesn't have a binded color ID.",
                wlPos.X,
                wlPos.Y,
                wlPos.world
            )
        );
    }
}
#endif

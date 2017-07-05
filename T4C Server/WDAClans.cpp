// WDAClans.cpp: implementation of the WDAClans class.
//
//////////////////////////////////////////////////////////////////////

//#include <afx.h>
#include "stdafx.h"
#include "WDAClans.h"
#include "Format.h"

using namespace vir;
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDAClans::WDAClans( Logger &cTraceLogger ) : WDATable( cTraceLogger )
{

}

WDAClans::~WDAClans()
{

}



//////////////////////////////////////////////////////////////////////////////////////////
void WDAClans::SaveTo
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
        "\nWriting clans."
        "\n"
    );

    // Write the highest clan 
    wdaFile.Write( dwHighestClan );

    DWORD savedClansSize = 0;
    vector< ClanRelation >::iterator i;

    // Dont't save read-only stuff.
    for( i = vClanRelations.begin(); i != vClanRelations.end(); i++ ){
        if( !(*i).m_ReadOnly ){
            savedClansSize++;
        }
    }

    wdaFile.Write( savedClansSize );

    for( i = vClanRelations.begin(); i != vClanRelations.end(); i++ ){
        ClanRelation &cClanRelation = (*i);
        
        if( cClanRelation.m_ReadOnly ){
            continue;
        }

        wdaFile.Write( cClanRelation.wFirstClanID );
        wdaFile.Write( cClanRelation.wSecondClanID );
        wdaFile.Write( cClanRelation.sClanRelation );

        TFormat cFormat;
        cOutput.Log(
            dlDebug,
            cFormat( "\nWriting clan relation between clan %u and %u (%d aggressivity)",
                cClanRelation.wFirstClanID,
                cClanRelation.wSecondClanID,
                cClanRelation.sClanRelation
            )
        );
    }

    {    
        savedClansSize = 0;
        
        int j;
        for( j = 0; j < vClans.size(); j++ ){
            if( !vClans[ j ].m_ReadOnly ){
                savedClansSize++;
            }
        }

        wdaFile.Write( savedClansSize );
        for( j = 0; j < vClans.size(); j++ ){
            if( vClans[ j ].m_ReadOnly ){
                continue;
            }

            wdaFile.Write( vClans[ j ].m_ID );
            wdaFile.Write( vClans[ j ].m_Name );
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
void WDAClans::CreateFrom
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

    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nLoading monster clans."
        "\n"
    );
    
    // Read the highest clan
    wdaFile.Read( dwHighestClan );
    
    // Read the quantity of clans.
    wdaFile.Read( dwSize );

    DWORD i;
    for( i = 0; i < dwSize; i++ ){
        ClanRelation cClanRelation;

        wdaFile.Read( cClanRelation.wFirstClanID );
        wdaFile.Read( cClanRelation.wSecondClanID );
        wdaFile.Read( cClanRelation.sClanRelation );

        TFormat cFormat;
        cOutput.Log(
            dlDebug,
            cFormat( "\nFound clan relation between clan %u and %u (%d aggressivity)",
                cClanRelation.wFirstClanID,
                cClanRelation.wSecondClanID,
                cClanRelation.sClanRelation
            )
        );

        cClanRelation.m_ReadOnly = createReadOnly;

        // Add clan to clan relations.
        vClanRelations.push_back( cClanRelation );
    }

    wdaFile.Read( dwSize );
    for( i = 0; i < dwSize; i++ ){
        Clan clan;

        wdaFile.Read( clan.m_ID );
        wdaFile.Read( clan.m_Name );

        clan.m_ReadOnly = createReadOnly;

        vClans.push_back( clan );
    }


}

#ifndef NO_DAO_SUPPORT
//////////////////////////////////////////////////////////////////////////////////////////
void WDAClans::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Creates the clan relations from a DAO database.
// 
(
 CDaoRecordset &cRecord, // The clan recordset
 CDaoDatabase &cDatabase // The database object (from which we fetch the highest ID)
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- DAO -----"
        "\nLoading monsters clans."
        "\n"
    );

    // If no records
    if( cRecord.IsEOF() ){
        return;
    }

    cRecord.MoveFirst();

    while( !cRecord.IsEOF() ){
        COleVariant oleData;
        ClanRelation cClanRelation;


        cRecord.GetFieldValue( "FirstClanID", oleData );
        cClanRelation.wFirstClanID  = V_I2( &oleData );
        cRecord.GetFieldValue( "SecondClanID", oleData );
        cClanRelation.wSecondClanID = V_I2( &oleData );
        cRecord.GetFieldValue( "MutualRelation", oleData );
        cClanRelation.sClanRelation = V_I2( &oleData );


        TFormat cFormat;
        cOutput.Log(
            dlDebug,
            cFormat( "\nFound clan relation between clan %u and %u (%d aggressivity)",
                cClanRelation.wFirstClanID,
                cClanRelation.wSecondClanID,
                cClanRelation.sClanRelation
            )
        );

        vClanRelations.push_back( cClanRelation );

        cRecord.MoveNext();
    }

    CDaoRecordset cClan( &cDatabase );
    
    dwHighestClan = 0;
    cClan.Open( dbOpenSnapshot, "SELECT * FROM Clans" );
    cClan.MoveFirst();
    while( !cClan.IsEOF() ){
        Clan clan;

        COleVariant oleData;
        
        cClan.GetFieldValue( "ClanID", oleData );
        clan.m_ID = V_I2( &oleData );

        cClan.GetFieldValue( "ClanName", oleData );
        clan.m_Name = V_BSTRT( &oleData );

        if( clan.m_ID > static_cast< long >( dwHighestClan ) ){
            dwHighestClan = clan.m_ID;
        }

        clan.m_ReadOnly = false;
        vClans.push_back( clan );
        
        cClan.MoveNext();
    }

    TFormat cFormat;
    cOutput.Log(
        dlDebugHigh,
        cFormat( 
            "\nHighest clan ID: %u",
            dwHighestClan
        )
    );


}
#endif


//////////////////////////////////////////////////////////////////////////////////////////
std::vector< WDAClans::ClanRelation > &WDAClans::GetClanRelations( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the clan relations
// 
// Return: std::vector< ClanRelation >, The clan relations.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vClanRelations;
}

//////////////////////////////////////////////////////////////////////////////////////////
std::vector< WDAClans::Clan > &WDAClans::GetClans()
{
    return vClans;
}

//////////////////////////////////////////////////////////////////////////////////////////
DWORD WDAClans::GetHighestClan( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the highest possible clan ID.
// 
// Return: DWORD, the highest possible clan ID.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return dwHighestClan;
}

//////////////////////////////////////////////////////////////////////////////////////////
void WDAClans::ResetHighestClan()
{
    dwHighestClan = 0;
    int i;
    for( i = 0; i < vClans.size(); i++ ){
        if( vClans[ i ].m_ID > dwHighestClan ){
            dwHighestClan = vClans[ i ].m_ID;
        }
    }
}
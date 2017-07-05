// WDASpellEffects.cpp: implementation of the WDASpellEffects class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDASpellEffects.h"
#include "Format.h"

using namespace vir;
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDASpellEffects::WDASpellEffects( Logger &cLogger, DEBUG_LEVEL dlMapDebugHigh ) : WDATable( cLogger )
{
    MapDebugHighLogLevel( dlMapDebugHigh );
}

WDASpellEffects::~WDASpellEffects()
{

}

// Accessors
//////////////////////////////////////////////////////////////////////////////////////////
DWORD WDASpellEffects::GetEffectStructureID( void )
//////////////////////////////////////////////////////////////////////////////////////////
// The ID of the effect structure.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return dwEffectStructureID;
}

//////////////////////////////////////////////////////////////////////////////////////////
vector< WDASpellEffectParameters > &WDASpellEffects::GetParams( void )
//////////////////////////////////////////////////////////////////////////////////////////
// The spell effect parameters.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vParams;
}

// Load/save
//////////////////////////////////////////////////////////////////////////////////////////
void WDASpellEffects::SaveTo
//////////////////////////////////////////////////////////////////////////////////////////
// Saves to a wdaFile
// 
(
 WDAFile &wdaFile // The wdaFile
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Save the effect structure ID
    wdaFile.Write( dwEffectStructureID );

    TFormat cFormat;
    cOutput.Log(
        dlDebugHigh,
        cFormat(
            "\n  Wrote Effect %u: ",
            dwEffectStructureID
        )
    );

    // Save the quantity of effect parameters.
    wdaFile.Write( (DWORD)vParams.size() );
    
    // Scroll through all parameters
    vector< WDASpellEffectParameters >::iterator i;
    for( i = vParams.begin(); i != vParams.end(); i++ ){
        // Save the spell parameter.
        (*i).SaveTo( wdaFile );
    }
}
    
    
//////////////////////////////////////////////////////////////////////////////////////////
void WDASpellEffects::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Creates from a wdaFile.
// 
(
 WDAFile &wdaFile, // The wdaFile
 bool createReadOnly
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Load the effect structure ID
    wdaFile.Read( dwEffectStructureID );

    TFormat cFormat;
    cOutput.Log(
        dlDebugHigh,
        cFormat(
            "\n  Effect %u: ",
            dwEffectStructureID
        )
    );

    DWORD dwSize = 0xABCDEF;

    // Get the quantity of effect parameters.
    wdaFile.Read( dwSize );

    // Scroll through all found parameters.
    DWORD i;
    for( i = 0; i < dwSize; i++ ){
        // Load the spell effect parameter
        WDASpellEffectParameters cParam( cOutput, dlDebugHigh );
        cParam.CreateFrom( wdaFile, createReadOnly );
        
        // Add the spell effect parameter to the list of parameters.
        vParams.push_back( cParam );
    }

}

//////////////////////////////////////////////////////////////////////////////////////////
bool WDASpellEffects::operator == (const WDASpellEffects &l )
{
    if( dwEffectStructureID != l.dwEffectStructureID ){
        return false;
    }

    if( vParams.size() != l.vParams.size() ){
        return false;
    }

    int i;
    for( i = 0; i < vParams.size(); i++ ){
        if( !( vParams[ i ] == l.vParams[ i ] ) ){
            return false;
        }
    }
    return true;
}

#ifndef NO_DAO_SUPPORT
//////////////////////////////////////////////////////////////////////////////////////////
void WDASpellEffects::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Loads the worlds from a DAO support    
// 
(
 CDaoRecordset &cRecord, // The sole record where the effect is.
 CDaoDatabase &cDatabase // The database.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    ASSERT( !cRecord.IsEOF() );
    // If no record was provided.
    if( cRecord.IsEOF() ){
        return;
    }
    
    COleVariant oleData;
    DWORD dwSpellEffectID;
    TFormat cFormat;

    // Fetch the effect's value.
    cRecord.GetFieldValue( "ID", oleData );
    dwSpellEffectID = V_I4( &oleData );

    cRecord.GetFieldValue( "EffectID", oleData );
    dwEffectStructureID = V_I4( &oleData );
  
    cOutput.Log(
        dlDebugHigh,
        cFormat(
            "\n  Effect %u: ",
            dwEffectStructureID
        )
    );
    
    // Open a new recordset to fetch the effects parameters.
    CDaoRecordset recParams( &cDatabase );
    
    recParams.Open(
        dbOpenSnapshot,
        cFormat( 
            "SELECT * FROM SpellEffectsParameters WHERE SpellEffectID=%u",
            dwSpellEffectID
        )
    );

    // If there are effect parameters.
    if( !recParams.IsEOF() ){
        // Scroll through all the found parameters.
        recParams.MoveFirst();
        while( !recParams.IsEOF() ){
            // Create a new SpellEffectParameter
            WDASpellEffectParameters cParam( cOutput, dlDebugHigh );

            // Create the spell effect parameters from this record.
            cParam.CreateFrom( recParams, cDatabase );

            // Add it to the vector of spell parameters.
            vParams.push_back( cParam );

            recParams.MoveNext();
        }
    }else{
        cOutput.Log(
            dlDebugHigh,
            "\nWARNING: Spell effect doesn't have any parameter."
        );
    }
}

#endif

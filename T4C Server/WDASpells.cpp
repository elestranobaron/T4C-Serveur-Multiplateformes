// WDASpells.cpp: implementation of the WDASpells class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDASpells.h"
#include "Format.h"
#include <map>

using namespace vir;
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDASpells::WDASpells( Logger &cLogger ) : WDATable( cLogger )
{

}

WDASpells::~WDASpells()
{

}


// Accessor    
//////////////////////////////////////////////////////////////////////////////////////////
std::vector< WDASpells::SpellData > &WDASpells::GetSpells( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns all the spells.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vSpells;
}

//////////////////////////////////////////////////////////////////////////////////////////
void WDASpells::SaveTo
//////////////////////////////////////////////////////////////////////////////////////////
// Saves to a wdaFile
// 
(
 WDAFile &wdaFile // the wdaFile
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nWritting spells."
        "\n"
    );
    
    DWORD savedSpellsSize = 0;
    vector< SpellData >::iterator i;
    
    for( i = vSpells.begin(); i != vSpells.end(); i++ ){
        if( !(*i).m_ReadOnly ){
            savedSpellsSize++;
        }
    }
    
    // Saves the quantity of spells.
    wdaFile.Write( savedSpellsSize );

    // Scroll through each spells.    
    for( i = vSpells.begin(); i != vSpells.end(); i++ ){
        SpellData &cSpell = (*i);        

        if( cSpell.m_ReadOnly ){
            continue;
        }
        
        TFormat cFormat;
        cOutput.Log(
            dlDebug,
            cFormat(
                "\nWriting spell %s (%u)",
                cSpell.csName.c_str(),
                cSpell.dwSpellID
            )
        );

        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\n  Mental exhaust: %s."
                "\n  MoveExhaust: %s"
                "\n  AttackExhaust: %s"
                "\n  Duration: %s"
                "\n  TimerFrequency: %s"
                "\n  Element: %u"
                "\n  ManaCost: %s"
                "\n  AreaRange: %u"
                "\n  VisualEffect: %u"
                "\n  TargetType: %u"
                "\n  AttackType: %u"
                "\n  MinWis: %u"
                "\n  MinInt: %u"
                "\n  MinLevel: %u"
                "\n  LineOfSight: %s"
                "\n  PVPcheck: %s",
                cSpell.csMentalExhaust.c_str(),
                cSpell.csMoveExhaust.c_str(),
                cSpell.csAttackExhaust.c_str(),
                cSpell.bsDuration.c_str(),
                cSpell.bsTimerFrequency.c_str(),
                cSpell.dwElement,
                cSpell.bsManaCost.c_str(),
                cSpell.dwAreaRange,
                cSpell.dwVisualEffect,
                cSpell.dwTargetType,
                cSpell.dwAttackType,
                cSpell.dwMinWis,
                cSpell.dwMinInt,
                cSpell.dwMinLevel,
                cSpell.boLineOfSight ? "true" : "false",
                cSpell.boPVPcheck ? "true" : "false"
            )
        );

        // Write the spell data.
        wdaFile.Write( cSpell.dwSpellID );
        wdaFile.Write( cSpell.csName );
        wdaFile.Write( cSpell.csMentalExhaust );
        wdaFile.Write( cSpell.csMoveExhaust );
        wdaFile.Write( cSpell.csAttackExhaust );
        wdaFile.Write( cSpell.bsDuration );
        wdaFile.Write( cSpell.bsTimerFrequency );
        wdaFile.Write( cSpell.dwElement );
        wdaFile.Write( cSpell.bsManaCost );
        wdaFile.Write( cSpell.dwAreaRange );
        wdaFile.Write( cSpell.dwVisualEffect );
        wdaFile.Write( cSpell.dwRangeVisualEffect );
        wdaFile.Write( cSpell.dwTargetType );
        wdaFile.Write( cSpell.dwAttackType );
        wdaFile.Write( cSpell.dwMinWis );
        wdaFile.Write( cSpell.dwMinInt );
        wdaFile.Write( cSpell.dwMinLevel );
        wdaFile.Write( cSpell.boLineOfSight );
        wdaFile.Write( cSpell.boPVPcheck );
        wdaFile.Write( cSpell.boAttackSpell );
        wdaFile.Write( cSpell.dwIcon );
        wdaFile.Write( cSpell.csSuccessPercentage );
        wdaFile.Write( cSpell.csDesc );        

        // Spell effects.
        {
            // Write the quantity of spell effects.
            wdaFile.Write( (DWORD)cSpell.vSpellEffects.size() );

            // Scroll through all the spell effects.        
            vector< WDASpellEffects >::iterator j;
            for( j = cSpell.vSpellEffects.begin(); j != cSpell.vSpellEffects.end(); j++ ){
                // Save the spell effect.
                (*j).SaveTo( wdaFile );
            }
        }
        // Spell requirements.
        {
            // Write the quantity of spell requirements.
            wdaFile.Write( (DWORD)cSpell.vSpellRequirements.size() );
            
            // Scroll through all the spell reqs.
            vector< WDASpellRequirements >::iterator j;
            for( j = cSpell.vSpellRequirements.begin(); j != cSpell.vSpellRequirements.end(); j++){
                (*j).SaveTo( wdaFile );
            }
        }
    } 
}
    
//////////////////////////////////////////////////////////////////////////////////////////
void WDASpells::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Creates from a wdaFile.
// 
(
 WDAFile &wdaFile, // the wdaFile
 bool createReadOnly
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD dwSize = 0xABCDEF;

    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nLoading spells."
        "\n"
    );    

    // Read the quantity of spells.
    wdaFile.Read( dwSize );

    // Load all saved spells.
    DWORD i;
    for( i = 0; i < dwSize; i++ ){
        SpellData cSpell;
        
        // Write the spell data.
        wdaFile.Read( cSpell.dwSpellID );
        wdaFile.Read( cSpell.csName );
        wdaFile.Read( cSpell.csMentalExhaust );
        wdaFile.Read( cSpell.csMoveExhaust );
        wdaFile.Read( cSpell.csAttackExhaust );
        wdaFile.Read( cSpell.bsDuration );
        wdaFile.Read( cSpell.bsTimerFrequency );
        wdaFile.Read( cSpell.dwElement );
        wdaFile.Read( cSpell.bsManaCost );
        wdaFile.Read( cSpell.dwAreaRange );
        wdaFile.Read( cSpell.dwVisualEffect );
        wdaFile.Read( cSpell.dwRangeVisualEffect );
        wdaFile.Read( cSpell.dwTargetType );
        wdaFile.Read( cSpell.dwAttackType );
        wdaFile.Read( cSpell.dwMinWis );
        wdaFile.Read( cSpell.dwMinInt );
        wdaFile.Read( cSpell.dwMinLevel );
        wdaFile.Read( cSpell.boLineOfSight );
        wdaFile.Read( cSpell.boPVPcheck );
        wdaFile.Read( cSpell.boAttackSpell );
        wdaFile.Read( cSpell.dwIcon );
        wdaFile.Read( cSpell.csSuccessPercentage );
        wdaFile.Read( cSpell.csDesc );

        cSpell.csName = GetBareString( cSpell.csName );
        cSpell.csDesc = GetBareString( cSpell.csDesc );

        TFormat cFormat;
        cOutput.Log(
            dlDebug,
            cFormat(
                "\nFound spell %s (%u)",
                cSpell.csName.c_str(),
                cSpell.dwSpellID
            )
        );

        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\n  Mental exhaust: %s."
                "\n  MoveExhaust: %s"
                "\n  AttackExhaust: %s"
                "\n  Duration: %s"
                "\n  TimerFrequency: %s"
                "\n  Element: %u"
                "\n  ManaCost: %s"
                "\n  AreaRange: %u"
                "\n  VisualEffect: %u"
                "\n  TargetType: %u"
                "\n  AttackType: %u"
                "\n  MinWis: %u"
                "\n  MinInt: %u"
                "\n  MinLevel: %u"
                "\n  LineOfSight: %s"
                "\n  PVPcheck: %s",
                cSpell.csMentalExhaust.c_str(),
                cSpell.csMoveExhaust.c_str(),
                cSpell.csAttackExhaust.c_str(),
                cSpell.bsDuration.c_str(),
                cSpell.bsTimerFrequency.c_str(),
                cSpell.dwElement,
                cSpell.bsManaCost.c_str(),
                cSpell.dwAreaRange,
                cSpell.dwVisualEffect,
                cSpell.dwTargetType,
                cSpell.dwAttackType,
                cSpell.dwMinWis,
                cSpell.dwMinInt,
                cSpell.dwMinLevel,
                cSpell.boLineOfSight ? "true" : "false",
                cSpell.boPVPcheck ? "true" : "false"
            )
        );
        
        // Spell effects.
        {
            // Read the quantity of spell effects.
            DWORD dwQ;

            wdaFile.Read( dwQ );
            DWORD j;
            for( j = 0; j < dwQ; j++ ){
                // Create the spell effects.
                WDASpellEffects cSpellEffects( cOutput, dlDebugHigh );
                cSpellEffects.CreateFrom( wdaFile, createReadOnly );
                // Add this spell effect to the list of spell effects.
                cSpell.vSpellEffects.push_back( cSpellEffects );
            }
        }
        // Spell requirements.
        {
            // Read the quantity of spell reqs.
            DWORD dwQ;

            wdaFile.Read( dwQ );
            DWORD j;
            for( j = 0; j < dwQ; j++ ){
                // Create the spell req.
                WDASpellRequirements cSpellReq( cOutput, dlDebugHigh );
                cSpellReq.CreateFrom( wdaFile, createReadOnly );
                // Add this spell req to the list of spell reqs.
                cSpell.vSpellRequirements.push_back( cSpellReq );
            }
        }

        cSpell.m_ReadOnly = createReadOnly;
        // Add the spell to the list of spells.
        vSpells.push_back( cSpell );
    }
}
#ifndef NO_DAO_SUPPORT    
    
//////////////////////////////////////////////////////////////////////////////////////////
void WDASpells::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Loads the worlds from a DAO support    
// 
(
 CDaoRecordset &cRecord, // The spells recordset.
 CDaoDatabase &cDatabase // The database.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- DAO -----"
        "\nLoading spells."
        "\n"
    );

    map< DWORD, DWORD > spellMap;
    
    // Loads all spells from the recordset.
    cRecord.MoveFirst();

    TFormat cFormat;
    // Scroll while there are spells.
    while( !cRecord.IsEOF() ){        
        COleVariant oleData;

        SpellData cSpell;

        // Fetch the spell's data.
        cRecord.GetFieldValue( "ID", oleData );
        cSpell.dwSpellID = V_I4( &oleData );

        cRecord.GetFieldValue( "Name", oleData );
        cSpell.csName = V_BSTRT( &oleData );
        
        cRecord.GetFieldValue( "MentalExhaust", oleData );
        cSpell.csMentalExhaust = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "MovementExhaust", oleData );
        cSpell.csMoveExhaust = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "AttackExhaust", oleData );
        cSpell.csAttackExhaust = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "Duration", oleData );
        cSpell.bsDuration = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "TimerFrequency", oleData );
        cSpell.bsTimerFrequency = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "Element", oleData );
        cSpell.dwElement = V_I4( &oleData );        

        cRecord.GetFieldValue( "ManaCost", oleData );
        cSpell.bsManaCost = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "AreaRange", oleData );
        cSpell.dwAreaRange = V_I4( &oleData );

        cRecord.GetFieldValue( "VisualEffect", oleData );
        cSpell.dwVisualEffect = V_I4( &oleData );

        cRecord.GetFieldValue( "RangeVisualEffect", oleData );
        cSpell.dwRangeVisualEffect = V_I4( &oleData );

        cRecord.GetFieldValue( "TargetType", oleData );
        cSpell.dwTargetType = V_I4( &oleData );

        cRecord.GetFieldValue( "AttackType", oleData );
        cSpell.dwAttackType = V_I4( &oleData );

        cRecord.GetFieldValue( "MinWis", oleData );
        cSpell.dwMinWis = V_I4( &oleData );

        cRecord.GetFieldValue( "MinInt", oleData );
        cSpell.dwMinInt = V_I4( &oleData );

        cRecord.GetFieldValue( "MinLevel", oleData );
        cSpell.dwMinLevel = V_I2( &oleData );
    
        cRecord.GetFieldValue( "LineOfSight", oleData );
        cSpell.boLineOfSight = V_I4( &oleData ) != 0 ? true : false;

        cRecord.GetFieldValue( "PVPcheck", oleData );
        cSpell.boPVPcheck = V_I4( &oleData ) != 0 ? true : false;

        cRecord.GetFieldValue( "AttackSpell", oleData );
        cSpell.boAttackSpell = V_I4( &oleData ) != 0 ? true : false;

        cRecord.GetFieldValue( "Icon", oleData );
        cSpell.dwIcon = V_I4( &oleData );

        cRecord.GetFieldValue( "SuccessPercentage", oleData );
        cSpell.csSuccessPercentage = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "DescText", oleData );
        cSpell.csDesc = V_BSTRT( &oleData );
        
        cOutput.Log(
            dlDebug,
            cFormat(
                "\nFound spell %s (%u)",
                cSpell.csName.c_str(),
                cSpell.dwSpellID
            )
        );

        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\n  Mental exhaust: %s."
                "\n  MoveExhaust: %s"
                "\n  AttackExhaust: %s"
                "\n  Duration: %s"
                "\n  TimerFrequency: %s"
                "\n  Element: %u"
                "\n  ManaCost: %s"
                "\n  AreaRange: %u"
                "\n  VisualEffect: %u"
                "\n  TargetType: %u"
                "\n  AttackType: %u"
                "\n  MinWis: %u"
                "\n  MinInt: %u"
                "\n  MinLevel: %u"
                "\n  LineOfSight: %s"
                "\n  PVPcheck: %s",
                cSpell.csMentalExhaust.c_str(),
                cSpell.csMoveExhaust.c_str(),
                cSpell.csAttackExhaust.c_str(),
                cSpell.bsDuration.c_str(),
                cSpell.bsTimerFrequency.c_str(),
                cSpell.dwElement,
                cSpell.bsManaCost.c_str(),
                cSpell.dwAreaRange,
                cSpell.dwVisualEffect,
                cSpell.dwTargetType,
                cSpell.dwAttackType,
                cSpell.dwMinWis,
                cSpell.dwMinInt,
                cSpell.dwMinLevel,
                cSpell.boLineOfSight ? "true" : "false",
                cSpell.boPVPcheck ? "true" : "false"
            )
        );

        vSpells.push_back( cSpell );

        // Save the last index.
        spellMap[ cSpell.dwSpellID ] = vSpells.size() - 1;

        cRecord.MoveNext();
    }
    // Load the spell effects for this spell.
    {
        CDaoRecordset recSpellEffects( &cDatabase );

        recSpellEffects.Open( dbOpenSnapshot, "SELECT * FROM SpellEffects" );
        
        // If there are spell effects.
        if( !recSpellEffects.IsEOF() ){
            for( recSpellEffects.MoveFirst(); !recSpellEffects.IsEOF(); recSpellEffects.MoveNext() ){
                COleVariant oleData;
                recSpellEffects.GetFieldValue( "SpellID", oleData );
                DWORD spellID = V_I4( &oleData );                

                // Find the associated spell.
                map< DWORD, DWORD >::iterator j;
                j = spellMap.find( spellID );
                if( j == spellMap.end() ){
                    continue;
                }

                if( spellID != vSpells[ (*j).second ].dwSpellID ){
                    cOutput.Log(
                        dlDebug,
                        cFormat(
                            "\nError1 loading effects for spell %u",
                            spellID
                        )
                    );
                }
            
                WDASpellEffects cSpellEffects( cOutput, dlDebugHigh );
                
                // Create the spell effects from this record.
                cSpellEffects.CreateFrom( recSpellEffects, cDatabase );
    
                // Add the spell effect to the spell.
                vSpells[ (*j).second ].vSpellEffects.push_back( cSpellEffects );
            };
            recSpellEffects.Close();
        }
    }
    
    // Load the spell requirements for this spell.
    {
        CDaoRecordset recReq( &cDatabase );

        recReq.Open( dbOpenSnapshot, "SELECT * FROM SpellRequirements" );

        if( !recReq.IsEOF() ){
            for( recReq.MoveFirst(); !recReq.IsEOF(); recReq.MoveNext() ){
                COleVariant oleData;
                recReq.GetFieldValue( "SpellID", oleData );
                DWORD spellID = V_I4( &oleData );                

                // Find the associated spell.
                map< DWORD, DWORD >::iterator j;
                j = spellMap.find( spellID );
                if( j == spellMap.end() ){
                    continue;
                }

                if( spellID != vSpells[ (*j).second ].dwSpellID ){
                    cOutput.Log(
                        dlDebug,
                        cFormat(
                            "\nError2 loading requirement for spell %u",
                            spellID
                        )
                    );
                }

                WDASpellRequirements cReq( cOutput, dlDebugHigh );

                // Create the spell requirements from this record.
                cReq.CreateFrom( recReq, cDatabase );
               
                // Add the requriement to the vector of requirements.
                vSpells[ (*j).second ].vSpellRequirements.push_back( cReq );
            }
            recReq.Close();
        }        
    }

}
#endif

//////////////////////////////////////////////////////////////////////////////////////////
WDASpells::SpellData *WDASpells::GetSpell( DWORD spellID )
{
    int i;
    for( i = 0; i < vSpells.size(); i++ ){
        if( vSpells[ i ].dwSpellID == spellID ){
            return &vSpells[ i ];
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
DWORD WDASpells::GetNextSpellID()
{
    DWORD highestSpellID = 10000;

    int i;
    for( i = 0; i < vSpells.size(); i++ ){
        if( vSpells[ i ].dwSpellID >= highestSpellID ){
            highestSpellID = vSpells[ i ].dwSpellID + 1;            
        }
    }
    return highestSpellID;
}
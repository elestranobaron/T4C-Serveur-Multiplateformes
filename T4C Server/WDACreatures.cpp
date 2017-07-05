// WDACreatures.cpp: implementation of the WDACreatures class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDACreatures.h"
#include "format.h"
#include <map>

using namespace vir;
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDACreatures::WDACreatures( vir::Logger &cOutputLogger ) : WDATable( cOutputLogger )
{

}

WDACreatures::~WDACreatures()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
std::vector< WDACreatures::CreatureData > &WDACreatures::GetCreatures( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns a vector of creature data.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vCreatures;
}

//////////////////////////////////////////////////////////////////////////////////////////
void WDACreatures::SaveTo
//////////////////////////////////////////////////////////////////////////////////////////
// Saves to a wdaFile
// 
(
 WDAFile &wdaFile // The WDA file to save to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nWriting creatures."
        "\n"
    );

    DWORD savedCreaturesSize = 0;
    vector< CreatureData >::iterator i;
    for( i = vCreatures.begin(); i != vCreatures.end(); i++ ){
        if( !(*i).m_ReadOnly ){
            savedCreaturesSize++;
        }
    }
    
    // Save the quantity of creatures.
    wdaFile.Write( savedCreaturesSize );

    // Scroll through the list of objects.
    for( i = vCreatures.begin(); i != vCreatures.end(); i++ ){
        CreatureData &cCreature = *i;

        if( cCreature.m_ReadOnly ){
            continue;
        }

        wdaFile.Write( cCreature.dwBindedID );
        wdaFile.Write( cCreature.csID );
        wdaFile.Write( cCreature.csName );
        wdaFile.Write( cCreature.dwSTR );
        wdaFile.Write( cCreature.dwEND );
        wdaFile.Write( cCreature.dwAGI );
        wdaFile.Write( cCreature.dwINT );
        wdaFile.Write( cCreature.dwWIL );
        wdaFile.Write( cCreature.dwWIS );        
        wdaFile.Write( cCreature.dwLCK );
        wdaFile.Write( cCreature.dwAirResist );
        wdaFile.Write( cCreature.dwEarthResist );
        wdaFile.Write( cCreature.dwWaterResist );
        wdaFile.Write( cCreature.dwFireResist );
        wdaFile.Write( cCreature.dwDarkResist );
        wdaFile.Write( cCreature.dwLightResist );
        wdaFile.Write( cCreature.dwAirPower );
        wdaFile.Write( cCreature.dwEarthPower );
        wdaFile.Write( cCreature.dwWaterPower );
        wdaFile.Write( cCreature.dwFirePower );
        wdaFile.Write( cCreature.dwDarkPower );
        wdaFile.Write( cCreature.dwLightPower );
        wdaFile.Write( cCreature.dwLevel );
        wdaFile.Write( cCreature.dwHP );
        wdaFile.Write( cCreature.dwDodgeSkill );
        wdaFile.Write( cCreature.dblAC );
        wdaFile.Write( cCreature.dwAppearance );
        wdaFile.Write( cCreature.dwDressBody );
        wdaFile.Write( cCreature.dwDressFeet );
        wdaFile.Write( cCreature.dwDressGloves );
        wdaFile.Write( cCreature.dwDressHelm );
        wdaFile.Write( cCreature.dwDressLegs );
        wdaFile.Write( cCreature.dwDressWeapon );
        wdaFile.Write( cCreature.dwDressShield );
        wdaFile.Write( cCreature.dwDressCape );
        wdaFile.Write( cCreature.dwAggressivness );
        wdaFile.Write( cCreature.dwClanID );
        wdaFile.Write( cCreature.dwSpeed );
        wdaFile.Write( cCreature.dblXPperHit );
        wdaFile.Write( cCreature.dblXPperDeath );
        wdaFile.Write( cCreature.dwMinGiveGold );
        wdaFile.Write( cCreature.dwMaxGiveGold );
        wdaFile.Write( cCreature.boCanAttack );             

        // Save attacks.
        {
            wdaFile.Write( (DWORD)cCreature.vAttacks.size() );
            
            vector< CreatureAttack >::iterator i;
            for( i = cCreature.vAttacks.begin(); i != cCreature.vAttacks.end(); i++ ){
                CreatureAttack &cAttack = *i;

                wdaFile.Write( cAttack.csDmgRoll );
                wdaFile.Write( cAttack.dwAttackSkill );
                wdaFile.Write( cAttack.dwAttackPercentage );
                wdaFile.Write( cAttack.dwAttackSpell );
                wdaFile.Write( cAttack.dwAttackMinRange );
                wdaFile.Write( cAttack.dwAttackMaxRange );
            }
        }
        // Save death flags.
        {
            wdaFile.Write( (DWORD)cCreature.vDeathFlags.size() );
            
            vector< CreatureDeathFlag >::iterator i;
            for( i = cCreature.vDeathFlags.begin(); i != cCreature.vDeathFlags.end(); i++ ){
                CreatureDeathFlag &cFlag = *i;

                wdaFile.Write( cFlag.dwFlag );
                wdaFile.Write( cFlag.dwFlagValue );
                wdaFile.Write( cFlag.boIncrement );
            }
        }
        // Save items
        {
            wdaFile.Write( (DWORD)cCreature.vItems.size() );
            
            vector< CreatureDeathItem >::iterator i;
            for( i = cCreature.vItems.begin(); i != cCreature.vItems.end(); i++ ){
                CreatureDeathItem &cItem = *i;
                
                wdaFile.Write( cItem.dwItemID );
                wdaFile.Write( cItem.dblDropPercentage );
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void WDACreatures::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Creates from a wdaFile.
// 
(
 WDAFile &wdaFile, // The WDA file to save to.
 bool createReadOnly
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    cOutput.Log(
        dlInfo,
        "\n----- WDA -----"
        "\nLoading objects."
        "\n"
    );

    
    // Get the quantity of objects
    DWORD dwSize;
    wdaFile.Read( dwSize );
       
    // Scroll through the list of objects.
    DWORD i;
    for( i = 0; i != dwSize; i++ ){
        CreatureData cCreature;

        wdaFile.Read( cCreature.dwBindedID );
        wdaFile.Read( cCreature.csID );
        wdaFile.Read( cCreature.csName );
        wdaFile.Read( cCreature.dwSTR );
        wdaFile.Read( cCreature.dwEND );
        wdaFile.Read( cCreature.dwAGI );
        wdaFile.Read( cCreature.dwINT );
        wdaFile.Read( cCreature.dwWIL );
        wdaFile.Read( cCreature.dwWIS );        
        wdaFile.Read( cCreature.dwLCK );
        wdaFile.Read( cCreature.dwAirResist );
        wdaFile.Read( cCreature.dwEarthResist );
        wdaFile.Read( cCreature.dwWaterResist );
        wdaFile.Read( cCreature.dwFireResist );
        wdaFile.Read( cCreature.dwDarkResist );
        wdaFile.Read( cCreature.dwLightResist );
        wdaFile.Read( cCreature.dwAirPower );
        wdaFile.Read( cCreature.dwEarthPower );
        wdaFile.Read( cCreature.dwWaterPower );
        wdaFile.Read( cCreature.dwFirePower );
        wdaFile.Read( cCreature.dwDarkPower );
        wdaFile.Read( cCreature.dwLightPower );
        wdaFile.Read( cCreature.dwLevel );
        wdaFile.Read( cCreature.dwHP );
        wdaFile.Read( cCreature.dwDodgeSkill );
        wdaFile.Read( cCreature.dblAC );
        wdaFile.Read( cCreature.dwAppearance );
        wdaFile.Read( cCreature.dwDressBody );
        wdaFile.Read( cCreature.dwDressFeet );
        wdaFile.Read( cCreature.dwDressGloves );
        wdaFile.Read( cCreature.dwDressHelm );
        wdaFile.Read( cCreature.dwDressLegs );
        wdaFile.Read( cCreature.dwDressWeapon );
        wdaFile.Read( cCreature.dwDressShield );
        wdaFile.Read( cCreature.dwDressCape );
        wdaFile.Read( cCreature.dwAggressivness );
        wdaFile.Read( cCreature.dwClanID );
        wdaFile.Read( cCreature.dwSpeed );
        wdaFile.Read( cCreature.dblXPperHit );
        wdaFile.Read( cCreature.dblXPperDeath );
        wdaFile.Read( cCreature.dwMinGiveGold );
        wdaFile.Read( cCreature.dwMaxGiveGold );
        wdaFile.Read( cCreature.boCanAttack );

        cCreature.csName = GetBareString( cCreature.csName );

        // Load attacks.
        {
            DWORD dwSize;
            wdaFile.Read( dwSize );            
            DWORD i;
            for( i = 0; i != dwSize; i++ ){
                CreatureAttack cAttack;

                wdaFile.Read( cAttack.csDmgRoll );
                wdaFile.Read( cAttack.dwAttackSkill );
                wdaFile.Read( cAttack.dwAttackPercentage );
                wdaFile.Read( cAttack.dwAttackSpell );
                wdaFile.Read( cAttack.dwAttackMinRange );
                wdaFile.Read( cAttack.dwAttackMaxRange );

                cCreature.vAttacks.push_back( cAttack );
            }
        }
        // Save death flags.
        {
            DWORD dwSize;
            wdaFile.Read( dwSize );            
            DWORD i;
            for( i = 0; i != dwSize; i++ ){
                CreatureDeathFlag cFlag;

                wdaFile.Read( cFlag.dwFlag );
                wdaFile.Read( cFlag.dwFlagValue );
                wdaFile.Read( cFlag.boIncrement );

                cCreature.vDeathFlags.push_back( cFlag );
            }
        }
        // Save items
        {
            DWORD dwSize;
            wdaFile.Read( dwSize );            
            DWORD i;
            for( i = 0; i != dwSize; i++ ){
                CreatureDeathItem cItem;
                
                wdaFile.Read( cItem.dwItemID );
                wdaFile.Read( cItem.dblDropPercentage );

                cCreature.vItems.push_back( cItem );
            }
        }

        cCreature.m_ReadOnly = createReadOnly;

        vCreatures.push_back( cCreature );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
WDACreatures::CreatureData *WDACreatures::GetReadOnlyCreature( std::string id )
{
    int i;
    for( i = 0; i < vCreatures.size(); i++ ){
        if( vCreatures[ i ].m_ReadOnly && stricmp( vCreatures[ i ].csID.c_str(), id.c_str() ) == 0 ){
            return &vCreatures[ i ];
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
WDACreatures::CreatureData *WDACreatures::GetWritableCreature( std::string id )
{
    int i;
    for( i = 0; i < vCreatures.size(); i++ ){
        if( !vCreatures[ i ].m_ReadOnly && stricmp( vCreatures[ i ].csID.c_str(), id.c_str() ) == 0 ){
            return &vCreatures[ i ];
        }
    }
    return NULL;
}

#ifndef NO_DAO_SUPPORT        
//////////////////////////////////////////////////////////////////////////////////////////
void WDACreatures::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Create from DAO database.
// 
(
 CDaoRecordset &cRecord, // The recordset.
 CDaoDatabase &cDatabase // The database.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // This function should not get an empty recordset!
    ASSERT( !cRecord.IsEOF() );

    if( cRecord.IsEOF() ){
        return;
    }

    cOutput.Log(
        dlInfo,
        "\n----- DAO -----"
        "\nLoading creatures."
        "\n"
    );

    map< DWORD, DWORD > creMap;

    // Scroll through all objects in the recordset
    cRecord.MoveFirst();
    while( !cRecord.IsEOF() ){
        COleVariant oleData;

        TFormat cFormat;

        CreatureData cCreature;

        cRecord.GetFieldValue( "BindedID", oleData );
        cCreature.dwBindedID = V_I4( &oleData );
        
        cRecord.GetFieldValue( "CreatureID", oleData );
        cCreature.csID = V_BSTRT( &oleData );
        
        cRecord.GetFieldValue( "Name", oleData );
        cCreature.csName = V_BSTRT( &oleData );
        
        cRecord.GetFieldValue( "STR", oleData );
        cCreature.dwSTR = V_I4( &oleData );
        
        cRecord.GetFieldValue( "END", oleData );
        cCreature.dwEND = V_I4( &oleData );
        
        cRecord.GetFieldValue( "AGI", oleData );
        cCreature.dwAGI = V_I4( &oleData );
        
        cRecord.GetFieldValue( "INTELL", oleData );
        cCreature.dwINT = V_I4( &oleData );
        
        cRecord.GetFieldValue( "WIS", oleData );
        cCreature.dwWIS = V_I4( &oleData );
        
        cRecord.GetFieldValue( "AirResist", oleData );
        cCreature.dwAirResist = V_I4( &oleData );
        
        cRecord.GetFieldValue( "EarthResist", oleData );
        cCreature.dwEarthResist = V_I4( &oleData );
        
        cRecord.GetFieldValue( "WaterResist", oleData );
        cCreature.dwWaterResist = V_I4( &oleData );
        
        cRecord.GetFieldValue( "FireResist", oleData );
        cCreature.dwFireResist = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DarkResist", oleData );
        cCreature.dwDarkResist = V_I4( &oleData );
        
        cRecord.GetFieldValue( "LightResist", oleData );
        cCreature.dwLightResist = V_I4( &oleData );
        
        cRecord.GetFieldValue( "AirPower", oleData );
        cCreature.dwAirPower = V_I4( &oleData );
        
        cRecord.GetFieldValue( "EarthPower", oleData );
        cCreature.dwEarthPower = V_I4( &oleData );
        
        cRecord.GetFieldValue( "WaterPower", oleData );
        cCreature.dwWaterPower = V_I4( &oleData );
        
        cRecord.GetFieldValue( "FirePower", oleData );
        cCreature.dwFirePower = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DarkPower", oleData );
        cCreature.dwDarkPower = V_I4( &oleData );
        
        cRecord.GetFieldValue( "LightPower", oleData );
        cCreature.dwLightPower = V_I4( &oleData );
        
        cRecord.GetFieldValue( "LVL", oleData );
        cCreature.dwLevel = V_I4( &oleData );
        
        cRecord.GetFieldValue( "HP", oleData );
        cCreature.dwHP = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DodgeSkill", oleData );
        cCreature.dwDodgeSkill = V_I4( &oleData );
        
        cRecord.GetFieldValue( "AC", oleData );        
        cCreature.dblAC = V_R8( &oleData );
        
        cRecord.GetFieldValue( "Appearance", oleData );
        cCreature.dwAppearance = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DressBody", oleData );
        cCreature.dwDressBody = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DressFeet", oleData );
        cCreature.dwDressFeet = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DressGloves", oleData );
        cCreature.dwDressGloves = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DressHelm", oleData );
        cCreature.dwDressHelm = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DressLegs", oleData );
        cCreature.dwDressLegs = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DressWeapon", oleData );
        cCreature.dwDressWeapon = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DressShield", oleData );
        cCreature.dwDressShield = V_I4( &oleData );
        
        cRecord.GetFieldValue( "DressCape", oleData );
        cCreature.dwDressCape = V_I4( &oleData );
        
        cRecord.GetFieldValue( "Aggressivness", oleData );
        cCreature.dwAggressivness = V_I4( &oleData );
        
        cRecord.GetFieldValue( "ClanID", oleData );
        cCreature.dwClanID = V_I4( &oleData );
        
        cRecord.GetFieldValue( "Speed", oleData );
        cCreature.dwSpeed = V_I4( &oleData );
        
        cRecord.GetFieldValue( "XPperHit", oleData );
        cCreature.dblXPperHit = V_R8( &oleData );
        
        cRecord.GetFieldValue( "XPperDeath", oleData );
        cCreature.dblXPperDeath = V_R8( &oleData );
        
        cRecord.GetFieldValue( "MinGiveGold", oleData );
        cCreature.dwMinGiveGold = V_I4( &oleData );
        
        cRecord.GetFieldValue( "MaxGiveGold", oleData );
        cCreature.dwMaxGiveGold = V_I4( &oleData );
        
        cRecord.GetFieldValue( "CanAttack", oleData );
        cCreature.boCanAttack = V_I4( &oleData ) != 0 ? true : false;


        cOutput.Log(
            dlDebug,
            cFormat(
                "\nFound creature %s.",
                cCreature.csID.c_str()
            )
        );


        // Add the object to the vector of objects
        vCreatures.push_back( cCreature );
        creMap[ cCreature.dwBindedID ] = vCreatures.size() - 1;
    
        cRecord.MoveNext();
    }// while( !cRecord.IsEOF() )

    // Load attacks
    {
        CDaoRecordset rec( &cDatabase );

        rec.Open(
            dbOpenSnapshot,
            "SELECT * FROM Creatures_Attacks"
        );

        // If the creature has attacks
        if( !rec.IsEOF() ){
            // Scroll
            for( rec.MoveFirst(); !rec.IsEOF(); rec.MoveNext() ){
                COleVariant oleData;
                rec.GetFieldValue( "CreatureID", oleData );
                DWORD creID = V_I4( &oleData );                

                // Find the associated spell.
                map< DWORD, DWORD >::iterator j;
                j = creMap.find( creID );
                if( j == creMap.end() ){
                    continue;
                }

                CreatureAttack cAttack;

                // Get the attack stats.
                rec.GetFieldValue( "DmgRoll", oleData );
                cAttack.csDmgRoll = V_BSTRT( &oleData );
                
                rec.GetFieldValue( "AttackSkill", oleData );        
                cAttack.dwAttackSkill = V_I4( &oleData );
                
                rec.GetFieldValue( "AttackPercentage", oleData );
                cAttack.dwAttackPercentage = V_R8( &oleData );
                
                rec.GetFieldValue( "AttackSpell", oleData );
                cAttack.dwAttackSpell = V_I4( &oleData );
                
                rec.GetFieldValue( "AttackMinRange", oleData );
                cAttack.dwAttackMinRange = V_I4( &oleData );

                rec.GetFieldValue( "AttackMaxRange", oleData );
                cAttack.dwAttackMaxRange = V_I4( &oleData );

                // Add it to the vector of containers.
                vCreatures[ (*j).second ].vAttacks.push_back( cAttack );
            }
        }
    }


    // Load death flags
    {
        CDaoRecordset rec( &cDatabase );

        rec.Open(
            dbOpenSnapshot,
            "SELECT * FROM Creatures_DeathFlags"
        );

        // If the creature has death flags.
        if( !rec.IsEOF() ){
            // Scroll
            rec.MoveFirst();
            while( !rec.IsEOF() ){
                COleVariant oleData;
                rec.GetFieldValue( "CreatureID", oleData );
                DWORD creID = V_I4( &oleData );                

                // Find the associated spell.
                map< DWORD, DWORD >::iterator j;
                j = creMap.find( creID );
                if( j == creMap.end() ){
                    continue;
                }

                CreatureDeathFlag cFlag;
                
                rec.GetFieldValue( "Flag", oleData );
                cFlag.dwFlag = V_I4( &oleData );

                rec.GetFieldValue( "FlagValue", oleData );
                cFlag.dwFlagValue = V_I4( &oleData );

                rec.GetFieldValue( "Increment", oleData );
                cFlag.boIncrement = V_I4( &oleData ) != 0 ? true : false;
                                    
                // Add it to the vector of containers.
                vCreatures[ (*j).second ].vDeathFlags.push_back( cFlag );
                rec.MoveNext();
            }
        }
    }

    // Load death items
    {
        CDaoRecordset rec( &cDatabase );

        rec.Open(
            dbOpenSnapshot,
            "SELECT * FROM Creatures_Items"
        );

        // If the creature has death flags.
        if( !rec.IsEOF() ){
            // Scroll
            rec.MoveFirst();
            while( !rec.IsEOF() ){
                COleVariant oleData;
                rec.GetFieldValue( "CreatureID", oleData );
                DWORD creID = V_I4( &oleData );                

                // Find the associated spell.
                map< DWORD, DWORD >::iterator j;
                j = creMap.find( creID );
                if( j == creMap.end() ){
                    continue;
                }

                CreatureDeathItem cItem;
                
                rec.GetFieldValue( "ItemID", oleData );
                cItem.dwItemID = V_I4( &oleData );
    
                rec.GetFieldValue( "DropPercentage", oleData );
                cItem.dblDropPercentage = V_R8( &oleData );
                                    
                // Add it to the vector
                vCreatures[ (*j).second ].vItems.push_back( cItem );
                rec.MoveNext();
            }
        }
    }
}
#endif
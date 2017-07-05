// WDAObjects.cpp: implementation of the WDAObjects class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDAObjects.h"
#include "Format.h"
#include <string>
#include <map>

using namespace std;
using namespace vir;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDAObjects::WDAObjects( Logger &cLogger ) : 
    WDATable( cLogger ), 
    m_NextHighestBoostID( 0 )
{

}

WDAObjects::~WDAObjects()
{

}

// Accessors
//////////////////////////////////////////////////////////////////////////////////////////
std::vector< WDAObjects::ObjectData > &WDAObjects::GetObjects( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the list of all items.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vObjects;
}
//////////////////////////////////////////////////////////////////////////////////////////
std::vector< WDAObjectsWorldObjects > &WDAObjects::GetLocations( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the list of all items scattered on the ground at load time.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return vLocations;
}
    
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjects::SaveTo
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
        "\nWriting objects."
        "\n"
    );


    DWORD savedObjectsSize = 0;
    vector< ObjectData >::iterator i;
    for( i = vObjects.begin(); i != vObjects.end(); i++ ){
        if( !(*i).m_ReadOnly ){
            savedObjectsSize++;
        }
    }

    
    // Save the quantity of objects
    wdaFile.Write( savedObjectsSize );    

    // Scroll through the list of objects.
    for( i = vObjects.begin(); i != vObjects.end(); i++ ){
        ObjectData &cObject = *i;

        if( cObject.m_ReadOnly ){
            continue;
        }
                
        // Write the object's data
        wdaFile.Write( cObject.csID );
        wdaFile.Write( cObject.dwBindedID );
        wdaFile.Write( cObject.dwStructureID );
        wdaFile.Write( cObject.csName );
        wdaFile.Write( cObject.dwAppearance );
        wdaFile.Write( cObject.dwSellType );
        wdaFile.Write( cObject.dwEquipPos );
        wdaFile.Write( cObject.dwSellPrice );
        wdaFile.Write( cObject.dwSize );
        wdaFile.Write( cObject.dblArmor_AC );
        wdaFile.Write( cObject.dwArmor_DodgeMalus );
        wdaFile.Write( cObject.dwArmor_MinEnd );
        wdaFile.Write( cObject.csWeapon_DmgRoll );
        wdaFile.Write( cObject.dwWeapon_Attack );
        wdaFile.Write( cObject.dwWeapon_Str );
        wdaFile.Write( cObject.dwWeapon_Agi );
        wdaFile.Write( cObject.csLock_KeyID );
        wdaFile.Write( cObject.dwLockDifficulty );
        wdaFile.Write( cObject.csBook_Text );
        wdaFile.Write( cObject.dwContainer_Gold );
        wdaFile.Write( cObject.dwContainer_GlobalRespawn );
        wdaFile.Write( cObject.dwContainer_UserRespawn );
        wdaFile.Write( cObject.csWeapon_Exhaust );
        wdaFile.Write( cObject.dwRadiance );
        wdaFile.Write( cObject.lCharges );
        wdaFile.Write( cObject.dwMinInt );
        wdaFile.Write( cObject.dwMinWis );
        wdaFile.Write( cObject.dwIntlID );
        wdaFile.Write( cObject.dwDropFlags );
        wdaFile.Write( cObject.boUnique );
        wdaFile.Write( cObject.csGmItemLocation );
        wdaFile.Write( cObject.boCanSummon );
        wdaFile.Write( cObject.boWeapon_Ranged );
        wdaFile.Write( cObject.boWeapon_RangedInfiniteAmmo );        

        TFormat cFormat;
        cOutput.Log(
            dlDebug,
            cFormat(
                "\nWriting item %s.",
                cObject.csID.c_str()
            )
        );
        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\n BindedID: %u"
                "\n StructureID: %u"
                "\n Name: %s"
                "\n Appearance: %u"
                "\n SellType: %u"
                "\n EquipPos: %u"
                "\n SellPrice: %u"
                "\n Size: %u"
                "\n Armor_AC: %f"
                "\n Armor_DodgeMalus: %u"
                "\n Armor_MinEnd: %u"
                "\n Weapon_DmgRoll: %s"
                "\n Weapon_Attack: %u"
                "\n Weapon_Str: %u"
                "\n Weapon_Agi: %u"
                "\n Lock_KeyID: %s"
                "\n LockDifficulty: %u"
                "\n Book_Text: %s"
                "\n Container_Gold: %u"
                "\n Container_GlobalRespawn: %u"
                "\n Container_UserRespawn: %u"
                "\n Exhaust: %s"
                "\n Radiance: %u"
                "\n Charges: %d"
                "\n MinInt: %u"
                "\n MinWis: %u"
                "\n IntlID: %u"
                "\n DropFlags: %u",
                cObject.dwBindedID,
                cObject.dwStructureID,
                cObject.csName.c_str(),
                cObject.dwAppearance,
                cObject.dwSellType,
                cObject.dwEquipPos,
                cObject.dwSellPrice,
                cObject.dwSize,
                cObject.dblArmor_AC,
                cObject.dwArmor_DodgeMalus,
                cObject.dwArmor_MinEnd,
                cObject.csWeapon_DmgRoll.c_str(),
                cObject.dwWeapon_Attack,
                cObject.dwWeapon_Str,
                cObject.dwWeapon_Agi,
                cObject.csLock_KeyID.c_str(),
                cObject.dwLockDifficulty,
                cObject.csBook_Text.c_str(),
                cObject.dwContainer_Gold,
                cObject.dwContainer_GlobalRespawn,
                cObject.dwContainer_UserRespawn,
                cObject.csWeapon_Exhaust.c_str(),
                cObject.dwRadiance,
                cObject.lCharges,
                cObject.dwMinInt,
                cObject.dwMinWis,
                cObject.dwIntlID,
                cObject.dwDropFlags
            )
        );

        // Write all containers
        {
            // Write the quantity of containers in this item
            wdaFile.Write( static_cast< DWORD >( cObject.vContainers.size() ) );

            // Scroll through all containers.
            vector< WDAObjectsContainerGroups >::iterator j;
            for( j = cObject.vContainers.begin(); j != cObject.vContainers.end(); j++ ){
                // Save the container
                (*j).SaveTo( wdaFile );
            }
        }
        // Write all attribute boosts.
        {
            // Write the quantity of attribute boosts.
            wdaFile.Write( static_cast< DWORD >( cObject.vAttrBoosts.size() ) );

            // Scroll through all attribute boosts.
            vector< WDAObjectsAttrBoosts >::iterator j;
            for( j = cObject.vAttrBoosts.begin(); j != cObject.vAttrBoosts.end(); j++ ){
                // Save the attribute boost
                (*j).SaveTo( wdaFile );
            }
        }
        // Write all spells.
        {
            // Write the quantity of spells.
            wdaFile.Write( static_cast< DWORD >( cObject.vSpells.size() ) );

            // Scroll through all spells.
            vector< WDAObjectsSpells >::iterator j;
            for( j = cObject.vSpells.begin(); j != cObject.vSpells.end(); j++ ){
                // Save the spell
                (*j).SaveTo( wdaFile );
            }
        }
    }// for( vObjects ...

    // Save the world objects.
    {

        DWORD worldObjectsSize = 0;

        vector< WDAObjectsWorldObjects >::iterator j;
        for( j = vLocations.begin(); j != vLocations.end(); j++ ){
            if( !(*j).IsReadOnly() ){
                worldObjectsSize++;
            }
        }

        wdaFile.Write( worldObjectsSize );
        
        for( j = vLocations.begin(); j != vLocations.end(); j++ ){
            if( (*j).IsReadOnly() ){
                continue;
            }

            (*j).SaveTo( wdaFile );
        }
    }
}
    
 
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjects::CreateFrom
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
        "\nLoading objects."
        "\n"
    );

    
    // Get the quantity of objects
    DWORD dwSize;
    wdaFile.Read( dwSize );
       
    // Scroll through the list of objects.
    DWORD i;
    for( i = 0; i != dwSize; i++ ){
        // Create a new object.
        ObjectData cObject;
                
        // Write the object's data
        wdaFile.Read( cObject.csID );
        wdaFile.Read( cObject.dwBindedID );
        wdaFile.Read( cObject.dwStructureID );
        wdaFile.Read( cObject.csName );
        wdaFile.Read( cObject.dwAppearance );
        wdaFile.Read( cObject.dwSellType );
        wdaFile.Read( cObject.dwEquipPos );
        wdaFile.Read( cObject.dwSellPrice );
        wdaFile.Read( cObject.dwSize );
        wdaFile.Read( cObject.dblArmor_AC );
        wdaFile.Read( cObject.dwArmor_DodgeMalus );
        wdaFile.Read( cObject.dwArmor_MinEnd );
        wdaFile.Read( cObject.csWeapon_DmgRoll );
        wdaFile.Read( cObject.dwWeapon_Attack );
        wdaFile.Read( cObject.dwWeapon_Str );
        wdaFile.Read( cObject.dwWeapon_Agi );
        wdaFile.Read( cObject.csLock_KeyID );
        wdaFile.Read( cObject.dwLockDifficulty );
        wdaFile.Read( cObject.csBook_Text );
        wdaFile.Read( cObject.dwContainer_Gold );
        wdaFile.Read( cObject.dwContainer_GlobalRespawn );
        wdaFile.Read( cObject.dwContainer_UserRespawn );
        wdaFile.Read( cObject.csWeapon_Exhaust );
        wdaFile.Read( cObject.dwRadiance );
        wdaFile.Read( cObject.lCharges );
        wdaFile.Read( cObject.dwMinInt );
        wdaFile.Read( cObject.dwMinWis );
        wdaFile.Read( cObject.dwIntlID );
        wdaFile.Read( cObject.dwDropFlags );
        wdaFile.Read( cObject.boUnique );
        wdaFile.Read( cObject.csGmItemLocation );
        wdaFile.Read( cObject.boCanSummon );
        wdaFile.Read( cObject.boWeapon_Ranged );
        wdaFile.Read( cObject.boWeapon_RangedInfiniteAmmo );

        cObject.csName = GetBareString( cObject.csName );
        cObject.csBook_Text = GetBareString( cObject.csBook_Text );

        TFormat cFormat;
        cOutput.Log(
            dlDebug,
            cFormat(
                "\nFound item %s.",
                cObject.csID.c_str()
            )
        );
        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\n BindedID: %u"
                "\n StructureID: %u"
                "\n Name: %s"
                "\n Appearance: %u"
                "\n SellType: %u"
                "\n EquipPos: %u"
                "\n SellPrice: %u"
                "\n Size: %u"
                "\n Armor_AC: %f"
                "\n Armor_DodgeMalus: %u"
                "\n Armor_MinEnd: %u"
                "\n Weapon_DmgRoll: %s"
                "\n Weapon_Attack: %u"
                "\n Weapon_Str: %u"
                "\n Weapon_Agi: %u"
                "\n Lock_KeyID: %s"
                "\n LockDifficulty: %u"
                "\n Book_Text: %s"
                "\n Container_Gold: %u"
                "\n Container_GlobalRespawn: %u"
                "\n Container_UserRespawn: %u"
                "\n Exhaust: %s"
                "\n Radiance: %u"
                "\n Charges: %d"
                "\n MinInt: %u"
                "\n MinWis: %u"
                "\n IntlID: %u"
                "\n DropFlags: %u",
                cObject.dwBindedID,
                cObject.dwStructureID,
                cObject.csName.c_str(),
                cObject.dwAppearance,
                cObject.dwSellType,
                cObject.dwEquipPos,
                cObject.dwSellPrice,
                cObject.dwSize,
                cObject.dblArmor_AC,
                cObject.dwArmor_DodgeMalus,
                cObject.dwArmor_MinEnd,
                cObject.csWeapon_DmgRoll.c_str(),
                cObject.dwWeapon_Attack,
                cObject.dwWeapon_Str,
                cObject.dwWeapon_Agi,
                cObject.csLock_KeyID.c_str(),
                cObject.dwLockDifficulty,
                cObject.csBook_Text.c_str(),
                cObject.dwContainer_Gold,
                cObject.dwContainer_GlobalRespawn,
                cObject.dwContainer_UserRespawn,
                cObject.csWeapon_Exhaust.c_str(),
                cObject.dwRadiance,
                cObject.lCharges,
                cObject.dwMinInt,
                cObject.dwMinWis,
                cObject.dwIntlID,
                cObject.dwDropFlags
            )
        );

        // Load all containers
        {
            // Load the quantity of containers in this item
            DWORD dwQ;
            wdaFile.Read( dwQ );

            // Scroll through all containers.
            DWORD j;
            for( j = 0; j != dwQ; j++ ){
                // Load the container
                WDAObjectsContainerGroups cContainer( cOutput, dlDebugHigh );
                cContainer.CreateFrom( wdaFile, createReadOnly );

                // Add the container.
                cObject.vContainers.push_back( cContainer );
            }
        }
        // Load all attribute boosts.
        {
            // Load the quantity of boosts in this item
            DWORD dwQ;
            wdaFile.Read( dwQ );

            // Scroll through all attributes.
            DWORD j;
            for( j = 0; j != dwQ; j++ ){
                // Load the boost
                WDAObjectsAttrBoosts cBoost( cOutput, dlDebugHigh );
                cBoost.CreateFrom( wdaFile, createReadOnly );

                // Add boost to object
                cObject.vAttrBoosts.push_back( cBoost );
            }
        }
        // Load all spells.
        {
            // Load the quantity of spells in this item
            DWORD dwQ;
            wdaFile.Read( dwQ );

            // Scroll through all spells.
            DWORD j;
            for( j = 0; j != dwQ; j++ ){
                // Load the spell
                WDAObjectsSpells cSpell( cOutput, dlDebugHigh );
                cSpell.CreateFrom( wdaFile, createReadOnly );

                // Add spell to object
                cObject.vSpells.push_back( cSpell );
            }
        }

        cObject.m_ReadOnly = createReadOnly;

        // Add the object to the list of objects.
        vObjects.push_back( cObject );
    }// for( vObjects ...

    // Load the world objects
    {
        DWORD dwQ;
        wdaFile.Read( dwQ );

        DWORD j;
        for( j = 0; j != dwQ; j++ ){
            WDAObjectsWorldObjects cPos( cOutput, dlDebugHigh );
            cPos.CreateFrom( wdaFile, createReadOnly );
                    
            // Add the location.
            vLocations.push_back( cPos );
        }
    }

    ComputeHighestBoostID();
}

//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjects::ComputeHighestBoostID()
{
  int i;
    for( i = 0; i < vObjects.size(); i++ ){
        ObjectData &obj = vObjects[ i ];
        int k;
        for( k = 0; k < obj.vAttrBoosts.size(); k++ ){
            WDAObjectsAttrBoosts &boost = obj.vAttrBoosts[ k ];
            if( boost.GetID() > m_NextHighestBoostID ){
                m_NextHighestBoostID = boost.GetID() + 1;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
DWORD WDAObjects::GetNextHighestBoostID()
{
    return m_NextHighestBoostID++;
}

//////////////////////////////////////////////////////////////////////////////////////////
WDAObjects::ObjectData *WDAObjects::GetWritableObject( std::string objID )
{
    int i;
    for( i = 0; i < vObjects.size(); i++ ){
        if( !vObjects[ i ].m_ReadOnly && stricmp( vObjects[ i ].csID.c_str(), objID.c_str() ) == 0 ){
            return &vObjects[ i ];
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
WDAObjects::ObjectData *WDAObjects::GetReadOnlyObject( std::string objID )
{
    int i;
    for( i = 0; i < vObjects.size(); i++ ){
        if( vObjects[ i ].m_ReadOnly && stricmp( vObjects[ i ].csID.c_str(), objID.c_str() ) == 0 ){
            return &vObjects[ i ];
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
WDAObjects::ObjectData *WDAObjects::GetWritableObject( DWORD objID )
{
    int i;
    for( i = 0; i < vObjects.size(); i++ ){
        if( !vObjects[ i ].m_ReadOnly && vObjects[ i ].dwBindedID == objID ){
            return &vObjects[ i ];
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
WDAObjects::ObjectData *WDAObjects::GetReadOnlyObject( DWORD objID )
{
    int i;
    for( i = 0; i < vObjects.size(); i++ ){
        if( vObjects[ i ].m_ReadOnly && vObjects[ i ].dwBindedID == objID ){
            return &vObjects[ i ];
        }
    }
    return NULL;
}


#ifndef NO_DAO_SUPPORT
//////////////////////////////////////////////////////////////////////////////////////////
void WDAObjects::CreateFrom
//////////////////////////////////////////////////////////////////////////////////////////
// Creates all objects from DAO support
// 
(
 CDaoRecordset &cRecord, // The recordset where all objects reside.
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
        "\nLoading objects."
        "\n"
    );

    map< string, DWORD > itemMap;
    TFormat cFormat;

    // Scroll through all objects in the recordset
    cRecord.MoveFirst();
    while( !cRecord.IsEOF() ){
        COleVariant oleData;        

        ObjectData cObject;

        // Loads the object's data.
        cRecord.GetFieldValue( "ObjectID", oleData );
        cObject.csID = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "BindedID", oleData );
        cObject.dwBindedID = V_I4( &oleData );

        cRecord.GetFieldValue( "ObjectStructure", oleData );
        cObject.dwStructureID = V_I4( &oleData );

        cRecord.GetFieldValue( "Name", oleData );
        cObject.csName = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "Appearance", oleData );
        cObject.dwAppearance = V_I4( &oleData );

        cRecord.GetFieldValue( "SellType", oleData );
        cObject.dwSellType = V_I4( &oleData );

        cRecord.GetFieldValue( "EquipPosition", oleData );
        cObject.dwEquipPos = V_I4( &oleData );

        cRecord.GetFieldValue( "SellingPrice", oleData );
        cObject.dwSellPrice = V_I4( &oleData );

        cRecord.GetFieldValue( "Size", oleData );
        cObject.dwSize = V_I4( &oleData );

        cRecord.GetFieldValue( "Armor_AC", oleData );
        cObject.dblArmor_AC = V_R8( &oleData );

        cRecord.GetFieldValue( "Armor_DodgeMalus", oleData );
        cObject.dwArmor_DodgeMalus = V_I4( &oleData );

        cRecord.GetFieldValue( "Armor_MinEnd", oleData );
        cObject.dwArmor_MinEnd = V_I4( &oleData );

        cRecord.GetFieldValue( "Weapon_DmgRoll", oleData );
        cObject.csWeapon_DmgRoll = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "Weapon_Att", oleData );
        cObject.dwWeapon_Attack = V_I4( &oleData );

        cRecord.GetFieldValue( "Weapon_Str", oleData );
        cObject.dwWeapon_Str = V_I4( &oleData );

        cRecord.GetFieldValue( "Weapon_Agi", oleData );
        cObject.dwWeapon_Agi = V_I4( &oleData );

        cRecord.GetFieldValue( "Lock_KeyID", oleData );
        cObject.csLock_KeyID = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "Lock_Difficulty", oleData );
        cObject.dwLockDifficulty = V_I4( &oleData );

        cRecord.GetFieldValue( "Book_Text", oleData );
        cObject.csBook_Text = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "Container_Gold", oleData );
        cObject.dwContainer_Gold = V_I4( &oleData );

        cRecord.GetFieldValue( "Container_GlobalRespawn", oleData );
        cObject.dwContainer_GlobalRespawn = V_I4( &oleData );

        cRecord.GetFieldValue( "Container_UserRespawn", oleData );
        cObject.dwContainer_UserRespawn = V_I4( &oleData );

        cRecord.GetFieldValue( "Weapon_Exhaust", oleData );
        cObject.csWeapon_Exhaust = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "Weapon_Ranged", oleData );
        cObject.boWeapon_Ranged = V_I4( &oleData ) != 0 ? true : false;
        
        cRecord.GetFieldValue( "Weapon_RangedInfiniteAmmo", oleData );
        cObject.boWeapon_RangedInfiniteAmmo = V_I4( &oleData ) != 0 ? true : false;

        cRecord.GetFieldValue( "Radiance", oleData );
        cObject.dwRadiance = V_I4( &oleData );

        cRecord.GetFieldValue( "Charges", oleData );
        cObject.lCharges = V_I4( &oleData );

        cRecord.GetFieldValue( "MinInt", oleData );
        cObject.dwMinInt = V_I4( &oleData );

        cRecord.GetFieldValue( "MinWis", oleData );
        cObject.dwMinWis = V_I4( &oleData );

        cRecord.GetFieldValue( "NameID", oleData );
        cObject.dwIntlID = V_I4( &oleData );

        cRecord.GetFieldValue( "DropFlags", oleData );
        cObject.dwDropFlags = V_I4( &oleData );

        cRecord.GetFieldValue( "Unique", oleData );
        cObject.boUnique = V_I4( &oleData ) != 0 ? true : false;

        cRecord.GetFieldValue( "GmItemLocation", oleData );
        cObject.csGmItemLocation = V_BSTRT( &oleData );

        cRecord.GetFieldValue( "CanSummon", oleData );
        cObject.boCanSummon = V_I4( &oleData ) != 0 ? true : false;

        cOutput.Log(
            dlDebug,
            cFormat(
                "\nFound item %s.",
                cObject.csID.c_str()
            )
        );
        cOutput.Log(
            dlDebugHigh,
            cFormat(
                "\n BindedID: %u"
                "\n StructureID: %u"
                "\n Name: %s"
                "\n Appearance: %u"
                "\n SellType: %u"
                "\n EquipPos: %u"
                "\n SellPrice: %u"
                "\n Size: %u"
                "\n Armor_AC: %f"
                "\n Armor_DodgeMalus: %u"
                "\n Armor_MinEnd: %u"
                "\n Weapon_DmgRoll: %s"
                "\n Weapon_Attack: %u"
                "\n Weapon_Str: %u"
                "\n Weapon_Agi: %u"
                "\n Lock_KeyID: %s"
                "\n LockDifficulty: %u"
                "\n Book_Text: %s"
                "\n Container_Gold: %u"
                "\n Container_GlobalRespawn: %u"
                "\n Container_UserRespawn: %u"
                "\n Exhaust: %s"
                "\n Radiance: %u"
                "\n Charges: %d"
                "\n MinInt: %u"
                "\n MinWis: %u"
                "\n IntlID: %u",
                cObject.dwBindedID,
                cObject.dwStructureID,
                cObject.csName.c_str(),
                cObject.dwAppearance,
                cObject.dwSellType,
                cObject.dwEquipPos,
                cObject.dwSellPrice,
                cObject.dwSize,
                cObject.dblArmor_AC,
                cObject.dwArmor_DodgeMalus,
                cObject.dwArmor_MinEnd,
                cObject.csWeapon_DmgRoll.c_str(),
                cObject.dwWeapon_Attack,
                cObject.dwWeapon_Str,
                cObject.dwWeapon_Agi,
                cObject.csLock_KeyID.c_str(),
                cObject.dwLockDifficulty,
                cObject.csBook_Text.c_str(),
                cObject.dwContainer_Gold,
                cObject.dwContainer_GlobalRespawn,
                cObject.dwContainer_UserRespawn,
                cObject.csWeapon_Exhaust.c_str(),
                cObject.dwRadiance,
                cObject.lCharges,
                cObject.dwMinInt,
                cObject.dwMinWis,
                cObject.dwIntlID
            )
        );

        // Add the object to the vector of objects
        vObjects.push_back( cObject );

        itemMap[ cObject.csID ] = vObjects.size() - 1;
    
        cRecord.MoveNext();
    }// while( !cRecord.IsEOF() )


    // Load the container data.
    {
        CDaoRecordset recCont( &cDatabase );

        recCont.Open(
            dbOpenSnapshot,
            "SELECT * FROM Objects_ContainerGroups"
        );

        // If the object has containers.
        if( !recCont.IsEOF() ){

            // Scroll through all object containers.
            for( recCont.MoveFirst(); !recCont.IsEOF(); recCont.MoveNext() ){
                COleVariant oleData;
                recCont.GetFieldValue( "ObjectID", oleData );
                string itemID = V_BSTRT( &oleData );                

                // Find the associated spell.
                map< string, DWORD >::iterator j;
                j = itemMap.find( itemID );
                if( j == itemMap.end() ){
                    continue;
                }

                if( itemID != vObjects[ (*j).second ].csID ){
                    cOutput.Log(
                        dlDebug,
                        cFormat(
                            "\nError1 loading container group for object %s",
                            itemID.c_str()
                        )
                    );
                }

                // Create a new container group.
                WDAObjectsContainerGroups cContainerGroup( cOutput, dlDebugHigh );
           
                // Create the container group from this record.
                cContainerGroup.CreateFrom( recCont, cDatabase );

                // Add it to the vector of containers.
                vObjects[ (*j).second ].vContainers.push_back( cContainerGroup );
            }
        }
    }
    // Load the attribute boosts.
    {
        CDaoRecordset recBoosts( &cDatabase );

        recBoosts.Open( 
            dbOpenSnapshot,
            "SELECT * FROM Objects_AttrBoosts"
        );

        // If the object has boosts.
        if( !recBoosts.IsEOF() ){

            // Scroll through all attr boosts
            for( recBoosts.MoveFirst(); !recBoosts.IsEOF(); recBoosts.MoveNext() ){
                COleVariant oleData;
                recBoosts.GetFieldValue( "ObjectID", oleData );
                string itemID = V_BSTRT( &oleData );                

                // Find the associated spell.
                map< string, DWORD >::iterator j;
                j = itemMap.find( itemID );
                if( j == itemMap.end() ){
                    continue;
                }

                if( itemID != vObjects[ (*j).second ].csID ){
                    cOutput.Log(
                        dlDebug,
                        cFormat(
                            "\nError1 loading container group for object %s",
                            itemID.c_str()
                        )
                    );
                }

                // Create a new attr boost.
                WDAObjectsAttrBoosts cAttrBoost( cOutput, dlDebugHigh );
           
                // Create the boost from this record
                cAttrBoost.CreateFrom( recBoosts, cDatabase );

                // Add it to the vector of attribute boosts
                vObjects[ (*j).second ].vAttrBoosts.push_back( cAttrBoost );
            }
        }
    }
    // Load the spells on this object.
    {
        CDaoRecordset recSpells( &cDatabase );

        recSpells.Open( 
            dbOpenSnapshot,
            "SELECT * FROM Objects_Spells"
        );

        // If the object has spells.
        if( !recSpells.IsEOF() ){

            // Scroll through all spells
            for( recSpells.MoveFirst(); !recSpells.IsEOF(); recSpells.MoveNext() ){
                COleVariant oleData;
                recSpells.GetFieldValue( "ObjectID", oleData );
                string itemID = V_BSTRT( &oleData );                

                // Find the associated spell.
                map< string, DWORD >::iterator j;
                j = itemMap.find( itemID );
                if( j == itemMap.end() ){
                    continue;
                }

                if( itemID != vObjects[ (*j).second ].csID ){
                    cOutput.Log(
                        dlDebug,
                        cFormat(
                            "\nError1 loading spells for object %s",
                            itemID.c_str()
                        )
                    );
                }

                // Create a new spell.
                WDAObjectsSpells cSpell( cOutput, dlDebugHigh );
           
                // Create the spell from this record
                cSpell.CreateFrom( recSpells, cDatabase );

                // Add it to the vector of spells
                vObjects[ (*j).second ].vSpells.push_back( cSpell );
            }
        }
    }

    cOutput.Log(
        dlInfo,
        "\n----- DAO -----"
        "\nLoading world objects."
        "\n"
    );

    // Then load the world objects.
    {
        CDaoRecordset recWorld( &cDatabase );

        recWorld.Open( dbOpenSnapshot, "SELECT * FROM WorldObjects" );

        // If recorset isn't empty.
        if( !recWorld.IsEOF() ){
            
            recWorld.MoveFirst();
            while( !recWorld.IsEOF() ){
                WDAObjectsWorldObjects cWorld( cOutput, dlDebugHigh );

                // Create the world pos.
                cWorld.CreateFrom( recWorld, cDatabase );

                // Add it to the list of world objects.
                vLocations.push_back( cWorld );                          

                recWorld.MoveNext();
            }
        }
    }

    ComputeHighestBoostID();
}
#endif
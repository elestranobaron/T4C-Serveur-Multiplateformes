// DynamicFlags.cpp: implementation of the DynamicFlags class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DynamicFlags.h"
#include <iterator>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DynamicFlags::DynamicFlags()
{
}

DynamicFlags::~DynamicFlags()
{
}


//////////////////////////////////////////////////////////////////////////////////////////
long DynamicFlags::ViewFlag
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the value of a given flag ID.
// 
(
 unsigned long dwFlagID,      // The flag ID.
 long          lDefaultValue  // Value to return if flag wasn't found.
)
// Return: long, the flag ID's value.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Insures exception-safe auto function locking.
    CAutoLock cAutoLock( &csThreadLock );
    
    FlagMap::iterator i;

    i = mFlagMap.find( dwFlagID );
    // If the key wasn't found.
    if( i == mFlagMap.end() ){
        // Return default value.
        return lDefaultValue;
    }       
    
	// Otherwise return the key's value.
    return (*i).second;
}

//////////////////////////////////////////////////////////////////////////////////////////
void DynamicFlags::SetFlag
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets a flag value.
// 
(
 unsigned long dwFlagID, // The flag to set a value for.
 long lFlagValue         // The flag's value.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( dwFlagID > 10000000 ){
        DWORD debugStack[ 10 ];
        int stackLevel = WalkStack( debugStack, 10 );
        if( stackLevel >= 10 ){
            stackLevel = 5;
        }

        std::string stackTrace;
        char buf[ 256 ];
        int i;
        for( i = 0; i < stackLevel; i++ ){
            _snprintf( buf, 256, "0x%x ", debugStack[ i ] );
            stackTrace += buf;
        }
        
    }

    // Insures exception-safe auto function locking.
    CAutoLock cAutoLock( &csThreadLock );
    
    // If the flag's value is null.
    if( lFlagValue == 0 ){
        // Remove the flag.
        RemoveFlag( dwFlagID );
    }else{
        // Set the flag's value.
        mFlagMap[ dwFlagID ] = lFlagValue;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////
void DynamicFlags::RemoveFlag
//////////////////////////////////////////////////////////////////////////////////////////
//  Removes a flag
// 
(
 unsigned long dwFlagID // The flag to remove.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Insures exception-safe auto function locking.
    CAutoLock cAutoLock( &csThreadLock );

    FlagMap::iterator i;

    i = mFlagMap.find( dwFlagID );
    // If the key wasn't found.
    if( i == mFlagMap.end() ){
        // Return.
        return;
    }       
    
	// Otherwise remove the flag from the map.
    mFlagMap.erase( i );
}

//////////////////////////////////////////////////////////////////////////////////////////
void DynamicFlags::GetFlags
//////////////////////////////////////////////////////////////////////////////////////////
//  This function will copy all current flags into a flag holder vector.
// 
(
 FlagCont &vFlags // The vector in which to copy the flags.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Insures exception-safe auto function locking.
    CAutoLock cAutoLock( &csThreadLock );

    // Copy the flags.
    std::copy( mFlagMap.begin(), mFlagMap.end(), back_inserter( vFlags ) );	
}


//////////////////////////////////////////////////////////////////////////////////////////
void DynamicFlags::DestroyFlags( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Destroy all flags.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Insures exception-safe auto function locking.
    CAutoLock cAutoLock( &csThreadLock );

    mFlagMap.clear();
}
// AutoConfig.cpp: implementation of the CAutoConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "AutoConfig.h"
#include "RegKeyHandler.h"
#include "Lock.h"
//#include <process.h>
#include <map>
#include <vector>
#include "ThreadMonitor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////////////////
// RegristyKey structure for storing registry keys.
class RegistryKey{
public:
    RegistryKey( void ){
        szCompareSubKey = NULL;
        szCompareValueName = NULL;
    };
    RegistryKey( LPCTSTR szSubKey, LPCTSTR szValue ) : sSubKey( szSubKey, sizeof( szSubKey ) ), sValueName( szValue, sizeof( szValue ) ){
        szCompareSubKey = NULL;
        szCompareValueName = NULL;
    };  

    HKEY    hKey;
	std::string  sSubKey;
	std::string  sValueName;
    LPCTSTR szCompareSubKey;
    LPCTSTR szCompareValueName;
};

//////////////////////////////////////////////////////////////////////////////////////////
bool operator <
//////////////////////////////////////////////////////////////////////////////////////////
// Comparison operator for operations with the set<> of registry keys.
// 
(
 const RegistryKey &kKey,       // First registry key object to compare.
 const RegistryKey &kSecondKey  // Second registry key object to compare.
)
// Return: bool operator, TRUE if kKey < kSecondKey
//////////////////////////////////////////////////////////////////////////////////////////
{    
    // If the main key value is lower
    if( kKey.hKey < kSecondKey.hKey ){
        return true;
    }else 
    // If the main key is the same
    if( kKey.hKey == kSecondKey.hKey ){
        // Compare the sub keys.
        int nStr;
        // If a comparison string pointer was provided for the 1st key.
        if( kKey.szCompareSubKey != NULL ){
            // If a comparison string pointer was provided for the 2nd key.
            if( kSecondKey.szCompareSubKey != NULL ){
                nStr = CMP( kKey.szCompareSubKey, kSecondKey.szCompareSubKey );
            }else{
                nStr = CMP( kKey.szCompareSubKey, kSecondKey.sSubKey.c_str() );
            }
        }else{
            // If a comparison string pointer was provided for the 2nd key.
            if( kSecondKey.szCompareSubKey != NULL ){
                nStr = CMP( kKey.sSubKey.c_str(), kSecondKey.szCompareSubKey );
            }else{
                nStr = CMP( kKey.sSubKey.c_str(), kSecondKey.sSubKey.c_str() );
            }
        }
        
        // If subkey is lower.
        if( nStr < 0 ){
            return true;
        }else 
        // If the subkeys are the same.
        if( nStr == 0 ){
            // If a comparison string pointer was provided for the 1st key.
            if( kKey.szCompareValueName != NULL ){
                // If a comparison string pointer was provided for the 2nd key.
                if( kSecondKey.szCompareValueName != NULL ){
                    return CMP( kKey.szCompareValueName, kSecondKey.szCompareValueName ) < 0;
                }else{
                    return CMP( kKey.szCompareValueName, kSecondKey.sValueName.c_str() ) < 0;
                }
            }else{
                // If a comparison string pointer was provided for the 2nd key.
                if( kSecondKey.szCompareValueName != NULL ){
                    return CMP( kKey.sValueName.c_str(), kSecondKey.szCompareValueName ) < 0;
                }else{
                    return CMP( kKey.sValueName.c_str(), kSecondKey.sValueName.c_str() ) < 0;
                }
            }
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Static variables.
typedef map< RegistryKey, string > StrKeys;
typedef map< RegistryKey, int >    IntKeys;

static CLock    cLock;            // Thread synchronization object.
static StrKeys  mStrValues;       // Contains a set of all string values.
static IntKeys  mIntValues;       // Contains a set of all integer values.
static vector< REGCALLBACK > vRegCallback;

HKEY     CAutoConfig::hCheckMainKey = 0;
string   CAutoConfig::sCheckSubKey;
string   CAutoConfig::sCheckValue;
HANDLE   CAutoConfig::hThread;
bool     CAutoConfig::boRunThread = TRUE;

//////////////////////////////////////////////////////////////////////////////////////////
void CAutoConfig::Create
//////////////////////////////////////////////////////////////////////////////////////////
// Creates the auto-configuration verifier.
// 
(
 HKEY hMainKey,         // Main key where values are. HKEY_* value.
 LPCTSTR szSubKey,      // Sub key where the check key is.
 LPCTSTR szCheckValue   // Registry value which will be created if the registry has changed.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Sets up the check key. The check key is the key which will appear whenever
    // a value has been added that requires reading the registry again.
    hCheckMainKey = hMainKey;
    sCheckSubKey = szSubKey;
    sCheckValue  = szCheckValue;

    //hThread = (HANDLE)_beginthread( ChangeDetectionThread, 0, NULL );
    pthread_t thread;
    pthread_create(&thread, NULL, ChangeDetectionThread, NULL);
    hThread = (HANDLE)pthread_self();
}

/*
//////////////////////////////////////////////////////////////////////////////////////////
void CAutoConfig::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Frees the auto configuration.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	int ret = 0;
    boRunThread = FALSE;
    if( WaitForSingleObject( hThread, 5000 ) == WAIT_TIMEOUT ){
        pthread_exit(&ret);//TerminateThread( hThread, -1 );
    }
}*/
//////////////////////////////////////////////////////////////////////////////////////////
void CAutoConfig::AddRegString
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a reg key to be checked
// 
(
 LPCTSTR szSubKey,      // The subkey to check.
 LPCTSTR szValue,       // The value to check.
 LPCTSTR szDefaultValue, // The default value if the registry key doesn't exist.
 HKEY    hKey           // Main key of the value to check.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RegistryKey         sKey;
    RegKeyHandler       regKey;
    string              sStr;

    // Create a new registry key value.
    sKey.hKey =         hKey;

	_LOG_DEBUG
        LOG_CRIT_ERRORS,
        "Fill ssubKey"
    LOG_

    sKey.sSubKey =      szSubKey;

	_LOG_DEBUG
        LOG_CRIT_ERRORS,
        "Fill sValuename"
    LOG_

    sKey.sValueName =   szValue;

	_LOG_DEBUG
        LOG_CRIT_ERRORS,
        "Open"
    LOG_

    // Open the registry to query the current registry value.   
    regKey.Open( hKey, szSubKey );

    string regValue;

	_LOG_DEBUG
        LOG_CRIT_ERRORS,
        "Get"
    LOG_

    // If the default value isn't defined
    if( szDefaultValue == NULL ){
        // Get registry string with an empty default string.
        regValue = regKey.GetProfileString( szValue, "" );
    }else{
        // Get registry string with the defined default string.
        regValue = regKey.GetProfileString( szValue, szDefaultValue );
    }

	_LOG_DEBUG
        LOG_CRIT_ERRORS,
        "Lock"
    LOG_

    // Add it to the map of string values.
    cLock.Lock();

	_LOG_DEBUG
        LOG_CRIT_ERRORS,
        "map"
    LOG_

    mStrValues[ sKey ] = regValue;

	_LOG_DEBUG
        LOG_CRIT_ERRORS,
        "unlock"
    LOG_

    cLock.Unlock();

	_LOG_DEBUG
        LOG_CRIT_ERRORS,
        "END"
    LOG_
}

//////////////////////////////////////////////////////////////////////////////////////////
void CAutoConfig::AddRegInt
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a registry integer key for checking.
// 
(
 LPCTSTR szSubKey,  // Sub key.
 LPCTSTR szValue,   // Value name.
 int nDefaultValue, // Default integer value.
 HKEY hKey          // The main key.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RegistryKey         sKey;
    RegKeyHandler       regKey;
    
    // Create a new registry key value.
    sKey.hKey =         hKey;
    sKey.sSubKey =      szSubKey;
    sKey.sValueName =   szValue;

    // Open the registry to query the current registry value.   
    regKey.Open( hKey, szSubKey );

    // Get its current value from the registry.
    int regValue =  regKey.GetProfileInt( szValue, nDefaultValue );

    // Add it to the set of keys.
    cLock.Lock();
    mIntValues[ sKey ] = regValue;
    cLock.Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
string CAutoConfig::GetStringValue
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the current string value of a registry key. The key must have been registered
// before it can be accessed.
// 
(
 LPCTSTR szSubKey,  // The subkey of the value to check.
 LPCTSTR szValue,   // The name of the value to check.
 HKEY    hKey       // The main key
)
//////////////////////////////////////////////////////////////////////////////////////////
{    
    RegistryKey sKey;
    
    // Fill-in the registry key to search for.
    sKey.hKey               = hKey;
    sKey.szCompareSubKey    = szSubKey;
    sKey.szCompareValueName = szValue;

    cLock.Lock();
    StrKeys::iterator i = mStrValues.find( sKey );

    // If the key wasn't added existed.
    if( i == mStrValues.end() ){
        cLock.Unlock();
        // return an empty string.
        return "";        
    }

    cLock.Unlock();
    // Return the value stored in the found registry object.
    return (*i).second;
}

//////////////////////////////////////////////////////////////////////////////////////////
int CAutoConfig::GetIntValue
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the current int value of a registry key. The key must have been registered
// before it can be accessed.
// 
(
 LPCTSTR szSubKey,  // Sub key.
 LPCTSTR szValue,   // Value name to get.
 HKEY hKey          // Main key.
)
// Return: int, the key's value.
//////////////////////////////////////////////////////////////////////////////////////////
{
    RegistryKey sKey;
    
    // Fill-in the registry key to search for.
    sKey.hKey       = hKey;
    sKey.sSubKey    = szSubKey;
    sKey.sValueName = szValue;

    cLock.Lock();
    IntKeys::iterator i = mIntValues.find( sKey );

    // If the key wasn't added existed.
    if( i == mIntValues.end() ){
        cLock.Unlock();
        // return an empty string.
        return 0;        
    }

    cLock.Unlock();
    // Return the value stored in the found registry object.
    return (*i).second;
}


//////////////////////////////////////////////////////////////////////////////////////////
void* CAutoConfig::ChangeDetectionThread // void simple wind
//////////////////////////////////////////////////////////////////////////////////////////
// This thread will query the registry every 2 seconds and update the values in the set<>.
// 
(
 LPVOID lpData // NULL
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("AutoConfig ChangeDetection");
    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "AutoConfig Thread Id=%u",
        pthread_self()//GetCurrentThreadId()
    LOG_    
    
    while( boRunThread ){
        sleep ( 2 );//Sleep( 2000 );

        // Open the key of the check value
        RegKeyHandler regCheckKey;
        regCheckKey.Open( hCheckMainKey, sCheckSubKey.c_str() );

        // If the check value has been set, then refresh all registered values.
        if( regCheckKey.GetProfileInt( sCheckValue.c_str(), 0 ) != 0 ){
            // Delete this registry key, since we've acknowledged that there needs to be a value refresh.
            regCheckKey.DeleteValue( sCheckValue.c_str() );

            // Stop any attempt to read from the sets of registry addresses.
            cLock.Lock();                        
            
            {
                IntKeys::iterator i;
                // Scroll through all integer items.
                for( i = mIntValues.begin(); i != mIntValues.end(); i++ ){
                    RegKeyHandler regKey;                        

                    // Open the key specified by this key.
                    regKey.Open( (*i).first.hKey, (*i).first.sSubKey.c_str() );
                                            
                    // Get the key's value, using the old value as default.
                    (*i).second = regKey.GetProfileInt( (*i).first.sValueName.c_str(), (*i).second );
                }
            }
         
            {
                StrKeys::iterator j;
                // Scroll through all string items.
                for( j = mStrValues.begin(); j != mStrValues.end(); j++ ){
                    RegKeyHandler regKey;

                    // Open the key specified by this key.
                    regKey.Open( (*j).first.hKey, (*j).first.sSubKey.c_str() );

                    // Get the key's value, using the old value as default.                
                    (*j).second = regKey.GetProfileString( (*j).first.sValueName.c_str(), (*j).second.c_str() );
                }
            }

            cLock.Unlock();

            // Call all registry update callbacks.
            vector< REGCALLBACK >::iterator h;
            for( h = vRegCallback.begin(); h != vRegCallback.end(); h++ ){
                (*h)();
            }
        }
    }
    return NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////
void CAutoConfig::AddRegUpdateCallback
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 REGCALLBACK lpRegCallback // Address of a registry callback function.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    vRegCallback.push_back( lpRegCallback );
}

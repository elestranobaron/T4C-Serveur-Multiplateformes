// RegKeyHandler.cpp: implementation of the RegKeyHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RegKeyHandler.h"
#include "Config.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RegKeyHandler::RegKeyHandler()
{	keyhandle = NULL;	
}

RegKeyHandler::~RegKeyHandler(){
if(keyhandle != NULL) RegCloseKey(keyhandle);
}

////////////////////////////////////////////////////////////////////////////
BOOL RegKeyHandler::Create(HKEY main_key, LPCTSTR sub_key){	
	DWORD exists;
	DWORD err;
	err = RegCreateKeyEx(main_key, sub_key, 0, _T(""), REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &keyhandle, &exists);
	mainkey = main_key;
	subkey = sub_key;
	
	if(err != ERROR_SUCCESS) return FALSE;	
	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
BOOL RegKeyHandler::Open(HKEY main_key, LPCTSTR sub_key){		
	if (Config::instance().initConfig(CONFIG_FILE) != TRUE)
	{
		printf("%s\n", "INIT CONFIG FAIL !");
		return FALSE;
	}
	/*DWORD err;
	
	if( keyhandle != NULL ){
		RegCloseKey( keyhandle );
	}

	err = RegOpenKeyEx(main_key, sub_key, 0, KEY_ALL_ACCESS, &keyhandle);

#ifdef _DEBUG
    if( err != ERROR_SUCCESS ){
        TRACE( "\r\nError 0x%x(%u) opening registry key %s.", err,err,sub_key );
    }
#endif

	mainkey = main_key;
	subkey = sub_key;

	if(err != ERROR_SUCCESS) return FALSE;	
	return TRUE;*/
	//return Config::instance().lookupValue<bool>("EnableLogging");
	return Config::instance().lookupValue<bool>(sub_key);
}


////////////////////////////////////////////////////////////////////////////
void RegKeyHandler::WriteProfileString(LPCTSTR item, LPCTSTR value){
	RegSetValueEx(keyhandle, item, 0, REG_SZ, (CONST BYTE *)value, lstrlen(value));
}; 
		
////////////////////////////////////////////////////////////////////////////
void RegKeyHandler::WriteProfileInt(LPCTSTR item, DWORD value){
	RegSetValueEx(keyhandle, item, 0, REG_DWORD, (unsigned char *)&value, sizeof(DWORD));
}

////////////////////////////////////////////////////////////////////////////
LPCTSTR RegKeyHandler::GetProfileString(LPCTSTR item, LPCTSTR default_arg){	
	DWORD count = 1020;
	DWORD type;
	
    returnstr[ 0 ] = 0;
	if(RegQueryValueEx(keyhandle, item, 0, &type, (LPBYTE)returnstr, &count) != ERROR_SUCCESS){		
		lstrcpy(returnstr, default_arg);
		return returnstr;
	}	
	return returnstr;
}
////////////////////////////////////////////////////////////////////////////////
DWORD RegKeyHandler::GetProfileInt(LPCTSTR item, DWORD default_arg)
{	
	DWORD count;
	DWORD type;
	unsigned char *value;

	if(RegQueryValueEx(keyhandle, item, NULL, &type, NULL, &count) != ERROR_SUCCESS) return default_arg;
	
	value = new unsigned char[count];
	
	if(RegQueryValueEx(keyhandle, item, NULL, &type, value, &count) != ERROR_SUCCESS){
		delete [] value;
		return default_arg;
	}

	if(type != REG_DWORD){
		delete [] value;
		return default_arg;
	}

	DWORD return_var = 0;
	
	for(signed int i = count - 1; i >= 0; i--){
		return_var *= 256;
		return_var += value[i];
	}
	delete[] value;
	return return_var;
}
//////////////////////////////////////////////////////////////////////////////////////////
void RegKeyHandler::Close( void ){
	if(keyhandle != NULL) RegCloseKey(keyhandle);
	keyhandle = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL RegKeyHandler::DeleteValue( LPCTSTR lpszItem ){
	if( RegDeleteValue( keyhandle, lpszItem ) == ERROR_SUCCESS ){
		return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////
BOOL RegKeyHandler::DeleteKey( LPCTSTR subkey ){
	if( RegDeleteKey( keyhandle, subkey ) == ERROR_SUCCESS ){
		return TRUE;
	}

	return FALSE;
}

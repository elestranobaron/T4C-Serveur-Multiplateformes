#include "stdafx.h"
#include "DebugTools.h"
#include "AppStrings.h"

namespace{
    std::string errorMsg;
}

void SetErrorStrId( DWORD id ){
    errorMsg = GetAppString( id );
}

void SetErrorStr( std::string err ){
    errorMsg = err;
}

std::string GetErrorStr(){
    return errorMsg;
}

void SetProgramError( std::string debugStr ){
    char buf[ 8192 ];
    sprintf( buf, GetAppString( IDS_PROGRAM_ERROR ).c_str(), debugStr.c_str() );
    SetErrorStr( buf );
}


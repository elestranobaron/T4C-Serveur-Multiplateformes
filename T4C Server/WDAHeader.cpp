// WDAHeader.cpp: implementation of the WDAHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WDAHeader.h"
#include "WDAFile.h"

#define TAG_VALUE 0x0CA7
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WDAHeader::WDAHeader() : m_ReadOnly( false )
{

}

WDAHeader::~WDAHeader()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
void WDAHeader::SaveTo( WDAFile &wdaFile, bool isReadOnly )
{
    wdaFile.Write( (WORD)TAG_VALUE );  // Tag
    wdaFile.Write( (WORD)1 );       // Version
    wdaFile.Write( isReadOnly );
}

//////////////////////////////////////////////////////////////////////////////////////////
bool WDAHeader::CreateFrom( WDAFile &wdaFile )
{
    WORD tag;

    wdaFile.Read( tag );
    wdaFile.Read( m_Version );
    wdaFile.Read( m_ReadOnly );

    if( tag != TAG_VALUE || !IsVersionOK() ){
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool WDAHeader::IsVersionOK()
{
    return m_Version == 1;
}
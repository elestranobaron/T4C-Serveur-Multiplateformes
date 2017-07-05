// *******************************************************************************************
// ***                                                                                     ***
//      File Name: WDAFile.h
//      Project:   T4C Server
//      Plateform: Windows NT
//      Creation:  5/3/1999
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         5/3/1999        1.0       FL             Initial developpement
//
//      Description
//          Encapsulates file operations for WDA data files. (WorldData).
//
//    If the data is scrambled:
//       Did you use the same Read( ... ) and Write( ... ) functions?
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_WDAFILE_H__8D88CCEA_D321_11D2_84AD_00E02922FA40__INCLUDED_)
#define AFX_WDAFILE_H__8D88CCEA_D321_11D2_84AD_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>

class WDAFileException{
public:
    enum ErrorType{
        EndOfFile, WriteError
    };
    
    WDAFileException( std::string csExplain, ErrorType error );

    ErrorType    GetError();
    std::string &GetExplanation();

private:
    ErrorType   errorType;
    std::string csExplanation;
};

class WDAFile  
{
public:
	WDAFile();
	virtual ~WDAFile();

    bool Create( std::string csPath );
    bool Open  ( std::string csPath );
    void Close ( void );

    void Write( const void *lpBuffer,  DWORD dwSize );
    // Warning, these function are not portable!
    void Write( DWORD       dwDword );
    void Write( WORD        wWord );
    void Write( const std::string &csString );
    void Write( BYTE        bByte );
    void Write( bool        boBool );
    void Write( signed int  nInt );
    void Write( signed long lLong );
    void Write( signed char cChar );
    void Write( signed short sShort );
    void Write( double      dblDouble );
    
    // Can throw a WDAFileException!
    void Read ( void *lpBuffer, DWORD dwSize, const char *szExceptionText = "a buffer" );
    // Warning, these function are not portable!
    void Read ( DWORD &dwDword );
    void Read ( WORD  &wWord );
    void Read ( std::string &csString );
    void Read ( BYTE &bByte );
    void Read ( bool &boBool );
    void Read ( signed int  &nInt );
    void Read ( signed long &lLong );
    void Read ( signed char &cChar );
    void Read ( signed short &sShort );
    void Read ( double &dblDouble );

private:
    inline BYTE Encrypt( const BYTE bByte, DWORD dwSeed );
    inline BYTE Decrypt( const BYTE bByte, DWORD dwSeed );

    FILE *fFile;

};

#endif // !defined(AFX_WDAFILE_H__8D88CCEA_D321_11D2_84AD_00E02922FA40__INCLUDED_)

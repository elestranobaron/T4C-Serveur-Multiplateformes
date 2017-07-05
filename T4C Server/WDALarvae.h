// WDALarvae.h: interface for the WDALarvae class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WDALARVAE_H__5453C342_D66A_11D2_84B3_00E02922FA40__INCLUDED_)
#define AFX_WDALARVAE_H__5453C342_D66A_11D2_84B3_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"
#include <string>

class WDAHives;
class WDALarvae : public WDATable  
{
public:	
    WDALarvae( vir::Logger &cLogger, vir::DEBUG_LEVEL dlDebugHigh );    
    friend WDAHives;

	virtual ~WDALarvae();
    
    // Accessors
    const std::string &GetLarvaID( void );   

    // Deep-copy operator
    void operator = ( const WDALarvae &cParam ){
        csLarvaID = cParam.csLarvaID;
    }

    void Setup( std::string larvae ){
        csLarvaID = larvae;
    }

private:  
    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // AreaLinks::CreateFrom does not need cRecord, it builds directly from the cDatabase.
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    std::string csLarvaID;

};

#endif // !defined(AFX_WDALARVAE_H__5453C342_D66A_11D2_84B3_00E02922FA40__INCLUDED_)

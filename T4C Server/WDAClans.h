// WDAClans.h: interface for the WDAClans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WDACLANS_H__FFB498A6_D575_11D2_84B1_00E02922FA40__INCLUDED_)
#define AFX_WDACLANS_H__FFB498A6_D575_11D2_84B1_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WDATable.h"

#include <vector>

class WDAClans : public WDATable  
{
public:
	WDAClans( vir::Logger &cTraceLogger );
	virtual ~WDAClans();

    // Exported structures
    struct ClanRelation{
        ClanRelation() : 
            m_ReadOnly( false ), wFirstClanID(0), wSecondClanID(0), sClanRelation(0)
        {}

        bool  m_ReadOnly;
        WORD  wFirstClanID;
        WORD  wSecondClanID;
        short sClanRelation;

        bool operator == (const ClanRelation &rel ) const{
            return m_ReadOnly    == rel.m_ReadOnly &&
                   wFirstClanID  == rel.wFirstClanID &&
                   wSecondClanID == rel.wSecondClanID &&
                   sClanRelation == rel.sClanRelation;
        }
    };
    
    struct Clan{
        bool m_ReadOnly;
        WORD m_ID;
        std::string m_Name;
    };
    
    
    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

#ifndef NO_DAO_SUPPORT    
    // Creates the clan relations from a DAO database.
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

    // Returns the clan relations
    virtual std::vector< ClanRelation > &GetClanRelations( void );
    
    virtual std::vector< Clan > &GetClans();

    // Returns the highest possible clan ID.
    virtual DWORD GetHighestClan();
    
    void ResetHighestClan();

private:

    DWORD dwHighestClan;
    std::vector< ClanRelation > vClanRelations;
    std::vector< Clan > vClans;
};

#endif // !defined(AFX_WDACLANS_H__FFB498A6_D575_11D2_84B1_00E02922FA40__INCLUDED_)

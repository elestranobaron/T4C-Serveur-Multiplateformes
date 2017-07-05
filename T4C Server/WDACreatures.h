// WDACreatures.h: interface for the WDACreatures class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WDACREATURES_H__9C6E6333_6095_11D3_856C_00E02922FA40__INCLUDED_)
#define AFX_WDACREATURES_H__9C6E6333_6095_11D3_856C_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "WDATable.h"

class WDACreatures : public WDATable  
{
public:
	WDACreatures( vir::Logger &cOutputLogger );
	virtual ~WDACreatures();

    struct CreatureAttack{
        CreatureAttack() : 
            dwAttackSkill(0), 
            dwAttackPercentage(0), 
            dwAttackSpell(0),
            dwAttackMinRange(0),
            dwAttackMaxRange(0)
        {}
            
        void Setup( std::string dmgRoll, DWORD attackSkill, DWORD attackPercentage, DWORD attackSpell, DWORD minRange, DWORD maxRange )
        {
            csDmgRoll = dmgRoll;
            dwAttackSkill = attackSkill;
            dwAttackPercentage = attackPercentage;
            dwAttackSpell = attackSpell;
            dwAttackMinRange = minRange;
            dwAttackMaxRange = maxRange;
        }

        bool operator == (const CreatureAttack &r ){
            return csDmgRoll          == r.csDmgRoll && 
                   dwAttackSkill      == r.dwAttackSkill &&
                   dwAttackPercentage == r.dwAttackPercentage && 
                   dwAttackSpell      == r.dwAttackSpell &&
                   dwAttackMinRange   == r.dwAttackMinRange && 
                   dwAttackMaxRange   == r.dwAttackMaxRange;
        }

        std::string csDmgRoll;
        DWORD dwAttackSkill;
        DWORD dwAttackPercentage;
        DWORD dwAttackSpell;
        DWORD dwAttackMinRange;
        DWORD dwAttackMaxRange;
    };

    struct CreatureDeathItem{
        CreatureDeathItem() : dwItemID(0), dblDropPercentage(0)
        {}
        
        bool operator==( const CreatureDeathItem &r ){
            return dwItemID          == r.dwItemID && 
                   dblDropPercentage == r.dblDropPercentage;
        }

        DWORD dwItemID;
        double dblDropPercentage;
    };
    
    struct CreatureDeathFlag{
        CreatureDeathFlag() : dwFlag(0), dwFlagValue(0), boIncrement(false)
        {}
        
        bool operator == ( const CreatureDeathFlag &r ){
            return dwFlag      == r.dwFlag &&
                   dwFlagValue == r.dwFlagValue &&
                   boIncrement == r.boIncrement;
        }

        DWORD dwFlag;
        DWORD dwFlagValue;
        bool  boIncrement;
    };

    struct CreatureData{
        CreatureData() :
            m_ReadOnly( false ),
            dwBindedID(0),
            dwSTR(0),
            dwEND(0),
            dwAGI(0),
            dwINT(0),
            dwWIL(0),
            dwWIS(0),     
            dwLCK(0),
            dwAirResist(0),
            dwEarthResist(0),
            dwWaterResist(0),
            dwFireResist(0),
            dwDarkResist(0),
            dwLightResist(0),
            dwAirPower(0),
            dwEarthPower(0),
            dwWaterPower(0),
            dwFirePower(0),
            dwDarkPower(0),
            dwLightPower(0),
            dwLevel(0),
            dwHP(0),
            dwDodgeSkill(0),
            dblAC(0),
            dwAppearance(0),
            dwDressBody(0),
            dwDressFeet(0),
            dwDressGloves(0),
            dwDressHelm(0),
            dwDressLegs(0),
            dwDressWeapon(0),
            dwDressShield(0),
            dwDressCape(0),
            dwAggressivness(0),
            dwClanID(0),
            dwSpeed(0),
            dblXPperHit(0),
            dblXPperDeath(0),
            dwMinGiveGold(0),
            dwMaxGiveGold(0),
            boCanAttack(true)
        {}


        bool m_ReadOnly;

        std::vector< CreatureAttack > vAttacks;
        std::vector< CreatureDeathItem > vItems;
        std::vector< CreatureDeathFlag > vDeathFlags;

        DWORD dwBindedID;
        std::string csID;
        std::string csName;
        DWORD dwSTR;
        DWORD dwEND;
        DWORD dwAGI;
        DWORD dwINT;
        DWORD dwWIL;
        DWORD dwWIS;        
        DWORD dwLCK;
        DWORD dwAirResist;
        DWORD dwEarthResist;
        DWORD dwWaterResist;
        DWORD dwFireResist;
        DWORD dwDarkResist;
        DWORD dwLightResist;
        DWORD dwAirPower;
        DWORD dwEarthPower;
        DWORD dwWaterPower;
        DWORD dwFirePower;
        DWORD dwDarkPower;
        DWORD dwLightPower;
        DWORD dwLevel;
        DWORD dwHP;
        DWORD dwDodgeSkill;
        double dblAC;
        DWORD dwAppearance;
        DWORD dwDressBody;
        DWORD dwDressFeet;
        DWORD dwDressGloves;
        DWORD dwDressHelm;
        DWORD dwDressLegs;
        DWORD dwDressWeapon;
        DWORD dwDressShield;
        DWORD dwDressCape;
        DWORD dwAggressivness;
        DWORD dwClanID;
        DWORD dwSpeed;
        double dblXPperHit;
        double dblXPperDeath;
        DWORD dwMinGiveGold;
        DWORD dwMaxGiveGold;
        bool  boCanAttack;
    };

    std::vector< CreatureData > &GetCreatures( void );

    // Saves to a wdaFile
    virtual void SaveTo( WDAFile &wdaFile );
    
    // Creates from a wdaFile.
    virtual void CreateFrom( WDAFile &wdaFile, bool createReadOnly );

    CreatureData *GetWritableCreature( std::string id );
    CreatureData *GetReadOnlyCreature( std::string id );



#ifndef NO_DAO_SUPPORT    
    // AreaLinks::CreateFrom does not need cRecord, it builds directly from the cDatabase.
    virtual void CreateFrom( CDaoRecordset &cRecord, CDaoDatabase &cDatabase );    
#endif

private:
    // Lists all possible objects.
    std::vector< CreatureData > vCreatures;

};

#endif // !defined(AFX_WDACREATURES_H__9C6E6333_6095_11D3_856C_00E02922FA40__INCLUDED_)

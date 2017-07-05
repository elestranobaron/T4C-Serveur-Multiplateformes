// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    NPC
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          NPC
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __NPC__
#define __NPC__

// Include files
#include "../Core/WDAFile.h"
#include "Instruction.h"
#include "NPC_Editor.h"
#include "RootInstruction.h"

#include <string>

//  todo
namespace NPC_Editor
{
class NPC
{
public:
    NPC( std::string name, std::string id, bool boCanMove = true, bool boPrivateTalk = false );
    NPC( const NPC &onpc );
	~NPC();

    struct SoldItem{
        bool operator ==( const SoldItem &i ){
            return( itemId == i.itemId && price == i.price );
        }
        std::string itemId;
        DWORD price;
    };
    struct BoughtItem{
        bool operator ==( const BoughtItem &i ){
            return( sellType == i.sellType && minPrice == i.minPrice && maxPrice == i.maxPrice );
        }
        SellTypes sellType;
        DWORD minPrice;
        DWORD maxPrice;
    };
    struct TrainedSkill{
        bool operator ==( const TrainedSkill &i ){
            return( skillId == i.skillId && maxSkillPnts == i.maxSkillPnts && price == i.price );
        }
        DWORD skillId;
        DWORD maxSkillPnts;
        DWORD price;
    };
    struct TaughtSkill{
        bool operator ==( const TaughtSkill &i ){
            return( skillId == i.skillId && price == i.price );
        }
        DWORD skillId;
        DWORD skillPnts;
        DWORD price;
    };

    std::string GetName() const { return name; }
	void SetName(const std::string &thename){	name = thename; }
    
    std::string GetId() const { return id; }
	void SetId(const std::string &theid){	id = theid; }
    
    std::string GetCreatureId() const { return creatureId; }
    void SetCreatureId(const std::string &thecreatureId){ creatureId = thecreatureId; }

	bool GetCanMove() const { return boCanMove; }
	void SetCanMove( const bool bState ) { boCanMove = bState; }

	bool GetPrivateTalk() const { return boPrivateTalk; }
	void SetPrivateTalk( const bool bState ) { boPrivateTalk = bState; }
    
    bool IsIntegrityOK();
    
    bool AddInstruction( Instruction *ins, Instruction *relativeIns, InsertionRelation relation );
    bool MoveInstruction( Instruction *instruction, Instruction *relativeIns, InsertionRelation relation );
    void DeleteInstruction( Instruction *ins );
        
    void Save( WDAFile &file );
    void Load( WDAFile &file );

    void SetSoldItemList( const std::list< SoldItem > &itemList ){
        itemsSold = itemList;
    }
    void GetSoldItemList( std::list< SoldItem >&itemList ){
        itemList = itemsSold;
    }
    void SetBoughtItemList( const std::list< BoughtItem > &itemList ){
        itemsBought = itemList;
    }
    void GetBoughtItemList( std::list< BoughtItem > &itemList ){
        itemList = itemsBought;
    }

    void GetTrainedSkillList( std::list< TrainedSkill > &skillList ){
        skillList = trainedSkills;
    }
    void SetTrainedSkillList( const std::list< TrainedSkill > &skillList ){
        trainedSkills = skillList;
    }

    void GetTaughtSkillList( std::list< TaughtSkill > &skillList ){
        skillList = taughtSkills;
    }
    void SetTaughtSkillList( const std::list< TaughtSkill > &skillList ){
        taughtSkills = skillList;
    }

    NPC &operator = ( const NPC &onpc );
	
    RootInstruction *GetRootInstruction();
private:

    std::string name;
	std::string id;
    std::string creatureId;

	bool boPrivateTalk;
	bool boCanMove;

	RootInstruction rootInstruction;

    std::list< SoldItem > itemsSold;
    std::list< BoughtItem > itemsBought;
    std::list< TrainedSkill > trainedSkills;
    std::list< TaughtSkill > taughtSkills;
};

// END CLASS DEFINITION NPC
            
}
#endif // __NPC__
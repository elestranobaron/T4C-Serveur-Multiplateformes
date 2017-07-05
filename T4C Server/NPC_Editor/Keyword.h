// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    Keyword
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          Keyword
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __Keyword__
#define __Keyword__

// Include files
#include "CompositeInstruction.h"
#include "NPC_Editor.h"
#include "../Core/WDAFile.h"

//  todo
namespace NPC_Editor
{
class Keyword	: public CompositeInstruction
{
public:
	Keyword();
	~Keyword();
    KeywordRelations GetKwRelation() const { return kwRelation; }
	void SetKwRelation(const KeywordRelations &thekwRelation){	kwRelation = thekwRelation; }
    void GetKw( std::list< std::string > &kws ){
        kws = keywords;
    }
    void SetKw( const std::list< std::string > &kws );
    
    void SaveImp( WDAFile &file );
    void LoadImp( WDAFile &file );
    
    bool IsDefaultKw(){
        return( GetHelpText() == GetAppString( IDS_DEFAULT_KEYWORD_HELP ) );
    }
    bool IsInitKw(){
        return( GetHelpText() == GetAppString( IDS_INITIAL_KEYWORD_HELP ) );
    }

	bool IsByeKw(){
		return( GetHelpText() == GetAppString( IDS_BYE_KEYWORD_HELP ) );
	}

	bool IsDeathKw(){
		return( GetName() == GetAppString( IDS_ONDEATH_KEYWORD_NAME ) );
	}

	bool IsAttackedKw(){
		return( GetName() == GetAppString( IDS_ONATTACKED_KEYWORD_NAME ) );
	}

	bool IsAttackKw(){
		return( GetName() == GetAppString( IDS_ONATTACK_KEYWORD_NAME ) );
	}

    bool IsDefaultInitKw(){
        return( IsDefaultKw() || IsInitKw() );
    }

	bool IsTriggerKw(){
		return( IsDeathKw() || IsAttackedKw() || IsAttackKw() );
	}


protected:

    Instruction *Clone();
private:
    void UpdateName();

    std::list<std::string>  keywords; 
	KeywordRelations        kwRelation; 

};

// END CLASS DEFINITION Keyword
            
}
#endif // __Keyword__
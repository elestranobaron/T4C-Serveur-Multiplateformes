// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    IfFlow
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          IfFlow
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __IfFlow__
#define __IfFlow__

// Include files
#include "../Core/BoostFormula.h"
#include "../Core/WDAFile.h"
#include "ControlFlow.h"
#include "ElseFlow.h"
#include "ElseIfFlow.h"

//  todo
namespace NPC_Editor
{
class IfFlow	: public Condition
{
public:
	IfFlow();
	~IfFlow();
    
    void SaveImp( WDAFile &file );
    void LoadImp( WDAFile &file );

    // Accessors
    void GetElseIfs( std::list< Instruction * > &elseIfs );
	ElseFlow* GetElseFlow();
    
    virtual bool AddInstruction( Instruction *ins, Instruction *relativeIns, InsertionRelation relation, bool &stopSearch );
    virtual void DeleteInstruction( Instruction *ins );

    virtual void SetCondition(const std::string &thecondition);

protected:
    Instruction *Clone();

private:
    void UpdateName();

	std::list<ElseIfFlow*>  elseIfs;
	ElseFlow               *elseFlow; 

};

// END CLASS DEFINITION IfFlow
            
}
#endif // __IfFlow__
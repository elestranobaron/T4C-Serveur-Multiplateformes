// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    CompositeInstruction
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          CompositeInstruction
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __CompositeInstruction__
#define __CompositeInstruction__

// Include files
#include "Instruction.h"
#include "NPC_Editor.h"
#include "../Core/WDAFile.h"

//  todo
namespace NPC_Editor
{
class CompositeInstruction	: public Instruction
{
public:
	CompositeInstruction( std::string name, std::string helpText, InstructionIds id );
	~CompositeInstruction();
    
    bool MoveInstruction( Instruction *ins, Instruction *relativeIns, InsertionRelation relation );
    void DeleteInstruction( Instruction *ins );
    bool AddInstruction( Instruction *ins, Instruction *relativeIns, InsertionRelation relation, bool &stopSearch );
        
    virtual void Save( WDAFile &file );
    virtual void Load( WDAFile &file );    

    void GetSubInstructions( std::list< Instruction * > &subInstructions );

    virtual bool AcceptsSubInstructions(){
        return true;
    }    

    virtual Instruction *Clone() = 0;
    virtual void Copy( Instruction *theCopy );

protected:
	std::list<Instruction*>	subInstructions; 

};

// END CLASS DEFINITION CompositeInstruction
            
}
#endif // __CompositeInstruction__
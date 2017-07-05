// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    RootInstruction
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          RootInstruction
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __RootInstruction__
#define __RootInstruction__

// Include files
#include "CompositeInstruction.h"
#include "Instruction.h"
#include "NPC_Editor.h"
#include "../Core/WDAFile.h"

//  todo
namespace NPC_Editor
{
class RootInstruction	: public CompositeInstruction
{
public:
	RootInstruction();
	~RootInstruction();
    
    bool AddInstruction( Instruction *ins, Instruction *relativeIns, InsertionRelation relation, bool &stopSearch );
    
    void SaveImp( WDAFile &file );
    void LoadImp( WDAFile &file );

protected:
    Instruction *Clone(){ return NULL; };

private:
    void UpdateName(){};

};

// END CLASS DEFINITION RootInstruction
            
}
#endif // __RootInstruction__
#include "stdafx.h"
#include "RootInstruction.h"

using namespace std;

namespace{
    string AnGetName(){
        return "<root-reserved>";
    }
    string AnGetHelp(){
        return "<root-reserved>";
    }
};


namespace NPC_Editor
{

RootInstruction::RootInstruction()	: CompositeInstruction( AnGetName(), AnGetHelp(), InsRoot)
{
}

RootInstruction::~RootInstruction()
{
}
/////////////////////////////////////////////////////////////////////////////
bool RootInstruction::AddInstruction
/////////////////////////////////////////////////////////////////////////////
// Adds an instruction to the root. First checks if it is added directly 
// at the root, then forwards it to CompositeInstruction.
//
(
Instruction *ins,
Instruction *relativeIns,
InsertionRelation relation,
bool &stopSearch
)
// Return: InsertionRelation
/////////////////////////////////////////////////////////////////////////////
{
    bool kwCheck = false;
    
    // If the relative instruction is the root.
    if( relativeIns == this || relativeIns == NULL ){
        kwCheck = true;
    }

    // If the relative instruction is part of the root's subinstructions.
    if( relation == asNext || relation == asPrevious ){
        list< Instruction * >::iterator i;
        for( i = subInstructions.begin(); i != subInstructions.end(); i++ ){
            if( (*i) == relativeIns ){
                kwCheck = true;
                break;
            }
        }
    }
    
    if( kwCheck ){
        // Return an error if the instruction isn't a keyword.
        if( ins->GetId() != InsKeyword ){
            SetErrorStrId( IDS_CANNOT_ADD_NON_KEYWORD_TO_ROOT );
            stopSearch = true;
            return false;
        }
    }
	

    return CompositeInstruction::AddInstruction( ins, relativeIns, relation, stopSearch );
}
/////////////////////////////////////////////////////////////////////////////
void  RootInstruction::SaveImp
/////////////////////////////////////////////////////////////////////////////
// 
//
(
 WDAFile &file
)
// Return: void 
/////////////////////////////////////////////////////////////////////////////
{
	
}
/////////////////////////////////////////////////////////////////////////////
void RootInstruction::LoadImp
/////////////////////////////////////////////////////////////////////////////
// 
//
(
WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
	
}
} // NPC_Editor


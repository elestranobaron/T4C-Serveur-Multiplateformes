#include "stdafx.h"
#include "CompositeInstruction.h"
#include "InstructionFactory.h"

using namespace std;

namespace NPC_Editor
{

CompositeInstruction::CompositeInstruction( std::string name, std::string helpText, InstructionIds id ) :
    Instruction( name, helpText, id )
{
}

CompositeInstruction::~CompositeInstruction()
{
    // Destroy all instructions
    list< Instruction * >::iterator i;
    for( i = subInstructions.begin(); i != subInstructions.end(); i++ ){
        delete *i;
    }
}
/////////////////////////////////////////////////////////////////////////////
bool CompositeInstruction::MoveInstruction
/////////////////////////////////////////////////////////////////////////////
// 
//
(
Instruction *ins,
Instruction *relativeIns,
InsertionRelation relation
)
// Return: InsertionRelation
/////////////////////////////////////////////////////////////////////////////
{

    return false;
}
/////////////////////////////////////////////////////////////////////////////
void CompositeInstruction::DeleteInstruction
/////////////////////////////////////////////////////////////////////////////
// 
//
(
Instruction *ins
)
// Return: Instruction
/////////////////////////////////////////////////////////////////////////////
{
    // Try to find the instruction
    list< Instruction * >::iterator i;
    for( i = subInstructions.begin(); i != subInstructions.end(); i++ ){
        if( *i == ins ){
            i = subInstructions.erase( i );
        }
    }
    for( i = subInstructions.begin(); i != subInstructions.end(); i++ ){
        (*i)->DeleteInstruction( ins );
    }
}
/////////////////////////////////////////////////////////////////////////////
bool CompositeInstruction::AddInstruction
/////////////////////////////////////////////////////////////////////////////
// Adds an instruction. This function will check for a relation between
// the given relative instruction and its sub instructions, then yield
// the control flow to them if it hasn't found any.
//
(
Instruction *ins,
Instruction *relativeIns,
InsertionRelation relation,
bool &stopSearch
)
// Return: bool
/////////////////////////////////////////////////////////////////////////////
{
    // Cannot have a NULL relative instruction.
    ATLASSERT( ins != NULL );

    if( ins == NULL ){
        SetProgramError( "CompositeInstruction::AddInstruction -> Cannot add a NULL instruction." ); 
        return false;
    }

    // If adding an instruction as child of this one.
    if( relation == asChild && ( relativeIns == this || relativeIns == NULL ) ){
        // Add it to the instruction list
        subInstructions.push_back( ins );
        return true;
    }

    // Check all instruction for their potential relationship.
    list< Instruction * >::iterator i;
    for( i = subInstructions.begin(); i != subInstructions.end(); i++ ){        
        // If forwarding the instruction worked.
        if( (*i)->AddInstruction( ins, relativeIns, relation, stopSearch ) ){
            return true;
        }
        // If the forwarding requires that the search stops (a relation was
        // found but adding was refused).
        if( stopSearch ){
            return false;
        }

        // Check for the next relation.
        if( relation == asNext && (*i) == relativeIns ){
            i++; // insert after.
            // Add the instruction right after this one.
            subInstructions.insert( i, ins );
            return true;
        }else if( relation == asPrevious && (*i) == relativeIns ){
            subInstructions.insert( i, ins );
            return true;
        }
    }
	
    // No instruction was found.
    SetProgramError( "CompositeInstruction::AddInstruction -> The relative instruction was never found." );
    return false;
}

/////////////////////////////////////////////////////////////////////////////
void  CompositeInstruction::Save
/////////////////////////////////////////////////////////////////////////////
// Save all instructions imbedded in this instruction.
//
(
  WDAFile &file
)
// Return: void 
/////////////////////////////////////////////////////////////////////////////
{
    // Save the instruction part.
    Instruction::Save( file );

    DWORD version = 0x01;
    DWORD size = subInstructions.size();
    
    file.Write( version );   
    file.Write( size );

    std::list<Instruction*>::iterator i;
    for( i = subInstructions.begin(); i != subInstructions.end(); i++ ){
        Instruction *ins = (*i);
        // Save the instruction Id.
        DWORD theId = ins->GetId();
        file.Write( theId );
        
        // Save the instructions data.
        ins->SaveImp( file );
        // Save any sub-instructions.
        ins->Save( file );
    }
}
/////////////////////////////////////////////////////////////////////////////
void CompositeInstruction::Load
/////////////////////////////////////////////////////////////////////////////
// 
//
(
 WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    // Load the instruction part.
    Instruction::Load( file );

    DWORD version = 0;
    DWORD size = 0, i;

    file.Read( version );
    file.Read( size );
    for( i = 0; i != size; i++ ){
        DWORD theId;
        file.Read( theId );

        Instruction *ins = InstructionFactory::GetInstance()->CreateInstruction( (InstructionIds)theId );
        if( ins == NULL ){
            throw "Program Error";
        }
        
        ins->LoadImp( file );
        ins->Load( file );

        ins->UpdateName();

        subInstructions.push_back( ins );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CompositeInstruction::GetSubInstructions
//////////////////////////////////////////////////////////////////////////////////////////
// Returns all sub-instructions under this instruction.
// 
(
 std::list< Instruction * > &subIns // The container that is to receive the instructions.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    std::list< Instruction * >::iterator i;
    for( i = subInstructions.begin(); i != subInstructions.end(); i++ ){
        subIns.push_back( *i );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CompositeInstruction::Copy
//////////////////////////////////////////////////////////////////////////////////////////
// Copies the sub instructions from the given copy
// 
(
 Instruction *theCopy // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Copy the normal instruction data
    Instruction::Copy( theCopy );

    // Clear the previous sub-instructions.
    std::list< Instruction * >::iterator i;
    for( i = subInstructions.begin(); i != subInstructions.end(); i++ ){
        delete *i;
    }
    subInstructions.clear();

    list< Instruction * > copySubInstructions;
    theCopy->GetSubInstructions( copySubInstructions );

    // Clone all subinstructions.
    for( i = copySubInstructions.begin(); i != copySubInstructions.end(); i++ ){
        subInstructions.push_back( (*i)->Clone() );
    }
}
} // NPC_Editor


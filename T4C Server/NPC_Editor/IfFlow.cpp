#include "stdafx.h"
#include "IfFlow.h"
#include "InstructionFactory.h"

using namespace std;

namespace{
    string AnGetName(){
        return GetAppString( IDS_INST_IF );
    }
    string AnGetHelp(){
        return GetAppString( IDS_INST_IF_HELP );
    }    
};

namespace NPC_Editor
{

IfFlow::IfFlow() : 
    Condition( AnGetName(), AnGetHelp(), InsIf ),
    elseFlow( NULL )
{
}

IfFlow::~IfFlow()
{
    if( elseFlow != NULL ){
        delete elseFlow;
    }
    list< ElseIfFlow * >::iterator i;
    for( i = elseIfs.begin(); i != elseIfs.end(); i++ ){
        delete *i;
    }
}
/////////////////////////////////////////////////////////////////////////////
void IfFlow::SaveImp
/////////////////////////////////////////////////////////////////////////////
// 
//
(
WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    Condition::SaveImp( file );

    file.Write( bool( elseFlow != NULL ) );

    if( elseFlow != NULL ){
        elseFlow->SaveImp( file );
        elseFlow->Save( file );
    }

    DWORD size = elseIfs.size();
    std::list<ElseIfFlow*>::iterator i;
    
    file.Write( size );

    for( i = elseIfs.begin(); i != elseIfs.end(); i++ ){
        (*i)->SaveImp( file );
        (*i)->Save( file );
    }
}
/////////////////////////////////////////////////////////////////////////////
void IfFlow::LoadImp
/////////////////////////////////////////////////////////////////////////////
// 
//
(
WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    Condition::LoadImp( file );

    bool isElseFlow = false;
    file.Read( isElseFlow );

    if( isElseFlow ){
        Instruction *ins = InstructionFactory::GetInstance()->CreateInstruction( InsElse );
        if( ins == NULL ){
            throw "Program Error";
        }
        ins->LoadImp( file );
        ins->Load( file );
        
        ins->UpdateName();

        elseFlow = static_cast< ElseFlow * >( ins );
    }

    DWORD size = 0, i;
    
    file.Read( size );
    for( i = 0; i != size; i++ ){
        Instruction *ins = InstructionFactory::GetInstance()->CreateInstruction( InsElseIf );
        if( ins == NULL ){
            throw "Program Error";
        }
        ins->LoadImp( file );
        ins->Load( file );

        ins->UpdateName();
        
        elseIfs.push_back( static_cast< ElseIfFlow * >( ins ) );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
bool IfFlow::AddInstruction
//////////////////////////////////////////////////////////////////////////////////////////
// Checks the ElseIF and Else.
// 
(
 Instruction *ins,              // The instruction to add
 Instruction *relativeIns,      // The relative instruction.
 InsertionRelation relation,    // The relation.
 bool &stopSearch               // 
)
// Return: virtual bool, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If this is a Else or ElseIF to add to this 
    if( ins->GetId() == InsElse && relativeIns == this ){
        stopSearch = true;
        if( elseFlow != NULL ){
            SetErrorStrId( IDS_CAN_ONLY_HAVE_ONE_ELSE );
            return false;
        }
        // Add the instruction to the elseFlow.
        elseFlow = static_cast< ElseFlow * >( ins );
        return true;
    }else if( ins->GetId() == InsElseIf && relativeIns == this ){
        stopSearch = true;        
        // Add the instruction to the elseIfFlow.
        elseIfs.push_back( static_cast< ElseIfFlow * >( ins ) );
        return true;
    }else{
        if( elseFlow != NULL ){
            if( elseFlow->AddInstruction( ins, relativeIns, relation, stopSearch ) ){
                return true;
            }
            if( stopSearch ){
                return false;
            }
        }
        // Check all elseIfs for their potential relationship.
        list< ElseIfFlow * >::iterator i;
        for( i = elseIfs.begin(); i != elseIfs.end(); i++ ){        
            // If forwarding the instruction worked.
            if( (*i)->AddInstruction( ins, relativeIns, relation, stopSearch ) ){
                return true;
            }
            // If the forwarding requires that the search stops (a relation was
            // found but adding was refused).
            if( stopSearch ){
                return false;
            }
        }

        return CompositeInstruction::AddInstruction( ins, relativeIns, relation, stopSearch );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void IfFlow::DeleteInstruction
//////////////////////////////////////////////////////////////////////////////////////////
// Deletes an instruction.
// 
(
 Instruction *ins // The instruction to delete.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( ins == elseFlow ){
        elseFlow = NULL;
    }

    list< ElseIfFlow * >::iterator i;
    for( i = elseIfs.begin(); i != elseIfs.end(); i++ ){
        if( *i == ins ){
            i = elseIfs.erase( i );
        }
    }

    CompositeInstruction::DeleteInstruction( ins );
}

//////////////////////////////////////////////////////////////////////////////////////////
void IfFlow::GetElseIfs
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the list of ElseIfs.
// 
(
 std::list< Instruction * > &ielseIfs // The list of ElseIfs.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    list< ElseIfFlow * >::iterator i;
    for( i = elseIfs.begin(); i != elseIfs.end(); i++ ){
        ielseIfs.push_back( *i );
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
ElseFlow* IfFlow::GetElseFlow( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the else flow. NULL if none.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return elseFlow;
}

//////////////////////////////////////////////////////////////////////////////////////////
Instruction *IfFlow::Clone( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Clone IF
//////////////////////////////////////////////////////////////////////////////////////////
{
    IfFlow *iff = new IfFlow;
    
    iff->Copy( this );
	
    // Clone all ElseIfs
    list< ElseIfFlow * >::iterator i;
    for( i = elseIfs.begin(); i != elseIfs.end(); i++ ){
        iff->elseIfs.push_back( static_cast< ElseIfFlow * >( (*i)->Clone() ) );
    }
    
    // Clone the else flow.
    if( elseFlow != NULL ){
        iff->elseFlow = static_cast< ElseFlow * >( this->elseFlow->Clone() );
    }

    return iff;
}

//////////////////////////////////////////////////////////////////////////////////////////
void IfFlow::UpdateName( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Update the IF's content.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    Condition::UpdateName( AnGetName() );
}

//////////////////////////////////////////////////////////////////////////////////////////
void IfFlow::SetCondition
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the condition and updates the name
// 
(
 const std::string &thecondition // The expression.
)
// Return: virtual, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    Condition::SetCondition( thecondition );

    UpdateName();
}

} // NPC_Editor


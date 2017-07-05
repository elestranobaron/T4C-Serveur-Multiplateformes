#include "stdafx.h"
#include "Command.h"

using namespace std;

namespace NPC_Editor
{

Command::Command( std::string name, std::string helpText, InstructionIds id ) :
    Instruction( name, helpText, id )
{
    cmdName = name;
}

Command::~Command()
{
}
/////////////////////////////////////////////////////////////////////////////
void Command::SaveImp
/////////////////////////////////////////////////////////////////////////////
// 
//
(
WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    DWORD size = values.size(), i;
    file.Write( size );
    
    for( i = 0; i != size; i++ ){
        file.Write( values[ i ] );
    }
}
/////////////////////////////////////////////////////////////////////////////
void Command::LoadImp
/////////////////////////////////////////////////////////////////////////////
// 
//
(
WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    DWORD size = 0, i;
    file.Read( size );
    for( i = 0; i != size; i++ ){
        string value;
        file.Read( value );
        values.push_back( value );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
Instruction *Command::Clone( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
    Command *cmd = new Command( this->GetName(), this->GetHelpText(), this->GetId() );

    // Copy the instruction data.
    cmd->Copy( this );
    cmd->attributes = this->attributes;
    cmd->values = this->values;
    return cmd;
}

void Command::GetValues(std::vector<std::string> &theValue){ 
    theValue = values;
}
void Command::SetValues(const std::vector<std::string> &thevalues){	
    values = thevalues; 
}

//////////////////////////////////////////////////////////////////////////////////////////
void Command::UpdateName( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Update the name.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( values.size() == 0 ){
        SetName( cmdName );
        return;
    }

    std::string newName = cmdName;
    newName += "( ";
    int i;
    for( i = 0; i < values.size(); i++ ){
        newName += values[ i ];
        if( i + 1 < values.size() ){
            newName += ", ";
        }
    }
    newName += " )";
    SetName( newName );
}

} // NPC_Editor


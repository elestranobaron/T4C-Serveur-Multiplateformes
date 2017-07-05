#include "stdafx.h"
// Static Model

// 
// Static Model

// 
#include "ControlFlow.h"
namespace NPC_Editor
{

ControlFlow::ControlFlow( std::string name, std::string helpText, InstructionIds id ) :
    CompositeInstruction( name, helpText, id )
{
}

ControlFlow::~ControlFlow()
{
}
} // NPC_Editor


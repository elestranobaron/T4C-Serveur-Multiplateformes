#include "stdafx.h"
#include "NPC.h"

using namespace std;

namespace NPC_Editor
{

NPC::NPC( std::string iname, std::string iid, bool imove, bool iprivate ) :
    name( iname ), id( iid ), boCanMove( imove ), boPrivateTalk( iprivate )
{
}

NPC::NPC( const NPC &onpc ){
    *this = onpc;
}

NPC::~NPC()
{
}

/////////////////////////////////////////////////////////////////////////////
bool NPC::IsIntegrityOK()
/////////////////////////////////////////////////////////////////////////////
// Currently no integrity check.
//
// Return: bool, true
/////////////////////////////////////////////////////////////////////////////
{
    return true;	
}
/////////////////////////////////////////////////////////////////////////////
bool NPC::AddInstruction
/////////////////////////////////////////////////////////////////////////////
// 
//
(
Instruction *ins,
Instruction *relativeIns,
InsertionRelation relation
)
// Return: bool
/////////////////////////////////////////////////////////////////////////////
{
    // Cannot add a NULL instruction.
    ATLASSERT( ins != NULL );
    if( ins == NULL ){ 
        SetProgramError( "NPC::AddInstruction -> Added NULL instruction instance." );
        return false; 
    };

    if( ins->GetId() == InsElseIf || ins->GetId() == InsElse ){
        ATLASSERT( relativeIns != NULL );
        if( relativeIns == NULL ){
            SetProgramError( "NPC::AddInstruction -> Added NULL relativeInstruction to Else/ElseIF." );
            return false;
        }
        if( relativeIns->GetId() != InsIf || relation != asChild ){
            SetErrorStrId( IDS_ELSE_MUST_BE_IF_CHILD );
            return false;
        }
    }
	
    // Forward to root instruction.
    bool stopSearch = false;
    return rootInstruction.AddInstruction( ins, relativeIns, relation, stopSearch );
}
/////////////////////////////////////////////////////////////////////////////
bool NPC::MoveInstruction
/////////////////////////////////////////////////////////////////////////////
// 
//
(
Instruction *ins,
Instruction *relativeIns,
InsertionRelation relation
)
// Return: bool
/////////////////////////////////////////////////////////////////////////////
{
    bool stopSearch = false;

    if( ins->GetId() == InsElse || ins->GetId() == InsElseIf ){
        return false;
    }

    if( rootInstruction.AddInstruction( ins, relativeIns, relation, stopSearch ) ){
        stopSearch = false;
        rootInstruction.DeleteInstruction( ins );
        return rootInstruction.AddInstruction( ins, relativeIns, relation, stopSearch );
    }

    return false;
}
/////////////////////////////////////////////////////////////////////////////
void NPC::DeleteInstruction
/////////////////////////////////////////////////////////////////////////////
// Deletes an instruction. Forwards it to the root instruction.
//
(
Instruction *ins
)
// Return: Instruction
/////////////////////////////////////////////////////////////////////////////
{
    // Cannot delete the root instruction.
    ATLASSERT( ins != &rootInstruction );
    rootInstruction.DeleteInstruction( ins );
}
//////////////////////////////////////////////////////////////////////////////////////////
RootInstruction *NPC::GetRootInstruction( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the root instruction.
//
//////////////////////////////////////////////////////////////////////////////////////////
{
    return &rootInstruction;
}

/////////////////////////////////////////////////////////////////////////////
void NPC::Save
/////////////////////////////////////////////////////////////////////////////
// 
//
(
WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    DWORD version = 0x02;
    file.Write( version );
    file.Write( creatureId );
	file.Write( boCanMove );
	file.Write( boPrivateTalk );

	for( int xxx = 0; xxx < 512; xxx++ )
		file.Write( true );

    {
        DWORD size = itemsSold.size();
        file.Write( size );

        list< SoldItem >::iterator i;
        for( i = itemsSold.begin(); i != itemsSold.end(); i++ ){
            file.Write( (*i).itemId );
            file.Write( (*i).price );
        }
    }
    {
        DWORD size = itemsBought.size();
        file.Write( size );

        list< BoughtItem >::iterator i;
        for( i = itemsBought.begin(); i != itemsBought.end(); i++ ){
            DWORD sellType = (*i).sellType;
            file.Write( sellType );
            file.Write( (*i).minPrice );
            file.Write( (*i).maxPrice );
        }
    }
    {
        DWORD size = trainedSkills.size();
        file.Write( size );

        list< TrainedSkill >::iterator i;
        for( i = trainedSkills.begin(); i != trainedSkills.end(); i++ ){
            file.Write( (*i).skillId );
            file.Write( (*i).maxSkillPnts );
            file.Write( (*i).price );
        }
    }
    {
        DWORD size = taughtSkills.size();
        file.Write( size );

        list< TaughtSkill >::iterator i;
        for( i = taughtSkills.begin(); i != taughtSkills.end(); i++ ){
            file.Write( (*i).skillId );
            file.Write( (*i).skillPnts );
            file.Write( (*i).price );
        }
    }
    
    // Save the instruction tree.
    rootInstruction.Save( file );
}
/////////////////////////////////////////////////////////////////////////////
void NPC::Load
/////////////////////////////////////////////////////////////////////////////
// 
//
(
 WDAFile &file
)
// Return: void 
/////////////////////////////////////////////////////////////////////////////
{
    DWORD version;
    
    file.Read( version );
    file.Read( creatureId );

	if( version == 0x02 )
	{
		file.Read( boCanMove );
		file.Read( boPrivateTalk );

		bool buf;
		for( int xxx = 0; xxx < 512; xxx++ )
			file.Read( buf );
	}

    DWORD size, i;
    file.Read( size );
    for( i = 0; i != size; i++ ){
        SoldItem item;
        file.Read( item.itemId );
        file.Read( item.price );
        itemsSold.push_back( item );
    }
    
    file.Read( size );
    for( i = 0; i != size; i++ ){
        BoughtItem item;
        DWORD sellType;
        file.Read( sellType );
        item.sellType = (SellTypes)sellType;
        file.Read( item.minPrice );
        file.Read( item.maxPrice );
        itemsBought.push_back( item );
    }

    file.Read( size );
    for( i = 0; i != size; i++ ){
        TrainedSkill skill;
        file.Read( skill.skillId );
        file.Read( skill.maxSkillPnts );
        file.Read( skill.price );
        trainedSkills.push_back( skill );
    }
    
    file.Read( size );
    for( i = 0; i != size; i++ ){
        TaughtSkill skill;
        file.Read( skill.skillId );
        file.Read( skill.skillPnts );
        file.Read( skill.price );
        taughtSkills.push_back( skill );
    }
    
    // Save the instruction tree.
    rootInstruction.Load( file );	
}

//////////////////////////////////////////////////////////////////////////////////////////
NPC &NPC::operator =
//////////////////////////////////////////////////////////////////////////////////////////
// Assignement operator.
// 
(
 const NPC &onpc // The NPC copy.
)
// Return: NPC &NPC::operator, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    name = onpc.name;
	id = onpc.id;
	boCanMove = onpc.boCanMove;
	boPrivateTalk = onpc.boPrivateTalk;
    creatureId = onpc.creatureId;
    itemsSold = onpc.itemsSold;
    itemsBought = onpc.itemsBought;
    trainedSkills = onpc.trainedSkills;
    taughtSkills = onpc.taughtSkills;
	
    
    rootInstruction.Copy( const_cast< RootInstruction * >( &onpc.rootInstruction ) );

    return *this;
}

} // NPC_Editor


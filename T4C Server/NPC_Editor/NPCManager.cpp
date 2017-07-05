#include "stdafx.h"
#include "NPCManager.h"
#include "InstructionFactory.h"
#include "..\T4CLog.h"

using namespace std;

namespace NPC_Editor
{

NPCManager::NPCManager()
{
    // Load the NPCs.

}

NPCManager::~NPCManager()
{
}
/////////////////////////////////////////////////////////////////////////////
NPC *NPCManager::CreateNPC
/////////////////////////////////////////////////////////////////////////////
// Creates an NPC with a name and an ID. If the ID of the NPC already exists,
// the function returns NULL, otherwise it returns the newly created NPC.
//
(
string name,
string id
)
// Return: NPC
/////////////////////////////////////////////////////////////////////////////
{
    // NPC already exists
    NpcMap::iterator i = npcList.find( id );
    if( i != npcList.end() ){
        SetErrorStrId( IDS_ERROR_NPC_ID_ALREADY_EXIST );
        return NULL;
    }

    NPC *newNpc = new NPC( name, id );

    InstructionFactory *factory = InstructionFactory::GetInstance();

    Instruction *initKw = factory->CreateInstruction( InsKeyword );
    Instruction *defKw = factory->CreateInstruction( InsKeyword );
    
    // The instruction factory must return valid instruction instances.
    ATLASSERT( initKw != NULL && defKw != NULL );
    if( initKw == NULL || defKw == NULL ){
        SetProgramError( "NPCManager::CreateNPC -> Got NULL default or initial keyword." );
        delete newNpc;
        return NULL;
    }

    // The initial keyword
    initKw->SetName( GetAppString( IDS_INITIAL_KEYWORD_NAME ) );
    initKw->SetHelpText( GetAppString( IDS_INITIAL_KEYWORD_HELP ) );

    // The default keyword.
    defKw->SetName( GetAppString( IDS_DEFAULT_KEYWORD_NAME ) );
    defKw->SetHelpText( GetAppString( IDS_DEFAULT_KEYWORD_HELP ) );
    

    // Add the default and initial keywords to the NPC.
    newNpc->AddInstruction( initKw, NULL,   asChild );
    newNpc->AddInstruction( defKw,  initKw, asNext );

    // Set the NPC's name to the NPC's id.
    newNpc->SetName( name );

    npcList[ id ] = newNpc;

    return newNpc;
}
/////////////////////////////////////////////////////////////////////////////
NPC *NPCManager::GetNPC
/////////////////////////////////////////////////////////////////////////////
// Returns the NPC instance that has the given id. The function returns NULL
// if no NPC of the given ID is found.
//
(
 string id
)
// Return: NPC
/////////////////////////////////////////////////////////////////////////////
{
    NpcMap::iterator i = npcList.find( id );
    if( i == npcList.end() ){
        SetErrorStrId( IDS_ERROR_NPC_ID_DOESNT_EXIST );
        return NULL;
    }

    return (*i).second;
}
/////////////////////////////////////////////////////////////////////////////
void NPCManager::DeleteNPC
/////////////////////////////////////////////////////////////////////////////
// Remove the NPC that has the given id. It deletes the NPC * instance as
// well.
//
(
 string id
)
/////////////////////////////////////////////////////////////////////////////
{
    NpcMap::iterator i = npcList.find( id );
    if( i == npcList.end() ){
        SetErrorStrId( IDS_ERROR_NPC_ID_DOESNT_EXIST );
        return;
    }
    delete (*i).second;
    npcList.erase( i );
}
/////////////////////////////////////////////////////////////////////////////
void NPCManager::Save
/////////////////////////////////////////////////////////////////////////////
// Save all NPCs to a WDA file
//
(
 WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    DWORD version = 0x01;

    DWORD npcQty = npcList.size();

    file.Write( version );
    file.Write( npcQty );

    NpcMap::iterator i;
    for( i = npcList.begin(); i != npcList.end(); i++ ){
        NPC *theNpc = (*i).second;
        // Save what is required to create a NPC.        
        file.Write( theNpc->GetName() );
        file.Write( theNpc->GetId() );
        
        // Save the NPC.
        theNpc->Save( file );
    }
	
}
/////////////////////////////////////////////////////////////////////////////
void NPCManager::Load
/////////////////////////////////////////////////////////////////////////////
// Loads the NPCs from a WDA file.
//
(
 WDAFile &file
)
// Return: void 
/////////////////////////////////////////////////////////////////////////////
{
    DWORD version = 0;
    DWORD npcQty = 0;
    
    file.Read( version );

    if( version != 0x01 ){
        return;
    }

    file.Read( npcQty );

    DWORD i;
    for( i = 0; i < npcQty; i++ ){
        string name, id;
        // Read the name and Id
        file.Read( name );
        file.Read( id );

        // Create the new
        NPC *newNpc = new NPC( name, id );

        // Load the NPC from the file.
        newNpc->Load( file );

        // Add to NPC list.
		if ( npcList.find(id) != npcList.end() ) {
			_LOG_DEBUG
				LOG_DEBUG_LVL1,
				"Found duplicate NPC ID %s, overriding previous one.",
				id.c_str()
			LOG_
		}
        npcList[ id ] = newNpc;
    }
	
}
/////////////////////////////////////////////////////////////////////////////
bool NPCManager::RenameNPC
/////////////////////////////////////////////////////////////////////////////
// Renames the NPC associated with the oldId and sets it the newId. If the
// newID already exists or if the oldId doesn't exist, it returns false.
//
(
 string oldId,
 string newId
)
// Return: 
/////////////////////////////////////////////////////////////////////////////
{
    NpcMap::iterator i = npcList.find( oldId );
    if( i == npcList.end() ){
        SetErrorStrId( IDS_ERROR_NPC_ID_DOESNT_EXIST );
        return false;
    }

    NpcMap::iterator j = npcList.find( newId );
    if( j != npcList.end() ){
        SetErrorStrId( IDS_ERROR_NPC_ID_ALREADY_EXIST );
        return false;
    }

    NPC *oldNpc = (*i).second;

    npcList.erase( i );
    
    oldNpc->SetId( newId );
    npcList[ newId ] = oldNpc;

    return true;
}
/////////////////////////////////////////////////////////////////////////////
void NPCManager::Initialize
/////////////////////////////////////////////////////////////////////////////
// [TODO]
//
(

)
// Return: void 
/////////////////////////////////////////////////////////////////////////////
{

	
}

//////////////////////////////////////////////////////////////////////////////////////////
NPCManager *NPCManager::GetInstance( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the npc manager instance.
//////////////////////////////////////////////////////////////////////////////////////////
{
    static NPCManager instance;
    return &instance;
}

//////////////////////////////////////////////////////////////////////////////////////////
void NPCManager::GetNPCList
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the list of NPCs in the supplied list.
// 
(
 std::list< NPC * > &inpcList // Container into which to dump the list of NPCs.
) const
//////////////////////////////////////////////////////////////////////////////////////////
{
    NpcMap::const_iterator i;
    for( i = npcList.begin(); i != npcList.end(); i++ ){
        inpcList.push_back( (*i).second );        
    }
}

} // NPC_Editor


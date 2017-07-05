///////////////////////////////////////////////////////////////////////////////////////
// NPC DLL

#include "stdafx.h"

#include <CreatureListing.h>
#include <AttackListing.h>
#include <MonsterStructure.h>
#include <NPCstructure.h>
#include <Unit.h>
#include "Random.h"

void CreateNPC();
void MonsterStatSetup();
void MonsterStatDestroy();
void RegisterNCP( void );

//////////////////////////////////////////////////////////////////////////////////////////
// Start a NPC interpretion block

//////////////////////////////////////////////////////////////////////////////////////////
// Inits NPCs
#define INIT_NPC_DATA_PART1 Random rnd; static AFX_EXTENSION_MODULE NPCsDLL;\
void RegisterNPC( void );\
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)\
{\
	UNREFERENCED_PARAMETER(lpReserved);\
	switch(dwReason) {\
    case DLL_PROCESS_ATTACH: \
			if (!AfxInitExtensionModule(NPCsDLL, hInstance))\
				return 0;

#define INIT_NPC_DATA_PART2 TRACE0("NPC DLL Initializing!\n");\
			TFCMAIN::RegisterUnitStartupFunction( MonsterStatSetup );\
			RegisterNPC();\
		break;\
    case DLL_THREAD_ATTACH: break;\
	case DLL_THREAD_DETACH: break;\
    case DLL_PROCESS_DETACH: \
			TRACE0("NPC DLL Terminating!\n");\
			MonsterStatDestroy();\
			AfxTermExtensionModule(NPCsDLL);\
		break;\
    }\
return 1;\
}\
void RegisterNPC( void ){

#define INIT_NPC_DATA INIT_NPC_DATA_PART1 INIT_NPC_DATA_PART2

#define REGISTER_NPC( ObjectName )	Unit::RegisterUnitMessageHandler( 30000, &ObjectName, #ObjectName, U_NPC, TRUE );

#define	END_INIT_NPC_DATA	};

#define INIT_NPC_CREATION	void CreateNPC(){

#define CREATE_NPC( ObjectName )	ObjectName.Create();

#define END_INIT_NPC_CREATION }

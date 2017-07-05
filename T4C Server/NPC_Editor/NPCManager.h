// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    NPCManager
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          NPCManager
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __NPCManager__
#define __NPCManager__

// Include files
#include "NPC.h"
#include "../Core/WDAFile.h"

#include <string>
#include <map>

namespace NPC_Editor
{
class NPCManager
{
public:
	~NPCManager();
    
    NPC *CreateNPC( std::string name, std::string id );
    
    NPC *GetNPC( std::string id );
    
    void DeleteNPC( std::string id );
    bool RenameNPC( std::string oldId, std::string newId );

    void Save( WDAFile &file );
    void Load( WDAFile &file );
    
    void Initialize();
    void GetNPCList( std::list< NPC * > &npcList ) const;

    static NPCManager *GetInstance();
private:
    typedef std::map<std::string, NPC *> NpcMap;

    NPCManager();

    NpcMap npcList;
};

// END CLASS DEFINITION NPCManager
            
}
#endif // __NPCManager__
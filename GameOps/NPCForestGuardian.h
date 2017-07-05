#include "NPCStructure.h"

#ifndef __NPCFORESTGUARDIAN_H
#define __NPCFORESTGUARDIAN_H

class NPCForestGuardian : public NPCstructure{
public:   
    NPCForestGuardian();
   ~NPCForestGuardian();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

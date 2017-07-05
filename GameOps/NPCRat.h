#include "NPCStructure.h"

#ifndef __NPCRAT_H
#define __NPCRAT_H

class NPCRat : public NPCstructure{
public:   
    NPCRat();
   ~NPCRat();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

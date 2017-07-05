#include "NPCStructure.h"

#ifndef __KINGAEDENASGRAVESOUL_H
#define __KINGAEDENASGRAVESOUL_H

class KingAedenasGravesoul : public NPCstructure{
public:   
    KingAedenasGravesoul();
   ~KingAedenasGravesoul();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );    
};

#endif

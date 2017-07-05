#include "NPCStructure.h"

#ifndef __GOBLINKINGGOWOGGULP_H
#define __GOBLINKINGGOWOGGULP_H

class GoblinKingGowogGulp : public NPCstructure{
public:   
    GoblinKingGowogGulp();
   ~GoblinKingGowogGulp();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

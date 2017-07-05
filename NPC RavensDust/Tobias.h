#include "NPCStructure.h"

#ifndef __TOBIAS_H
#define __TOBIAS_H

class Tobias : public NPCstructure{
public:   
    Tobias();
   ~Tobias();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

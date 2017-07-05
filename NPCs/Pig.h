#include "NPCStructure.h"

#ifndef __PIG_H
#define __PIG_H

class Pig : public NPCstructure{
public:   
    Pig();
   ~Pig();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

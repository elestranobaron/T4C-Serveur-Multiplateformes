#include "NPCStructure.h"

#ifndef __GRIMISH_H
#define __GRIMISH_H

class Grimish : public NPCstructure{
public:   
    Grimish();
   ~Grimish();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif

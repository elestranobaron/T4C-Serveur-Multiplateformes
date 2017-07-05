#include "NPCStructure.h"

#ifndef __DORKENROTSMELL_H
#define __DORKENROTSMELL_H

class DorkenRotsmell : public NPCstructure{
public:   
    DorkenRotsmell();
   ~DorkenRotsmell();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif

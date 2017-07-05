#include "NPCStructure.h"

#ifndef __MOBOLINHAADGUARD3_H
#define __MOBOLINHAADGUARD3_H

class MOBOlinHaadGuard3 : public NPCstructure{
public:   
    MOBOlinHaadGuard3();
   ~MOBOlinHaadGuard3();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif

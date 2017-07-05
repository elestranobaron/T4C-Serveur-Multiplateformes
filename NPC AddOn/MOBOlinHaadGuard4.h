#include "NPCStructure.h"

#ifndef __MOBOLINHAADGUARD4_H
#define __MOBOLINHAADGUARD4_H

class MOBOlinHaadGuard4 : public NPCstructure{
public:   
    MOBOlinHaadGuard4();
   ~MOBOlinHaadGuard4();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif

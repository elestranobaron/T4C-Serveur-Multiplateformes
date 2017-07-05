#include "SimpleMonster.h"

#ifndef __CENTAURAVENGER_H
#define __CENTAURAVENGER_H

class CentaurAvenger : public SimpleMonster{
public:   
    CentaurAvenger();
   ~CentaurAvenger();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    
};

#endif

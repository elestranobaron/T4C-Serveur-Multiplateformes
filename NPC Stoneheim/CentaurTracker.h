#include "SimpleMonster.h"

#ifndef __CENTAURTRACKER_H
#define __CENTAURTRACKER_H

class CentaurTracker : public  SimpleMonster{
public:   
    CentaurTracker();
   ~CentaurTracker();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );  
    
};

#endif

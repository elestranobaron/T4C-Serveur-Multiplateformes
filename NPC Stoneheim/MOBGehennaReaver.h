#include "SimpleMonster.h"

#ifndef __MOBGEHENNAREAVER_H
#define __MOBGEHENNAREAVER_H

class MOBGehennaReaver : public SimpleMonster{
public:   
    MOBGehennaReaver();
   ~MOBGehennaReaver();
    void Create( void );
    void OnAttackHit( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
 
};

#endif

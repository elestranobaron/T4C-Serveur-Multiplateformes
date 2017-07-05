#include "SimpleMonster.h"

#ifndef __MOBMERCENARYA_H
#define __MOBMERCENARYA_H

class MOBMercenaryA : public SimpleMonster{
public:   
    MOBMercenaryA();
   ~MOBMercenaryA();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

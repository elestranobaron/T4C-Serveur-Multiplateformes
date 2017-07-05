#include "SimpleMonster.h"

#ifndef __MOBPURIFIER_H
#define __MOBPURIFIER_H

class MOBPurifier : public SimpleMonster{
public:   
    MOBPurifier();
   ~MOBPurifier();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );    
};
#endif

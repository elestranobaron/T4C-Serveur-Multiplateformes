#include "SimpleMonster.h"

#ifndef __MOBMADMAN_H
#define __MOBMADMAN_H

class MOBMadMan : public SimpleMonster{
public:   
    MOBMadMan();
   ~MOBMadMan();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
};

#endif

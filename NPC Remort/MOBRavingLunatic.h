#include "SimpleMonster.h"

#ifndef __MOBRAVINGLUNATIC_H
#define __MOBRAVINGLUNATIC_H

class MOBRavingLunatic : public SimpleMonster{
public:   
    MOBRavingLunatic();
   ~MOBRavingLunatic();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
};

#endif

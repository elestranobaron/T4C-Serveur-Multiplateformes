#include "SimpleMonster.h"

#ifndef __MOBGIANTBLACKWIDOW_H
#define __MOBGIANTBLACKWIDOW_H

class MOBGiantBlackWidow : public SimpleMonster{
public:   
    MOBGiantBlackWidow();
   ~MOBGiantBlackWidow();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

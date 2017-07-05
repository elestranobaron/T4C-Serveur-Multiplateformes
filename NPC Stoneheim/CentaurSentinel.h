#include "SimpleMonster.h"

#ifndef __CENTAURSENTINEL_H
#define __CENTAURSENTINEL_H

class CentaurSentinel : public SimpleMonster{
public:   
    CentaurSentinel();
   ~CentaurSentinel();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );  
};

#endif

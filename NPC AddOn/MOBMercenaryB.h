#include "SimpleMonster.h"

#ifndef __MOBMERCENARYB_H
#define __MOBMERCENARYB_H

class MOBMercenaryB : public SimpleMonster{
public:   
    MOBMercenaryB();
   ~MOBMercenaryB();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

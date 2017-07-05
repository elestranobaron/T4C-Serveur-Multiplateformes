#include "SimpleMonster.h"

#ifndef __MOBMERCENARYC_H
#define __MOBMERCENARYC_H

class MOBMercenaryC : public SimpleMonster{
public:   
    MOBMercenaryC();
   ~MOBMercenaryC();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

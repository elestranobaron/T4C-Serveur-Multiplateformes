#include "SimpleMonster.h"

#ifndef __LORDSTONECREST_H
#define __LORDSTONECREST_H

class LordStonecrest : public  SimpleMonster{
public:   
    LordStonecrest();
   ~LordStonecrest();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    
};

#endif

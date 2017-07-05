#include "SimpleMonster.h"

#ifndef __MOBCELESTIALCOBRA_H
#define __MOBCELESTIALCOBRA_H

class MOBCelestialCobra : public SimpleMonster{
public:   
    MOBCelestialCobra();
   ~MOBCelestialCobra();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE ); 
    
};

#endif

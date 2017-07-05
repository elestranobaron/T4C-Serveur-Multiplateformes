#include "SimpleMonster.h"

#ifndef __GAENENELTHORN_H
#define __GAENENELTHORN_H

class GaenenElthorn : public SimpleMonster{
public:   
    GaenenElthorn();
   ~GaenenElthorn();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );   
    void OnHit( UNIT_FUNC_PROTOTYPE );   
};

#endif

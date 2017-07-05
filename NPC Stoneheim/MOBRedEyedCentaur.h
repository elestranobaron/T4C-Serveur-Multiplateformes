#include "SimpleMonster.h"

#ifndef __MOBREDEYEDCENTAUR_H
#define __MOBREDEYEDCENTAUR_H

class MOBRedEyedCentaur : public SimpleMonster{
public:   
    MOBRedEyedCentaur();
   ~MOBRedEyedCentaur();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif

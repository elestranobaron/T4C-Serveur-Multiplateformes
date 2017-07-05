#include "SimpleMonster.h"

#ifndef __SHADEENMASKEDASSASSIN_H
#define __SHADEENMASKEDASSASSIN_H

class ShadeenMaskedAssassin : public SimpleMonster{
public:   
    ShadeenMaskedAssassin();
   ~ShadeenMaskedAssassin();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

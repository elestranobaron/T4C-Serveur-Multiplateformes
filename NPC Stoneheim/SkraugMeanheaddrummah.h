#include "SimpleMonster.h"

#ifndef __SKRAUGMEANHEADDRUMMAH_H
#define __SKRAUGMEANHEADDRUMMAH_H

class SkraugMeanheaddrummah : public SimpleMonster{
public:   
    SkraugMeanheaddrummah();
   ~SkraugMeanheaddrummah();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

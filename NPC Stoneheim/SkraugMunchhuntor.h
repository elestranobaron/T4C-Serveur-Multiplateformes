#include "SimpleMonster.h"

#ifndef __SKRAUGMUNCHHUNTOR_H
#define __SKRAUGMUNCHHUNTOR_H

class SkraugMunchhuntor : public SimpleMonster{
public:   
    SkraugMunchhuntor();
   ~SkraugMunchhuntor();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

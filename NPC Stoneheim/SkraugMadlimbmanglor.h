#include "SimpleMonster.h"

#ifndef __SKRAUGMADLIMBMANGLOR_H
#define __SKRAUGMADLIMBMANGLOR_H

class SkraugMadlimbmanglor : public SimpleMonster{
public:   
    SkraugMadlimbmanglor();
   ~SkraugMadlimbmanglor();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

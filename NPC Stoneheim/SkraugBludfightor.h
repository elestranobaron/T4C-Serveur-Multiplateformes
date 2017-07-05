#include "SimpleMonster.h"

#ifndef __SKRAUGBLUDFIGHTOR_H
#define __SKRAUGBLUDFIGHTOR_H

class SkraugBludfightor : public SimpleMonster{
public:   
    SkraugBludfightor();
   ~SkraugBludfightor();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

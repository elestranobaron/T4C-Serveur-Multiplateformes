#include "SimpleMonster.h"

#ifndef __SKRAUGTOTEMHERBDOKTOR_H
#define __SKRAUGTOTEMHERBDOKTOR_H

class SkraugTotemherbdoktor : public SimpleMonster{
public:   
    SkraugTotemherbdoktor();
   ~SkraugTotemherbdoktor();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

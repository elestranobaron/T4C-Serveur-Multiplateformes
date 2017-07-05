#include "SimpleMonster.h"

#ifndef __SKRAUGBIGWORVIKTOR_H
#define __SKRAUGBIGWORVIKTOR_H

class SkraugBigworviktor : public SimpleMonster{
public:   
    SkraugBigworviktor();
   ~SkraugBigworviktor();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

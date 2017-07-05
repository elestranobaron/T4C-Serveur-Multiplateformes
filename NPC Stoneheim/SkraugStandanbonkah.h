#include "SimpleMonster.h"

#ifndef __SKRAUGSTANDANBONKAH_H
#define __SKRAUGSTANDANBONKAH_H

class SkraugStandanbonkah : public SimpleMonster{
public:   
    SkraugStandanbonkah();
   ~SkraugStandanbonkah();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif


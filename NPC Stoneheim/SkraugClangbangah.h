#include "SimpleMonster.h"

#ifndef __SKRAUGCLANGBANGAH_H
#define __SKRAUGCLANGBANGAH_H

class SkraugClangbangah : public SimpleMonster{
public:   
    SkraugClangbangah();
   ~SkraugClangbangah();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

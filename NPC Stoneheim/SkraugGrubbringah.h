#include "SimpleMonster.h"

#ifndef __SKRAUGGRUBBRINGAH_H
#define __SKRAUGGRUBBRINGAH_H

class SkraugGrubbringah : public SimpleMonster{
public:   
    SkraugGrubbringah();
   ~SkraugGrubbringah();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

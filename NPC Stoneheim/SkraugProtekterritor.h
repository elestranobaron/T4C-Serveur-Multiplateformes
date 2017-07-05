#include "SimpleMonster.h"

#ifndef __SKRAUGPROTEKTERRITOR_H
#define __SKRAUGROTEKTERRITOR_H

class SkraugProtekterritor : public SimpleMonster{
public:   
    SkraugProtekterritor();
   ~SkraugProtekterritor();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

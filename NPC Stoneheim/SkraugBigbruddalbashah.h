#include "SimpleMonster.h"

#ifndef __SKRAUGBIGBRUDDALBASHAH_H
#define __SKRAUGBIGBRUDDALBASHAH_H

class SkraugBigbruddalbashah : public SimpleMonster{
public:   
    SkraugBigbruddalbashah();
   ~SkraugBigbruddalbashah();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );	 
	 void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

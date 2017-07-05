#include "SimpleMonster.h"

#ifndef __MOBLOON_H
#define __MOBLOON_H

class MOBLoon : public SimpleMonster{
public:   
    MOBLoon();
   ~MOBLoon();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnPopup( UNIT_FUNC_PROTOTYPE );
};

#endif

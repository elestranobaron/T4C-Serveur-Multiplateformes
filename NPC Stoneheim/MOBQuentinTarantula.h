#include "SimpleMonster.h"

#ifndef __MOBQUENTINTARANTULA_H
#define __MOBQUENTINTARANTULA_H

class MOBQuentinTarantula : public SimpleMonster{
public:   
    MOBQuentinTarantula();
   ~MOBQuentinTarantula();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
	 void OnPopup( UNIT_FUNC_PROTOTYPE ); 
};

#endif

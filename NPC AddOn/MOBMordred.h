#include "SimpleMonster.h"

#ifndef __MOBMORDRED_H
#define __MOBMORDRED_H

class MOBMordred : public SimpleMonster{
public:   
    MOBMordred();
   ~MOBMordred();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif

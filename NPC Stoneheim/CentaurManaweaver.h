#include "SimpleMonster.h"

#ifndef __CENTAURMANAWEAVER_H
#define __CENTAURMANAWEAVER_H

class CentaurManaweaver : public  SimpleMonster{
public:   
    CentaurManaweaver();
   ~CentaurManaweaver();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif

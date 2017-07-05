#include "SimpleMonster.h"

#ifndef __MOBCRAZEDNURSE_H
#define __MOBCRAZEDNURSE_H

class MOBCrazedNurse : public SimpleMonster{
public:   
    MOBCrazedNurse();
   ~MOBCrazedNurse();
    void Create( void );
    void OnAttackHit( UNIT_FUNC_PROTOTYPE );
    void OnHit( UNIT_FUNC_PROTOTYPE );
};

#endif

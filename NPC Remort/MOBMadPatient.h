#include "SimpleMonster.h"

#ifndef __MOBMADPATIENT_H
#define __MOBMADPATIENT_H

class MOBMadPatient : public SimpleMonster{
public:   
    MOBMadPatient();
   ~MOBMadPatient();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
};

#endif

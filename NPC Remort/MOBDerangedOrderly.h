#include "SimpleMonster.h"

#ifndef __MOBDERANGEDORDERLY_H
#define __MOBDERANGEDORDERLY_H

class MOBDerangedOrderly : public SimpleMonster{
public:   
    MOBDerangedOrderly();
   ~MOBDerangedOrderly();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
};

#endif

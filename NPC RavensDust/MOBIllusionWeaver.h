#include "SimpleMonster.h"

#ifndef __MOBILLUSIONWEAVER_H
#define __MOBILLUSIONWEAVER_H

class MOBIllusionWeaver : public SimpleMonster{
public:   
    MOBIllusionWeaver();
   ~MOBIllusionWeaver();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
};

#endif

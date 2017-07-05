#include "SimpleMonster.h"

#ifndef __MOBYOGGOTHWORM_H
#define __MOBYOGGOTHWORM_H

class MOBYoggothWorm : public SimpleMonster{
public:   
    MOBYoggothWorm();
   ~MOBYoggothWorm();
    void Create( void );
    void OnAttackHit( UNIT_FUNC_PROTOTYPE );
    
};
#endif

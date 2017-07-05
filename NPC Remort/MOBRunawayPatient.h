#include "NPCstructure.h"

#ifndef __MOBRUNAWAYPATIENT_H
#define __MOBRUNAWAYPATIENT_H

class MOBRunawayPatient : public NPCstructure{
public:   
    MOBRunawayPatient();
   ~MOBRunawayPatient();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
};

#endif

#include "NPCStructure.h"

#ifndef __HEALINGWELL_H
#define __HEALINGWELL_H

class HealingWell : public NPCstructure{
public:   
    HealingWell();
    ~HealingWell();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE ); 
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif

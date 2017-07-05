#include "NPCStructure.h"

#ifndef __HEALINGPLANT_H
#define __HEALINGPLANT_H

class HealingPlant : public NPCstructure{
public:   
    HealingPlant();
    ~HealingPlant();
    void Create( void );   
    void OnInitialise( UNIT_FUNC_PROTOTYPE);
    
};

#endif

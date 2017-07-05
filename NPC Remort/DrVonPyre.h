#include "NPCStructure.h"

#ifndef __DRVONPYRE_H
#define __DRVONPYRE_H

class DrVonPyre : public NPCstructure{
public:   
    DrVonPyre();
   ~DrVonPyre();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );   
};

#endif 


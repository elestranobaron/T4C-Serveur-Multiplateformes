#include "NPCStructure.h"

#ifndef __MOBDELWOBBLE_H
#define __MOBDELWOBBLE_H

class MOBDelwobble : public NPCstructure{
public:   
    MOBDelwobble();
   ~MOBDelwobble();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif

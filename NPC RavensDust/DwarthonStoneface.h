#include "NPCStructure.h"

#ifndef __DWARTHONSTONEFACE_H
#define __DWARTHONSTONEFACE_H

class DwarthonStoneface : public NPCstructure{
public:   
    DwarthonStoneface();
   ~DwarthonStoneface();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif

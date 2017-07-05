#include "NPCStructure.h"

#ifndef __IAGOCABALLERO_H
#define __IAGOCABALLERO_H

class IagoCaballero : public NPCstructure{
public:   
    IagoCaballero();
    ~IagoCaballero();
    void Create( void );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

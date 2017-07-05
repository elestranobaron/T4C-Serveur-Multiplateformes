#include "NPCStructure.h"

#ifndef __GASHEMGUUD_H
#define __GASHEMGUUD_H

class GashEmguud : public NPCstructure{
public:   
    GashEmguud();
   ~GashEmguud();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif

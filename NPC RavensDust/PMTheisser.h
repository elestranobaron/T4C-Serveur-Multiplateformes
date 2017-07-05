#include "NPCStructure.h"

#ifndef __PMTHEISSER_H
#define __PMTHEISSER_H

class PMTheisser : public NPCstructure{
public:   
    PMTheisser();
   ~PMTheisser();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif


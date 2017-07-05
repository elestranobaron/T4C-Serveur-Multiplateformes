#include "NPCStructure.h"

#ifndef __DELNARSTEELBLADE_H
#define __DELNARSTEELBLADE_H

class DelnarSteelblade : public NPCstructure{
public:   
    DelnarSteelblade();
   ~DelnarSteelblade();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);

};

#endif

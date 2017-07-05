#include "NPCStructure.h"

#ifndef __MOBHERETICWARRIOR_H
#define __MOBHERETICWARRIOR_H

class MOBHereticWarrior : public NPCstructure{
public:   
    MOBHereticWarrior(); 
   ~MOBHereticWarrior();
    void Create( void ); 
	 void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

#include "NPCStructure.h"

#ifndef __MOBMADBERSERKERDEMON_H
#define __MOBMADBERSERKERDEMON_H

class MOBMadBerserkerDemon : public NPCstructure{
public:   
    MOBMadBerserkerDemon();
   ~MOBMadBerserkerDemon();
    void Create( void );
	 void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE ); 
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

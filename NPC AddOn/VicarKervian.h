#include "NPCStructure.h"

#ifndef __VICARKERVIAN_H
#define __VICARKERVIAN_H

class VicarKervian : public NPCstructure{
public:   
    VicarKervian();
   ~VicarKervian();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE);
	void OnAttack( UNIT_FUNC_PROTOTYPE); 

};

#endif

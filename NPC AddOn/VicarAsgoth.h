#include "NPCStructure.h"

#ifndef __VICARASGOTH_H
#define __VICARASGOTH_H

class VicarAsgoth : public NPCstructure{
public:   
    VicarAsgoth();
   ~VicarAsgoth();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE); 
	void OnAttack( UNIT_FUNC_PROTOTYPE); 
};

#endif

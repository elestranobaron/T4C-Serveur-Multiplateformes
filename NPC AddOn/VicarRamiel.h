#include "NPCStructure.h"

#ifndef __VICARRAMIEL_H
#define __VICARRAMIEL_H

class VicarRamiel : public NPCstructure{
public:   
    VicarRamiel();
   ~VicarRamiel();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE);
	void OnAttack( UNIT_FUNC_PROTOTYPE); 
};

#endif

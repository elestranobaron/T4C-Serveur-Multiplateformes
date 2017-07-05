#include "NPCStructure.h"

#ifndef __ANTHORTHEMAD_H
#define __ANTHORTHEMAD_H

class AnthorTheMad : public NPCstructure{
public:
	AnthorTheMad();
	~AnthorTheMad();
	void Create( void );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif
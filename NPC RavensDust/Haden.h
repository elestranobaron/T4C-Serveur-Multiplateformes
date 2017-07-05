#include "NPCStructure.h"

#ifndef __HADEN_H
#define __HADEN_H

class Haden : public NPCstructure{
public:   
	Haden();
	~Haden();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );    
};

#endif







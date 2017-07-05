#include "NPCStructure.h"

#ifndef __ANTONIAN_H
#define __ANTONIAN_H

class Antonian : public NPCstructure{
public:
	Antonian();
	~Antonian();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
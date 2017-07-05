#include "NPCStructure.h"

#ifndef __AMELIA_H
#define __AMELIA_H

class Amelia : public NPCstructure{
public:
	Amelia();
	~Amelia();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
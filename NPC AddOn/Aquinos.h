#include "NPCStructure.h"

#ifndef __AQUINOS_H
#define __AQUINOS_H

class Aquinos : public NPCstructure{
public:
	Aquinos();
	~Aquinos();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
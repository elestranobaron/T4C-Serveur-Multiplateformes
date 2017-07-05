#include "NPCStructure.h"

#ifndef __GYPSY_H
#define __GYPSY_H

class Gypsy : public NPCstructure{
public:
	Gypsy();
	~Gypsy();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
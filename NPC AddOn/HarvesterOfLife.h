#include "NPCStructure.h"

#ifndef __HARVESTEROFLIFE_H
#define __HARVESTEROFLIFE_H

class HarvesterOfLife : public NPCstructure{
public:
	HarvesterOfLife();
	~HarvesterOfLife();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif
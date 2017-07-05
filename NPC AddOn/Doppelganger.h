#include "NPCStructure.h"
#include "SimpleMonster.h"

#ifndef __DOPPELGANGER_H
#define __DOPPELGANGER_H

class Doppelganger : public SimpleMonster{
public:
	Doppelganger();
	~Doppelganger();
	void Create( void );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif
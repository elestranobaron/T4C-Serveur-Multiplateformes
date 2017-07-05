#include "SimpleMonster.h"

#ifndef __ARENAMOB40_H
#define __ARENAMOB40_H

class ArenaMob40 : public SimpleMonster{
public:
	ArenaMob40();
	~ArenaMob40();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
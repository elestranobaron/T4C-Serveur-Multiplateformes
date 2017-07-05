#include "SimpleMonster.h"

#ifndef __ARENAMOB350_H
#define __ARENAMOB350_H

class ArenaMob350 : public SimpleMonster{
public:
	ArenaMob350();
	~ArenaMob350();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
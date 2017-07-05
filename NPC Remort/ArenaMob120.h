#include "SimpleMonster.h"

#ifndef __ARENAMOB120_H
#define __ARENAMOB120_H

class ArenaMob120 : public SimpleMonster{
public:
	ArenaMob120();
	~ArenaMob120();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
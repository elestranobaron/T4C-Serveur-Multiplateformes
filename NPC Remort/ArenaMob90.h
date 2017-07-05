#include "SimpleMonster.h"

#ifndef __ARENAMOB90_H
#define __ARENAMOB90_H

class ArenaMob90 : public SimpleMonster{
public:
	ArenaMob90();
	~ArenaMob90();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
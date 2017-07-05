#include "SimpleMonster.h"

#ifndef __ARENAMOB180_H
#define __ARENAMOB180_H

class ArenaMob180 : public SimpleMonster{
public:
	ArenaMob180();
	~ArenaMob180();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
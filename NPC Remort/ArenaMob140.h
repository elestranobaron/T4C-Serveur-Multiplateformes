#include "SimpleMonster.h"

#ifndef __ARENAMOB140_H
#define __ARENAMOB140_H

class ArenaMob140 : public SimpleMonster{
public:
	ArenaMob140();
	~ArenaMob140();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
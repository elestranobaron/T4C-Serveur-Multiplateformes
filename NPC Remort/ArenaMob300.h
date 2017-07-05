#include "SimpleMonster.h"

#ifndef __ARENAMOB300_H
#define __ARENAMOB300_H

class ArenaMob300 : public SimpleMonster{
public:
	ArenaMob300();
	~ArenaMob300();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
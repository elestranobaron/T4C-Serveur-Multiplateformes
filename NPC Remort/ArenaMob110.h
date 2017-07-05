#include "SimpleMonster.h"

#ifndef __ARENAMOB110_H
#define __ARENAMOB110_H

class ArenaMob110 : public SimpleMonster{
public:
	ArenaMob110();
	~ArenaMob110();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
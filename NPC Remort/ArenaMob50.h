#include "SimpleMonster.h"

#ifndef __ARENAMOB50_H
#define __ARENAMOB50_H

class ArenaMob50 : public SimpleMonster{
public:
	ArenaMob50();
	~ArenaMob50();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
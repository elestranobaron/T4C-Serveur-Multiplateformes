#include "SimpleMonster.h"

#ifndef __ARENAMOB100_H
#define __ARENAMOB100_H

class ArenaMob100 : public SimpleMonster{
public:
	ArenaMob100();
	~ArenaMob100();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
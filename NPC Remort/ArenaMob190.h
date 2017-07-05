#include "SimpleMonster.h"

#ifndef __ARENAMOB190_H
#define __ARENAMOB190_H

class ArenaMob190 : public SimpleMonster{
public:
	ArenaMob190();
	~ArenaMob190();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
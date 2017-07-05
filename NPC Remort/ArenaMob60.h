#include "SimpleMonster.h"

#ifndef __ARENAMOB60_H
#define __ARENAMOB60_H

class ArenaMob60 : public SimpleMonster{
public:
	ArenaMob60();
	~ArenaMob60();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
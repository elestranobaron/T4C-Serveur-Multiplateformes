#include "SimpleMonster.h"

#ifndef __ARENAMOB325_H
#define __ARENAMOB325_H

class ArenaMob325 : public SimpleMonster{
public:
	ArenaMob325();
	~ArenaMob325();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
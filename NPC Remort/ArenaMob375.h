#include "SimpleMonster.h"

#ifndef __ARENAMOB375_H
#define __ARENAMOB375_H

class ArenaMob375 : public SimpleMonster{
public:
	ArenaMob375();
	~ArenaMob375();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
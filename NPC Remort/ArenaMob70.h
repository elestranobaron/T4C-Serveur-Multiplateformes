#include "SimpleMonster.h"

#ifndef __ARENAMOB70_H
#define __ARENAMOB70_H

class ArenaMob70 : public SimpleMonster{
public:
	ArenaMob70();
	~ArenaMob70();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
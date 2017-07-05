#include "SimpleMonster.h"

#ifndef __ARENAMOB150_H
#define __ARENAMOB150_H

class ArenaMob150 : public SimpleMonster{
public:
	ArenaMob150();
	~ArenaMob150();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
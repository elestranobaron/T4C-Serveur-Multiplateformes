#include "SimpleMonster.h"

#ifndef __ARENAMOB170_H
#define __ARENAMOB170_H

class ArenaMob170 : public SimpleMonster{
public:
	ArenaMob170();
	~ArenaMob170();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "SimpleMonster.h"

#ifndef __ARENAMOB160_H
#define __ARENAMOB160_H

class ArenaMob160 : public SimpleMonster{
public:
	ArenaMob160();
	~ArenaMob160();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "SimpleMonster.h"

#ifndef __ARENAMOB80_H
#define __ARENAMOB80_H

class ArenaMob80 : public SimpleMonster{
public:
	ArenaMob80();
	~ArenaMob80();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
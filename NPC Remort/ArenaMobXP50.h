#include "SimpleMonster.h"

#ifndef __ARENAMOBXP50_H
#define __ARENAMOBXP50_H

class ArenaMobXP50 : public SimpleMonster{
public:
	ArenaMobXP50();
	~ArenaMobXP50();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
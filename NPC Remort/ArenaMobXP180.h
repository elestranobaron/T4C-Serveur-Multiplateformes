#include "SimpleMonster.h"

#ifndef __ARENAMOBXP180_H
#define __ARENAMOBXP180_H

class ArenaMobXP180 : public SimpleMonster{
public:
	ArenaMobXP180();
	~ArenaMobXP180();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
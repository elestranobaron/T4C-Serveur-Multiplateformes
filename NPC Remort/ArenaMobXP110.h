#include "SimpleMonster.h"

#ifndef __ARENAMOBXP110_H
#define __ARENAMOBXP110_H

class ArenaMobXP110 : public SimpleMonster{
public:
	ArenaMobXP110();
	~ArenaMobXP110();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
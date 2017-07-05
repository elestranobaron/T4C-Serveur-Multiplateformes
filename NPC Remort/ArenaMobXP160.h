#include "SimpleMonster.h"

#ifndef __ARENAMOBXP160_H
#define __ARENAMOBXP160_H

class ArenaMobXP160 : public SimpleMonster{
public:
	ArenaMobXP160();
	~ArenaMobXP160();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "SimpleMonster.h"

#ifndef __ARENAMOBXP130_H
#define __ARENAMOBXP130_H

class ArenaMobXP130 : public SimpleMonster{
public:
	ArenaMobXP130();
	~ArenaMobXP130();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
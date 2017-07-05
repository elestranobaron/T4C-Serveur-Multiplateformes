#include "SimpleMonster.h"

#ifndef __ARENAMOBXP80_H
#define __ARENAMOBXP80_H

class ArenaMobXP80 : public SimpleMonster{
public:
	ArenaMobXP80();
	~ArenaMobXP80();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
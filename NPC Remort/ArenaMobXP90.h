#include "SimpleMonster.h"

#ifndef __ARENAMOBXP90_H
#define __ARENAMOBXP90_H

class ArenaMobXP90 : public SimpleMonster{
public:
	ArenaMobXP90();
	~ArenaMobXP90();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
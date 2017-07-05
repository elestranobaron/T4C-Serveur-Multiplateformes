#include "SimpleMonster.h"

#ifndef __ARENAMOBXP120_H
#define __ARENAMOBXP120_H

class ArenaMobXP120 : public SimpleMonster{
public:
	ArenaMobXP120();
	~ArenaMobXP120();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
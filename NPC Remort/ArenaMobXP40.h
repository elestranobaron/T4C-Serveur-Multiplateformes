#include "SimpleMonster.h"

#ifndef __ARENAMOBXP40_H
#define __ARENAMOBXP40_H

class ArenaMobXP40 : public SimpleMonster{
public:
	ArenaMobXP40();
	~ArenaMobXP40();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
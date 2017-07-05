#include "SimpleMonster.h"

#ifndef __ARENAMOBXP350_H
#define __ARENAMOBXP350_H

class ArenaMobXP350 : public SimpleMonster{
public:
	ArenaMobXP350();
	~ArenaMobXP350();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "SimpleMonster.h"

#ifndef __ARENAMOBXP60_H
#define __ARENAMOBXP60_H

class ArenaMobXP60 : public SimpleMonster{
public:
	ArenaMobXP60();
	~ArenaMobXP60();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
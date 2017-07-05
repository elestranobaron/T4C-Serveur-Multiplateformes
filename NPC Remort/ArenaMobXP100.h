#include "SimpleMonster.h"

#ifndef __ARENAMOBXP100_H
#define __ARENAMOBXP100_H

class ArenaMobXP100 : public SimpleMonster{
public:
	ArenaMobXP100();
	~ArenaMobXP100();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "SimpleMonster.h"

#ifndef __ARENAMOBXP325_H
#define __ARENAMOBXP325_H

class ArenaMobXP325 : public SimpleMonster{
public:
	ArenaMobXP325();
	~ArenaMobXP325();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
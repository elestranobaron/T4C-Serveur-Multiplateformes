#include "SimpleMonster.h"

#ifndef __ARENAMOBXP70_H
#define __ARENAMOBXP70_H

class ArenaMobXP70 : public SimpleMonster{
public:
	ArenaMobXP70();
	~ArenaMobXP70();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
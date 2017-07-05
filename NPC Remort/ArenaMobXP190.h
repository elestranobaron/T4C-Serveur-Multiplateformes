#include "SimpleMonster.h"

#ifndef __ARENAMOBXP190_H
#define __ARENAMOBXP190_H

class ArenaMobXP190 : public SimpleMonster{
public:
	ArenaMobXP190();
	~ArenaMobXP190();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
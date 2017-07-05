#include "SimpleMonster.h"

#ifndef __ARENAMOBXP170_H
#define __ARENAMOBXP170_H

class ArenaMobXP170 : public SimpleMonster{
public:
	ArenaMobXP170();
	~ArenaMobXP170();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
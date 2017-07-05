#include "SimpleMonster.h"

#ifndef __ARENAMOBXP375_H
#define __ARENAMOBXP375_H

class ArenaMobXP375 : public SimpleMonster{
public:
	ArenaMobXP375();
	~ArenaMobXP375();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
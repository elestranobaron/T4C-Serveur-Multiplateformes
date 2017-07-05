#include "SimpleMonster.h"

#ifndef __ARENAMOBXP300_H
#define __ARENAMOBXP300_H

class ArenaMobXP300 : public SimpleMonster{
public:
	ArenaMobXP300();
	~ArenaMobXP300();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
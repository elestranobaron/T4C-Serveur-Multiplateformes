#include "SimpleMonster.h"

#ifndef __ARENAMOBXP500_H
#define __ARENAMOBXP500_H

class ArenaMobXP500 : public SimpleMonster{
public:
	ArenaMobXP500();
	~ArenaMobXP500();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
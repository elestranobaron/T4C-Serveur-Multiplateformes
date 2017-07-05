#include "SimpleMonster.h"

#ifndef __ARENAMOB450_H
#define __ARENAMOB450_H

class ArenaMob450 : public SimpleMonster{
public:
	ArenaMob450();
	~ArenaMob450();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
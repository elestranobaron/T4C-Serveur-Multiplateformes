#include "SimpleMonster.h"

#ifndef __ARENAMOB500_H
#define __ARENAMOB500_H

class ArenaMob500 : public SimpleMonster{
public:
	ArenaMob500();
	~ArenaMob500();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
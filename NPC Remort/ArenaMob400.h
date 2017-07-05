#include "SimpleMonster.h"

#ifndef __ARENAMOB400_H
#define __ARENAMOB400_H

class ArenaMob400 : public SimpleMonster{
public:
	ArenaMob400();
	~ArenaMob400();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
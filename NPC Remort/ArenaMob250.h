#include "SimpleMonster.h"

#ifndef __ARENAMOB250_H
#define __ARENAMOB250_H

class ArenaMob250 : public SimpleMonster{
public:
	ArenaMob250();
	~ArenaMob250();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
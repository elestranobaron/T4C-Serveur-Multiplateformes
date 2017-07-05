#include "SimpleMonster.h"

#ifndef __ARENAMOB225_H
#define __ARENAMOB225_H

class ArenaMob225 : public SimpleMonster{
public:
	ArenaMob225();
	~ArenaMob225();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
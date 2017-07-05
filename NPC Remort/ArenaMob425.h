#include "SimpleMonster.h"

#ifndef __ARENAMOB425_H
#define __ARENAMOB425_H

class ArenaMob425 : public SimpleMonster{
public:
	ArenaMob425();
	~ArenaMob425();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
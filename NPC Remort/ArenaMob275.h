#include "SimpleMonster.h"

#ifndef __ARENAMOB275_H
#define __ARENAMOB275_H

class ArenaMob275 : public SimpleMonster{
public:
	ArenaMob275();
	~ArenaMob275();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
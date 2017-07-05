#include "SimpleMonster.h"

#ifndef __ARENAMOB475_H
#define __ARENAMOB475_H

class ArenaMob475 : public SimpleMonster{
public:
	ArenaMob475();
	~ArenaMob475();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
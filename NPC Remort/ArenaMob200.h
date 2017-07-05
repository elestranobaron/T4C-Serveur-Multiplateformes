#include "SimpleMonster.h"

#ifndef __ARENAMOB200_H
#define __ARENAMOB200_H

class ArenaMob200 : public SimpleMonster{
public:
	ArenaMob200();
	~ArenaMob200();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
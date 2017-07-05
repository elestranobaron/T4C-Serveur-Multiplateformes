#include "SimpleMonster.h"

#ifndef __ARENAMOBXP425_H
#define __ARENAMOBXP425_H

class ArenaMobXP425 : public SimpleMonster{
public:
	ArenaMobXP425();
	~ArenaMobXP425();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
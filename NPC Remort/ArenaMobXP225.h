#include "SimpleMonster.h"

#ifndef __ARENAMOBXP225_H
#define __ARENAMOBXP225_H

class ArenaMobXP225 : public SimpleMonster{
public:
	ArenaMobXP225();
	~ArenaMobXP225();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
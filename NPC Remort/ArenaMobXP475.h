#include "SimpleMonster.h"

#ifndef __ARENAMOBXP475_H
#define __ARENAMOBXP475_H

class ArenaMobXP475 : public SimpleMonster{
public:
	ArenaMobXP475();
	~ArenaMobXP475();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
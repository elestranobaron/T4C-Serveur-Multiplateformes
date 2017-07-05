#include "SimpleMonster.h"

#ifndef __ARENAMOBXP250_H
#define __ARENAMOBXP250_H

class ArenaMobXP250 : public SimpleMonster{
public:
	ArenaMobXP250();
	~ArenaMobXP250();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
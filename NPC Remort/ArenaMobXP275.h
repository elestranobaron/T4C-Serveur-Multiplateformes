#include "SimpleMonster.h"

#ifndef __ARENAMOBXP275_H
#define __ARENAMOBXP275_H

class ArenaMobXP275 : public SimpleMonster{
public:
	ArenaMobXP275();
	~ArenaMobXP275();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
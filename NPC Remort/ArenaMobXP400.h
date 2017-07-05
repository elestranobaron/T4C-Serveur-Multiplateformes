#include "SimpleMonster.h"

#ifndef __ARENAMOBXP400_H
#define __ARENAMOBXP400_H

class ArenaMobXP400 : public SimpleMonster{
public:
	ArenaMobXP400();
	~ArenaMobXP400();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
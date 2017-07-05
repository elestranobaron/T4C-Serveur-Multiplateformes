#include "SimpleMonster.h"

#ifndef __ARENAMOBXP200_H
#define __ARENAMOBXP200_H

class ArenaMobXP200 : public SimpleMonster{
public:
	ArenaMobXP200();
	~ArenaMobXP200();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
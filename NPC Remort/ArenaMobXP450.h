#include "SimpleMonster.h"

#ifndef __ARENAMOBXP450_H
#define __ARENAMOBXP450_H

class ArenaMobXP450 : public SimpleMonster{
public:
	ArenaMobXP450();
	~ArenaMobXP450();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
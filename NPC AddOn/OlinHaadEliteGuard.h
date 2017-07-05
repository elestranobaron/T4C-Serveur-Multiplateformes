#include "NPCStructure.h"
#include "SimpleMonster.h"

#ifndef __OLINHAADELITEGUARD_H
#define __OLINHAADELITEGUARD_H

class OlinHaadEliteGuard : public SimpleMonster{
public:
	OlinHaadEliteGuard();
	~OlinHaadEliteGuard();
	void Create( void );
	void OnAttack( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif
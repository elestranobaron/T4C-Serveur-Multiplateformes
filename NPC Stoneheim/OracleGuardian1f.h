#include "SimpleMonster.h"

#ifndef __ORACLEGUARDIAN1F_H
#define __ORACLEGUARDIAN1F_H

class OracleGuardian1f : public SimpleMonster{
public:   
	OracleGuardian1f();
	~OracleGuardian1f();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

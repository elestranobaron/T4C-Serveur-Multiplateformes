#include "SimpleMonster.h"

#ifndef __ORACLEGUARDIAN1B_H
#define __ORACLEGUARDIAN1B_H

class OracleGuardian1b : public SimpleMonster{
public:   
	OracleGuardian1b();
	~OracleGuardian1b();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

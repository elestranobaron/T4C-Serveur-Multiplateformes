#include "SimpleMonster.h"

#ifndef __ORACLEGUARDIAN1A_H
#define __ORACLEGUARDIAN1A_H

class OracleGuardian1a : public SimpleMonster{
public:   
	OracleGuardian1a();
	~OracleGuardian1a();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

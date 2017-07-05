#include "SimpleMonster.h"

#ifndef __ORACLEGUARDIAN1C_H
#define __ORACLEGUARDIAN1C_H

class OracleGuardian1c : public SimpleMonster{
public:   
	OracleGuardian1c();
	~OracleGuardian1c();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

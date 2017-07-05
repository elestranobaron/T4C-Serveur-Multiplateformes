#include "SimpleMonster.h"

#ifndef __ORACLEGUARDIAN1E_H
#define __ORACLEGUARDIAN1E_H

class OracleGuardian1e : public SimpleMonster{
public:   
	OracleGuardian1e();
	~OracleGuardian1e();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

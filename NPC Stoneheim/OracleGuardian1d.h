#include "SimpleMonster.h"

#ifndef __ORACLEGUARDIAN1D_H
#define __ORACLEGUARDIAN1D_H

class OracleGuardian1d : public SimpleMonster{
public:   
	OracleGuardian1d();
	~OracleGuardian1d();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

#include "SimpleMonster.h"

#ifndef __ORACLEINVULNERABLEGUARDIAN_H
#define __ORACLEINVULNERABLEGUARDIAN_H

class OracleVulnerableGuardian : public SimpleMonster{
public:   
	OracleVulnerableGuardian();
	~OracleVulnerableGuardian();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif

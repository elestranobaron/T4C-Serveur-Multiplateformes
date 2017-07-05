#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST2A_H
#define __ORACLETRAPPEDCHEST2A_H

class OracleTrappedChest2a : public NPCstructure{
public:
	OracleTrappedChest2a();
	~OracleTrappedChest2a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

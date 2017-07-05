#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST2B_H
#define __ORACLETRAPPEDCHEST2B_H

class OracleTrappedChest2b : public NPCstructure{
public:
	OracleTrappedChest2b();
	~OracleTrappedChest2b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

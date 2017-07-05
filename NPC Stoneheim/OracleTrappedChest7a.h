#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST7A_H
#define __ORACLETRAPPEDCHEST7A_H

class OracleTrappedChest7a : public NPCstructure{
public:
	OracleTrappedChest7a();
	~OracleTrappedChest7a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

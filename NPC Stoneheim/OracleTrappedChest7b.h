#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST7B_H
#define __ORACLETRAPPEDCHEST7B_H

class OracleTrappedChest7b : public NPCstructure{
public:
	OracleTrappedChest7b();
	~OracleTrappedChest7b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

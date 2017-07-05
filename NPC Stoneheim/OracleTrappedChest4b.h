#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST4B_H
#define __ORACLETRAPPEDCHEST4B_H

class OracleTrappedChest4b : public NPCstructure{
public:
	OracleTrappedChest4b();
	~OracleTrappedChest4b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

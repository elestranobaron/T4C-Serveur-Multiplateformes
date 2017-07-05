#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST4A_H
#define __ORACLETRAPPEDCHEST4A_H

class OracleTrappedChest4a : public NPCstructure{
public:
	OracleTrappedChest4a();
	~OracleTrappedChest4a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

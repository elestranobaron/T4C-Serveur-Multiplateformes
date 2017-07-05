#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST6A_H
#define __ORACLETRAPPEDCHEST6A_H

class OracleTrappedChest6a : public NPCstructure{
public:
	OracleTrappedChest6a();
	~OracleTrappedChest6a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

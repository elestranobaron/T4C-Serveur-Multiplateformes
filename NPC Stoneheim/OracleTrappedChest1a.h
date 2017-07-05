#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST1A_H
#define __ORACLETRAPPEDCHEST1A_H

class OracleTrappedChest1a : public NPCstructure{
public:
	OracleTrappedChest1a();
	~OracleTrappedChest1a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

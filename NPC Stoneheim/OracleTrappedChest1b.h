#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST1B_H
#define __ORACLETRAPPEDCHEST1B_H

class OracleTrappedChest1b : public NPCstructure{
public:
	OracleTrappedChest1b();
	~OracleTrappedChest1b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

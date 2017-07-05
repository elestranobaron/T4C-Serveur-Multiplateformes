#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST5B_H
#define __ORACLETRAPPEDCHEST5B_H

class OracleTrappedChest5b : public NPCstructure{
public:
	OracleTrappedChest5b();
	~OracleTrappedChest5b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

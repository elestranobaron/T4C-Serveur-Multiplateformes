#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST5A_H
#define __ORACLETRAPPEDCHEST5A_H

class OracleTrappedChest5a : public NPCstructure{
public:
	OracleTrappedChest5a();
	~OracleTrappedChest5a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

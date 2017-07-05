#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST3A_H
#define __ORACLETRAPPEDCHEST3A_H

class OracleTrappedChest3a : public NPCstructure{
public:
	OracleTrappedChest3a();
	~OracleTrappedChest3a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST3B_H
#define __ORACLETRAPPEDCHEST3B_H

class OracleTrappedChest3b : public NPCstructure{
public:
	OracleTrappedChest3b();
	~OracleTrappedChest3b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

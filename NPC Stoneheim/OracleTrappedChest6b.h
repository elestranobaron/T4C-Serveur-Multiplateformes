#include "NPCStructure.h"

#ifndef __ORACLETRAPPEDCHEST6B_H
#define __ORACLETRAPPEDCHEST6B_H

class OracleTrappedChest6b : public NPCstructure{
public:
	OracleTrappedChest6b();
	~OracleTrappedChest6b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

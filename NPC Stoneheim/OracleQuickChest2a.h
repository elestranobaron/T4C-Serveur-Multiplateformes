#include "NPCStructure.h"

#ifndef __ORACLEQUICKCHEST2A_H
#define __ORACLEQUICKCHEST2A_H

class OracleQuickChest2a : public NPCstructure{
public:
	OracleQuickChest2a();
	~OracleQuickChest2a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

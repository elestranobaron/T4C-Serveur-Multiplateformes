#include "NPCStructure.h"

#ifndef __ORACLEQUICKCHEST2B_H
#define __ORACLEQUICKCHEST2B_H

class OracleQuickChest2b : public NPCstructure{
public:
	OracleQuickChest2b();
	~OracleQuickChest2b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

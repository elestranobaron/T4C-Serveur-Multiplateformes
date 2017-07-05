#include "NPCStructure.h"

#ifndef __ORACLEQUICKCHEST1B_H
#define __ORACLEQUICKCHEST1B_H

class OracleQuickChest1b : public NPCstructure{
public:
	OracleQuickChest1b();
	~OracleQuickChest1b();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

#include "NPCStructure.h"

#ifndef __ORACLEQUICKCHEST1A_H
#define __ORACLEQUICKCHEST1A_H

class OracleQuickChest1a : public NPCstructure{
public:
	OracleQuickChest1a();
	~OracleQuickChest1a();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

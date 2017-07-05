#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST6_H
#define __ORACLERANDOMCHEST6_H

class OracleRandomChest6 : public NPCstructure{
public:
	OracleRandomChest6();
	~OracleRandomChest6();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

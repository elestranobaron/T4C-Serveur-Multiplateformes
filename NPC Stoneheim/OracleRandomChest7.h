#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST7_H
#define __ORACLERANDOMCHEST7_H

class OracleRandomChest7 : public NPCstructure{
public:
	OracleRandomChest7();
	~OracleRandomChest7();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

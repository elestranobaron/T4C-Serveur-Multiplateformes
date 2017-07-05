#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST2_H
#define __ORACLERANDOMCHEST2_H

class OracleRandomChest2 : public NPCstructure{
public:
	OracleRandomChest2();
	~OracleRandomChest2();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

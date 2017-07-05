#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST10_H
#define __ORACLERANDOMCHEST10_H

class OracleRandomChest10 : public NPCstructure{
public:
	OracleRandomChest10();
	~OracleRandomChest10();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

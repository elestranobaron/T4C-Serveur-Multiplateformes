#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST4_H
#define __ORACLERANDOMCHEST4_H

class OracleRandomChest4 : public NPCstructure{
public:
	OracleRandomChest4();
	~OracleRandomChest4();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

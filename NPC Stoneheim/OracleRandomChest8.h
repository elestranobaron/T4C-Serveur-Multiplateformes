#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST8_H
#define __ORACLERANDOMCHEST8_H

class OracleRandomChest8 : public NPCstructure{
public:
	OracleRandomChest8();
	~OracleRandomChest8();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

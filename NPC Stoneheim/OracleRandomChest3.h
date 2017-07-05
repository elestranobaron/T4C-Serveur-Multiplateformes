#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST3_H
#define __ORACLERANDOMCHEST3_H

class OracleRandomChest3 : public NPCstructure{
public:
	OracleRandomChest3();
	~OracleRandomChest3();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

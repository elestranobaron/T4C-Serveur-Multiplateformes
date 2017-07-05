#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST1_H
#define __ORACLERANDOMCHEST1_H

class OracleRandomChest1 : public NPCstructure{
public:
	OracleRandomChest1();
	~OracleRandomChest1();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST9_H
#define __ORACLERANDOMCHEST9_H

class OracleRandomChest9 : public NPCstructure{
public:
	OracleRandomChest9();
	~OracleRandomChest9();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

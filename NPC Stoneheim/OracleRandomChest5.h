#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST5_H
#define __ORACLERANDOMCHEST5_H

class OracleRandomChest5 : public NPCstructure{
public:
	OracleRandomChest5();
	~OracleRandomChest5();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

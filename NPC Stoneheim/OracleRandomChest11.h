#include "NPCStructure.h"

#ifndef __ORACLERANDOMCHEST11_H
#define __ORACLERANDOMCHEST11_H

class OracleRandomChest11 : public NPCstructure{
public:
	OracleRandomChest11();
	~OracleRandomChest11();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

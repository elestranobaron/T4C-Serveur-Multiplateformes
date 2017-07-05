#include "NPCStructure.h"

#ifndef __ORACLECHEST14_H
#define __ORACLECHEST14_H

class OracleChest14 : public NPCstructure{
public:
	OracleChest14();
	~OracleChest14();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

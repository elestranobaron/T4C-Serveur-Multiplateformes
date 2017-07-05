#include "NPCStructure.h"

#ifndef __ORACLECHEST15_H
#define __ORACLECHEST15_H

class OracleChest15 : public NPCstructure{
public:
	OracleChest15();
	~OracleChest15();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

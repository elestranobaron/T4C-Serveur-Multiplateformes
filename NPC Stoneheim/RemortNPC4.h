#include "NPCStructure.h"

#ifndef __REMORTNPC4_H
#define __REMORTNPC4_H

class RemortNPC4 : public NPCstructure{
public:
	RemortNPC4();
	~RemortNPC4();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
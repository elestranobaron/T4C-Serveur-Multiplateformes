#include "NPCStructure.h"

#ifndef __REMORTNPC3_H
#define __REMORTNPC3_H

class RemortNPC3 : public NPCstructure{
public:
	RemortNPC3();
	~RemortNPC3();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
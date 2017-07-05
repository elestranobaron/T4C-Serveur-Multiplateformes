#include "NPCStructure.h"

#ifndef __REMORTNPC2_H
#define __REMORTNPC2_H

class RemortNPC2 : public NPCstructure{
public:
	RemortNPC2();
	~RemortNPC2();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
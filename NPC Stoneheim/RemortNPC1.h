#include "NPCStructure.h"

#ifndef __REMORTNPC1_H
#define __REMORTNPC1_H

class RemortNPC1 : public NPCstructure{
public:
	RemortNPC1();
	~RemortNPC1();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "NPCStructure.h"

#ifndef __REMORTNPC5_H
#define __REMORTNPC5_H

class RemortNPC5 : public NPCstructure{
public:
	RemortNPC5();
	~RemortNPC5();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
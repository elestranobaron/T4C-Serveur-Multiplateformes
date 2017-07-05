#include "NPCStructure.h"

#ifndef __OLINHAAD1_H
#define __OLINHAAD1_H

class OlinHaad1 : public NPCstructure{
public:
	OlinHaad1();
	~OlinHaad1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
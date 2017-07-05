#include "NPCStructure.h"

#ifndef __ALOYSIUSSTARBOLT_H
#define __ALOYSIUSSTARBOLT_H

class AloysiusStarbolt : public NPCstructure{
public:   
	AloysiusStarbolt();
	~AloysiusStarbolt();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
    
};

#endif

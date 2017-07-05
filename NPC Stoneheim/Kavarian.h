#include "NPCStructure.h"

#ifndef __KAVARIAN_H
#define __KAVARIAN_H

class Kavarian : public NPCstructure{
public:
	Kavarian();
	~Kavarian();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

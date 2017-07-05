#include "NPCStructure.h"

#ifndef __MORDENTHAL_H
#define __MORDENTHAL_H

class Mordenthal : public NPCstructure{
public:
	Mordenthal();
	~Mordenthal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif

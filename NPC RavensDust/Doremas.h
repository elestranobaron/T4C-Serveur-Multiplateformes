#include "NPCStructure.h"

#ifndef __DOREMAS_H
#define __DOREMAS_H

class Doremas : public NPCstructure{
public:   
	Doremas();
	~Doremas();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif

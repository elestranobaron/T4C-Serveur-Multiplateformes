#include "NPCStructure.h"

#ifndef __NISSUSHALOSEEKER_H
#define __NISSUSHALOSEEKER_H

class NissusHaloseeker : public NPCstructure{
public:
	NissusHaloseeker();
	~NissusHaloseeker();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE ); 

};

#endif
#include "NPCStructure.h"

#ifndef __VINCENTSWIFTBLADE_H
#define __VINCENTSWIFTBLADE_H

class VincentSwiftblade : public NPCstructure{
public:
	VincentSwiftblade();
	~VincentSwiftblade();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif

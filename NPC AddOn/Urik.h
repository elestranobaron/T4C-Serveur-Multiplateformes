#include "NPCStructure.h"

#ifndef __URIK_H
#define __URIK_H

class Urik : public NPCstructure{
public:
	Urik();
	~Urik();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
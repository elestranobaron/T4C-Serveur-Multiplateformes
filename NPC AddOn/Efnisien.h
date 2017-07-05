#include "NPCStructure.h"

#ifndef __EFNISIEN_H
#define __EFNISIEN_H

class Efnisien : public NPCstructure{
public:
	Efnisien();
	~Efnisien();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
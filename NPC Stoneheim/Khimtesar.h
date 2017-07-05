#include "NPCStructure.h"

#ifndef __KHIMTESAR_H
#define __KHIMTESAR_H

class Khimtesar : public NPCstructure{
public:
	Khimtesar();
	~Khimtesar();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
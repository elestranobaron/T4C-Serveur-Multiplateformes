#include "NPCStructure.h"

#ifndef __KEDERIC_H
#define __KEDERIC_H

class Kederic : public NPCstructure{
public:   
	Kederic();
	~Kederic();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

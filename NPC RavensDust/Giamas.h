#include "NPCStructure.h"

#ifndef __GIAMAS_H
#define __GIAMAS_H

class Giamas : public NPCstructure{
public:   
	Giamas();
	~Giamas();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
	 
};

#endif

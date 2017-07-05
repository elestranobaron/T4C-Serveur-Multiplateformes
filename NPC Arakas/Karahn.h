#include <NPCStructure.h>

#ifndef __KARAHN_H
#define __KARAHN_H

class Karahn : public NPCstructure{
public:   
	Karahn();
	~Karahn();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

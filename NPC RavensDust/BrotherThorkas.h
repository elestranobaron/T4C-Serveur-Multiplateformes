#include "NPCStructure.h"

#ifndef __BROTHERTHORKAS_H
#define __BROTHERTHORKAS_H

class BrotherThorkas : public NPCstructure{
public:   
	BrotherThorkas();
	~BrotherThorkas();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
    
};

#endif

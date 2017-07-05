#include "NPCStructure.h"

#ifndef __ELYSANABLACKROSE_H
#define __ELYSABLACKROSE_H

class ElysanaBlackrose : public NPCstructure{
public:   
	ElysanaBlackrose();
	~ElysanaBlackrose();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
    
};

#endif

#include "NPCStructure.h"

#ifndef __TALIRON_H
#define __TALIRON_H

class Taliron : public NPCstructure{
public:   
    Taliron();
   ~Taliron();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

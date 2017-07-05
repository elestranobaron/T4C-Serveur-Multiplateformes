#include "NPCStructure.h"

#ifndef __ADRIANA_H
#define __ADRIANA_H

class Adriana : public NPCstructure{
public:   
    Adriana();
   ~Adriana();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

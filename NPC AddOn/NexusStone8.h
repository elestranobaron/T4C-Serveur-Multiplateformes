#include "NPCStructure.h"

#ifndef __NEXUSSTONE8_H
#define __NEXUSSTONE8_H

class NexusStone8 : public NPCstructure{
public:   
    NexusStone8();
   ~NexusStone8();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
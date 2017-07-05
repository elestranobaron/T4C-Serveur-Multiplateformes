#include "NPCStructure.h"

#ifndef __NEXUSSTONE7_H
#define __NEXUSSTONE7_H

class NexusStone7 : public NPCstructure{
public:   
    NexusStone7();
   ~NexusStone7();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
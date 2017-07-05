#include "NPCStructure.h"

#ifndef __NEXUSSTONE13_H
#define __NEXUSSTONE13_H

class NexusStone13 : public NPCstructure{
public:   
    NexusStone13();
   ~NexusStone13();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
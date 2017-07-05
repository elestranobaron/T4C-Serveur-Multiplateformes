#include "NPCStructure.h"

#ifndef __NEXUSSTONE2_H
#define __NEXUSSTONE2_H

class NexusStone2 : public NPCstructure{
public:   
    NexusStone2();
   ~NexusStone2();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
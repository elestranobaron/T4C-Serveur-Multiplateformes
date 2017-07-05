#include "NPCStructure.h"

#ifndef __NEXUSSTONE6_H
#define __NEXUSSTONE6_H

class NexusStone6 : public NPCstructure{
public:   
    NexusStone6();
   ~NexusStone6();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
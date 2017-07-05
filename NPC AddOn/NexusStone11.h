#include "NPCStructure.h"

#ifndef __NEXUSSTONE11_H
#define __NEXUSSTONE11_H

class NexusStone11 : public NPCstructure{
public:   
    NexusStone11();
   ~NexusStone11();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
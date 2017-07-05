#include "NPCStructure.h"

#ifndef __NEXUSSTONE12_H
#define __NEXUSSTONE12_H

class NexusStone12 : public NPCstructure{
public:   
    NexusStone12();
   ~NexusStone12();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
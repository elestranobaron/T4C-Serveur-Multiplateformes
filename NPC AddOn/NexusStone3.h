#include "NPCStructure.h"

#ifndef __NEXUSSTONE3_H
#define __NEXUSSTONE3_H

class NexusStone3 : public NPCstructure{
public:   
    NexusStone3();
   ~NexusStone3();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
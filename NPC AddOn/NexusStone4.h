#include "NPCStructure.h"

#ifndef __NEXUSSTONE4_H
#define __NEXUSSTONE4_H

class NexusStone4 : public NPCstructure{
public:   
    NexusStone4();
   ~NexusStone4();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
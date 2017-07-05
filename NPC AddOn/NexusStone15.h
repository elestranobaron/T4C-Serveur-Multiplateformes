#include "NPCStructure.h"

#ifndef __NEXUSSTONE15_H
#define __NEXUSSTONE15_H

class NexusStone15 : public NPCstructure{
public:   
    NexusStone15();
   ~NexusStone15();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "NPCStructure.h"

#ifndef __NEXUSSTONE14_H
#define __NEXUSSTONE14_H

class NexusStone14 : public NPCstructure{
public:   
    NexusStone14();
   ~NexusStone14();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
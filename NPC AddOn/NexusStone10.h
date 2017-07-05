#include "NPCStructure.h"

#ifndef __NEXUSSTONE10_H
#define __NEXUSSTONE10_H

class NexusStone10 : public NPCstructure{
public:   
    NexusStone10();
   ~NexusStone10();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
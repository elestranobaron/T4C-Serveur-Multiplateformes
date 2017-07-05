#include "NPCStructure.h"

#ifndef __NEXUSSTONE9_H
#define __NEXUSSTONE9_H

class NexusStone9 : public NPCstructure{
public:   
    NexusStone9();
   ~NexusStone9();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "NPCStructure.h"

#ifndef __GULFRIDSTEELHAMMER_H
#define __GULFRIDSTEELHAMMER_H

class GulfridSteelhammer : public NPCstructure{
public:   
    GulfridSteelhammer();
   ~GulfridSteelhammer();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );    
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
			 
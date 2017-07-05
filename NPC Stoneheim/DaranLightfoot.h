#include "NPCStructure.h"

#ifndef __DARANLIGHTFOOT_H
#define __DARANLIGHTFOOT_H

class DaranLightfoot: public NPCstructure{
public:   
    DaranLightfoot();
   ~DaranLightfoot();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

    
};														  


#endif

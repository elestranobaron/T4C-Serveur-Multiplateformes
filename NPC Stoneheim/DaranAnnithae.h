#include "NPCStructure.h"

#ifndef __DARANANNITHAE_H
#define __DARANANNITHAE_H

class DaranAnnithae: public NPCstructure{
public:   
    DaranAnnithae();
   ~DaranAnnithae();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

    
};														  


#endif

 
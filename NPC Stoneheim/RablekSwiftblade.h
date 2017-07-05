#include "NPCStructure.h"

#ifndef __RABLEKSWIFTBLADE_H
#define __RABLEKSWIFTBLADE_H

class RablekSwiftblade : public NPCstructure{
public:   
    RablekSwiftblade();
    ~RablekSwiftblade();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
  
};


#endif

#include "NPCStructure.h"

#ifndef __NAFUHRBLOODHAMMER_H
#define __NAFUHRBLOODHAMMER_H

class NafuhrBloodhammer : public NPCstructure{
public:   
    NafuhrBloodhammer();
   ~NafuhrBloodhammer();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

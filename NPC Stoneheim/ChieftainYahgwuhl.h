#include "NPCStructure.h"

#ifndef __CHIEFTAINYAHGWUHL_H
#define __CHIEFTAINYAHGWUHL_H

class ChieftainYahgwuhl: public NPCstructure{
public:   
    ChieftainYahgwuhl();
   ~ChieftainYahgwuhl();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

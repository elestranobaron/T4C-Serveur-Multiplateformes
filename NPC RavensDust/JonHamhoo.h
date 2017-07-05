#include "NPCStructure.h"

#ifndef __JONHAMHOO_H
#define __JONHAMHOO_H

class JonHamhoo : public NPCstructure{
public:   
    JonHamhoo();
   ~JonHamhoo();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

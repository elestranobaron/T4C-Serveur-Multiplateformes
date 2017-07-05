#include "NPCStructure.h"

#ifndef __AMANDRA_H
#define __AMANDRA_H

class Amandra : public NPCstructure{
public:   
    Amandra();
   ~Amandra();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

#include "NPCStructure.h"

#ifndef __METANAS_H
#define __METANAS_H

class Metanas : public NPCstructure{
public:   
    Metanas();
   ~Metanas();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

#include "NPCStructure.h"

#ifndef __RONDY_H
#define __RONDY_H

class Rondy : public NPCstructure{
public:   
    Rondy();
   ~Rondy();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

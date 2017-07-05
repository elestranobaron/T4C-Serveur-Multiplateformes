#include "NPCStructure.h"

#ifndef __NIMLI_H
#define __NIMLI_H

class Nimli : public NPCstructure{
public:   
    Nimli();
   ~Nimli();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

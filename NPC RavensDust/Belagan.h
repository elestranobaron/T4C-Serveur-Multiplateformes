#include "NPCStructure.h"

#ifndef __BELAGAN_H
#define __BELAGAN_H

class Belagan : public NPCstructure{
public:   
    Belagan();
   ~Belagan();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

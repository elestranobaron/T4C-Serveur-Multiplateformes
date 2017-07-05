#include "NPCStructure.h"

#ifndef __DRARDOS_H
#define __DRARDOS_H

class Drardos : public NPCstructure{
public:   
    Drardos();
   ~Drardos();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

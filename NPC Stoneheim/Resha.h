#include "NPCStructure.h"

#ifndef __RESHA_H
#define __RESHA_H

class Resha : public NPCstructure{
public:   
    Resha();
   ~Resha();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

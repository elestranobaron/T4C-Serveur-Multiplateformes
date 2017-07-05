#include "NPCStructure.h"

#ifndef __GERAM_H
#define __GERAM_H

class Geram : public NPCstructure{
public:   
    Geram();
   ~Geram();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

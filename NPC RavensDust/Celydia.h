#include "NPCStructure.h"

#ifndef __CELYDIA_H
#define __CELYDIA_H

class Celydia : public NPCstructure{
public:   
    Celydia();
   ~Celydia();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

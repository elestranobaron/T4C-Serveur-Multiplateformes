#include "NPCStructure.h"

#ifndef __JAMAR_H
#define __JAMAR_H

class Jamar : public NPCstructure{
public:   
    Jamar();
   ~Jamar();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

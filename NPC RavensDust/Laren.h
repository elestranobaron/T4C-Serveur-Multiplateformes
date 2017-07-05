#include "NPCStructure.h"

#ifndef __LAREN_H
#define __LAREN_H

class Laren : public NPCstructure{
public:   
    Laren();
   ~Laren();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

#include "NPCStructure.h"

#ifndef __ARCHIBALD_H
#define __ARCHIBALD_H

class Archibald : public NPCstructure{
public:   
    Archibald();
   ~Archibald();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

#include "NPCStructure.h"

#ifndef __CORSAIRMAGERE_H
#define __CORSAIRMAGERE_H

class CorsairMagere : public NPCstructure{
public:   
    CorsairMagere();
   ~CorsairMagere();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

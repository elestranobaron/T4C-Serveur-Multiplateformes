#include "NPCStructure.h"

#ifndef __VARGUS_H
#define __VARGUS_H

class Vargus : public NPCstructure{
public:   
    Vargus();
   ~Vargus();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

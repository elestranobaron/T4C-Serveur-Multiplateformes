#include "NPCStructure.h"


#ifndef __TORGAS_H
#define __TORGAS_H


class Torgas : public NPCstructure{
public:   
    Torgas();
   ~Torgas();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
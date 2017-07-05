#include "NPCStructure.h"

#ifndef __THEA_H
#define __THEA_H

class Thea : public NPCstructure{
public:   
    Thea();
   ~Thea();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );    
};

#endif

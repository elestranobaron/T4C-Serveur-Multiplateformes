#include "NPCStructure.h"

#ifndef __MENARK_H
#define __MENARK_H

class Menark : public NPCstructure{
public:   
    Menark();
   ~Menark();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

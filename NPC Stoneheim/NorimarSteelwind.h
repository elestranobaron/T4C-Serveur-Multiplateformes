#include "NPCStructure.h"

#ifndef __NORIMARSTEELWIND_H
#define __NORIMARSTEELWIND_H

class NorimarSteelwind : public NPCstructure{
public:   
    NorimarSteelwind();
   ~NorimarSteelwind();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

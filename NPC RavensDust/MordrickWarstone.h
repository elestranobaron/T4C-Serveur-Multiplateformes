#include "NPCStructure.h"

#ifndef __MORDRICKWARSTONE_H
#define __MORDRICKWARSTONE_H

class MordrickWarstone : public NPCstructure{
public:   
    MordrickWarstone();
   ~MordrickWarstone();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

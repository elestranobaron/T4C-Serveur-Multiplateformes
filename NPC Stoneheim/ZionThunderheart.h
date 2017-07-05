#include "NPCStructure.h"

#ifndef __ZIONTHUNDERHEART_H
#define __ZIONTHUNDERHEART_H

class ZionThunderheart : public NPCstructure{
public:   
    ZionThunderheart();
   ~ZionThunderheart();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

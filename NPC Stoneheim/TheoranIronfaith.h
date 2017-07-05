#include "NPCStructure.h"

#ifndef __THEORANIRONFAITH_H
#define __THEORANIRONFAITH_H

class TheoranIronfaith : public NPCstructure{
public:   
    TheoranIronfaith();
   ~TheoranIronfaith();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

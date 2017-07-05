#include "NPCStructure.h"

#ifndef __CHIEFWUUTHGORAN_H
#define __CHIEFWUUTHGORAN_H

class ChiefWuuthgoran : public NPCstructure{
public:   
    ChiefWuuthgoran();
   ~ChiefWuuthgoran();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

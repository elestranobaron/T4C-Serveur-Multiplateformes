#include "NPCStructure.h"

#ifndef __HUNTERTRUGGWORGWLOTH_H
#define __HUNTERTRUGGWORGWLOTH_H

class HunterTruggWorgwloth : public NPCstructure{
public:   
    HunterTruggWorgwloth();
   ~HunterTruggWorgwloth();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );    
};

#endif

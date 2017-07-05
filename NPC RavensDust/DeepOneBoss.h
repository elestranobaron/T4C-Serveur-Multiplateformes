#include "NPCStructure.h"

#ifndef __DEEPONEBOSS_H
#define __DEEPONEBOSS_H

class DeepOneBoss : public NPCstructure{
public:   
    DeepOneBoss();
   ~DeepOneBoss();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

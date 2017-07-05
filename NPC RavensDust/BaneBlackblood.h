#include "NPCStructure.h"

#ifndef __BANEBLACKBLOOD_H
#define __BANEBLACKBLOOD_H

class BaneBlackblood : public NPCstructure{
public:   
    BaneBlackblood();
   ~BaneBlackblood();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
//    
};

#endif

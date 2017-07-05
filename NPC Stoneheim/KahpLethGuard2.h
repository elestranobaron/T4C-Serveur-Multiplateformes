#include "NPCStructure.h"

#ifndef __KAHPLETHGUARD2_H
#define __KAHPLETHGUARD2_H

class KahpLethGuard2 : public NPCstructure{
public:   
    KahpLethGuard2();
   ~KahpLethGuard2();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

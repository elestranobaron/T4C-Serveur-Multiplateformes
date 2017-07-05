#include "NPCStructure.h"

#ifndef __KAHPLETHGUARD1_H
#define __KAHPLETHGUARD1_H

class KahpLethGuard1 : public NPCstructure{
public:   
    KahpLethGuard1();
   ~KahpLethGuard1();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

#include "NPCStructure.h"

#ifndef __MOONTUGGUARD1_H
#define __MOONTUGGUARD1_H

class MoonTugGuard1 : public NPCstructure{
public:   
    MoonTugGuard1();
   ~MoonTugGuard1();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

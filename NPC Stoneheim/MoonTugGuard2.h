#include "NPCStructure.h"

#ifndef __MOONTUGGUARD2_H
#define __MOONTUGGUARD2_H

class MoonTugGuard2 : public NPCstructure{
public:   
    MoonTugGuard2();
   ~MoonTugGuard2();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

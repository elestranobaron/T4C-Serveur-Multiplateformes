#include "NPCStructure.h"

#ifndef __CAPTAINIRONLEG_H
#define __CAPTAINIRONLEG_H

class CaptainIronleg : public NPCstructure{
public:   
    CaptainIronleg();
   ~CaptainIronleg();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

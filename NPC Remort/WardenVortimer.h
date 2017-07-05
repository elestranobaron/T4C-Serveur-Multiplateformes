#include "NPCStructure.h"

#ifndef __WARDENVORTIMER_H
#define __WARDENVORTIMER_H

class WardenVortimer : public NPCstructure{
public:   
    WardenVortimer();
   ~WardenVortimer();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

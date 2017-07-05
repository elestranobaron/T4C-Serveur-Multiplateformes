#include "NPCStructure.h"

#ifndef __GLAENSHENMILANDIRA_H
#define __GLAENSHENMILANDIRA_H

class Glaenshenmilandira : public NPCstructure{
public:   
    Glaenshenmilandira();
   ~Glaenshenmilandira();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif

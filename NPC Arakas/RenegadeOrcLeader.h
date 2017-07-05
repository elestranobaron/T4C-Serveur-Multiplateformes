#include "NPCStructure.h"

#ifndef __RENEGADEORCLEADER_H
#define __RENEGADEORCLEADER_H

class RenegadeOrcLeader : public NPCstructure{
public:   
    RenegadeOrcLeader();
   ~RenegadeOrcLeader();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );   
   void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif

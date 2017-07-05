#include "NPCStructure.h"

#ifndef __MHORGWLOTH_H
#define __MHORGWLOTH_H

class Mhorgwloth : public NPCstructure{
public:   
    Mhorgwloth();
   ~Mhorgwloth();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnDeath( UNIT_FUNC_PROTOTYPE );
   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

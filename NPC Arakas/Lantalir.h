#include "NPCStructure.h"

#ifndef __LANTALIR_H
#define __LANTALIR_H

class Lantalir : public NPCstructure{
public:   
    Lantalir();
   ~Lantalir();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );   
   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

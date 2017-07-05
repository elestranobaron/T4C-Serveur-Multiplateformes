#include "NPCStructure.h"

#ifndef __YRIAN_H
#define __YRIAN_H

class Yrian: public NPCstructure{
public:   
    Yrian();
   ~Yrian();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE ); 
   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

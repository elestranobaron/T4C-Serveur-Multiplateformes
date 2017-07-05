#include "NPCStructure.h"

#ifndef __ELDRIG_H
#define __ELDRIG_H

class Eldrig : public NPCstructure{
public:   
   Eldrig();
   ~Eldrig();
   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif

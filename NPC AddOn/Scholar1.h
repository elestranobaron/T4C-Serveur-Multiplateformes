#include "NPCStructure.h"

#ifndef __SCHOLAR1_H
#define __SCHOLAR1_H

class Scholar1 : public NPCstructure{
public:   
	Scholar1();
   ~Scholar1();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
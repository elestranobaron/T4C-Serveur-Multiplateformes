#include "NPCStructure.h"

#ifndef __SCHOLAR4_H
#define __SCHOLAR4_H

class Scholar4 : public NPCstructure{
public:   
	Scholar4();
   ~Scholar4();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "NPCStructure.h"

#ifndef __SCHOLAR3_H
#define __SCHOLAR3_H

class Scholar3 : public NPCstructure{
public:   
	Scholar3();
   ~Scholar3();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
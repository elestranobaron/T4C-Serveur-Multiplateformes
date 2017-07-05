#include "NPCStructure.h"

#ifndef __TARNIAN_H
#define __TARNIAN_H

class Tarnian : public NPCstructure{
public:   
	Tarnian();
   ~Tarnian();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
#include "NPCStructure.h"

#ifndef __NAMELESSBARD_H
#define __NAMELESSBARD_H

class NamelessBard : public NPCstructure{
public:   
	NamelessBard();
   ~NamelessBard();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
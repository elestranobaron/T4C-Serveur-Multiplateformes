#include "NPCStructure.h"

#ifndef __WORLDWILDHORSE_H
#define __WORLDWILDHORSE_H

class WorldWildHorse : public NPCstructure{
public:   
   WorldWildHorse();
   ~WorldWildHorse();
   void Create( void );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif


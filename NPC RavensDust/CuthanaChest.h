#include "NPCStructure.h"

#ifndef __CUTHANACHEST_H
#define __CUTHANACHEST_H

class CuthanaChest : public NPCstructure{
public:   
   CuthanaChest();
   ~CuthanaChest();
   void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

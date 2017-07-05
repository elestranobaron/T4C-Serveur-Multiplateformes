#include "NPCStructure.h"

#ifndef __VARGUSCHEST_H
#define __VARGUSCHEST_H

class VargusChest : public NPCstructure{
public:   
   VargusChest();
   ~VargusChest();
   void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

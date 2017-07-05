#include "NPCStructure.h"

#ifndef __SAFE_H
#define __SAFE_H

class Safe : public NPCstructure{
public:   
   Safe();
   ~Safe();
   void Create( void );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

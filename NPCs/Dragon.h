#include "NPCStructure.h"

#ifndef __DRAGON_H
#define __DRAGON_H

class Dragon : public NPCstructure{
public:   
	Dragon();
   ~Dragon();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
   void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
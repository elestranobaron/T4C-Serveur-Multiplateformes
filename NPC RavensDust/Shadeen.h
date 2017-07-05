// Shadeen.h: interface for the Shadeen class.
//
//////////////////////////////////////////////////////////////////////

#include "NPCStructure.h"

#ifndef __SHADEEN_H
#define __SHADEEN_H

class Shadeen : public NPCstructure{
public:   
    Shadeen();
   ~Shadeen();
   void Create( void );
   void OnAttack( UNIT_FUNC_PROTOTYPE ); 
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnDeath( UNIT_FUNC_PROTOTYPE);
   void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif

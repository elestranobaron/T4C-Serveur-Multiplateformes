#include <NPCStructure.h>

#ifndef __RIBCAGE_H
#define __RIBCAGE_H

class Ribcage : public NPCstructure{
public:   
   Ribcage();
   ~Ribcage();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

#include <NPCStructure.h>

#ifndef __MADDOOREXIT_H
#define __MADDOOREXIT_H

class MadDoorExit : public NPCstructure{
public:   
   MadDoorExit();
   ~MadDoorExit();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
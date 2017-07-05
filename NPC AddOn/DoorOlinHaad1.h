#include <NPCStructure.h>

#ifndef __DOOROLINHAAD1_H
#define __DOOROLINHAAD1_H

class DoorOlinHaad1 : public NPCstructure{
public:   
   DoorOlinHaad1();
   ~DoorOlinHaad1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
#include <NPCStructure.h>

#ifndef __DOOREFNISIEN2_H
#define __DOOREFNISIEN2_H

class DoorEfnisien2 : public NPCstructure{
public:   
   DoorEfnisien2();
   ~DoorEfnisien2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
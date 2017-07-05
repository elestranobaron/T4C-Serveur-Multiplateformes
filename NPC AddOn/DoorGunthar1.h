#include <NPCStructure.h>

#ifndef __DOORGUNTHAR1_H
#define __DOORGUNTHAR1_H

class DoorGunthar1 : public NPCstructure{
public:   
   DoorGunthar1();
   ~DoorGunthar1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
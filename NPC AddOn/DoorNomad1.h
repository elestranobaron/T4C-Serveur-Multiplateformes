#include <NPCStructure.h>

#ifndef __DOORNOMAD1_H
#define __DOORNOMAD1_H

class DoorNomad1 : public NPCstructure{
public:   
   DoorNomad1();
   ~DoorNomad1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
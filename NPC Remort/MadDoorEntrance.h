#include <NPCStructure.h>

#ifndef __MADDOORENTRANCE_H
#define __MADDOORENTRANCE_H

class MadDoorEntrance : public NPCstructure{
public:   
   MadDoorEntrance();
   ~MadDoorEntrance();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
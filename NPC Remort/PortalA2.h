#include <NPCStructure.h>

#ifndef __PORTALA2_H
#define __PORTALA2_H

class PortalA2 : public NPCstructure{
public:   
   PortalA2();
   ~PortalA2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

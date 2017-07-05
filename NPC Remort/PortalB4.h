#include <NPCStructure.h>

#ifndef __PORTALB4_H
#define __PORTALB4_H

class PortalB4 : public NPCstructure{
public:   
   PortalB4();
   ~PortalB4();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

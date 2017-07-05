#include <NPCStructure.h>

#ifndef __PORTALJ3_H
#define __PORTALJ3_H

class PortalJ3 : public NPCstructure{
public:   
   PortalJ3();
   ~PortalJ3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

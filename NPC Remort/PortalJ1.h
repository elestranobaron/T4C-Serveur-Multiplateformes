#include <NPCStructure.h>

#ifndef __PORTALJ1_H
#define __PORTALJ1_H

class PortalJ1 : public NPCstructure{
public:   
   PortalJ1();
   ~PortalJ1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

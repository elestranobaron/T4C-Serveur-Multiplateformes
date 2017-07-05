#include <NPCStructure.h>

#ifndef __PORTALJ4_H
#define __PORTALJ4_H

class PortalJ4 : public NPCstructure{
public:   
   PortalJ4();
   ~PortalJ4();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

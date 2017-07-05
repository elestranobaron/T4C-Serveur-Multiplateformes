#include <NPCStructure.h>

#ifndef __PORTALH3_H
#define __PORTALH3_H

class PortalH3 : public NPCstructure{
public:   
   PortalH3();
   ~PortalH3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

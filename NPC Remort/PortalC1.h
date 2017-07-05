#include <NPCStructure.h>

#ifndef __PORTALC1_H
#define __PORTALC1_H

class PortalC1 : public NPCstructure{
public:   
   PortalC1();
   ~PortalC1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

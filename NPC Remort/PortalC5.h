#include <NPCStructure.h>

#ifndef __PORTALC5_H
#define __PORTALC5_H

class PortalC5 : public NPCstructure{
public:   
   PortalC5();
   ~PortalC5();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif

#include <NPCStructure.h>

#ifndef __PORTALN_H
#define __PORTALN_H

class PortalN : public NPCstructure{
public:   
	PortalN();
	~PortalN();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

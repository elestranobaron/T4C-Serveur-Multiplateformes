#include <NPCStructure.h>

#ifndef __PORTALS_H
#define __PORTALS_H

class PortalS : public NPCstructure{
public:   
	PortalS();
	~PortalS();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

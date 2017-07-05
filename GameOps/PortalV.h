#include <NPCStructure.h>

#ifndef __PORTALV_H
#define __PORTALV_H

class PortalV : public NPCstructure{
public:   
	PortalV();
	~PortalV();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

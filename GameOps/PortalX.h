#include <NPCStructure.h>

#ifndef __PORTALX_H
#define __PORTALX_H

class PortalX : public NPCstructure{
public:   
	PortalX();
	~PortalX();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

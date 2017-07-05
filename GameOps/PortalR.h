#include <NPCStructure.h>

#ifndef __PORTALR_H
#define __PORTALR_H

class PortalR : public NPCstructure{
public:   
	PortalR();
	~PortalR();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

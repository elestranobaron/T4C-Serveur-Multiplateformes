#include <NPCStructure.h>

#ifndef __PORTALW_H
#define __PORTALW_H

class PortalW : public NPCstructure{
public:   
	PortalW();
	~PortalW();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

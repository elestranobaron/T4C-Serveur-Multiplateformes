#include <NPCStructure.h>

#ifndef __PORTALZ_H
#define __PORTALZ_H

class PortalZ : public NPCstructure{
public:   
	PortalZ();
	~PortalZ();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

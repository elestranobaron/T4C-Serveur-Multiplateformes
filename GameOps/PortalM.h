#include <NPCStructure.h>

#ifndef __PORTALM_H
#define __PORTALM_H

class PortalM : public NPCstructure{
public:   
	PortalM();
	~PortalM();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

#include <NPCStructure.h>

#ifndef __PORTALP_H
#define __PORTALP_H

class PortalP : public NPCstructure{
public:   
	PortalP();
	~PortalP();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

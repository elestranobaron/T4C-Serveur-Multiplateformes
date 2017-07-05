#include <NPCStructure.h>

#ifndef __PORTALG_H
#define __PORTALG_H

class PortalG : public NPCstructure{
public:   
	PortalG();
	~PortalG();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

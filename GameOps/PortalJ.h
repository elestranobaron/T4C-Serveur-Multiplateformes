#include <NPCStructure.h>

#ifndef __PORTALJ_H
#define __PORTALJ_H

class PortalJ : public NPCstructure{
public:   
	PortalJ();
	~PortalJ();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

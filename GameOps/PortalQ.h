#include <NPCStructure.h>

#ifndef __PORTALQ_H
#define __PORTALQ_H

class PortalQ : public NPCstructure{
public:   
	PortalQ();
	~PortalQ();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

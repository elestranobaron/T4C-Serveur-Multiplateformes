#include <NPCStructure.h>

#ifndef __PORTALO_H
#define __PORTALO_H

class PortalO : public NPCstructure{
public:   
	PortalO();
	~PortalO();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

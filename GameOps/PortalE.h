#include <NPCStructure.h>

#ifndef __PORTALE_H
#define __PORTALE_H

class PortalE : public NPCstructure{
public:   
	PortalE();
	~PortalE();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

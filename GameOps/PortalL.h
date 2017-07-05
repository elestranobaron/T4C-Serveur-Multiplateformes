#include <NPCStructure.h>

#ifndef __PORTALL_H
#define __PORTALL_H

class PortalL : public NPCstructure{
public:   
	PortalL();
	~PortalL();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

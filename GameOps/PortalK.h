#include <NPCStructure.h>

#ifndef __PORTALK_H
#define __PORTALK_H

class PortalK : public NPCstructure{
public:   
	PortalK();
	~PortalK();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

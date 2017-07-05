#include <NPCStructure.h>

#ifndef __PORTALF_H
#define __PORTALF_H

class PortalF : public NPCstructure{
public:   
	PortalF();
	~PortalF();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

#include <NPCStructure.h>

#ifndef __PORTALU_H
#define __PORTALU_H

class PortalU : public NPCstructure{
public:   
	PortalU();
	~PortalU();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

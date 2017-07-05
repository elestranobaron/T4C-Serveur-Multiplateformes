#include <NPCStructure.h>

#ifndef __PORTALA_H
#define __PORTALA_H

class PortalA : public NPCstructure{
public:   
	PortalA();
	~PortalA();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

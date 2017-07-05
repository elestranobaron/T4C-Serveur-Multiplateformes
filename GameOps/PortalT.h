#include <NPCStructure.h>

#ifndef __PORTALT_H
#define __PORTALT_H

class PortalT : public NPCstructure{
public:   
	PortalT();
	~PortalT();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

#include <NPCStructure.h>

#ifndef __PORTALD_H
#define __PORTALD_H

class PortalD : public NPCstructure{
public:   
	PortalD();
	~PortalD();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

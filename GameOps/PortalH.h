#include <NPCStructure.h>

#ifndef __PORTALH_H
#define __PORTALH_H

class PortalH : public NPCstructure{
public:   
	PortalH();
	~PortalH();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

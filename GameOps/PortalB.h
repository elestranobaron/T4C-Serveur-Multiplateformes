#include <NPCStructure.h>

#ifndef __PORTALB_H
#define __PORTALB_H

class PortalB : public NPCstructure{
public:   
	PortalB();
	~PortalB();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

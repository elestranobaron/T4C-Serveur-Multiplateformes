#include <NPCStructure.h>

#ifndef __PORTALC_H
#define __PORTALC_H

class PortalC : public NPCstructure{
public:   
	PortalC();
	~PortalC();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

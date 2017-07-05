#include <NPCStructure.h>

#ifndef __PORTALI_H
#define __PORTALI_H

class PortalI : public NPCstructure{
public:   
	PortalI();
	~PortalI();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

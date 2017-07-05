#include <NPCStructure.h>

#ifndef __SILVERSKYPORTAL_H
#define __SILVERSKYPORTAL_H

class SilverSkyPortal : public NPCstructure{
public:   
	SilverSkyPortal();
	~SilverSkyPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

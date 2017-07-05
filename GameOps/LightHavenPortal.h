#include <NPCStructure.h>

#ifndef __LIGHTHAVENPORTAL_H
#define __LIGHTHAVENPORTAL_H

class LightHavenPortal : public NPCstructure{
public:   
	LightHavenPortal();
	~LightHavenPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

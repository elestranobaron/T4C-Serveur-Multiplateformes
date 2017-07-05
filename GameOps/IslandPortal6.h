#include <NPCStructure.h>

#ifndef __ISLANDPORTAL6_H
#define __ISLANDPORTAL6_H

class IslandPortal6 : public NPCstructure{
public:   
	IslandPortal6();
	~IslandPortal6();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

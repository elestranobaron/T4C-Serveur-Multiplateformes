#include <NPCStructure.h>

#ifndef __ISLANDPORTAL22_H
#define __ISLANDPORTAL22_H

class IslandPortal22 : public NPCstructure{
public:   
	IslandPortal22();
	~IslandPortal22();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

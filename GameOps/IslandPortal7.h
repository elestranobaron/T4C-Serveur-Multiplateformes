#include <NPCStructure.h>

#ifndef __ISLANDPORTAL7_H
#define __ISLANDPORTAL7_H

class IslandPortal7 : public NPCstructure{
public:   
	IslandPortal7();
	~IslandPortal7();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

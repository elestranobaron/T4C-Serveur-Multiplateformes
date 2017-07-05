#include <NPCStructure.h>

#ifndef __ISLANDPORTAL27_H
#define __ISLANDPORTAL27_H

class IslandPortal27 : public NPCstructure{
public:   
	IslandPortal27();
	~IslandPortal27();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

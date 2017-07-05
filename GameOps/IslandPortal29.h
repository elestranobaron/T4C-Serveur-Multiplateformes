#include <NPCStructure.h>

#ifndef __ISLANDPORTAL29_H
#define __ISLANDPORTAL29_H

class IslandPortal29 : public NPCstructure{
public:   
	IslandPortal29();
	~IslandPortal29();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

#include <NPCStructure.h>

#ifndef __ISLANDPORTAL18_H
#define __ISLANDPORTAL18_H

class IslandPortal18 : public NPCstructure{
public:   
	IslandPortal18();
	~IslandPortal18();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

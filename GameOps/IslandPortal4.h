#include <NPCStructure.h>

#ifndef __ISLANDPORTAL4_H
#define __ISLANDPORTAL4_H

class IslandPortal4 : public NPCstructure{
public:   
	IslandPortal4();
	~IslandPortal4();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

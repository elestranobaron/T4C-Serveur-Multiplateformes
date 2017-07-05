#include <NPCStructure.h>

#ifndef __ISLANDPORTAL19_H
#define __ISLANDPORTAL19_H

class IslandPortal19 : public NPCstructure{
public:   
	IslandPortal19();
	~IslandPortal19();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

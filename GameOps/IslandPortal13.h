#include <NPCStructure.h>

#ifndef __ISLANDPORTAL13_H
#define __ISLANDPORTAL13_H

class IslandPortal13 : public NPCstructure{
public:   
	IslandPortal13();
	~IslandPortal13();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

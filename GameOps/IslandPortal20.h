#include <NPCStructure.h>

#ifndef __ISLANDPORTAL20_H
#define __ISLANDPORTAL20_H

class IslandPortal20 : public NPCstructure{
public:   
	IslandPortal20();
	~IslandPortal20();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

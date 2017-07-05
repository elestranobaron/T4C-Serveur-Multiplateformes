#include <NPCStructure.h>

#ifndef __ISLANDPORTAL1_H
#define __ISLANDPORTAL1_H

class IslandPortal1 : public NPCstructure{
public:   
	IslandPortal1();
	~IslandPortal1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

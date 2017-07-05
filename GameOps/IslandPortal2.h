#include <NPCStructure.h>

#ifndef __ISLANDPORTAL2_H
#define __ISLANDPORTAL2_H

class IslandPortal2 : public NPCstructure{
public:   
	IslandPortal2();
	~IslandPortal2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

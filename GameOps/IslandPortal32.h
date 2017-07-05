#include <NPCStructure.h>

#ifndef __ISLANDPORTAL32_H
#define __ISLANDPORTAL32_H

class IslandPortal32 : public NPCstructure{
public:   
	IslandPortal32();
	~IslandPortal32();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

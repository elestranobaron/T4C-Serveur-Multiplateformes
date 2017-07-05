#include <NPCStructure.h>

#ifndef __ISLANDPORTAL8_H
#define __ISLANDPORTAL8_H

class IslandPortal8 : public NPCstructure{
public:   
	IslandPortal8();
	~IslandPortal8();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

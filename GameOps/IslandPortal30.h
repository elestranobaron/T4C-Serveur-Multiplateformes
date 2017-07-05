#include <NPCStructure.h>

#ifndef __ISLANDPORTAL30_H
#define __ISLANDPORTAL30_H

class IslandPortal30 : public NPCstructure{
public:   
	IslandPortal30();
	~IslandPortal30();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

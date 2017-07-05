#include <NPCStructure.h>

#ifndef __ISLANDPORTAL3_H
#define __ISLANDPORTAL3_H

class IslandPortal3 : public NPCstructure{
public:   
	IslandPortal3();
	~IslandPortal3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

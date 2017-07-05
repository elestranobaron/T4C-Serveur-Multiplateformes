#include <NPCStructure.h>

#ifndef __ISLANDPORTAL9_H
#define __ISLANDPORTAL9_H

class IslandPortal9 : public NPCstructure{
public:   
	IslandPortal9();
	~IslandPortal9();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

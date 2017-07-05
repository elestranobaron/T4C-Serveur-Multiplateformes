#include <NPCStructure.h>

#ifndef __ISLANDPORTAL17_H
#define __ISLANDPORTAL17_H

class IslandPortal17 : public NPCstructure{
public:   
	IslandPortal17();
	~IslandPortal17();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

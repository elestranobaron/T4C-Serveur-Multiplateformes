#include <NPCStructure.h>

#ifndef __ISLANDPORTAL34_H
#define __ISLANDPORTAL34_H

class IslandPortal34 : public NPCstructure{
public:   
	IslandPortal34();
	~IslandPortal34();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

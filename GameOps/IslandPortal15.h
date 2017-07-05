#include <NPCStructure.h>

#ifndef __ISLANDPORTAL15_H
#define __ISLANDPORTAL15_H

class IslandPortal15 : public NPCstructure{
public:   
	IslandPortal15();
	~IslandPortal15();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

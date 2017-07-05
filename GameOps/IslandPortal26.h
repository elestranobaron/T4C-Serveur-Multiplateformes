#include <NPCStructure.h>

#ifndef __ISLANDPORTAL26_H
#define __ISLANDPORTAL26_H

class IslandPortal26 : public NPCstructure{
public:   
	IslandPortal26();
	~IslandPortal26();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

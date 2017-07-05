#include <NPCStructure.h>

#ifndef __ISLANDPORTAL28_H
#define __ISLANDPORTAL28_H

class IslandPortal28 : public NPCstructure{
public:   
	IslandPortal28();
	~IslandPortal28();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

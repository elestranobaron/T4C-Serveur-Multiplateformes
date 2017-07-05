#include <NPCStructure.h>

#ifndef __ISLANDPORTAL10_H
#define __ISLANDPORTAL10_H

class IslandPortal10 : public NPCstructure{
public:   
	IslandPortal10();
	~IslandPortal10();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

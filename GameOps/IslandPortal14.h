#include <NPCStructure.h>

#ifndef __ISLANDPORTAL14_H
#define __ISLANDPORTAL14_H

class IslandPortal14 : public NPCstructure{
public:   
	IslandPortal14();
	~IslandPortal14();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

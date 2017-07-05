#include <NPCStructure.h>

#ifndef __ISLANDPORTAL21_H
#define __ISLANDPORTAL21_H

class IslandPortal21 : public NPCstructure{
public:   
	IslandPortal21();
	~IslandPortal21();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

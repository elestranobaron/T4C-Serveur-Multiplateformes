#include <NPCStructure.h>

#ifndef __ISLANDMADNESSPORTAL_H
#define __ISLANDMADNESSPORTAL_H

class IslandMadnessPortal : public NPCstructure{
public:   
	IslandMadnessPortal();
	~IslandMadnessPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

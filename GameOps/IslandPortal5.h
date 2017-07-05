#include <NPCStructure.h>

#ifndef __ISLANDPORTAL5_H
#define __ISLANDPORTAL5_H

class IslandPortal5 : public NPCstructure{
public:   
	IslandPortal5();
	~IslandPortal5();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

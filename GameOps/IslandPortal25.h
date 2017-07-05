#include <NPCStructure.h>

#ifndef __ISLANDPORTAL25_H
#define __ISLANDPORTAL25_H

class IslandPortal25 : public NPCstructure{
public:   
	IslandPortal25();
	~IslandPortal25();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

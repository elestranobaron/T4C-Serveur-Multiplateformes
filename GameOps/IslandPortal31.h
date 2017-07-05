#include <NPCStructure.h>

#ifndef __ISLANDPORTAL31_H
#define __ISLANDPORTAL31_H

class IslandPortal31 : public NPCstructure{
public:   
	IslandPortal31();
	~IslandPortal31();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

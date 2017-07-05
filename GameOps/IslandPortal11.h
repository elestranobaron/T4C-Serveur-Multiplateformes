#include <NPCStructure.h>

#ifndef __ISLANDPORTAL11_H
#define __ISLANDPORTAL11_H

class IslandPortal11 : public NPCstructure{
public:   
	IslandPortal11();
	~IslandPortal11();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

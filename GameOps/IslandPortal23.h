#include <NPCStructure.h>

#ifndef __ISLANDPORTAL23_H
#define __ISLANDPORTAL23_H

class IslandPortal23 : public NPCstructure{
public:   
	IslandPortal23();
	~IslandPortal23();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

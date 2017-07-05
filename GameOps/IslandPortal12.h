#include <NPCStructure.h>

#ifndef __ISLANDPORTAL12_H
#define __ISLANDPORTAL12_H

class IslandPortal12 : public NPCstructure{
public:   
	IslandPortal12();
	~IslandPortal12();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

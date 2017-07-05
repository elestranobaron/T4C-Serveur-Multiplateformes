#include <NPCStructure.h>

#ifndef __ISLANDPORTAL16_H
#define __ISLANDPORTAL16_H

class IslandPortal16 : public NPCstructure{
public:   
	IslandPortal16();
	~IslandPortal16();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
